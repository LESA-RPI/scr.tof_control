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
     @file          DoorGroup.h
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

#ifndef CONFIGURATION_DOORGROUP_H
#define CONFIGURATION_DOORGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI DoorGroup: public ParameterGroup
{

public:



    typedef enum
    {

        Positive = 43,

        Negative = 45,

    } DoorPolarity; // enum DoorPolarity


    typedef enum
    {

        DoorClearOff,

        DoorClearOn,

    } DoorClearFunction; // enum DoorClearFunction



    DoorGroup();


    unsigned char getDoorCount(void) const;


    void setDoorCount(const unsigned char doorCount);


    unsigned short getDoorAddress(const unsigned char index) const;


    void setDoorAddress(const unsigned char index, const unsigned short address);


    unsigned short getDoorDelay(const unsigned char index) const;


    void setDoorDelay(const unsigned char index, const unsigned short delay);


    DoorGroup::DoorPolarity getDoorPolarity(const unsigned char index) const;


    void setDoorPolarity(const unsigned char index, const DoorPolarity polarity);


    DoorClearFunction getDoorClearFunction(void) const;


    void setDoorClearFunction(const DoorClearFunction doorClearFunction);


    short getDoorClearVolumeWidthLeft(void) const;


    void setDoorClearVolumeWidthLeft(const short doorClearVolumeWidthLeft);


    short getDoorClearVolumeWidthRight(void) const;


    void setDoorClearVolumeWidthRight(const short doorClearVolumeWidthRight);


    short getDoorClearVolumeDepthIn(void) const;


    void setDoorClearVolumeDepthIn(const short doorClearVolumeDepthIn);


    short getDoorClearVolumeDepthOut(void) const;


    void setDoorClearVolumeDepthOut(const short doorClearVolumeDepthOut);


    short getDoorClearVolumeHeightTop(void) const;


    void setDoorClearVolumeHeightTop(const short doorClearVolumeHeightTop);


    short getDoorClearVolumeHeightBottom(void) const;


    void setDoorClearVolumeHeightBottom(const short doorClearVolumeHeightBottom);





}; // class DoorGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_DOORGROUP_H

