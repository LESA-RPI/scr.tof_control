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

#ifndef DRIVERS_UDP_NETWORKINFO_H
#define DRIVERS_UDP_NETWORKINFO_H

// workaround for win32: needs to be first include
#if defined(__WIN32) || defined(_WIN32)
    #include <winsock2.h>
#endif

// STL includes
#include <list>

// iris includes
#include "iris/Common.h"

// OS dependent includes
#if defined(__WIN32) || defined(_WIN32)
    //#include <winsock2.h>
    #define __in_ecount(x)
    #define __in
    #include <iphlpapi.h>
#else
    #include <ifaddrs.h>
    #include <netinet/in.h>
    #include <sys/types.h>
    typedef unsigned long u_long;
#endif

namespace iris {

namespace drivers {

namespace udp {

/**
 * Provides information about the local IPv4 network
 */
class SENSORAPI NetworkInfo {

public:

    /**
     * Encapsulates a local IPv4 address binding
     */
    class Binding {

    protected:

        /**
         * Holds the local address
         */
        u_long localAddress;

        /**
         * Holds the network mask
         */
        u_long networkMask;

        /**
         * Holds the broadcast address
         */
        u_long broadcastAddress;

    public:

        /**
         * Returns the local address
         *
         * @return Local address
         */
        u_long getLocalAddress(void) const;

        /**
         * Returns the network mask
         *
         * @return Network mask
         */
        u_long getNetworkMask(void) const;

        /**
         * Returns the broadcast address
         *
         * @return Broadcast address
         */
        u_long getBroadcastAddress(void) const;

        /**
         * Constructor
         *
         * @param localAddress Local address
         * @param networkMask Network mask
         * @param broadcastAddress Broadcast address
         */
        Binding(const u_long localAddress, const u_long networkMask, const u_long broadcastAddress);

    };

    /**
     * Typedef for list of local bindings
     */
    typedef std::list<Binding> BindingList;

    /**
     * Returns a list of local bindings
     *
     * @return BindingList containing the local bindings
     */
    static BindingList getBindings(void);

}; // class NetworkInfo

} // namespace udp

} // namespace drivers

} // namespace iris

#endif // DRIVERS_UDP_NETWORKINFO_H
