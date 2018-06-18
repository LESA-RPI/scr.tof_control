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

#ifndef HEXFILES_HEXFILESTREAMREADER_H
#define HEXFILES_HEXFILESTREAMREADER_H

// STL includes
#include <istream>

// iris includes
#include "iris/Common.h"
#include "HexFileReader.h"

namespace iris {

namespace hexfiles {

/**
 * Implements a HEX file decoder which reads from a stream
 */
class SENSORAPI HexFileStreamReader: public HexFileReader {

protected:

    /**
     * Holds the underlying stream instance
     */
    std::istream* stream;

    /**
     * Opens the input
     *
     * @return <code>true</code> if successful, <code>false</code>
     *         otherwise
     */
    bool openFile(void);

    /**
     * Closes the input
     *
     * @return <code>true</code> if successful, <code>false</code>
     *         otherwise
     */
    bool closeFile(void);

    /**
     * Reads a line from the input
     *
     * @param buffer Buffer to receive the line
     * @param maxLen Maximum number of bytes to read
     *
     * @return <code>true</code> if successful, <code>false</code>
     *         otherwise
     */
    bool readNextLine(char* const buffer, const unsigned char maxLen);

    /**
     * Opens the input stream
     *
     * @return Stream instance (or <code>null</code> in case of failure)
     */
    virtual std::istream* openStream(void) = 0;

    /**
     * Closes the input stream
     *
     * @param stream Stream instance
     *
     * @return <code>true</code> if successful, <code>false</code>
     *         otherwise
     */
    virtual bool closeStream(std::istream* stream) = 0;

public:

    /**
     * Constructor
     *
     * @param userData User-defined additional parameter for callback
     * @param callback Callback for decoding process
     */
    HexFileStreamReader(void* userData, const HexFileCallback callback);

}; // class HexFileStreamReader

} // namespace hexfile

} // namespace

#endif // HEXFILES_HEXFILESTREAMREADER_H
