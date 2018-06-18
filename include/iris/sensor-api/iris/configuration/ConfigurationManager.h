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

#ifndef CONFIGURATION_CONFIGURATIONMANAGER_H
#define CONFIGURATION_CONFIGURATIONMANAGER_H

// STL includes
#include <map>
#include <string>
#include <ostream>
#include <sstream>

// iris includes


// OS dependent includes
#ifdef __ADSPBLACKFIN__
#include "UIP20/UipTypes.h"
#define SENSORAPI
#else
#include "iris/Common.h"
    #ifdef APIBUILD
        #include "UipTypes.h"
    #else
        #include "iris/UipTypes.h"
    #endif
#endif

namespace iris {

#ifndef __ADSPBLACKFIN__
namespace dist500 {
    // forward
    class Dist500;
}
#endif

namespace configuration {

class BaseConfiguration;

class InMemoryParameterAccessHandler;
class AbstractParameterAccessHandler;

class SENSORAPI ParameterGroup {

public:

  typedef enum { ubyteValue, sbyteValue, ushortValue, sshortValue, ulongValue, slongValue, ulonglongValue, slonglongValue, floatValue, doubleValue, boolValue,
      ubyteArray, sbyteArray, ushortArray, sshortArray, ulongArray, slongArray, ulonglongArray, slonglongArray, floatArray, doubleArray, boolArray, anyType, fixLenString } DataType;

  typedef enum { immanentParam, alwaysReplaceParam, optionallyReplaceParam, alwaysReplaceOrResetParam, neverChangeParam, volatileParam } UpdateType;

  typedef bool (*ARRAY_PARAMETER_VALIDITY_CHECK_CALLBACK) (const iris::uip::ushort groupId, const iris::uip::ushort paramId, const void* valuePtr, const iris::uip::ushort valueSize);

  typedef bool (*INTEGER_PARAMETER_VALIDITY_CHECK_CALLBACK) (const iris::uip::ushort groupId, const iris::uip::ushort paramId, const signed long value);

  typedef bool (*FLOATING_POINT_PARAMETER_VALIDITY_CHECK_CALLBACK) (const iris::uip::ushort groupId, const iris::uip::ushort paramId, const double value);

protected:

  typedef struct _ParameterDefinition {

    /*const*/ DataType dataType;

    /*const*/ iris::uip::ushort arraySize;

    char* baseAddress;

    unsigned long addressOffsetInGroup;

    /*const*/ iris::uip::ushort elementSize;

    /*const*/ iris::uip::ushort totalSize;

    UpdateType updateType;

    signed long minValue;

    signed long maxValue;

    signed long defaultValue;
    
    bool handleAsString;
    
    char* defaultString;

    union {
        ARRAY_PARAMETER_VALIDITY_CHECK_CALLBACK arrayCallback;
        INTEGER_PARAMETER_VALIDITY_CHECK_CALLBACK integerCallback;
        FLOATING_POINT_PARAMETER_VALIDITY_CHECK_CALLBACK floatingPointCallback;
    } validityCheckCallbacks;

    _ParameterDefinition(const DataType dataType, const iris::uip::ushort arraySize, const unsigned long addressOffsetInGroup, const iris::uip::ushort elementSize, const iris::uip::ushort totalSize,
                         const UpdateType updateType, signed long minValue, signed long maxValue, signed long defaultValue, const bool handleAsString);

    virtual ~_ParameterDefinition();

    _ParameterDefinition(const _ParameterDefinition &source);

    _ParameterDefinition& operator = (const _ParameterDefinition& source);

    bool operator == (const _ParameterDefinition& other) const;

    bool operator != (const _ParameterDefinition& other) const;

  } ParameterDefinition;

  typedef std::map<iris::uip::ushort, ParameterDefinition*> ParameterMap;

  typedef std::map<std::string, iris::uip::ushort> NameIdMap;

  typedef std::map<iris::uip::ushort, std::string> IdNameMap;

  ParameterMap parameters;

  NameIdMap nameMap;

  IdNameMap idMap;

  const iris::uip::ushort groupId; // ID of parameter group

  const std::string groupName;

  char* baseAddress;

  unsigned long addressOffsetInGroup;

  char* oldBaseAddress;

  iris::uip::ulong groupSize;

  iris::uip::ulong oldGroupSize;

  ParameterDefinition* _registerParameter(const iris::uip::ushort paramId, const std::string paramName, const DataType dataType, const iris::uip::ushort arraySize = 1,
                         const UpdateType updateType = immanentParam, signed long minValue = 0, signed long maxValue = 0, signed long defaultValue = 0);
  
