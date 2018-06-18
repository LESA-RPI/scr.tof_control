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

#ifndef NAMESPACES_H_
#define NAMESPACES_H_

// NOTE: THIS FILE MAINLY SERVES AS NAMESPACE DOCUMENTATION SOURCE FOR DOXYGEN

/**
 * "Base namespace" which hosts all sub-namespaces for the iris-defined classes
 * and types
 */
namespace iris {

/**
 * Namespace containg classes dealing with configuration data
 */
namespace configuration {
} // namespace configuration

/**
 * Namespace for DIST500 related stuff (eg communication, service tasks, signal
 * recording)
 */
namespace dist500 {
} // namespace dist500

/**
 * Namespace for drivers (eg specialized sensor classes) and related code.
 */
namespace drivers {
    /**
     * Controller Area Network (CAN) related.
     */
    namespace can { }
    /**
     * Proprietary (iris) MAC-based Ethernet protocol
     */
    namespace icef { }
    /**
     * Udp based Ethernet communication
     */
    namespace udp { }
    /**
     * Serial communication aka RS-232.
     */
    namespace serial { }
} // namespace drivers

/**
 * Namespace for exception classes within the sensor API framework
 */
namespace exceptions {
} // namespace exceptions

/**
 * Namespace which holds classes for processing Intel Hex files (.hex and .ldr)
 */
namespace hexfiles {
} // namespace hexfiles

/**
 * Namespace containing basic message handling classes
 */
namespace messages {
} // namespace messages

/**
 * Namespace containing classes used in metrology (eg statistical processing
 * tools)
 */
namespace metrology {
} // namespace metrology

#ifndef SKIP_DOXYGEN 
/**
 * Namespace for GUI-related classes (all of which are based on the Qt library)
 *
 * @see https://www.qt.io/
 */
namespace qt {
} // namespace qt
#endif 

/**
 * Namespace for classes dealing with shared libraries (ie DLLs / dynlibs)
 */
namespace sharedlibs {
} // namespace sharelibs

/**
 * Namespace for synchronization classes (semaphores, mutexes, etc)
 */
namespace synchronization {
} // namespace synchronization

/**
 * Namespace for thread-related classes
 */
namespace threads {
} // namespace threads

/**
 * Namespace for UFF (Universal File Format) related code. UFF is used for update container formats and signal recordings.
 */
namespace uff {
} // namespace uff

/**
 * Namespace defining UIP protocol classes (low- and high level messages)
 */
namespace uip {
} // namespace uip

/**
 * Namespace for helper classes
 */
namespace utilities {
} // namespace utilities

} // namespace iris

#endif /* NAMESPACES_H_ */
