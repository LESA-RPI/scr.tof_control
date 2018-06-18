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



/******************************************************************************/
/*!
     @file          FirmwareGroup.h
     @date          31-07-2017 14:23:28
     @author	    auto-generated with: generate_config_code.py

     code_generator:  generate_config_code.py
     generator_version: 1.1.3
     specification_file: dist500_config_spec_official.xml
     parameter_set_version: 1.7


     Warning: This file is generated automatically.
              Manual changes will be lost on next invocation!
*/
/******************************************************************************/

#ifndef CONFIGURATION_FIRMWAREGROUP_H
#define CONFIGURATION_FIRMWAREGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI FirmwareGroup: public ParameterGroup
{

public:


    typedef signed char Name[32];


    typedef signed char Version[16];


    typedef signed char Time[20];


    typedef signed char HexFile[64];



    typedef enum
    {

        Communication,

        Application,

    } DspFirmware; // enum DspFirmware



    FirmwareGroup();


    void getCommunicationName(Name& communicationName) const;


    void setCommunicationName(const Name& communicationName);


    void getCommunicationVersion(Version& communicationVersion) const;


    void setCommunicationVersion(const Version& communicationVersion);


    void getCommunicationTime(Time& communicationTime) const;


    void setCommunicationTime(const Time& communicationTime);


    void getCommunicationHexFile(HexFile& communicationHexFile) const;


    void setCommunicationHexFile(const HexFile& communicationHexFile);


    unsigned long getCommunicationSize(void) const;


    void setCommunicationSize(const unsigned long communicationSize);


    unsigned long getCommunicationChecksum(void) const;


    void setCommunicationChecksum(const unsigned long communicationChecksum);


    void getApplicationName(Name& applicationName) const;


    void setApplicationName(const Name& applicationName);


    void getApplicationVersion(Version& applicationVersion) const;


    void setApplicationVersion(const Version& applicationVersion);


    void getApplicationTime(Time& applicationTime) const;


    void setApplicationTime(const Time& applicationTime);


    void getApplicationHexFile(HexFile& applicationHexFile) const;


    void setApplicationHexFile(const HexFile& applicationHexFile);


    unsigned long getApplicationSize(void) const;


    void setApplicationSize(const unsigned long applicationSize);


    unsigned long getApplicationChecksum(void) const;


    void setApplicationChecksum(const unsigned long applicationChecksum);


    void getFpgaFileName1(Name& fpgaFileName1) const;


    void setFpgaFileName1(const Name& fpgaFileName1);


    void getFpgaFileVersion1(Version& fpgaFileVersion1) const;


    void setFpgaFileVersion1(const Version& fpgaFileVersion1);


    void getFpgaFileTime1(Time& fpgaFileTime1) const;


    void setFpgaFileTime1(const Time& fpgaFileTime1);


    void getFpgaFileHexFile1(HexFile& fpgaFileHexFile1) const;


    void setFpgaFileHexFile1(const HexFile& fpgaFileHexFile1);


    unsigned long getFpgaFileSize1(void) const;


    void setFpgaFileSize1(const unsigned long fpgaFileSize1);


    unsigned long getFpgaFileChecksum1(void) const;


    void setFpgaFileChecksum1(const unsigned long fpgaFileChecksum1);


    void getFpgaFileName2(Name& fpgaFileName2) const;


    void setFpgaFileName2(const Name& fpgaFileName2);


    void getFpgaFileVersion2(Version& fpgaFileVersion2) const;


    void setFpgaFileVersion2(const Version& fpgaFileVersion2);


    void getFpgaFileTime2(Time& fpgaFileTime2) const;


    void setFpgaFileTime2(const Time& fpgaFileTime2);


    void getFpgaFileHexFile2(HexFile& fpgaFileHexFile2) const;


    void setFpgaFileHexFile2(const HexFile& fpgaFileHexFile2);


    unsigned long getFpgaFileSize2(void) const;


    void setFpgaFileSize2(const unsigned long fpgaFileSize2);


    unsigned long getFpgaFileChecksum2(void) const;


    void setFpgaFileChecksum2(const unsigned long fpgaFileChecksum2);


    unsigned short getFpgaBootMode(void) const;


    void setFpgaBootMode(const unsigned short fpgaBootMode);


    DspFirmware getActiveDspFirmware(void) const;


    void setActiveDspFirmware(const DspFirmware activeDspFirmware);


    void getActiveDspFirmwareVersion(Version& activeDspFirmwareVersion) const;


    void setActiveDspFirmwareVersion(const Version& activeDspFirmwareVersion);


    unsigned short getActiveFpgaFirmwareVersion(void) const;


    void setActiveFpgaFirmwareVersion(const unsigned short activeFpgaFirmwareVersion);





}; // class FirmwareGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_FIRMWAREGROUP_H

