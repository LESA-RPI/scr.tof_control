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
     @file          ComponentGroup.h
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

#ifndef CONFIGURATION_COMPONENTGROUP_H
#define CONFIGURATION_COMPONENTGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI ComponentGroup: public ParameterGroup
{

public:


    typedef signed char SensorNameLong[64];


    typedef signed char SensorNameShort[32];


    typedef signed char SensorSerial[16];


    typedef signed char ProductionIndex[16];


    typedef signed char ProductionId[16];


    typedef signed char NameLong[32];


    typedef signed char NameShort[16];


    typedef signed char Serial[16];




    ComponentGroup();


    void getSensorNameLong(SensorNameLong& sensorNameLong) const;


    void setSensorNameLong(const SensorNameLong& sensorNameLong);


    void getSensorNameShort(SensorNameShort& sensorNameShort) const;


    void setSensorNameShort(const SensorNameShort& sensorNameShort);


    void getSensorSerial(SensorSerial& sensorSerial) const;


    void setSensorSerial(const SensorSerial& sensorSerial);


    void getProductionIndex(ProductionIndex& productionIndex) const;


    void setProductionIndex(const ProductionIndex& productionIndex);


    void getProductionId(ProductionId& productionId) const;


    void setProductionId(const ProductionId& productionId);


    void getBasisNameLong(NameLong& basisNameLong) const;


    void setBasisNameLong(const NameLong& basisNameLong);


    void getBasisNameShort(NameShort& basisNameShort) const;


    void setBasisNameShort(const NameShort& basisNameShort);


    void getBasisSerial(Serial& basisSerial) const;


    void setBasisSerial(const Serial& basisSerial);


    void getLed1NameLong(NameLong& led1NameLong) const;


    void setLed1NameLong(const NameLong& led1NameLong);


    void getLed1NameShort(NameShort& led1NameShort) const;


    void setLed1NameShort(const NameShort& led1NameShort);


    void getLed1Serial(Serial& led1Serial) const;


    void setLed1Serial(const Serial& led1Serial);


    void getLed2NameLong(NameLong& led2NameLong) const;


    void setLed2NameLong(const NameLong& led2NameLong);


    void getLed2NameShort(NameShort& led2NameShort) const;


    void setLed2NameShort(const NameShort& led2NameShort);


    void getLed2Serial(Serial& led2Serial) const;


    void setLed2Serial(const Serial& led2Serial);


    void getChassisNameLong(NameLong& chassisNameLong) const;


    void setChassisNameLong(const NameLong& chassisNameLong);


    void getChassisNameShort(NameShort& chassisNameShort) const;


    void setChassisNameShort(const NameShort& chassisNameShort);


    void getChassisSerial(Serial& chassisSerial) const;


    void setChassisSerial(const Serial& chassisSerial);


    unsigned char getBlackfinRevision(void) const;


    void setBlackfinRevision(const unsigned char blackfinRevision);


    unsigned char getSensorRevision(void) const;


    void setSensorRevision(const unsigned char sensorRevision);


    void getMarecNameLong(NameLong& marecNameLong) const;


    void setMarecNameLong(const NameLong& marecNameLong);


    void getMarecNameShort(NameShort& marecNameShort) const;


    void setMarecNameShort(const NameShort& marecNameShort);


    void getMarecSerial(Serial& marecSerial) const;


    void setMarecSerial(const Serial& marecSerial);


    void getLowerAssemblyNameLong(NameLong& lowerAssemblyNameLong) const;


    void setLowerAssemblyNameLong(const NameLong& lowerAssemblyNameLong);


    void getLowerAssemblyNameShort(NameShort& lowerAssemblyNameShort) const;


    void setLowerAssemblyNameShort(const NameShort& lowerAssemblyNameShort);


    void getLowerAssemblySerial(Serial& lowerAssemblySerial) const;


    void setLowerAssemblySerial(const Serial& lowerAssemblySerial);





}; // class ComponentGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_COMPONENTGROUP_H

