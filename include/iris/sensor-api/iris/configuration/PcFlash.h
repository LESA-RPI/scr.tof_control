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

#ifndef PCFLASH_H
#define PCFLASH_H

// iris includes
#include "../Common.h"

class SENSORAPI PcFlash {
public:
    typedef unsigned char UINT8;
    typedef unsigned short UINT16;
    typedef UINT16 *UINT16_PTR;
    typedef unsigned long UINT32;
    virtual bool lockSector(UINT8 banknum, UINT8 sectnum) = 0;
    virtual bool unlockSector(UINT8 banknum, UINT8 sectnum) = 0;
    virtual bool eraseSector(UINT8 banknum, UINT8 sectnum) = 0;
    virtual bool programFlash(UINT8 banknum, UINT32 address, UINT16_PTR buffer, UINT32 numitems, bool bufferedMode = true) = 0;
    virtual bool readFlash(UINT8 banknum, UINT32 address, UINT16_PTR buffer, UINT32 numitems) = 0;
    //void enableReadArrayMode(void);
    virtual bool programFlash(UINT8 banknum, UINT32 address, UINT16 value) = 0;
    virtual bool readFlash(UINT8 banknum, UINT32 address, UINT16_PTR buffer) = 0;
    /*bool readSectorStatus(UINT8 banknum, UINT16 sectnum, TMPL_FDATA &blockstat);
    bool readHardwareInfo(struct TMPL_QueryData &query, struct TMPL_ExtQueryData &extquery);
    static void getDeviceType(UINT16 &manufacturer, UINT16 &type);*/
    PcFlash();
    virtual ~PcFlash();
    virtual unsigned short* getFlashMemoryAddress(unsigned long address) = 0;
    virtual void acquireMutex(void) = 0;
    virtual void releaseMutex(void) = 0;
};

typedef struct {
    char TypeName[64];
    char Dummy[0xb00 - 64];
} t_ConfigurationFlashDataStruct;

typedef PcFlash* (*FlashDriverInstanceFactory) (void);

extern FlashDriverInstanceFactory flashDriverInstanceFactory;

PcFlash* getFlashDriverInstance(void);

#endif // PCFLASH_H
