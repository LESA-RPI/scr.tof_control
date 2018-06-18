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

#ifndef COMMON_H
#define COMMON_H

#if defined(SENSORAPI_DLL) && (defined(__WIN32) || defined(_WIN32))
    #if defined(APIBUILD) && !defined(APIFORCEIMPORT)
        #define SENSORAPI __declspec(dllexport)
    #else
        #define SENSORAPI __declspec(dllimport)
    #endif
#else
    #define SENSORAPI
#endif

#if defined(SENSORAPI_DLL) && (defined(__WIN32) || defined(_WIN32))
    #if defined(APIQTBUILD) && !defined(APIQTFORCEIMPORT)
        #define SENSORAPIQT __declspec(dllexport)
    #else
        #define SENSORAPIQT __declspec(dllimport)
    #endif
#else
    #define SENSORAPIQT
#endif

#if defined(APIBUILD)
    #include "UipMessage.h"
    #include "iris/private/IrisOnly.h"
#endif

#if defined(_MSC_VER)
    #pragma warning (disable: 4251 4275)
    #if !defined(APIBUILD)
        #ifndef MSVCLIBPRAGMA
            #define MSVCLIBPRAGMA
            #ifdef DEBUG
                #ifdef SENSORAPI_DLL
                    #pragma comment (lib, "IrmaMatrixDebug1.lib")
                #else
                    #pragma comment (lib, "IrmaMatrixDebug.lib")
                #endif
            #else
                #ifdef SENSORAPI_DLL
                    #pragma comment (lib, "IrmaMatrix1.lib")
                #else
                    #pragma comment (lib, "IrmaMatrix.lib")
                #endif
            #endif
            #ifdef UNDER_CE
                #pragma comment (lib, "iphlpapi.lib") // Windows CE IP helper API
                #pragma comment (lib, "ws2.lib") // Windows CE Windows Sockets 2.2
            #endif
        #endif
    #endif
    #ifndef UNDER_CE
        #pragma comment (lib, "wintrust.lib")
        #pragma comment (lib, "imagehlp.lib")
        #pragma comment (lib, "crypt32.lib")
        #pragma comment (lib, "netapi32.lib")
    #endif
#endif

#if defined(ENABLE_HEAPMANAGER_CALLBACK)
    #include "iris/utilities/HeapHelper.h"
#endif

#ifndef SENSORAPI_NO_NS_ABBR
#include "Namespaces.h"
namespace ic = iris::configuration;
namespace id5 = iris::dist500;
namespace id = iris::drivers;
namespace idc = iris::drivers::can;
namespace idi = iris::drivers::icef;
namespace ids = iris::drivers::serial;
namespace idu = iris::drivers::udp;
namespace ie = iris::exceptions;
namespace ih = iris::hexfiles;
namespace im = iris::metrology;
namespace ime = iris::messages;
namespace is = iris::synchronization;
namespace ish = iris::sharedlibs;
namespace it = iris::threads;
namespace iu = iris::uff;
namespace iut = iris::utilities;
namespace iq = iris::qt;
#endif

// This macro is used to suppress unused-variable warnings
#ifndef IRIS_UNUSED
#define IRIS_UNUSED(x) ((void) x);
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1500)
    // Declare integer types not available in MS Visual C++ versions 2008 and older
    typedef __int8 int8_t;
    typedef unsigned char uint8_t;
    typedef __int16 int16_t;
    typedef unsigned short uint16_t;
    typedef __int32 int32_t;
    typedef unsigned int uint32_t;
#endif

#endif // COMMON_H
