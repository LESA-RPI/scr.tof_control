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

#ifndef CONFIGURATION_CONFIGURATION_H
#define CONFIGURATION_CONFIGURATION_H

// iris includes
// TODO: JALA: convert to forward declarations
#include "iris/Common.h"
#include "ConfigurationManager.h"
#include "CommunicationGroup.h"
#include "ComponentGroup.h"
#include "ConfigurationGroup.h"
#include "CountingGroup.h"
#include "DoorGroup.h"
#include "FirmwareGroup.h"
#include "FpgaPictureGroup.h"
#include "FunctionAreaDoorGroup.h"
#include "FunctionAreaGroup.h"
#include "IpServicesGroup.h"
#include "LoggerGroup.h"
#include "TimestampGroup.h"
#include "ToolInfoGroup.h"
#include "HallSensorGroup.h"
#include "ImageGroup.h"
#include "ReservedGroup.h"
#include "SeparationGroup.h"
#include "iris/dist500/SensorInfoProvider.h"
#ifdef __ADSPBLACKFIN__
#include "flash.h"
#include "SensorBaseClasses.h"
#endif

namespace iris {

namespace configuration {

class SENSORAPI Dist500Configuration: public Configuration, public iris::dist500::SensorInfoProvider {
  
private:
  iris::configuration::CommunicationGroup* comm;
  iris::configuration::ComponentGroup* comp;
  iris::configuration::ConfigurationGroup* config;
  iris::configuration::CountingGroup* count;
  iris::configuration::DoorGroup* door;
  iris::configuration::FirmwareGroup* firmware;
  iris::configuration::FpgaPictureGroup* picture;
  iris::configuration::FunctionAreaDoorGroup* faDoor;
  iris::configuration::FunctionAreaGroup* fa;
  iris::configuration::IpServicesGroup* ips;
  iris::configuration::LoggerGroup* logger;
  iris::configuration::TimestampGroup* time;
  iris::configuration::ToolInfoGroup* tool;
  iris::configuration::HallSensorGroup* hallSensor;
  iris::configuration::ImageGroup* image;
  iris::configuration::ReservedGroup* reserved;
  iris::configuration::SeparationGroup* separation;  

  void translateInfoTime(char* src, iris::configuration::FirmwareGroup::Time& dst);
  
public:
  Dist500Configuration();
  
  const iris::configuration::CommunicationGroup& getCommunicationGroup(void);
  iris::configuration::CommunicationGroup& getWriteableCommunicationGroup(void);
  const iris::configuration::ComponentGroup& getComponentGroup(void);
  iris::configuration::ComponentGroup& getWriteableComponentGroup(void);  
  const iris::configuration::ConfigurationGroup& getConfigurationGroup(void);
  iris::configuration::ConfigurationGroup& getWriteableConfigurationGroup(void);  
  const iris::configuration::CountingGroup& getCountingGroup(void);
  iris::configuration::CountingGroup& getWriteableCountingGroup(void); 
  const iris::configuration::DoorGroup& getDoorGroup(void);
  iris::configuration::DoorGroup& getWriteableDoorGroup(void);
  const iris::configuration::FirmwareGroup& getFirmwareGroup(void);
  iris::configuration::FirmwareGroup& getWriteableFirmwareGroup(void);
  const iris::configuration::FpgaPictureGroup& getFpgaPictureGroup(void);
  iris::configuration::FpgaPictureGroup& getWriteableFpgaPictureGroup(void);
  const iris::configuration::FunctionAreaDoorGroup& getFunctionAreaDoorGroup(void);
  iris::configuration::FunctionAreaDoorGroup& getWriteableFunctionAreaDoorGroup(void);
  const iris::configuration::FunctionAreaGroup& getFunctionAreaGroup(void);
  iris::configuration::FunctionAreaGroup& getWriteableFunctionAreaGroup(void);
  const iris::configuration::IpServicesGroup& getIpServicesGroup(void);
  iris::configuration::IpServicesGroup& getWriteableIpServicesGroup(void);
  const iris::configuration::LoggerGroup& getLoggerGroup(void);
  iris::configuration::LoggerGroup& getWriteableLoggerGroup(void);
  const iris::configuration::TimestampGroup& getTimestampGroup(void);
  iris::configuration::TimestampGroup& getWriteableTimestampGroup(void);
  const iris::configuration::ToolInfoGroup& getToolInfoGroup(void);
  iris::configuration::ToolInfoGroup& getWriteableToolInfoGroup(void);
  const iris::configuration::HallSensorGroup& getHallSensorGroup(void);
  iris::configuration::HallSensorGroup& getWriteableHallSensorGroup(void);
  const iris::configuration::ImageGroup& getImageGroup(void);
  iris::configuration::ImageGroup& getWriteableImageGroup(void);
  const iris::configuration::ReservedGroup& getReservedGroup(void);
  iris::configuration::ReservedGroup& getWriteableReservedGroup(void);
  const iris::configuration::SeparationGroup& getSeparationGroup(void);
  iris::configuration::SeparationGroup& getWriteableSeparationGroup(void);

  iris::dist500::SensorInfo getSensorInfo(bool forceRefresh = false);

