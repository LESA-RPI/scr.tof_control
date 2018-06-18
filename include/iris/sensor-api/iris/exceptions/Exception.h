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

#ifndef EXCEPTIONS_EXCEPTION_H
#define EXCEPTIONS_EXCEPTION_H

// STL includes
#include <exception>
#include <string>

// iris includes
#include "iris/Common.h"

namespace iris {

namespace exceptions {

/**
 * Base class for exceptions occuring within the sensor API
 */
class SENSORAPI Exception: public std::exception {

protected:

    /**
     * Contains the error code
     */
    const int code;

    /**
     * Contains the error message
     */
    const std::string message;

public:

    /**
     * Constructor.
     * Initializes a new Exception instance with the given values
     *
     * @param codeArg Error code
     * @param messageArg Error message
     */
    Exception(int codeArg, std::string messageArg) throw ();

    /**
     * Destructor
     */
    virtual ~Exception() throw ();

    /**
     * Returns the error code
     *
     * @return Error code
     */
    int getCode(void) const;

    /**
     * Returns the error message
     *
     * @return Error message
     */
    std::string getMessage(void) const;

}; // class Exception

} // namespace exceptions

} // namespace iris

#endif // EXCEPTIONS_EXCEPTION_H
