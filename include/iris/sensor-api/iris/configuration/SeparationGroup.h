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
     @file          SeparationGroup.h
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

#ifndef CONFIGURATION_SEPARATIONGROUP_H
#define CONFIGURATION_SEPARATIONGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI SeparationGroup: public ParameterGroup
{

public:




    SeparationGroup();


    unsigned short getToleratedErrorFramerate(void) const;


    void setToleratedErrorFramerate(const unsigned short toleratedErrorFramerate);


    short getMonitoredVolumeLeftBorder(void) const;


    void setMonitoredVolumeLeftBorder(const short monitoredVolumeLeftBorder);


    short getMonitoredVolumeRightBorder(void) const;


    void setMonitoredVolumeRightBorder(const short monitoredVolumeRightBorder);


    short getMonitoredVolumeOutsideBorder(void) const;


    void setMonitoredVolumeOutsideBorder(const short monitoredVolumeOutsideBorder);


    short getMonitoredVolumeInsideBorder(void) const;


    void setMonitoredVolumeInsideBorder(const short monitoredVolumeInsideBorder);


    unsigned short getMonitoredVolumeMinDistance(void) const;


    void setMonitoredVolumeMinDistance(const unsigned short monitoredVolumeMinDistance);


    unsigned short getMonitoredVolumeMaxDistance(void) const;


    void setMonitoredVolumeMaxDistance(const unsigned short monitoredVolumeMaxDistance);


    unsigned short getMinimumPersonHeight(void) const;


    void setMinimumPersonHeight(const unsigned short minimumPersonHeight);


    unsigned short getMaximumPersonHeight(void) const;


    void setMaximumPersonHeight(const unsigned short maximumPersonHeight);


    unsigned short getMinimumPersonWidth(void) const;


    void setMinimumPersonWidth(const unsigned short minimumPersonWidth);


    unsigned short getMaximumPersonWidth(void) const;


    void setMaximumPersonWidth(const unsigned short maximumPersonWidth);


    unsigned short getMinimumPersonThickness(void) const;


    void setMinimumPersonThickness(const unsigned short minimumPersonThickness);


    unsigned short getMaximumPersonThickness(void) const;


    void setMaximumPersonThickness(const unsigned short maximumPersonThickness);


    bool getIsSensorInRevolvingDoorDrum(void) const;


    void setIsSensorInRevolvingDoorDrum(const bool isSensorInRevolvingDoorDrum);





}; // class SeparationGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_SEPARATIONGROUP_H