  void registerFloatParameter(const iris::uip::ushort paramId, const char* paramName,
                         const UpdateType updateType = immanentParam, float minValue = 0, float maxValue = 0, float defaultValue = 0);
                         
  void registerDoubleParameter(const iris::uip::ushort paramId, const char* paramName,
                         const UpdateType updateType = immanentParam, double minValue = 0, double maxValue = 0, double defaultValue = 0);
                         
  void registerStringParameter(const iris::uip::ushort paramId, const char* paramName, const iris::uip::ushort strLen = 1,
                         const UpdateType updateType = immanentParam, const char* defaultValue = 0);

  static signed long f2sl(const float f);
  
  static float sl2f(const signed long sl);
  
  void registerParameterArray(const iris::uip::ushort paramStartId, const iris::uip::ushort skipValue, const iris::uip::ushort paramCount, const std::string paramName, const DataType dataType, const iris::uip::ushort arraySize = 1,
                         const UpdateType updateType = immanentParam, signed long minValue = 0, signed long maxValue = 0, signed long defaultValue = 0);
                         
  void normalizeString(char* baseAddress, iris::uip::ushort size);
  
  void setConfiguration(BaseConfiguration* config);
  
  BaseConfiguration* config;

  friend class BaseConfiguration;

//  ParameterGroup(const iris::uip::ushort groupId, const std::string& groupName);

  bool isValueValid(const iris::uip::ushort paramId, const ParameterDefinition* definition, const void* value);

  void _resetParam(ParameterDefinition* definition, const bool forceImmanentOverwrite = false);

  friend class InMemoryParameterAccessHandler;

public:

  iris::uip::ushort getArray(const iris::uip::ushort paramId, void* buffer, const DataType dataType) const;

  iris::uip::ushort setArray(const iris::uip::ushort paramId, const void* buffer, const DataType dataType);

  void setArrayParameterDefault(const iris::uip::ushort paramId, const void* defaultValue);

  void setArrayParameterDefault(const std::string& paramName, const void* defaultValue);

  void prepareForUse(void);

  void registerParameter(const iris::uip::ushort paramId,               // Parameter ID (innerhalb der Parametergruppe eindeutig)              
                         const std::string paramName,                   // Parametername                                                       
                         const DataType dataType,                       // Basis-Datentyp des Parameters (muss zu signed long kompatibel sein) 
                         const iris::uip::ushort arraySize = 1,         // Anzahl der Elemente vom Basis-Datentyp. 1, wenn kein Array          
                         const UpdateType updateType = immanentParam,   // Art der Beeinflussung des Parameterwertes bei Firmwareupdate        
                         signed long minValue = 0,                      // minimaler Wert                                                      
                         signed long maxValue = 0,                      // maximaler Wert                                                      
                         signed long defaultValue = 0);                 // Standardwert                                                        

  void setArrayParameterValidityCheckCallback(const iris::uip::ushort paramId, ARRAY_PARAMETER_VALIDITY_CHECK_CALLBACK callback);

  void setArrayParameterValidityCheckCallback(const std::string& paramName, ARRAY_PARAMETER_VALIDITY_CHECK_CALLBACK callback);

  void setIntegerParameterValidityCheckCallback(const iris::uip::ushort paramId, INTEGER_PARAMETER_VALIDITY_CHECK_CALLBACK callback);

  void setIntegerParameterValidityCheckCallback(const std::string& paramName, INTEGER_PARAMETER_VALIDITY_CHECK_CALLBACK callback);

  void setFloatingPointParameterValidityCheckCallback(const iris::uip::ushort paramId, FLOATING_POINT_PARAMETER_VALIDITY_CHECK_CALLBACK callback);

  void setFloatingPointParameterValidityCheckCallback(const std::string& paramName, FLOATING_POINT_PARAMETER_VALIDITY_CHECK_CALLBACK callback);

  bool isIntegerValueValid(const iris::uip::ushort paramId, const signed long value);

  bool isIntegerValueValid(const std::string& paramName, const signed long value);

  bool isFloatingPointValueValid(const iris::uip::ushort paramId, const signed long value);

  bool isFloatingPointValueValid(const std::string& paramName, const double value);

  bool isArrayValueValid(const iris::uip::ushort paramId, const signed long value);

  bool isArrayValueValid(const std::string& paramName, const double value);

