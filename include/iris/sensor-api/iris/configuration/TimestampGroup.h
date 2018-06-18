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
     @file          TimestampGroup.h
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

#ifndef CONFIGURATION_TIMESTAMPGROUP_H
#define CONFIGURATION_TIMESTAMPGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI TimestampGroup: public ParameterGroup
{

public:


    typedef signed char Date[20];




    TimestampGroup();


    void getDateOfBirth(Date& dateOfBirth) const;


    void setDateOfBirth(const Date& dateOfBirth);


    void getDateOfBurnIn(Date& dateOfBurnIn) const;


    void setDateOfBurnIn(const Date& dateOfBurnIn);


    void getDateOfFunctionalTest(Date& dateOfFunctionalTest) const;


    void setDateOfFunctionalTest(const Date& dateOfFunctionalTest);


    void getUploadCommunicationDate(Date& uploadCommunicationDate) const;


    void setUploadCommunicationDate(const Date& uploadCommunicationDate);


    void getUploadApplicationDate(Date& uploadApplicationDate) const;


    void setUploadApplicationDate(const Date& uploadApplicationDate);


    void getUploadFpgaFileDate1(Date& uploadFpgaFileDate1) const;


    void setUploadFpgaFileDate1(const Date& uploadFpgaFileDate1);


    void getUploadFpgaFileDate2(Date& uploadFpgaFileDate2) const;


    void setUploadFpgaFileDate2(const Date& uploadFpgaFileDate2);





}; // class TimestampGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_TIMESTAMPGROUP_H

