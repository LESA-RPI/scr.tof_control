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

#ifndef DRIVERS_MULTIMAILBOX_H
#define DRIVERS_MULTIMAILBOX_H

// iris includes
#include "iris/Common.h"

// internal class forwards
#ifndef DONT_DECLARE_UIPMESSAGE
    class UipMessage;
#endif

namespace iris {

namespace utilities {
    class MailBox;
}

namespace drivers {

/**
 * Bundles three mailboxes (for UIP levels 0..2) into one convenience class
 */
class SENSORAPI MultiMailBox {

protected:

    /**
     * Typedef for triple mailbox
     */
    typedef iris::utilities::MailBox* ThreeMailBoxPointers[3];

    /**
     * Mailbox instances
     */
    ThreeMailBoxPointers mailBoxes;

public:

    /**
     * Constructor
     *
     * @param capacity Number of message entries (for each sub-mailbox)
     */
    MultiMailBox(const int capacity);

    /**
     * Destructor
     */
    virtual ~MultiMailBox();

    /**
     * Takes a message from a sub-mailbox
     *
     * @param level UIP level (0..2)
     * @param timeoutMs Timeout in milliseconds
     *
     * @return Received UipMessage instance when succeeded or <code>null</code>
     *         if timeout has occured
     */
    UipMessage* getMessage(const int level, int timeoutMs);

    /**
     * Puts a message into a sub-mailbox
     *
     * @param level UIP level (0..2)
     * @param message Message to be delivered
     */
    bool putMessage(const int level, const UipMessage* message);

}; // class MultiMailBox

} // namespace drivers

} // namespace iris

#endif // DRIVERS_MULTIMAILBOX_H
