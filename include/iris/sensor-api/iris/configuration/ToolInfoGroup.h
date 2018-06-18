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
     @file          ToolInfoGroup.h
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

#ifndef CONFIGURATION_TOOLINFOGROUP_H
#define CONFIGURATION_TOOLINFOGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI ToolInfoGroup: public ParameterGroup
{

public:


    typedef signed char Tool[32];


    typedef signed char ToolVersion[16];


    typedef signed char Pc[16];


    typedef signed char Address[32];


    typedef signed char User[32];




    ToolInfoGroup();


    void getCommunicationUploadTool(Tool& communicationUploadTool) const;


    void setCommunicationUploadTool(const Tool& communicationUploadTool);


    void getCommunicationUploadVersion(ToolVersion& communicationUploadVersion) const;


    void setCommunicationUploadVersion(const ToolVersion& communicationUploadVersion);


    void getCommunicationUploadPc(Pc& communicationUploadPc) const;


    void setCommunicationUploadPc(const Pc& communicationUploadPc);


    void getCommunicationUploadAddress(Address& communicationUploadAddress) const;


    void setCommunicationUploadAddress(const Address& communicationUploadAddress);


    void getCommunicationUploadUser(User& communicationUploadUser) const;


    void setCommunicationUploadUser(const User& communicationUploadUser);


    void getApplicationUploadTool(Tool& applicationUploadTool) const;


    void setApplicationUploadTool(const Tool& applicationUploadTool);


    void getApplicationUploadVersion(ToolVersion& applicationUploadVersion) const;


    void setApplicationUploadVersion(const ToolVersion& applicationUploadVersion);


    void getApplicationUploadPc(Pc& applicationUploadPc) const;


    void setApplicationUploadPc(const Pc& applicationUploadPc);


    void getApplicationUploadAddress(Address& applicationUploadAddress) const;


    void setApplicationUploadAddress(const Address& applicationUploadAddress);


    void getApplicationUploadUser(User& applicationUploadUser) const;


    void setApplicationUploadUser(const User& applicationUploadUser);


    void getFpgaFileUploadTool(Tool& fpgaFileUploadTool) const;


    void setFpgaFileUploadTool(const Tool& fpgaFileUploadTool);


    void getFpgaFileUploadVersion(ToolVersion& fpgaFileUploadVersion) const;


    void setFpgaFileUploadVersion(const ToolVersion& fpgaFileUploadVersion);


    void getFpgaFileUploadPc(Pc& fpgaFileUploadPc) const;


    void setFpgaFileUploadPc(const Pc& fpgaFileUploadPc);


    void getFpgaFileUploadAddress(Address& fpgaFileUploadAddress) const;


    void setFpgaFileUploadAddress(const Address& fpgaFileUploadAddress);


    void getFpgaFileUploadUser(User& fpgaFileUploadUser) const;


    void setFpgaFileUploadUser(const User& fpgaFileUploadUser);





}; // class ToolInfoGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_TOOLINFOGROUP_H

