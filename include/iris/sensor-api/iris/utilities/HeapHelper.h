// ***************************************************************************
// *    _      _       ____                                 _    ____ ___    *
// *   (_)_ __(_)___  / ___|  ___ _ __  ___  ___  _ __     / \  |  _ \_ _|   *
// *   | | '__| / __| \___ \ / _ \ '_ \/ __|/ _ \| '__|   / _ \ | |_) | |    *
// *   | | |  | \__ \  ___) |  __/ | | \__ \ (_) | |     / ___ \|  __/| |    *
// *   |_|_|  |_|___/ |____/ \___|_| |_|___/\___/|_|    /_/   \_\_|  |___|   *
// *                                                                         *
// *   Copyright (c) 2010 by iris-GmbH, Berlin         All rights reserved   *
// *                                                                         *
// ***************************************************************************

// ---------------------------------------------------------------------------
// Please refer to LICENSE.TXT for more information on copyright and licensing
// terms with respect to this library and its source codes.
// ---------------------------------------------------------------------------

#ifndef UTILITIES_HEAPHELPER_H
#define UTILITIES_HEAPHELPER_H

// STL includes
#include <new>
#include <set>
#include <vector>
#include <map>
#include <cstdlib>
#include <new>
#include <limits>

// iris includes
#include <iris/synchronization/Mutex.h>
#include <iris/synchronization/Lock.h>

#ifndef ENABLE_HEAPMANAGER_CALLBACK
#error This file must only be used when the define ENABLE_HEAPMANAGER_CALLBACK exists
#endif

namespace iris {

namespace utilities {

template <class T>
struct LocalAllocator {
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    template <class U> struct rebind { typedef LocalAllocator<U> other; };
    LocalAllocator() throw() {}
    LocalAllocator(const LocalAllocator&) throw() {}

    template <class U> LocalAllocator(const LocalAllocator<U>&) throw(){}

    ~LocalAllocator() throw() {}

    pointer address(reference x) const { return &x; }
    const_pointer address(const_reference x) const { return &x; }

    pointer allocate(size_type s, void const * = 0) {
        if (0 == s)
            return NULL;
        pointer temp = (pointer)malloc(s * sizeof(T));
        if (temp == NULL)
            throw std::bad_alloc();
        return temp;
    }

    void deallocate(pointer p, size_type) {
        free(p);
    }

