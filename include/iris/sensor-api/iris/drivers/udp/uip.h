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

#ifndef DRIVERS_UDP_UIP_H
#define DRIVERS_UDP_UIP_H

typedef unsigned char u8_t;
typedef signed char s8_t;
typedef unsigned short u16_t;
typedef signed short s16_t;
typedef unsigned long u32_t;
typedef signed long s32_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Computes the frame lengths for a UIP frame
 *
 * @param payloadLen UIP Payload length
 *
 * @return Total frame length in bytes
 */
u16_t computeFrameLength(const u16_t payloadLen);

/**
 * Retrieves the UIP header values and the payload length from a UIP frame (if valid)
 *
 * @param frame Pointer to received bytes
 * @param frameLen Number of received bytes
 * @param rcv Buffer for UIP receiver
 * @param snd Buffer for UIP sender
 * @param type Buffer for UIP type
 * @param version Buffer for UIP version
 * @param payloadPtr Buffer for UIP payload pointer
 * @param msgLevel Buffer to receive the UIP level
 *
 * @return Payload length or -1 if invalid
 */
s16_t extractPayloadLength(const u8_t *frame, const u16_t frameLen, u8_t *rcv,
        u8_t *snd, u8_t *type, u8_t *version, u8_t **payloadPtr, u8_t* msgLevel);

/**
 * Encodes a UIP frame
 *
 * @param buffer Buffer to receive the constructed frame
 * @param receiver UIP receiver
 * @param sender UIP sender
 * @param type UIP type
 * @param version UIP version
 * @param payload Pointer to UIP payload
 * @param payloadLen Length of UIP payload
 * @param msgLevel UIP level
 *
 * @return Total size of constructed frame
 */
u16_t makeFrame(u8_t* buffer, const u8_t receiver, const u8_t sender,
        const u8_t type, const u8_t version, const u8_t* payload,
        const u16_t payloadLen, const u8_t msgLevel);

/**
 * Decodes a UIP frame (if valid)
 *
 * @param frame Pointer to received bytes
 * @param frameLen Number of received bytes
 * @param receiver Buffer for UIP receiver
 * @param sender Buffer for UIP sender
 * @param type Buffer for UIP type
 * @param version Buffer for UIP version
 * @param payloadBuffer Buffer to receive the UIP payload bytes
 * @param payloadLen Buffer to receive the UIP payload len
 * @param skipChecksumVerification Flag indicating if checksum verification
 *        is desired (<code>true</code>) or not (<code>false</code>)
 * @param msgLevel Buffer to receive the UIP level
 *
 * @return 1 if frame is valid, 0 otherwise
 */
u8_t decodeFrame(const u8_t *frame, const u16_t frameLen, u8_t* receiver,
        u8_t* sender, u8_t* type, u8_t* version, u8_t* payloadBuffer,
        u16_t *payloadLen, u8_t skipChecksumVerification, u8_t* msgLevel);

#ifdef __cplusplus
}
#endif

// special address constants
#define UIP_BROADCAST_ADDR 0xFF
#define UIP_HOST_PC_ADDR 0xFC
#define UIP_SERVICE_PC_ADDR 0xFE

#endif // DRIVERS_UDP_UIP_H
