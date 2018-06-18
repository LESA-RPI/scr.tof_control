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

#ifndef API_UIPMESSAGE_H_
#define API_UIPMESSAGE_H_

// STL includes
#include <ostream>

// iris includes
#include "../messages/Message.h"

namespace iris {

namespace uip {

/// UIP address type
typedef unsigned char UIP_ADDRESS;

/// UIP message type type
typedef unsigned char UIP_TYPE;

/// UIP level type
typedef unsigned char UIP_LEVEL;

/// UIP version type
typedef unsigned char UIP_VERSION;

/// UIP payload len type
typedef unsigned short UIP_PAYLOAD_LEN;

/**
 * Represents a message in the UIP protocol
 */
class UipMessage: public iris::messages::Message {

private:

    /**
     * UIP message header definition
     */
    typedef struct {

        /// Receiver UIP address
        UIP_ADDRESS receiver;

        /// Sender UIP address
        UIP_ADDRESS sender;

        /// UIP message type
        UIP_TYPE type;

        /// UIP message version
        UIP_VERSION version;

        /// UIP payload length in bytes
        UIP_PAYLOAD_LEN payloadLen;

    } UIP_HEADER;

    /**
     * Message header
     */
    UIP_HEADER header;

    /**
     * UIP level information (0..2)
     */
    UIP_LEVEL level;

public:

    /**
     * Constructor
     *
     * @param receiver Receiver UIP address
     * @param sender Sender UIP address
     * @param type UIP emssage type
     * @param version UIP message version
     * @param payloadLen Payload length in bytes
     * @param payload Pointer to payload bytes
     */
    UipMessage(UIP_ADDRESS receiver, UIP_ADDRESS sender, UIP_TYPE type,
            UIP_VERSION version, UIP_PAYLOAD_LEN payloadLen = 0, char *payload =
                    NULL);

    /**
     * Destructor
     */
    virtual ~UipMessage();

    /**
     * Returns a hash value for the message type
     *
     * @return Hash value
     */
    int getTypeHash(void);

    /**
     * Computes a hash value for the message type and version
     *
     * @return Hash value
     */
    static int getTypeHash(UIP_TYPE type, UIP_VERSION version);

    /**
     * Returns the receiver
     *
     * @return Receiver UIP address
     */
    UIP_ADDRESS getReceiver(void);

    /**
     * Returns the sender
     *
     * @return Sender UIP address
     */
    UIP_ADDRESS getSender(void);

    /**
     * Returns message type
     *
     * @return UIP message type
     */
    UIP_TYPE getType(void);

    /**
     * Returns the message version
     *
     * @return UIP message version
     */
    UIP_VERSION getVersion(void);

    /**
     * Returns the payload length
     *
     * @return UIP payload length in bytes
     */
    UIP_PAYLOAD_LEN getPayloadLen(void);

    /**
     * Returns the payload
     *
     * @return Pointer to payload bytes
     */
    char* getPayload(void);

    /**
     * Prints a debug string for the message to an output stream
     *
     * @param ostream Output stream to receive the hex dump
     */
    void printDebugInfo(std::ostream& ostream);

    /**
     * Returns the message class name
     *
     * @return Message class name
     */
    const char* getMessageClassName(void);

    /**
     * Returns the message variant
     *
     * @return Variant
     */
    int getVariant(void);

    /**
     * Returns the message level
     *
     * @return UIP level (0..2)
     */
    UIP_LEVEL getLevel(void);

    /**
     * Sets the message level
     *
     * @param level UIP level (0..2)
     */
    void setLevel(UIP_LEVEL level);

}; // class UipMessage

//std::ostream& operator <<(std::ostream&, UipMessage message);

} // namespace uip

} // namespace iris

#endif /*API_UIPMESSAGE_H_*/
