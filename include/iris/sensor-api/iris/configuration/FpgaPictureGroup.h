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
     @file          FpgaPictureGroup.h
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

#ifndef CONFIGURATION_FPGAPICTUREGROUP_H
#define CONFIGURATION_FPGAPICTUREGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI FpgaPictureGroup: public ParameterGroup
{

public:



    typedef enum
    {

        NoFrequency,

        FirstFrequency,

        SecondFrequency,

        ThirdFrequency,

        FourthFrequency,

    } Frequency; // enum Frequency


    typedef enum
    {

        HdrOff,

        HdrOn,

        HdrNonInterlaced,

    } HdrMode; // enum HdrMode



    FpgaPictureGroup();


    Frequency getFrequency(void) const;


    void setFrequency(const Frequency frequency);


    unsigned short getOffset(void) const;


    void setOffset(const unsigned short offset);


    unsigned short getIlluminationControl(void) const;


    void setIlluminationControl(const unsigned short illuminationControl);


    unsigned short getThreshold(void) const;


    void setThreshold(const unsigned short threshold);


    unsigned short getSaturation(void) const;


    void setSaturation(const unsigned short saturation);


    unsigned short getIntegrationTime(void) const;


    void setIntegrationTime(const unsigned short integrationTime);


    Frequency getUploadFrequency(void) const;


    void setUploadFrequency(const Frequency uploadFrequency);


    unsigned short getPicturePeriod(void) const;


    void setPicturePeriod(const unsigned short picturePeriod);


    unsigned short getMaxTemperature(void) const;


    void setMaxTemperature(const unsigned short maxTemperature);


    bool getLedPermanentRunning(void) const;


    void setLedPermanentRunning(const bool ledPermanentRunning);


    unsigned short getMirroring(void) const;


    void setMirroring(const unsigned short mirroring);


    bool getExposureControl(void) const;


    void setExposureControl(const bool exposureControl);


    float getW(void) const;


    void setW(const float w);


    float getKp(void) const;


    void setKp(const float kp);


    float getKi(void) const;


    void setKi(const float ki);


    float getKd(void) const;


    void setKd(const float kd);


    float getKs(void) const;


    void setKs(const float ks);


    float getMaxSatPix(void) const;


    void setMaxSatPix(const float maxSatPix);


    float getKwdec(void) const;


    void setKwdec(const float kwdec);


    float getKwinc(void) const;


    void setKwinc(const float kwinc);


    float getMinexpv(void) const;


    void setMinexpv(const float minexpv);


    float getMaxexpv(void) const;


    void setMaxexpv(const float maxexpv);


    float getMinexpvR2(void) const;


    void setMinexpvR2(const float minexpvR2);


    float getMaxexpvR2(void) const;


    void setMaxexpvR2(const float maxexpvR2);


    float getOffsetTemperature(void) const;


    void setOffsetTemperature(const float offsetTemperature);


    float getTemperatureCoefficient(void) const;


    void setTemperatureCoefficient(const float temperatureCoefficient);


    float getTemperatureCoefficientR2(void) const;


    void setTemperatureCoefficientR2(const float temperatureCoefficientR2);


    HdrMode getHdrMode(void) const;


    void setHdrMode(const HdrMode hdrMode);


    float getHdrFactor(void) const;


    void setHdrFactor(const float hdrFactor);


    float getHdrFactorR2(void) const;


    void setHdrFactorR2(const float hdrFactorR2);





}; // class FpgaPictureGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_FPGAPICTUREGROUP_H

