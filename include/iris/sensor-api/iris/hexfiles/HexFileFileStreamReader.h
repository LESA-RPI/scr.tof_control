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

#ifndef HEXFILES_HEXFILEFILESTREAMREADER_H
#define HEXFILES_HEXFILEFILESTREAMREADER_H

// STL includes
#include <string>

// iris includes
#include "iris/Common.h"
#include "iris/hexfiles/HexFileStreamReader.h"

namespace iris {

namespace hexfiles {

/**
 * Implements a HEX file decoder which reads from a file
 */
class SENSORAPI HexFileFileStreamReader: public HexFileStreamReader {

protected:

    /**
     * Holds the HEX file name
     */
    std::string filename;

    /**
     * Opens the stream
     *
     * @return Stream instance
     */
    std::istream* openStream(void);

    /**
     * Closes the stream
     *
     * @param stream Stream instance to be closed
     */
    bool closeStream(std::istream* stream);

public:

    /**
     * Constructor
     *
     * @param filename Name of HEX file
     * @param userData User-defined additional callback parameter
     * @param callback Callback for decoding process
     */
    HexFileFileStreamReader(const std::string& filename, void* userData,
            HexFileCallback callback);
    
    /**
     * Destructor
     */
    ~HexFileFileStreamReader();

}; // class HexFileStreamReader

} // namespace hexfiles

} // namespace iris

#endif // HEXFILES_HEXFILEFILESTREAMREADER_H