  ParameterGroup(const iris::uip::ushort groupId, const std::string& groupName);

  virtual ~ParameterGroup();

  std::string getGroupName(void) const;

  iris::uip::ushort getGroupId(void) const;

  DataType getParamType(const iris::uip::ushort paramId) const;

  DataType getParamType(const std::string& paramName) const;

  std::string getParamName(const iris::uip::ushort paramId) const;

  iris::uip::ushort getParamId(const std::string& paramName) const;

  iris::uip::ushort getParamCount(void) const;

  iris::uip::ushort getParamId(const iris::uip::ushort index) const;

  void getParamIds(iris::uip::ushort* buffer) const;

  iris::uip::ushort getArraySize(const iris::uip::ushort paramId) const;

  iris::uip::ushort getArraySize(const std::string& paramName) const;

  bool getBoolValue(const iris::uip::ushort paramId) const;

  iris::uip::ubyte getUbyteValue(const iris::uip::ushort paramId) const;

  iris::uip::sbyte getSbyteValue(const iris::uip::ushort paramId) const;

  iris::uip::ushort getUshortValue(const iris::uip::ushort paramId) const;

  iris::uip::sshort getSshortValue(const iris::uip::ushort paramId) const;

  iris::uip::ulong getUlongValue(const iris::uip::ushort paramId) const;

  iris::uip::slong getSlongValue(const iris::uip::ushort paramId) const;

  iris::uip::ulonglong getUlonglongValue(const iris::uip::ushort paramId) const;

  iris::uip::slonglong getSlonglongValue(const iris::uip::ushort paramId) const;

  float getFloatValue(const iris::uip::ushort paramId) const;

  double getDoubleValue(const iris::uip::ushort paramId) const;

  void getBoolArray(const iris::uip::ushort paramId, bool* buffer) const;

  void getUbyteArray(const iris::uip::ushort paramId, iris::uip::ubyte* buffer) const;

  void getSbyteArray(const iris::uip::ushort paramId, iris::uip::sbyte* buffer) const;

  void getUshortArray(const iris::uip::ushort paramId, iris::uip::ushort* buffer) const;

  void getSshortArray(const iris::uip::ushort paramId, iris::uip::sshort* buffer) const;

  void getUlongArray(const iris::uip::ushort paramId, iris::uip::ulong* buffer) const;

  void getSlongArray(const iris::uip::ushort paramId, iris::uip::slong* buffer) const;

  void getUlonglongArray(const iris::uip::ushort paramId, iris::uip::ulonglong* buffer) const;

  void getSlonglongArray(const iris::uip::ushort paramId, iris::uip::slonglong* buffer) const;

  void getFloatArray(const iris::uip::ushort paramId, float* buffer) const;

  void getDoubleArray(const iris::uip::ushort paramId, double* buffer) const;

  void setBoolValue(const iris::uip::ushort paramId, const bool value);

  void setUbyteValue(const iris::uip::ushort paramId, const iris::uip::ubyte value);

  void setSbyteValue(const iris::uip::ushort paramId, const iris::uip::sbyte value);

  void setUshortValue(const iris::uip::ushort paramId, const iris::uip::ushort value);

  void setSshortValue(const iris::uip::ushort paramId, const iris::uip::sshort value);

  void setUlongValue(const iris::uip::ushort paramId, const iris::uip::ulong value);

  void setSlongValue(const iris::uip::ushort paramId, const iris::uip::slong value);

  void setUlonglongValue(const iris::uip::ushort paramId, const iris::uip::ulonglong value);

  void setSlonglongValue(const iris::uip::ushort paramId, const iris::uip::slonglong value);

  void setFloatValue(const iris::uip::ushort paramId, const float value);

  void setDoubleValue(const iris::uip::ushort paramId, const double value);

  void setBoolArray(const iris::uip::ushort paramId, const bool* values);

  void setUbyteArray(const iris::uip::ushort paramId, const iris::uip::ubyte* values);

  void setSbyteArray(const iris::uip::ushort paramId, const iris::uip::sbyte* values);

  void setUshortArray(const iris::uip::ushort paramId, const iris::uip::ushort* values);

  void setSshortArray(const iris::uip::ushort paramId, const iris::uip::sshort* values);

  void setUlongArray(const iris::uip::ushort paramId, const iris::uip::ulong* values);

  void setSlongArray(const iris::uip::ushort paramId, const iris::uip::slong* values);

  void setUlonglongArray(const iris::uip::ushort paramId, const iris::uip::ulonglong* values);