    size_type max_size() const throw() {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    void construct(pointer p, const T& val) {
        new((void *)p) T(val);
    }

    void destroy(pointer p) {
        p->~T();
    }
};

class BaseHeapHelper {
public:
    virtual ~BaseHeapHelper();
    virtual void* singleNew(size_t size) throw (std::bad_alloc) = 0;
    virtual void singleDelete(void* p) throw () = 0;
    virtual void* arrayNew(size_t size) throw(std::bad_alloc) = 0;
    virtual void arrayDelete(void* p) throw() = 0;
    virtual void* singleNewNoThrow(size_t size, const std::nothrow_t&) throw() = 0;
    virtual void singleDeleteNoThrow(void* p, const std::nothrow_t&) throw() = 0;
    virtual void* arrayNewNoThrow(size_t size, const std::nothrow_t&) throw() = 0;
    virtual void arrayDeleteNoThrow(void* p, const std::nothrow_t&) throw() = 0;
};

class ExecutiveHeapHelper: public BaseHeapHelper {
public:
    virtual ~ExecutiveHeapHelper();
    virtual void* singleNew(size_t size) throw (std::bad_alloc);
    virtual void singleDelete(void* p) throw ();
    virtual void* arrayNew(size_t size) throw(std::bad_alloc);
    virtual void arrayDelete(void* p) throw();
    virtual void* singleNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void singleDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    virtual void* arrayNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void arrayDeleteNoThrow(void* p, const std::nothrow_t&) throw();
};

struct PointerComparator {
    bool operator() (const void* a, const void* b) const {
        return (long) a < (long) b;
    }
};

typedef struct {
    int fileIndex;
    int lineNo;
} CodeLocation;

typedef std::map<long, CodeLocation, std::less<long>, LocalAllocator<std::map<long, CodeLocation> > > CodeLocationMap;

/*typedef struct {
    FileList files;
    CodeLocationMap locations;
} CodeLocationInfo;*/

typedef struct _Allocation {
    void* caller;
    bool array;
    size_t size;
    _Allocation(): caller(0), array(false), size(0) { }
    _Allocation(void* caller, bool array, size_t size): caller(caller), array(array), size(size) { }
    _Allocation(const _Allocation& other): caller(other.caller), array(other.array), size(other.size) {
    }
    const _Allocation& operator = (const _Allocation &other) {
        caller = other.caller;
        array = other.array;
        size = other.size;
        return *this;
    }
    _Allocation& operator = (_Allocation &other) {
        caller = other.caller;
        array = other.array;
        size = other.size;
        return *this;
    }
} Allocation;

typedef std::map<void*, Allocation, PointerComparator, LocalAllocator<std::map<void*, Allocation>::allocator_type> > AllocationMap;

typedef std::vector<std::string, LocalAllocator<std::vector<std::string>::allocator_type> > FileList;

class SymbolResolver {
    mutable FileList fileList;
    mutable CodeLocationMap codeLocations;
public:
    SymbolResolver(const char* mapFile);
    SymbolResolver(const bool dll = false);
    std::string getFunctionName(const void* addr) const;
};

template <class T> class CheckingHeapHelper: public T {
    AllocationMap allocations;
    void signalDeleteError(const void* p, const bool unknown, const bool array);
    const SymbolResolver* resolver;
    bool logging;
    iris::synchronization::Mutex mutex;
    std::string caller(void);
public:
    CheckingHeapHelper();
    virtual void* singleNew(size_t size) throw (std::bad_alloc);
    virtual void singleDelete(void* p) throw ();
    virtual void* arrayNew(size_t size) throw(std::bad_alloc);
    virtual void arrayDelete(void* p) throw();
    virtual void* singleNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void singleDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    virtual void* arrayNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void arrayDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    void enableLog(const SymbolResolver* resolver = 0);
    void disableLog(void);
    AllocationMap getPointersInUse(const AllocationMap &base);
    AllocationMap getPointersInUse(void);
    void dumpPointersInUse(const AllocationMap& base, const SymbolResolver *resolver = 0);
    void dumpPointersInUse(const SymbolResolver *resolver = 0);
    void setResolver(const SymbolResolver *resolver);
};

template <class T> CheckingHeapHelper<T>::CheckingHeapHelper(): resolver(0), logging(false) {
}

template <class T> std::string CheckingHeapHelper<T>::caller(void) {
    if (resolver) {
        return resolver->getFunctionName(__builtin_return_address(3));

    }
    return "???";
}

template <class T> void* CheckingHeapHelper<T>::singleNew(size_t size) throw (std::bad_alloc) {
    iris::synchronization::Lock lock(mutex);
    void* p = T::singleNew(size);
    allocations[p] = Allocation(__builtin_return_address(2), false, size);
    if (logging) {
        std::cout << caller()<< " new (" << size << ")" << " -> " << p << std::endl;
    }
    return p;
}

template <class T> void CheckingHeapHelper<T>::singleDelete(void* p) throw () {
    iris::synchronization::Lock lock(mutex);
    if (logging) {
        std::cout << caller()<< " delete (" << p << ")" << std::endl;
    }
    AllocationMap::const_iterator i = allocations.find(p);
    if (i == allocations.end()) {
        signalDeleteError(p, true, false);
    } else {
        if (i->second.array) {
            signalDeleteError(p, false, false);
        }
    }
    T::singleDelete(p);
    allocations.erase(p);
}

template <class T> void* CheckingHeapHelper<T>::arrayNew(size_t size) throw(std::bad_alloc) {
    iris::synchronization::Lock lock(mutex);
    void* p = T::arrayNew(size);
    allocations[p] = Allocation(__builtin_return_address(2), true, size);
    if (logging) {
        std::cout << caller()<< " new[] (" << size << ")" << " -> " << p << std::endl;
    }
    return p;
}

template <class T> void CheckingHeapHelper<T>::arrayDelete(void* p) throw() {
    iris::synchronization::Lock lock(mutex);
    if (logging) {
        std::cout << caller()<< " delete[] (" << p << ")" << std::endl;
    }
    AllocationMap::const_iterator i = allocations.find(p);
    if (i == allocations.end()) {
        signalDeleteError(p, true, true);
    } else {
        if (!i->second.array) {
            signalDeleteError(p, false, true);
        }
    }
    T::arrayDelete(p);
    allocations.erase(p);
}

template <class T> void* CheckingHeapHelper<T>::singleNewNoThrow(size_t size, const std::nothrow_t& t) throw() {
    iris::synchronization::Lock lock(mutex);
    void* p = T::singleNewNoThrow(size, t);
    allocations[p] = Allocation(__builtin_return_address(2), false, size);
    if (logging) {
        std::cout << caller()<< " nt_new (" << size << ")" << " -> " << p << std::endl;
    }
    return p;
}

template <class T> void CheckingHeapHelper<T>::singleDeleteNoThrow(void* p, const std::nothrow_t& t) throw() {
    iris::synchronization::Lock lock(mutex);
    if (logging) {
        std::cout << caller()<< " nt_delete (" << p << ")" << std::endl;
    }
    AllocationMap::const_iterator i = allocations.find(p);
    if (i == allocations.end()) {
        signalDeleteError(p, true, false);
    } else {
        if (i->second.array) {
            signalDeleteError(p, false, false);
        }
    }
    T::singleDeleteNoThrow(p, t);
    allocations.erase(p);
}

template <class T> void* CheckingHeapHelper<T>::arrayNewNoThrow(size_t size, const std::nothrow_t& t) throw() {
    iris::synchronization::Lock lock(mutex);
    void* p = T::arrayNewNoThrow(size, t);
    allocations[p] = Allocation(__builtin_return_address(2), true, size);
    if (logging) {
        std::cout << caller()<< " nt_new[] (" << size << ")" << " -> " << p << std::endl;
    }
    return p;
}

template <class T> void CheckingHeapHelper<T>::arrayDeleteNoThrow(void* p, const std::nothrow_t& t) throw() {
    iris::synchronization::Lock lock(mutex);
    if (logging) {
        std::cout << caller()<< " nt_delete[] (" << p << ")" << std::endl;
    }
    AllocationMap::const_iterator i = allocations.find(p);
    if (i == allocations.end()) {
        signalDeleteError(p, true, true);
    } else {
        if (!i->second.array) {
            signalDeleteError(p, false, true);
        }
    }
    T::arrayDeleteNoThrow(p, t);
    allocations.erase(p);
}

template <class T> void CheckingHeapHelper<T>::enableLog(const SymbolResolver* resolver) {
    iris::synchronization::Lock lock(mutex);
    if (resolver) {
        this->resolver = resolver;
    }
    logging = true;
}

template <class T> void CheckingHeapHelper<T>::disableLog(void) {
    iris::synchronization::Lock lock(mutex);
    logging = false;
    //this->resolver = 0;
}

template <class T> void CheckingHeapHelper<T>::signalDeleteError(const void* p, const bool unknown, const bool array) {
    iris::synchronization::Lock lock(mutex);
    std::cout << "pointer " << p << " to be deleted " << (unknown ? "unknown" : (array ? "allocated using new, not new[]" : "allocated using new[], not new")) << " !" << std::endl;
    if (resolver) {
        std::cout << "  caller is " << resolver->getFunctionName(__builtin_return_address(3)) << std::endl;
    }
}

template <class T> AllocationMap CheckingHeapHelper<T>::getPointersInUse(const AllocationMap& base) {
    mutex.acquire();
    AllocationMap now = allocations;
    mutex.release();
    AllocationMap inUse;
    for (AllocationMap::const_iterator p = now.begin(); p != now.end(); ++p) {
        void* addr = p->first;
        if (base.find(addr) == base.end()) {
            inUse[addr] = p->second;
        }
    }
    return inUse;
}

template <class T> AllocationMap CheckingHeapHelper<T>::getPointersInUse(void) {
    iris::synchronization::Lock lock(mutex);
    AllocationMap now = allocations;
    return now;
}

template <class T> void CheckingHeapHelper<T>::dumpPointersInUse(const SymbolResolver* resolver) {
    AllocationMap inUse = getPointersInUse();
    if (!resolver) {
        iris::synchronization::Lock lock(mutex);
        resolver = this->resolver;
    }
    for (AllocationMap::const_iterator p = inUse.begin(); p != inUse.end(); ++p) {
        void* addr = p->first;
        Allocation a = p->second;
        void* caller = a.caller;
        size_t size = a.size;
        iris::synchronization::Lock lock(mutex);
        if (resolver) {
            std::cout << (a.array ? "[] " : "") << size << " @ " << addr << " allocated by " << resolver->getFunctionName(caller) << std::endl;
        } else {
            std::cout << (a.array ? "[] " : "") << size << " @ " << addr << " allocated by " << caller << std::endl;
        }
    }
    if (inUse.empty()) {
        iris::synchronization::Lock lock(mutex);
        std::cout << "no allocations (known to CheckingHeapHelper) at all" << std::endl;
    }
}

template <class T> void CheckingHeapHelper<T>::dumpPointersInUse(const AllocationMap& base, const SymbolResolver* resolver) {
    AllocationMap inUse = getPointersInUse(base);
    if (!resolver) {
        iris::synchronization::Lock lock(mutex);
        resolver = this->resolver;
    }
    bool any = false;
    for (AllocationMap::const_iterator p = inUse.begin(); p != inUse.end(); ++p) {
        void* addr = p->first;
        if (base.find(addr) == base.end()) {
            any = true;
            Allocation a = p->second;
            void* caller = a.caller;
            size_t size = a.size;
            iris::synchronization::Lock lock(mutex);
            if (resolver) {
                std::cout << (a.array ? "[] " : "") << size << " @ " << addr << " allocated by " << resolver->getFunctionName(caller) << std::endl;
            } else {
                std::cout << (a.array ? "[] " : "") << size << " @ " << addr << " allocated by " << caller << std::endl;
            }
        }
    }
    if (!any) {
        iris::synchronization::Lock lock(mutex);
        std::cout << "no allocations " << (base.empty() ? "(known to CheckingHeapHelper) at all" : "compared to the base set") << std::endl;
    }
}

template <class T> void CheckingHeapHelper<T>::setResolver(const SymbolResolver *resolver) {
    iris::synchronization::Lock lock(mutex);
    this->resolver = resolver;
}

#if defined(APIBUILD) && !defined(APIFORCEIMPORT)

class FallbackHeapHelper: public ExecutiveHeapHelper {
    static std::nothrow_t _nothrow;
public:
    virtual void* singleNew(size_t size) throw (std::bad_alloc);
    virtual void singleDelete(void* p) throw ();
    virtual void* arrayNew(size_t size) throw(std::bad_alloc);
    virtual void arrayDelete(void* p) throw();
    virtual void* singleNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void singleDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    virtual void* arrayNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void arrayDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    void* _singleNewNoThrow(size_t size, const std::nothrow_t&) throw();
    void _singleDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    void* _arrayNewNoThrow(size_t size, const std::nothrow_t&) throw();
    void _arrayDeleteNoThrow(void* p, const std::nothrow_t&) throw();
};

class ProxyHeapHelper: public BaseHeapHelper {
    FallbackHeapHelper fallbackHeapHelper;
    BaseHeapHelper* actualHeapHelper;
public:
    ProxyHeapHelper();
    virtual void* singleNew(size_t size) throw (std::bad_alloc);
    virtual void singleDelete(void* p) throw ();
    virtual void* arrayNew(size_t size) throw(std::bad_alloc);
    virtual void arrayDelete(void* p) throw();
    virtual void* singleNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void singleDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    virtual void* arrayNewNoThrow(size_t size, const std::nothrow_t&) throw();
    virtual void arrayDeleteNoThrow(void* p, const std::nothrow_t&) throw();
    void attachExecutiveHeapHelper(ExecutiveHeapHelper& executive);
    void detachExecutiveHeapHelper(ExecutiveHeapHelper& executive);
    void detachExecutiveHeapHelper(void);
};

typedef CheckingHeapHelper<FallbackHeapHelper> CheckingFallbackHeapHelper;
typedef CheckingHeapHelper<ProxyHeapHelper> CheckingProxyHeapHelper;
typedef CheckingHeapHelper<ExecutiveHeapHelper> CheckingExecutiveHeapHelper;

#endif

void SENSORAPI enableExecutiveHeapHelper(ExecutiveHeapHelper& executive);
void SENSORAPI disableExecutiveHeapHelper(void);

} // namespace utilities

} // namespace iris

#endif // UTILITIES_HEAPHELPER_H
