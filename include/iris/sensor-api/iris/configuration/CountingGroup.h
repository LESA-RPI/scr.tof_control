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
     @file          CountingGroup.h
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

#ifndef CONFIGURATION_COUNTINGGROUP_H
#define CONFIGURATION_COUNTINGGROUP_H

// iris includes
#include "../Common.h"
#include "ConfigurationManager.h"

namespace iris
{

namespace configuration
{

class SENSORAPI CountingGroup: public ParameterGroup
{

public:



    typedef enum
    {

        NoCounting,

        CountingActive,

    } Counting; // enum Counting


    typedef enum
    {

        DummyCounter,

        PersonCounter,

    } CountAlgorithm; // enum CountAlgorithm


    typedef enum
    {

        ClassifierOff,

        ClassifierOn,

    } ClassifierMode; // enum ClassifierMode


    typedef enum
    {

        PushDisabled,

        PushOnCountEvent,

        PushOnInterval,

        PushOnDoorClosed,

    } PushOptionType; // enum PushOptionType



    CountingGroup();


    short getXPosition(void) const;


    void setXPosition(const short xPosition);


    short getYPosition(void) const;


    void setYPosition(const short yPosition);


    unsigned short getMountingHeight(void) const;


    void setMountingHeight(const unsigned short mountingHeight);


    Counting getCounting(void) const;


    void setCounting(const Counting counting);


    unsigned short getMasterSensor(void) const;


    void setMasterSensor(const unsigned short masterSensor);


    CountAlgorithm getCountingAlgorithm(void) const;


    void setCountingAlgorithm(const CountAlgorithm countingAlgorithm);


    unsigned short getFramesAfterDoorClosing(void) const;


    void setFramesAfterDoorClosing(const unsigned short framesAfterDoorClosing);


    bool getCounterOverrunEnable(void) const;


    void setCounterOverrunEnable(const bool counterOverrunEnable);


    unsigned short getXDistanceToWallLeft(void) const;


    void setXDistanceToWallLeft(const unsigned short xDistanceToWallLeft);


    unsigned short getXDistanceToWallRight(void) const;


    void setXDistanceToWallRight(const unsigned short xDistanceToWallRight);


    short getYCountCurtain(const unsigned char index) const;


    void setYCountCurtain(const unsigned char index, const signed short curtain);


    unsigned short getMinObjectHeight(void) const;


    void setMinObjectHeight(const unsigned short minObjectHeight);


    unsigned short getThresholdCildAdult(void) const;


    void setThresholdChildAdult(const unsigned short thresholdChildAdult);


    unsigned short getZMinDetection(void) const;


    void setZMinDetection(const unsigned short zMinDetection);


    unsigned short getDoorToSensorDistance(void) const;


    void setDoorToSensorDistance(const unsigned short doorToSensorDistance);


    unsigned short getPeoplePathLength(void) const;


    void setPeoplePathLength(const unsigned short peoplePathLength);


    short getBoardingPeoplePathDifference(void) const;


    void setBoardingPeoplePathDifference(const short boardingPeoplePathDifference);


    bool getCountSmallChildren(void) const;


    void setCountSmallChildren(const bool countSmallChildren);


    unsigned short getMedianFilter(void) const;


    void setMedianFilter(const unsigned short medianFilter);


    unsigned short getAverageFilter(void) const;


    void setAverageFilter(const unsigned short averageFilter);


    unsigned short getMaxDistFeatureFusion(void) const;


    void setMaxDistFeatureFusion(const unsigned short maxDistFeatureFusion);


    unsigned short getSideWallLeft(void) const;


    void setSideWallLeft(const unsigned short sideWallLeft);


    unsigned short getSideWallRight(void) const;


    void setSideWallRight(const unsigned short sideWallRight);


    short getVehicleEdgeOffset(void) const;


    void setVehicleEdgeOffset(const short vehicleEdgeOffset);


    short getXAxisRotationAngle(void) const;


    void setXAxisRotationAngle(const short xAxisRotationAngle);


    short getYAxisRotationAngle(void) const;


    void setYAxisRotationAngle(const short yAxisRotationAngle);


    short getZAxisRotationAngle(void) const;


    void setZAxisRotationAngle(const short zAxisRotationAngle);


    unsigned short getDoorOpeningAngleLeft(void) const;


    void setDoorOpeningAngleLeft(const unsigned short doorOpeningAngleLeft);


    unsigned short getDoorOpeningAngleRight(void) const;


    void setDoorOpeningAngleRight(const unsigned short doorOpeningAngleRight);


    bool getAdultEnable(void) const;


    void setAdultEnable(const bool adultEnable);


    bool getChildEnable(void) const;


    void setChildEnable(const bool childEnable);


    bool getBikeEnable(void) const;


    void setBikeEnable(const bool bikeEnable);


    bool getBuggyEnable(void) const;


    void setBuggyEnable(const bool buggyEnable);


    bool getDogEnable(void) const;


    void setDogEnable(const bool dogEnable);


    bool getBaggageEnable(void) const;


    void setBaggageEnable(const bool baggageEnable);


    bool getSabotageEnable(void) const;


    void setSabotageEnable(const bool sabotageEnable);


    unsigned long long getSabotageParameter(void) const;


    void setSabotageParameter(const unsigned long long sabotageParameter);


    unsigned char getSabotageAggregation(void) const;


    void setSabotageAggregation(const unsigned char sabotageAggregation);


    bool getDoorDetectionEnable(void) const;


    void setDoorDetectionEnable(const bool doorDetectionEnable);


    unsigned char getStartActivationMode(void) const;


    void setStartActivationMode(const unsigned char startActivationMode);


    unsigned char getCategoryCount(void) const;


    void setCategoryCount(const unsigned char categoryCount);


    unsigned char getCategoryId(const unsigned char index) const;


    void setCategoryId(const unsigned char index, const unsigned char id);


    iris::uip::category_type getCategoryType(const unsigned char index) const;


    void setCategoryType(const unsigned char index, const iris::uip::category_type type);


    unsigned short getCategoryParam(const unsigned char index, const unsigned char paramIndex) const;


    void setCategoryParam(const unsigned char index, const unsigned char paramIndex, const unsigned short param);


    ClassifierMode getClassifierMode(void) const;


    void setClassifierMode(const ClassifierMode classifierMode);


    PushOptionType getCountingDataPushOption(void) const;


    void setCountingDataPushOption(const PushOptionType countingDataPushOption);


    unsigned long getCountingDataPushInterval(void) const;


    void setCountingDataPushInterval(const unsigned long countingDataPushInterval);





}; // class CountingGroup

} // namespace configuration

} // namespace iris
#endif // CONFIGURATION_COUNTINGGROUP_H