  void invalidateSensorInfo(void);

  bool hasSensorInfo(void) const;

  operator iris::dist500::SensorInfo ();

#ifdef __ADSPBLACKFIN__
  void mapStructToManager(t_ConfigurationFlashDataStruct& cfg);
  void mapFirmwareInfos(t_FirmwareInfo& bootloaderInfo, t_FirmwareInfo& applicationInfo);
#endif

  Dist500Configuration(const Dist500Configuration& source);

  Dist500Configuration& operator = (Dist500Configuration& source);

  void cloneDataFrom(const Dist500Configuration& source);

}; // class Dist500Configuration

class SENSORAPI Dist500LiveConfiguration: public LiveConfiguration, public iris::dist500::SensorInfoProvider {

private:
  iris::configuration::CommunicationGroup* comm;
  iris::configuration::ComponentGroup* comp;
  iris::configuration::ConfigurationGroup* config;
  iris::configuration::CountingGroup* count;
  iris::configuration::DoorGroup* door;
  iris::configuration::FirmwareGroup* firmware;
  iris::configuration::FpgaPictureGroup* picture;
  iris::configuration::FunctionAreaDoorGroup* faDoor;
  iris::configuration::FunctionAreaGroup* fa;
  iris::configuration::IpServicesGroup* ips;
  iris::configuration::LoggerGroup* logger;
  iris::configuration::TimestampGroup* time;
  iris::configuration::ToolInfoGroup* tool;
  iris::configuration::HallSensorGroup* hallSensor;
  iris::configuration::ImageGroup* image;
  iris::configuration::ReservedGroup* reserved;
  iris::configuration::SeparationGroup* separation;  

  void translateInfoTime(char* src, iris::configuration::FirmwareGroup::Time& dst);

public:
  Dist500LiveConfiguration(iris::dist500::Dist500* dist500);

  const iris::configuration::CommunicationGroup& getCommunicationGroup(void);
  iris::configuration::CommunicationGroup& getWriteableCommunicationGroup(void);
  const iris::configuration::ComponentGroup& getComponentGroup(void);
  iris::configuration::ComponentGroup& getWriteableComponentGroup(void);
  const iris::configuration::ConfigurationGroup& getConfigurationGroup(void);
  iris::configuration::ConfigurationGroup& getWriteableConfigurationGroup(void);
  const iris::configuration::CountingGroup& getCountingGroup(void);
  iris::configuration::CountingGroup& getWriteableCountingGroup(void);
  const iris::configuration::DoorGroup& getDoorGroup(void);
  iris::configuration::DoorGroup& getWriteableDoorGroup(void);
  const iris::configuration::FirmwareGroup& getFirmwareGroup(void);
  iris::configuration::FirmwareGroup& getWriteableFirmwareGroup(void);
  const iris::configuration::FpgaPictureGroup& getFpgaPictureGroup(void);
  iris::configuration::FpgaPictureGroup& getWriteableFpgaPictureGroup(void);
  const iris::configuration::FunctionAreaDoorGroup& getFunctionAreaDoorGroup(void);
  iris::configuration::FunctionAreaDoorGroup& getWriteableFunctionAreaDoorGroup(void);
  const iris::configuration::FunctionAreaGroup& getFunctionAreaGroup(void);
  iris::configuration::FunctionAreaGroup& getWriteableFunctionAreaGroup(void);
  const iris::configuration::IpServicesGroup& getIpServicesGroup(void);
  iris::configuration::IpServicesGroup& getWriteableIpServicesGroup(void);
  const iris::configuration::LoggerGroup& getLoggerGroup(void);
  iris::configuration::LoggerGroup& getWriteableLoggerGroup(void);
  const iris::configuration::TimestampGroup& getTimestampGroup(void);
  iris::configuration::TimestampGroup& getWriteableTimestampGroup(void);
  const iris::configuration::ToolInfoGroup& getToolInfoGroup(void);
  iris::configuration::ToolInfoGroup& getWriteableToolInfoGroup(void);
  const iris::configuration::HallSensorGroup& getHallSensorGroup(void);
  iris::configuration::HallSensorGroup& getWriteableHallSensorGroup(void);
  const iris::configuration::ImageGroup& getImageGroup(void);
  iris::configuration::ImageGroup& getWriteableImageGroup(void);
  const iris::configuration::ReservedGroup& getReservedGroup(void);
  iris::configuration::ReservedGroup& getWriteableReservedGroup(void);
  const iris::configuration::SeparationGroup& getSeparationGroup(void);
  iris::configuration::SeparationGroup& getWriteableSeparationGroup(void);

  iris::dist500::SensorInfo getSensorInfo(bool forceRefresh = false);

  void invalidateSensorInfo(void);

  bool hasSensorInfo(void) const;

#ifdef __ADSPBLACKFIN__
  void mapStructToManager(t_ConfigurationFlashDataStruct& cfg);
  void mapFirmwareInfos(t_FirmwareInfo& bootloaderInfo, t_FirmwareInfo& applicationInfo);
#endif

}; // class Dist500Configuration

} // namespace configuration

} // namespace iris

#endif // CONFIGURATION_CONFIGURATION_H
