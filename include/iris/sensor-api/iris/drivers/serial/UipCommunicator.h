#ifndef DRIVERS_SERIAL_UIPCOMMUNICATOR_H
#define DRIVERS_SERIAL_UIPCOMMUNICATOR_H

// workaround for win32: needs to be first include
#if defined(__WIN32) || defined(_WIN32)
#include <winsock2.h>
#endif

// iris includes
#include "iris/Common.h"
#include "UipMessage.h"

namespace iris {

namespace drivers {

namespace serial {

const static int MAX_UIP_FRAME_LENGTH = 1500;

class SerialDriver;

class SENSORAPI UipCommunicator {
private:

        int state;
        char buffer[MAX_UIP_FRAME_LENGTH];
        volatile int bufferPos;
        int remainingPayloadLength;
        bool shortLen;
        SerialDriver* driver;
        const static int STATE_WAITING_FOR_I = -1;
        const static int STATE_I_RECEIVED = 0;
        const static int STATE_R_RECEIVED = 1;
        const static int STATE_M_RECEIVED = 2;
        const static int STATE_A_RECEIVED = 3;
        const static int STATE_DUMMYDEST_RECEIVED = 4;
        const static int STATE_DUMMYSRC_RECEIVED = 5;
        const static int STATE_UIPVER_RECEIVED = 6;
        const static int STATE_DEST_RECEIVED = 7;
        const static int STATE_SRC_RECEIVED = 8;
        const static int STATE_LENLO_RECEIVED = 9;
        const static int STATE_LENHI_RECEIVED = 10;
        const static int STATE_TYPE_RECEIVED = 11;
        const static int STATE_VERSION_RECEIVED = 12;
        const static int STATE_PAYLOAD_RECEIVED = 13;
        const static int STATE_CHECKSUM_RECEIVED = 14;

        const static bool USE_WORKAROUND = true;
        const static bool FORCE_UIP20 = true;

        bool forceUip20;

public:
        UipCommunicator(SerialDriver* driver);
        virtual ~UipCommunicator();
        void reset(void);
        void processBytes(char* chars, int offset, int len);
        static char computeUipChecksum(char* frame, int len);
        int makeFrame(UipMessage* message, char* buffer, unsigned char senderAddress);
        void close(void);        
        void setForceUip20(bool force);
};

}

}

}

#endif // DRIVERS_SERIAL_UIPCOMMUNICATOR_H