  void setSlonglongArray(const iris::uip::ushort paramId, const iris::uip::slonglong* values);

  void setFloatArray(const iris::uip::ushort paramId, const float* values);

  void setDoubleArray(const iris::uip::ushort paramId, const double* values);

  bool getBoolValue(const std::string& paramName) const;

  iris::uip::ubyte getUbyteValue(const std::string& paramName) const;

  iris::uip::sbyte getSbyteValue(const std::string& paramName) const;

  iris::uip::ushort getUshortValue(const std::string& paramName) const;

  iris::uip::sshort getSshortValue(const std::string& paramName) const;

  iris::uip::ulong getUlongValue(const std::string& paramName) const;

  iris::uip::slong getSlongValue(const std::string& paramName) const;

  iris::uip::ulonglong getUlonglongValue(const std::string& paramName) const;

  iris::uip::slonglong getSlonglongValue(const std::string& paramName) const;

  float getFloatValue(const std::string& paramName) const;

  double getDoubleValue(const std::string& paramName) const;

  void getBoolArray(const std::string& paramName, const bool* buffer) const;

  void getUbyteArray(const std::string& paramName, iris::uip::ubyte* buffer) const;

  void getSbyteArray(const std::string& paramName, iris::uip::sbyte* buffer) const;

  void getUshortArray(const std::string& paramName, iris::uip::ushort* buffer) const;

  void getSshortArray(const std::string& paramName, iris::uip::sshort* buffer) const;

  void getUlongArray(const std::string& paramName, iris::uip::ulong* buffer) const;

  void getSlongArray(const std::string& paramName, iris::uip::slong* buffer) const;

  void getUlonglongArray(const std::string& paramName, iris::uip::ulonglong* buffer) const;

  void getSlonglongArray(const std::string& paramName, iris::uip::slonglong* buffer) const;

  void getFloatArray(const std::string& paramName, float* buffer) const;

  void getDoubleArray(const std::string& paramName, double* buffer) const;

  void setBoolValue(const std::string& paramName, const bool value);

  void setUbyteValue(const std::string& paramName, const iris::uip::ubyte value);

  void setSbyteValue(const std::string& paramName, const iris::uip::sbyte value);

  void setUshortValue(const std::string& paramName, const iris::uip::ushort value);

  void setSshortValue(const std::string& paramName, const iris::uip::sshort value);

  void setUlongValue(const std::string& paramName, const iris::uip::ulong value);

  void setSlongValue(const std::string& paramName, const iris::uip::slong value);

  void setUlonglongValue(const std::string& paramName, const iris::uip::ulonglong value);

  void setSlonglongValue(const std::string& paramName, const iris::uip::slonglong value);

  void setFloatValue(const std::string& paramName, const float value);

  void setDoubleValue(const std::string& paramName, const double value);

  void setBoolArray(const std::string& paramName, const bool* values);

  void setUbyteArray(const std::string& paramName, const iris::uip::ubyte* values);

  void setSbyteArray(const std::string& paramName, const iris::uip::sbyte* values);

  void setUshortArray(const std::string& paramName, const iris::uip::ushort* values);

  void setSshortArray(const std::string& paramName, const iris::uip::sshort* values);

  void setUlongArray(const std::string& paramName, const iris::uip::ulong* values);

  void setSlongArray(const std::string& paramName, const iris::uip::slong* values);

  void setUlonglongArray(const std::string& paramName, const iris::uip::ulonglong* values);

  void setSlonglongArray(const std::string& paramName, const iris::uip::slonglong* values);

  void setFloatArray(const std::string& paramName, const float* values);

  void setDoubleArray(const std::string& paramName, const double* values);

  UpdateType getUpdateType(const std::string& paramName) const;

  signed long getMinValue(const std::string& paramName) const;

  float getFloatMinValue(const std::string& paramName) const;

  double getDoubleMinValue(const std::string& paramName) const;

  signed long getMaxValue(const std::string& paramName) const;

  float getFloatMaxValue(const std::string& paramName) const;

  double getDoubleMaxValue(const std::string& paramName) const;

  signed long getDefaultValue(const std::string& paramName) const;

  float getFloatDefaultValue(const std::string& paramName) const;

  double getDoubleDefaultValue(const std::string& paramName) const;

  const char* getStringDefaultValue(const std::string& paramName) const;

  UpdateType getUpdateType(const iris::uip::ushort paramId) const;

