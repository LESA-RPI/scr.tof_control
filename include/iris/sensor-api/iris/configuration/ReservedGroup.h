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
     @file          ReservedGroup.h
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

#ifndef CONFIGURATION_RESERVEDGROUP_H
#define CONFIGURATION_RESERVEDGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI ReservedGroup: public ParameterGroup
{

public:



    typedef enum
    {

        ReservedParam1,

        ReservedParam2,

        ReservedParam3,

        ReservedParam4,

        ReservedParam5,

        ReservedParam6,

        ReservedParam7,

        ReservedParam8,

        ReservedParam9,

        ReservedParam10,

        ReservedParam11,

        ReservedParam12,

        ReservedParam13,

        ReservedParam14,

        ReservedParam15,

        ReservedParam16,

        ReservedParam17,

        ReservedParam18,

        ReservedParam19,

        ReservedParam20,

    } ReservedParameterIndex; // enum ReservedParameterIndex



    ReservedGroup();


    signed long getReservedParam(ReservedParameterIndex index) const;


    void setReservedParam(const ReservedParameterIndex index, const signed long reservedParam);





}; // class ReservedGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_RESERVEDGROUP_H

