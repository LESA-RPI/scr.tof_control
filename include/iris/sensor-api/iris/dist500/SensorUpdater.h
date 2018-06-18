#ifndef SENSORUPDATER_H
#define SENSORUPDATER_H

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

#include <stdint.h> // for uint32_t

// iris includes
#include "iris/dist500/Dist500.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace uip {
    class UipUpdateErrorMessage;
}

namespace dist500 {

/**
 * @brief The UpdaterState enum
 * Additionally, there is a waiting for restart boolean
 */
enum UpdaterState {
    UPDATER_STATE_START,
    UPDATER_STATE_CONNECTIVITY_CHECK,
    UPDATER_STATE_CLEANING_CHECK,
    UPDATER_STATE_CLEANING_FINALIZE,
    UPDATER_STATE_CLEANING_RESTARTABLE,
    UPDATER_STATE_REQUESTING_INSTALL,
    UPDATER_STATE_RUNNING,
    UPDATER_STATE_RUNNING_FINALIZABLE,
    UPDATER_STATE_RUNNING_RESTARTABLE,
    UPDATER_STATE_RUNNING_RESTART_ERROR,
    UPDATER_STATE_FINALIZING_ERROR,
    UPDATER_STATE_FINALIZED,
    UPDATER_STATE_FAILED
};

// todo move to class namespace
typedef void (*CALLBACK_UPDATESTATUSMESSAGE) (const std::string& str);
typedef void (*CALLBACK_UPDATEPROGRESSMESSAGE) (uint8_t step, float stepProgress);

/**
 * @brief The SensorUpdater class
 */
class SensorUpdater : virtual public Dist500Base
{
public:
    SensorUpdater(iris::drivers::Sensor& sensor);
    ~SensorUpdater();
    
    /**
     * @brief setFileUri
     * @param fileUri
     */
    void setFileUri(const std::string& fileUri);
    
    /**
     * @brief runUpdate
     * @param retryAttempts If set to greater than 1, retries will be attempted.
     */
    void runUpdate(unsigned int retryAttempts = 1);
    
    void finalizeFailedUpdate();
    
    /**
     * @brief isDone Returns whether the update has stopped and will not go on (success or failure).
     * @return True if the update is done, but it can mean success of failure.
     */
    bool isDone() const {return m_isUpdateDone;}
    
    bool isSuccess() const {return UPDATER_STATE_FINALIZED == m_state;}
    
    /**
     * @brief getUpdateId Returns the update id that is currently used for the update.
     * @return 
     * @note If several attempts are made, the update id will be renewed for each new attempt. This method returns only the most recent id.
     */
    std::string getUpdateId() const {return m_uniqueUpdateId;}
    
    void setStatusMessageCallback(CALLBACK_UPDATESTATUSMESSAGE cb) {m_cbUpdateStatus = cb;}
    void setProgressCallback(CALLBACK_UPDATEPROGRESSMESSAGE cb) {m_cbUpdateProgress = cb;}
    
    std::string getUpdateLog() const {return m_logString;}
    
private:
    SensorUpdater();// forbid
    SensorUpdater(const SensorUpdater&);// forbid
    SensorUpdater& operator=(const SensorUpdater&);// forbid
    
    void generateUpdateId();
    bool printSensorIpInfo(iris::dist500::Dist500& d5);
    void logUpdateError(iris::uip::UipUpdateErrorMessage* errorReply);
    
    void logStatus(const std::string& str);
    void nextStep();
    void setProgress(float progress);

    uint64_t getElapsedMsSinceBoot();
    uint64_t getElapsedMsInEpoch();
    uint64_t getElapsedMsInAttempt();
    uint64_t getElapsedMsInStep();
    
    SENSOR_RESULT checkUnfinalizedUpdate();
    SENSOR_RESULT finalizeUnfinalizedUpdate();
    SENSOR_RESULT requestInstallUpdate();
    SENSOR_RESULT waitDuringInstallation();
    SENSOR_RESULT finalizeInstallation();
    SENSOR_RESULT checkConnection();
    SENSOR_RESULT restartSensor();
    void processStates();
    std::string stringFromUpdateStatus(iris::uip::update_status_enumeration val);
    
    mutable iris::synchronization::Mutex m_receiveMutex;
    CALLBACK_UPDATESTATUSMESSAGE m_cbUpdateStatus;
    CALLBACK_UPDATEPROGRESSMESSAGE m_cbUpdateProgress;
    std::string m_logString;
    std::string m_fileUri;
    
    UpdaterState m_state;
    unsigned int m_currentStep;
    unsigned int m_totalSteps;
    float m_currentStepProgress;
    uint64_t m_timeAttemptStart;
    uint64_t m_timeStepStart;
    bool m_isUpdateDone;
    /**
     * @brief m_attempts The number of attempts that the update was tried
     */
    unsigned int m_attempts;
    unsigned int m_attemptsLeft;
    unsigned int m_restartsLeft;
    std::string m_uniqueUpdateId;
    std::string m_queriedUpdateId;
    bool m_queriedUpdate;
    unsigned char m_senderUip;
};

}

}

#endif // SENSORUPDATER_H