  signed long getMinValue(const iris::uip::ushort paramId) const;

  float getFloatMinValue(const iris::uip::ushort paramId) const;

  double getDoubleMinValue(const iris::uip::ushort paramId) const;

  signed long getMaxValue(const iris::uip::ushort paramId) const;

  float getFloatMaxValue(const iris::uip::ushort paramId) const;

  double getDoubleMaxValue(const iris::uip::ushort paramId) const;

  signed long getDefaultValue(const iris::uip::ushort paramId) const;
  
  float getFloatDefaultValue(const iris::uip::ushort paramId) const;
  
  double getDoubleDefaultValue(const iris::uip::ushort paramId) const;

  const char* getStringDefaultValue(const iris::uip::ushort paramId) const;

  void getFullParamInfo(const iris::uip::ushort paramId, DataType& dataType, iris::uip::ushort& arraySize, iris::uip::ushort& totalSize, UpdateType& updateType, signed long& minValue, signed long& maxValue, signed long& defaultValue) const;

  void getFullParamInfo(const std::string& paramName, DataType& dataType, iris::uip::ushort& arraySize, iris::uip::ushort& totalSize, UpdateType& updateType, signed long& minValue, signed long& maxValue, signed long& defaultValue) const;
  
  iris::uip::ushort getRawArray(const std::string& paramName, void* buffer) const;

  iris::uip::ushort getRawArray(const iris::uip::ushort paramId, void* buffer) const;

  iris::uip::ushort setRawArray(const std::string& paramName, const void* buffer);

  iris::uip::ushort setRawArray(const iris::uip::ushort paramId, const void* buffer);

  void setParamConstraints(const unsigned short paramId, const UpdateType updateType, const signed long minValue, const signed long maxValue, const signed long defaultValue);

  void setParamConstraints(const std::string& paramName, const UpdateType updateType, const signed long minValue, const signed long maxValue, const signed long defaultValue);

  bool getArrayParameterDefault(const iris::uip::ushort paramId, void* defaultBuffer) const;

  bool getArrayParameterDefault(const std::string& paramName, void* defaultBuffer) const;

  std::string createDebugInfoString(void) const;

  void writeDebugInfoToStream(std::ostream& os) const;

  void writeDebugInfoToConsole(void) const;

  void resetParam(const iris::uip::ushort paramId);

  void resetParam(const std::string& paramName);

  void reset(void);

  bool isParamKnown(const iris::uip::ushort paramId) const;

  bool isParamKnown(const std::string& paramName) const;

  bool isParamWithinLimits(const iris::uip::ushort paramId);

  bool isParamWithinLimits(const std::string paramName);

  ParameterGroup(ParameterGroup& source);

  //ParameterGroup& operator = (ParameterGroup& source);

  bool operator == (const ParameterGroup& other) const;

  bool operator != (const ParameterGroup& other) const;

  BaseConfiguration* getConfiguration(void) const;

}; // class ParameterGroup

class SENSORAPI BaseConfiguration {
  
public:
  typedef enum {    
    ConfigPassed = 0,
    ConfigFailed,
    FlashUnlockSectorFailed = 0xFE01,
    FlashEraseSectorFailed,
    FlashWriteCfgFailed,
    FlashWriteMagicFailed,
    FlashWriteParamFailed,
    FlashLockSectorFailed,
    NoParameterGroup,
  } ConfigurationResult;

protected:

  typedef std::map<iris::uip::ushort, ParameterGroup*> GroupMap;

  typedef std::map<std::string, iris::uip::ushort> NameIdMap;

  GroupMap parameterGroups;

  NameIdMap nameMap;

  void registerGroup(ParameterGroup* paramGroup);

  ConfigurationResult savePartToFlash(const bool immanent, const int sector, const bool eraseBeforeWriting, const unsigned long addressOffset);

  bool restorePartFromFlash(const bool setConfig, const bool immanent, const int sector, const unsigned long addressOffset, bool& newMagicFound, bool& paramsOK);

  static const unsigned long NEW_MAGIC_NUMBER = 0x434e4647;  // 'CNFG';

  static const unsigned long OLD_MAGIC_NUMBER = 0x43464721;  // 'CFG!';

  static const unsigned int crc32table[256];

  static unsigned int computeCrc32(unsigned short* start, unsigned int wordSize);
  
  bool immanentDataOverwriteAllowed;

  AbstractParameterAccessHandler* accessHandler;

public:

