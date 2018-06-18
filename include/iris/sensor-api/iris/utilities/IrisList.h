// ***************************************************************************
// *    _      _       ____                                 _    ____ ___    *
// *   (_)_ __(_)___  / ___|  ___ _ __  ___  ___  _ __     / \  |  _ \_ _|   *
// *   | | '__| / __| \___ \ / _ \ '_ \/ __|/ _ \| '__|   / _ \ | |_) | |    *
// *   | | |  | \__ \  ___) |  __/ | | \__ \ (_) | |     / ___ \|  __/| |    *
// *   |_|_|  |_|___/ |____/ \___|_| |_|___/\___/|_|    /_/   \_\_|  |___|   *
// *                                                                         *
// *   Copyright (c) 2012 by iris-GmbH, Berlin         All rights reserved   *
// *                                                                         *
// ***************************************************************************

// ---------------------------------------------------------------------------
// Please refer to LICENSE.TXT for more information on copyright and licensing
// terms with respect to this library and its source codes.
// ---------------------------------------------------------------------------

#ifndef UTILITIES_IRISLIST_H
#define UTILITIES_IRISLIST_H

// STL includes
#include <list>
#include <set>

namespace iris {

namespace utilities {

template <class T> class IrisList {
private:
    int _size;
    class IrisNode {
    public:
        T _data;
        IrisNode* _next;
        explicit IrisNode(const T& data);
    };
    IrisNode* _head;
    IrisNode* _tail;
    void append(const T& data);
    void clear(void);
public:
    typedef std::list<T> StdListType;
    typedef std::set<T> StdSetType;
    typedef IrisList<T> OwnType;
    IrisList<T>();
    IrisList<T>(const StdListType& stlList);
    IrisList<T>(const StdSetType& stlSet);
    IrisList<T>(const OwnType& source);
    OwnType& operator = (const StdListType& stlList);
    OwnType& operator = (const StdSetType& stlSet);
    OwnType& operator = (const OwnType& source);
    T& at(const int idx) const;
    T& operator [] (const int idx) const;
    int size(void) const;
    virtual ~IrisList<T>();
};

template <class T> IrisList<T>::IrisNode::IrisNode(const T &data): _data(data), _next(0) {
}

template <class T> void IrisList<T>::append(const T& data) {
    IrisNode* node = new IrisNode(data);
    if (!_tail) {
        _head = _tail = node;
    } else {
        _tail->_next = node;
        _tail = node;
    }
    node->_data = data;
    _size++;
}

template <class T> void IrisList<T>::clear(void) {
    IrisNode* node = _head;
    while (node) {
        IrisNode* next = node->_next;
        delete node;
        node = next;
    }
    _head = _tail = 0;
    _size = 0;
}

template <class T> IrisList<T>::IrisList(): _size(0), _head(0), _tail(0) {
}

template <class T> IrisList<T>::IrisList(const StdListType& stlList): _size(0), _head(0), _tail(0) {
    *this = stlList;
}

template <class T> IrisList<T>::IrisList(const StdSetType& stlSet): _size(0), _head(0), _tail(0) {
    *this = stlSet;
}

template <class T> IrisList<T>::IrisList(const OwnType& source): _size(0), _head(0), _tail(0) {
    *this = source;
}

template <class T> typename IrisList<T>::OwnType& IrisList<T>::operator = (const StdListType& stlList) {
    clear();
    for (typename StdListType::const_iterator it = stlList.begin(); it != stlList.end(); it++) {
        append(*it);
    }
    return *this;
}

template <class T> typename IrisList<T>::OwnType& IrisList<T>::operator = (const StdSetType& stlSet) {
    clear();
    for (typename StdSetType::const_iterator it = stlSet.begin(); it != stlSet.end(); it++) {
        append(*it);
    }
    return *this;
}

template <class T> typename IrisList<T>::OwnType& IrisList<T>::operator = (const OwnType& source) {
    clear();
    IrisNode* node = source._head;
    while (node) {
        append(node->_data);
        node = node->_next;
    }
    return *this;
}

template <class T> T& IrisList<T>::at(const int idx) const {
    IrisNode* node = _head;
    int i = 0;
    while (node) {
        if (i == idx) {
            break;
        }
        node = node->_next;
        i++;
    }
    return node->_data;
}

template <class T> T& IrisList<T>::operator [] (const int idx) const {
    return at(idx);
}

template <class T> int IrisList<T>::size(void) const {
    return _size;
}

template <class T> IrisList<T>::~IrisList() {
    clear();
}

}

}

#endif // UTILITIES_IRISLIST_H
