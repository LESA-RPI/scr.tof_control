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

#ifndef SHAREDLIBS_SHAREDLIB_H
#define SHAREDLIBS_SHAREDLIB_H

// STL includes
#include <string>

// iris includes
#include "iris/Common.h"

// OS dependent includes
#if defined(__WIN32) || defined(_WIN32)
#include <windows.h>
#endif

namespace iris {

namespace sharedlibs {

class SharedLibManager;

/**
 * Acts as a wrapper for a dynamic library (ie DLL / dynlib) on the OS level
 */
class SENSORAPI SharedLib {

public:

    /**
     * Determines the address of a function (or symbol) within a dynamic library
     *
     * @param symbolName Name of the symbol
     * @param throwException Controls whether an exception is thrown if the
     *        symbol does not exist (<code>true</code>) or if <code>NULL</code>
     *        if returned in such case (<code>false</code>)
     *
     * @return Symbol address if found, <code>NULL</code> otherwise
     */
    void* getSymbolAddr(const std::string& symbolName,
            const bool throwException = false) const;

    /**
     * Checks whether the given function or symbol is present in the library
     *
     * @param symbolName Name of the symbol
     *
     * @return <code>true</code> if present, <code>fasle</code> otherwise
     */
    bool hasSymbol(const std::string& symbolName) const;

    /**
     * Checks the given SharedLib instance for equality.
     * Two libs are equal by definition if they have the same handle
     */
    bool operator ==(const SharedLib& other);

    /**
     * Checks the given SharedLib instance for unequality.
     * Two libs are unequal by definition if they have different handles
     */
    bool operator !=(const SharedLib& other);

protected:

    /**
     * Internal handle type for dynlibs (OS specific)
     */
#if defined(__WIN32) || defined(_WIN32)
    typedef HMODULE HandleType;
#else
    typedef void* HandleType;
#endif

    /**
     * Constructor (non-public; only to be used by SharedLibManager)
     */
    SharedLib(const HandleType handle, const std::string normLibName,
            const SharedLibManager& manager);

    /**
     * Destructor
     */
    virtual ~SharedLib();

    /**
     * Returns the internal handle
     *
     * @return Handle (type is OS specific)
     */
    HandleType getHandle(void) const;

    /**
     * Returns the normalized library name
     *
     * @return Normalized name
     */
    std::string getNormLibName(void) const;

    /**
     * Returns the associated SharedLibManager
     *
     * @return SharedLibManager instance
     */
    const SharedLibManager& getLibManager(void) const;

    /**
     * Holds the internal handle (type is OS specific)
     */
    const HandleType handle;

    /**
     * Contains the normalized library name
     */
    const std::string normLibName;

    /**
     * References the associated SharedLibManager
     */
    const SharedLibManager& manager;

    friend class SharedLibManager;

}; // class SharedLib

} // namespace sharedlibs

} // namespace iris

#endif // SHAREDLIBS_SHAREDLIB_H
