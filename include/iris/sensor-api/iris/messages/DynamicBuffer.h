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

#ifndef MESSAGES_DYNAMICBUFFER_H_
#define MESSAGES_DYNAMICBUFFER_H_

// STL includes
#include <ostream>

// iris includes
#include "iris/Common.h"

namespace iris {

namespace messages {

/**
 * Encapsulates a binary read/write buffer that can grow dynamically
 */
class SENSORAPI DynamicBuffer {

protected:

    /**
     * Pointer to buffer memory
     */
    char *buffer;

    /**
     * Flag indicating if buffer memory has been allocated internally or
     * externally
     */
    bool ownAllocation;

    /**
     * Current read/write position
     */
    unsigned short position;

    /**
     * Current size
     */
    unsigned short length;

    /**
     * Maximum size
     */
    unsigned short maxLength;

public:

    /**
     * Constructor
     *
     * @param maxLength Maximum length
     * @param buffer Optional pointer to external buffer memory
     */
    DynamicBuffer(unsigned short maxLength, char* buffer = NULL);

    /**
     * Destructor
     */
    virtual ~DynamicBuffer();

    /**
     * Returns the internal buffer pointer
     *
     * @return Buffer
     */
    char* getBuffer(void);

    /**
     * Returns the length limitation
     *
     * @return Maximum length
     */
    unsigned short getMaxLength(void);

    /**
     * Sets the absolute position of the read/write pointer
     *
     * @param newPosition Desired position
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool setPosition(unsigned short newPosition);

    /**
     * Moves the read/write pointer relative to its current position
     *
     * @param movement Relative movement
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool movePosition(signed short movement);

    /**
     * Returns the current read/write position
     *
     * @return Position
     */
    unsigned short getPosition(void);

    /**
     * Returns the current buffer length
     *
     * @return Length
     */
    unsigned short getLength(void);

    /**
     * Sets the buffer length
     *
     * @param newLength New length (must not exceed maximum length)
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool setLength(unsigned short newLength);

    /**
     * Clears the buffer
     */
    void clear(void);

    /**
     * Resets the read/write pointer to zero
     */
    void reset(void);

    /**
     * Writes a block of bytes at the current position
     *
     * @param data Data to be written
     * @param size Length of data in bytes
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeBlock(const void* data, const unsigned short size);

    /**
     * Writes an unsigned byte at the current position
     *
     * @param byte Byte to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeUByte(const unsigned char byte);

    /**
     * Writes a signed byte at the current position
     *
     * @param byte Byte to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeSByte(const signed char byte);

    /**
     * Writes an unsigned word (16 bits) at the current position
     *
     * @param word Word to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeUWord(const unsigned short word);

    /**
     * Writes a signed word (16 bits) at the current position
     *
     * @param word Word to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeSWord(const signed short word);

    /**
     * Writes an unsigned long (32 bits) at the current position
     *
     * @param lng Long to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeULong(const unsigned long lng);

    /**
     * Writes a signed long (32 bits) at the current position
     *
     * @param lng Long to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeSLong(const signed long lng);

    /**
     * Writes an unsigned long long (64 bits) at the current position
     *
     * @param lng64 Long long to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeULong64(const unsigned long long lng64);

    /**
     * Writes a signed long long (64 bits) at the current position
     *
     * @param lng64 Long long to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeSLong64(const signed long long lng64);

    /**
     * Writes a string at the current position
     *
     * @param string String to be written
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeString(const char* string);

    /**
     * Writes a string at the current position using a fixed size
     *
     * @param string String to be written
     * @param size Destination size in bytes
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool writeString(const char* string, const unsigned short size);

    /**
     * Reads a data block from the current position
     *
     * @param data Block buffer
     * @param size Number of bytes
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readBlock(void* data, const unsigned short size);

    /**
     * Reads an unsigned byte from the current position
     *
     * @param byte Byte buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readUByte(unsigned char &byte);

    /**
     * Reads a signed byte from the current position
     *
     * @param byte Byte buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readSByte(signed char &byte);

    /**
     * Reads an unsigned word (16 bits) from the current position
     *
     * @param word Word buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readUWord(unsigned short &word);

    /**
     * Reads a signed word (16 bits) from the current position
     *
     * @param word Word buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readSWord(signed short &word);

    /**
     * Reads an unsigned long (32 bits) from the current position
     *
     * @param lng Long buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readULong(unsigned long &lng);

    /**
     * Reads a signed long (32 bits) from the current position
     *
     * @param lng Long buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readSLong(signed long &lng);

    /**
     * Reads an unsigned long long (64 bits) from the current position
     *
     * @param lng64 Long long buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readULong64(unsigned long long &lng64);

    /**
     * Reads a signed long long (64 bits) from the current position
     *
     * @param lng64 Long long buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readSLong64(signed long long &lng64);

    /**
     * Reads a string from the current position
     *
     * @param string String buffer
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readString(char* string);

    /**
     * Reads a string from the current position using a fixed length
     *
     * @param string String buffer
     * @param size Number of bytes
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readString(char* string, const unsigned short size);

    /**
     * Prints a debug hex-dump of the buffer to an output stream
     *
     * @param ostream Output stream to receive the hex dump
     */
    virtual void printDebugInfo(std::ostream& ostream);

    /**
     * Prints a debug hex-dump of a part of the buffer to an output stream
     *
     * @param ostream Output stream to receive the hex dump
     * @param offset Starting offset
     * @param length Number of bytes
     */
    virtual void printDebugInfoPart(std::ostream& ostream,
            const unsigned short offset, const unsigned short length);

}; // class DynamicBuffer

/**
 * Prints debug information for a DynamicBuffer into an output stream
 *
 * @param ostream Output stream
 * @param message DynamicBuffer pointer
 *
 * @return The original ostream reference
 */
std::ostream& operator << (std::ostream& ostream, DynamicBuffer* message);

} // namespace messages

} // namespace iris

#endif // MESSAGES_DYNAMICBUFFER_H
