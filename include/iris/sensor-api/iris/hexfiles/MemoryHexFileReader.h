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

// iris includes
#include "HexFileStreamReader.h"

namespace iris {

namespace hexfiles {

class MemoryHexFileReader: public HexFileStreamReader {
protected:
    char* contents;
    unsigned int size;
public:
    MemoryHexFileReader(char* contents, unsigned int size, void* userData, const HexFileCallback callback);
    virtual std::istream* openStream(void);
    virtual bool closeStream(std::istream* stream);
}; // class MemoryHexFileReader

} // namespace hexfiles

} // namespace iris
