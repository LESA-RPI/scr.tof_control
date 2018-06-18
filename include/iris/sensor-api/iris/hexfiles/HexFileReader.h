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

#ifndef HEXFILES_HEXFILEREADER_H
#define HEXFILES_HEXFILEREADER_H

// iris includes
#include "iris/Common.h"

namespace iris {

namespace hexfiles {

/**
 * Implements a HEX file decoder for an arbitrary source
 */
class SENSORAPI HexFileReader {

public:

    /**
     * Typedef for hex file decoding callback
     *
     * @param userData User-defined callback parameter
     * @param address Start address of byte block
     * @param data Pointer to data
     * @param len Number of bytes
     */
    typedef void (*HexFileCallback)(void* userData,
            const unsigned long address, const unsigned char* const data,
            const unsigned char len);

    /**
     * Constructor
     *
     * @param userData User-defined callback parameter
     * @param callback Decoding callback function
     */
    HexFileReader(void* userData, const HexFileCallback callback);

    /**
     * Destructor
     */
    virtual ~HexFileReader();

    /**
     * Performs the decoding process; triggers the callback for any
     * decoded block of bytes
     *
     * @return <code>true</code> if successful, <code>false</code> if not
     */
    bool decodeFile(void);

    void setCallback(void* userData, const HexFileCallback callback);

protected:

    /**
     * Maximum data bytes per line
     */
    enum {
        MAX_DATA_BYTES = 32
    };

    /**
     * Hex file line type
     */
    typedef enum {

        /**
         * Data bytes
         */
        HexData,

        /**
         * End of file
         */
        HexEof,

        /**
         * Extended segment address
         */
        HexExtSegmAddr,

        /**
         * Start segment address
         */
        HexStartSegmAddr,

        /**
         * Linear address
         */
        HexExtLinAddr,

        /**
         * Linear start address
         */
        HexStartLinAddr

    } HEX_LINE_TYPE;

#pragma pack(1)

    /**
     * Represents a hex file line
     */
    typedef struct {

        /**
         * Line length (number of bytes)
         */
        unsigned char length;

        /**
         * Address (high byte)
         */
        unsigned char addressHi;

        /**
         * Address (low byte)
         */
        unsigned char addressLo;

        /**
         * Line type
         */
        unsigned char type;

        /**
         * Data bytes
         */
        unsigned char data[MAX_DATA_BYTES];

        /**
         * Checksum
         */
        unsigned char checksum;

    } HEX_FILE_LINE;

#pragma pack()

    /**
     * Opens the source file. This method is abstract and needs to be
     * implemented by derived classes
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    virtual bool openFile(void) = 0;

    /**
     * Closes the source file. This method is abstract and needs to be
     * implemented by derived classes
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    virtual bool closeFile(void) = 0;

    /**
     * Reads the next line from the source file. This method is abstract and
     * needs to be implemented by derived classes
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    virtual bool readNextLine(char* const buffer,
                              const unsigned char maxLen) = 0;

    /**
     * Translates the two digit hex values chars into the corresponding 8 bit values
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool encodeLineAsBinary(void);

    /**
     * Checks whether the current line has a valid checksum
     *
     * @return <code>true</code> if checksum is valid, <code>false</code>
     *         otherwise
     */
    bool isLineValid(void);

    /**
     * Executes the callback function bases on the current address and buffer
     */
    void fireCallback(void);

    /**
     * Current decoding address
     */
    unsigned long baseAddress;

    /**
     * User callback function pointer
     */
    HexFileCallback callback;

    /**
     * User-defined data for callback
     */
    void *callbackUserData;

    /**
     * Buffer for current line in decoded form
     */
    HEX_FILE_LINE currentLine;

    /**
     * Buffer for current line in raw form
     */
    char* lineBuffer;

    /**
     * Maximum length of input line (including colon, CR and LF)
     */
    unsigned int maxLen;

    /**
     * Current line number
     */
    unsigned int lineNo;

    /**
     * Array of hex chars (for decoding)
     */
    static const char* const HEX_CHARS;

}; // class HexFileReader

} // namespace hexfiles

} // namespace iris

#endif // HEXFILES_HEXFILEREADER_H
