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

#ifndef MESSAGES_MESSAGE_H
#define MESSAGES_MESSAGE_H

// STL includes
#include <ostream>

// iris includes
#include "iris/Common.h"
#include "DynamicBuffer.h"

namespace iris {

namespace messages {

/**
 * Base type for messages providing basic functionality which can be extended by
 * protocol-specific child classes
 */
class SENSORAPI Message: public DynamicBuffer {

protected:

    /**
     * Optional pointer to linked message (<code>null</code> if none)
     */
    Message *nextMessage;

public:

    /**
     * Maximum message length constant
     */
    static const short int MAX_MESSAGE_SIZE = 1500;

    /**
     * Constructor
     *
     * @param size Maximum length
     */
    Message(short size = MAX_MESSAGE_SIZE);

    /**
     * Destructor
     */
    virtual ~Message();

    /**
     * Returns a hash value for the message type
     *
     * @return Hash value
     *
     * @note Needs to be overwritten by derived classes
     */
    virtual int getTypeHash(void);

    /**
     * Returns the message class name
     *
     * @return Message class name
     *
     * @note Needs to be overwritten by derived classes
     */
    virtual const char* getMessageClassName(void);

    /**
     * Links a given message to the existing one
     *
     * @param other Message to be linked
     */
    void linkTo(Message *other);

    /**
     * Returns the linked message, if any
     *
     * @return Message pointer if existant, <code>null</code> otherwise
     */
    Message* getNextMessage(void);

    /**
     * Checkes whether a linked message exists
     *
     * @return <code>true</code> if existant, <code>false</code> otherwise
     */
    bool hasNextMessage(void);

    /**
     * Returns the message variant
     *
     * @return Variant
     *
     * @note Needs to be overwritten by derived classes
     */
    virtual int getVariant(void);

}; // class Message

/**
 * Prints debug information for a Message into an output stream
 *
 * @param ostream Output stream
 * @param message Message pointer
 *
 * @return The original ostream reference
 */
std::ostream& operator <<(std::ostream& ostream, Message *message);

} // namespace messages

} // namespace iris

#endif // MESSAGES_MESSAGE_H
