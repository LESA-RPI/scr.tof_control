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

#ifndef SHAREDLIBS_SHAREDLIBMANAGER_H
#define SHAREDLIBS_SHAREDLIBMANAGER_H

// STL includes
#include <map>
#include <vector>

// iris includes
#include "iris/Common.h"
#include "SharedLib.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace sharedlibs {

/**
 * Manages dynamic libraries (ie DLLs / dynlibs)
 */
class SENSORAPI SharedLibManager {

public:

    /**
     * Holds a list of SharedLib instances representing the libs currently
     * loaded by the SharedLibManager
     */
    typedef std::vector<SharedLib*> LibList;

    /**
     * Loads a given library and creates a wrapper object for it.
     * If the same library has been loaded before, the previously created
     * wrapper instance is returned, not a new one.
     *
     * @param libName File name of library to be loaded
     * @param alreadyLoaded Return flag indicating if the given lib has been
     *        loaded before
     *
     * @return SharedLib instance representing the library
     *
     * @throw Exception if the O/S signals an error while loading the library
     */
    SharedLib& loadLibrary(const std::string& libName, bool& alreadyLoaded);

    /**
     * Loads a given library and creates a wrapper object for it.
     * If the same library has been loaded before, the previously created
     * wrapper instance is returned, not a new one.
     *
     * @param libName File name of library to be loaded
     *
     * @return SharedLib instance representing the library
     *
     * @throw Exception if the O/S signals an error while loading the library
     */
    SharedLib& loadLibrary(const std::string& libName);

    /**
     * Unloads the given library and frees its resources.
     * The SharedLib instance itself is also freed
     *
     * @param library Library to be unloaded
     *
     * @note References to the driver are invalid after that operation
     */
    void unloadLibrary(SharedLib& library);

    /**
     * Checks whether the given library is valid.
     * A library is valid if it is present in the list of active libs
     *
     * @param library Library wrapper to be checked
     *
     * @return <code>true</code> is valid, <code>false</code> otherwise
     */
    bool isValid(const SharedLib& library) const;

    /**
     * Returns the global SharedLibManager instance
     *
     * @return Reference to static instance
     *
     * @note Singleton pattern
     */
    static SharedLibManager& getInstance(void);

    /**
     * Returns a list of the currently loaded libraries
     *
     * @return List of SharedLib instances
     */
    LibList getLoadedLibraries(void);

protected:

    /**
     * Constructor.
     *
     * @note Non-public to enforce singleton
     */
    SharedLibManager();

    /**
     * Destructor.
     *
     * @note Non-public to enforce singleton
     */
    virtual ~SharedLibManager();

    /**
     * Maps library file names to SharedLib instances
     */
    typedef std::map<std::string, SharedLib*> LoadedLibs;

    /**
     * Maps library handles (OS specific) to SharedLib instanced
     */
    typedef std::map<const SharedLib::HandleType, SharedLib*> LibHandles;

    /**
     * Map of currently loaded libraries (by filename)
     */
    LoadedLibs loadedLibs;

    /**
     * Map of currently loaded libraries (by handle)
     */
    LibHandles libHandles;

    /**
     * Global SharedLibManger instance
     *
     * @note Singleton
     */
    static SharedLibManager instance;

    /**
     * Mutex to synchronize access to loadedLibs and libHandles members
     */
    iris::synchronization::Mutex mutex;

public:

    /**
     * Unloads all registered libraries
     */
    void unloadLibraries(void);

}; // class SharedLibManager

} // namespace sharedlibs

} // namespace iris

#endif // SHAREDLIBS_SHAREDLIBMANAGER_H
