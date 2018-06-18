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
     @file          CommunicationGroup.h
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

#ifndef CONFIGURATION_COMMUNICATIONGROUP_H
#define CONFIGURATION_COMMUNICATIONGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI CommunicationGroup: public ParameterGroup
{

public:


    typedef unsigned char MacAddress[6];


    typedef unsigned char IpAddress[4];



    typedef enum
    {

        NoCan,

        CanIrmaProtocol,

        CanOpenProtocol,

        CanJ1939Protocol,

    } CanProtocol; // enum CanProtocol


    typedef enum
    {

        StatusLedOff,

        StatusLedNormalMode,

        StatusLedBothPermanent,

        StatusLedLeftPermanent,

        StatusLedRightPermanent,

        OperationMode1,

        OperationMode2,

    } StatusLedMode; // enum StatusLedMode


    typedef enum
    {

        StaticIp,

        Dhcp,

    } IpAddressConfiguration; // enum IpAddressConfiguration



    CommunicationGroup();


    void getMacAddr(MacAddress& macAddr) const;


    void setMacAddr(const MacAddress& macAddr);


    void getIpAddr(IpAddress& ipAddr) const;


    void setIpAddr(const IpAddress& ipAddr);


    void getNetMask(IpAddress& netMask) const;


    void setNetMask(const IpAddress& netMask);


    void getGateway(IpAddress& gateway) const;


    void setGateway(const IpAddress& gateway);


    unsigned short getPort(void) const;


    void setPort(const unsigned short port);


    void getDns(IpAddress& dns) const;


    void setDns(const IpAddress& dns);


    void getSntp1(IpAddress& sntp1) const;


    void setSntp1(const IpAddress& sntp1);


    void getSntp2(IpAddress& sntp2) const;


    void setSntp2(const IpAddress& sntp2);


    IpAddressConfiguration getIpAddressConfiguration(void) const;


    void setIpAddressConfiguration(const IpAddressConfiguration ipAddressConfiguration);


    unsigned char getSensorCount(void) const;


    void setSensorCount(const unsigned char sensorCount);


    void getSensorMac(const unsigned char index, MacAddress& addr) const;


    void setSensorMac(const unsigned char index, const MacAddress& addr);


    unsigned char getOwnUipAddr(void) const;


    void setOwnUipAddr(const unsigned char ownUipAddr);


    unsigned char getGatewayUipAddr(void) const;


    void setGatewayUipAddr(const unsigned char gatewayUipAddr);


    unsigned short getCanSpeed(void) const;


    void setCanSpeed(const unsigned short canSpeed);


    CanProtocol getCanProtocol(void) const;


    void setCanProtocol(const CanProtocol canProtocol);


    unsigned short getCanOpenParam(void) const;


    void setCanOpenParam(const unsigned short canOpenParam);


    StatusLedMode getStatusLedMode(void) const;


    void setStatusLedMode(const StatusLedMode statusLedMode);


    unsigned short getIbisIpPort(void) const;


    void setIbisIpPort(const unsigned short ibisIpPort);


    // convenience functions

#ifdef __ADSPBLACKFIN__
    unsigned long getCanIrmaAddress(void) const;
#endif


#ifndef __ADSPBLACKFIN__
    unsigned long getCanIrmaAddress(void) const;
#endif


#ifdef __ADSPBLACKFIN__
    void saveCanIrmaAddress(void) const;
#endif


    void setIpAddrMac(void);

    void setSensorMacOwn(void);


private:

}; // class CommunicationGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_COMMUNICATIONGROUP_H