  typedef enum {bothConfigValid, primaryConfigInvalid, backupConfigInvalid, bothConfigInvalid} ConfigState;  

  void saveToFlash(void);

  ConfigurationResult saveConfigToFlash(void);

  bool restoreFromFlash(bool& backupActive, ConfigState& configState, bool& parameterValid);

  std::string getGroupName(const iris::uip::ushort groupId) const;

  iris::uip::ushort getGroupId(const std::string& groupName) const;

  const ParameterGroup* getParameterGroup(const iris::uip::ushort groupId) const;

  const ParameterGroup* getParameterGroup(const std::string& groupName) const;

  ParameterGroup* getWritableParameterGroup(const iris::uip::ushort groupId);

  ParameterGroup* getWritableParameterGroup(const std::string& groupName);

  iris::uip::ushort getGroupCount(void) const;

  iris::uip::ushort getGroupId(const iris::uip::ushort index) const;

  void getGroupIds(iris::uip::ushort* buffer) const;
  
  BaseConfiguration(AbstractParameterAccessHandler* accessHandler);

  virtual ~BaseConfiguration();
  
  bool isImmanentDataOverwriteAllowed(void);

  void unlockImmanentData(void);

  void lockImmanentData(void);

  std::string createDebugInfoString(void) const;

  void writeDebugInfoToStream(std::ostream& os) const;

  void writeDebugInfoToConsole(void) const;

  void reset(void);

  void clear(void);

  iris::uip::ulong getTotalParamCount(void);

  BaseConfiguration(const BaseConfiguration& source);

  BaseConfiguration& operator = (BaseConfiguration& source);

  bool operator == (const BaseConfiguration& other) const;

  bool operator != (const BaseConfiguration& other) const;

  AbstractParameterAccessHandler* getParameterAccessHandler(void) const;

}; // class BaseConfiguration

class InMemoryConfiguration: public BaseConfiguration {

public:

    InMemoryConfiguration();

    InMemoryConfiguration(const InMemoryConfiguration& source);

    InMemoryConfiguration& operator = (InMemoryConfiguration& source);

}; // class InMemoryConfiguration

typedef InMemoryConfiguration Configuration;

#ifndef __ADSPBLACKFIN__
class LiveConfiguration: public BaseConfiguration {

public:

    LiveConfiguration(iris::dist500::Dist500* dist500);

    LiveConfiguration(const LiveConfiguration& source);

    LiveConfiguration& operator = (LiveConfiguration& source);

}; // class LiveConfiguration
#endif

class SENSORAPI AbstractParameterAccessHandler {

public:

    virtual iris::uip::ushort getArray(const ParameterGroup* group, const iris::uip::ushort paramId, void* buffer, const ParameterGroup::DataType dataType) const = 0;

    virtual iris::uip::ushort setArray(ParameterGroup* group, const iris::uip::ushort paramId, const void* buffer, const ParameterGroup::DataType dataType) = 0;

    virtual AbstractParameterAccessHandler* clone(void) const = 0;

    virtual ~AbstractParameterAccessHandler() {}

}; // class AbstraceParameterAccessHandler

class SENSORAPI InMemoryParameterAccessHandler: public AbstractParameterAccessHandler {

public:

    iris::uip::ushort getArray(const ParameterGroup* group, const iris::uip::ushort paramId, void* buffer, const ParameterGroup::DataType dataType) const;

    iris::uip::ushort setArray(ParameterGroup *group, const iris::uip::ushort paramId, const void* buffer, const ParameterGroup::DataType dataType);

    AbstractParameterAccessHandler* clone(void) const;

}; // class InMemoryParameterAccessHandler

#ifndef __ADSPBLACKFIN__
class SENSORAPI LiveParameterAccessHandler: public AbstractParameterAccessHandler {

protected:

    iris::dist500::Dist500* dist500;

public:

    LiveParameterAccessHandler(iris::dist500::Dist500* dist500);

    iris::uip::ushort getArray(const ParameterGroup* group, const iris::uip::ushort paramId, void* buffer, const ParameterGroup::DataType dataType) const;

    iris::uip::ushort setArray(ParameterGroup *group, const iris::uip::ushort paramId, const void* buffer, const ParameterGroup::DataType dataType);

    iris::dist500::Dist500* getDist500(void) const;

    AbstractParameterAccessHandler* clone(void) const;

}; // class LiveParameterAccessHandler
#endif

} // namespace configuration

} // namespace iris

#endif // CONFIGURATION_CONFIGURATIONMANAGER_H
