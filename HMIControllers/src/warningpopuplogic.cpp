#include "warningpopuplogic.h"

#include <algorithm>
#include <mutex>

#include "sm_warningpopupdata.h"
#include "zl_log.h"

bool VehicleSignal::operator==(const VehicleSignal &other) const
{
    return m_signalName == other.m_signalName;
}
// I use this hash to make our code more clear, because without it, we should write a lot of if-else
// note the boost::any_cast may be throw an exception, so we should use try-catch to catch the exception
// but I think it is not necessary, because we have check the signal name before we call the setter
const std::unordered_map<std::string, std::function<void(boost::any)>> con_signalSetters = {
    {DRIVER_SIDE_IS_OPEN, [](boost::any value)
     { SharedMemory::door_Pop.setValue(boost::any_cast<bool>(value)); }},
    {SYSTEM_STATUS_IS_READY, [](boost::any value)
     { SharedMemory::door_Pop.setValue(boost::any_cast<bool>(value)); }},
    {ABNORMAL_TIER_STATE, [](boost::any value){
        auto tuple = boost::any_cast<std::tuple<v1::VSS::Chassis::Axle::TierState,
                        v1::VSS::Chassis::Axle::TierState, 
                        v1::VSS::Chassis::Axle::TierState, 
                        v1::VSS::Chassis::Axle::TierState>>(value);
        SharedMemory::TPMSPressureStaFL_Pop.setValue(std::get<0>(tuple));
        SharedMemory::TPMSPressureStaFR_Pop.setValue(std::get<1>(tuple));
        SharedMemory::TPMSPressureStaRL_Pop.setValue(std::get<2>(tuple));
        SharedMemory::TPMSPressureStaRR_Pop.setValue(std::get<3>(tuple));
    }},
    {SEAT_BELT_NOT_FASTENED, [](boost::any value)
     { SharedMemory::Seatbelt_Pop.setValue(boost::any_cast<bool>(value)); }},
    {BATTERY_LEVEL_IS_LOW, [](boost::any value)
     { SharedMemory::BatSOCRptWarning_Pop.setValue(boost::any_cast<bool>(value)); }}, 
    {TPMS_STATE_IS_ERROR, [](boost::any value)
    { SharedMemory::TPMSError_Pop.setValue(boost::any_cast<bool>(value)); }},
    {SRS_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::SRSError_Pop.setValue(boost::any_cast<bool>(value)); }},
    {ABS_IS_ERROR, [](boost::any value)
    { SharedMemory::ABSfailed_Pop.setValue(boost::any_cast<bool>(value)); }},
    {ESC_IS_ERROR, [](boost::any value)
    { SharedMemory::ESCFailed_Pop.setValue(boost::any_cast<bool>(value)); }},
    {HDC_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::HDCWorkSts_Pop.setValue(boost::any_cast<bool>(value)); }},
    {EBD_IS_ERROR, [](boost::any value)
    { SharedMemory::EBDFailed_Pop.setValue(boost::any_cast<bool>(value)); }},
    {AVH_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::AVHSts_Pop.setValue(boost::any_cast<bool>(value)); }},
    {EPS_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::BasicElecSteerFailed_Pop.setValue(boost::any_cast<bool>(value)); }},
    {CRUISE_CONTROL_IS_ERROR, [](boost::any value)
    { SharedMemory::CruiseCtrlStaError_Pop.setValue(boost::any_cast<bool>(value)); }},
    {ENGINE_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::EngineSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {TRANSMISSION_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::EngineSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {LIMP_HOME_STATUS_IS_LIMP_HOME, [](boost::any value)
    { SharedMemory::LimpHomeSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {TRACTION_BATTERY_TEMPERATURE_IS_WARNING, [](boost::any value)
    { SharedMemory::PwrTrainHighTempWrning_Pop.setValue(boost::any_cast<bool>(value)); }},
    {TRACTION_BATTERY_IS_GROUND_CONNECTED, [](boost::any value)
    { SharedMemory::PwrTrainConnectSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {ELECTRIC_MOTOR_TEMPERATURE_IS_WARNING, [](boost::any value)
    { SharedMemory::MotorHighTempWrning_Pop.setValue(boost::any_cast<bool>(value)); }},
    {TRACTION_BATTERY_IS_ERROR, [](boost::any value)
    { SharedMemory::BMSSysFailSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {ELECTRIC_MOTOR_IS_ERROR, [](boost::any value)
    { SharedMemory::DrvMotorSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {PCU_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::PCUFailSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {INSULATION_STATUS_IS_ERROR, [](boost::any value)
    { SharedMemory::InsulationWrning_Pop.setValue(boost::any_cast<bool>(value)); }},
    {PAS_IS_ERROR, [](boost::any value)
    { SharedMemory::PASwarn_Pop.setValue(boost::any_cast<bool>(value)); }},
    {PAS_SENSOR_STATE_IS_ERROR, [](boost::any value)
    { SharedMemory::PASSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {PEPS_STATUS_IS_WARNING, [](boost::any value)
    { SharedMemory::PEPSWarnSta_Pop.setValue(boost::any_cast<bool>(value)); }},
    {TIER_STATE_IS_VIRGIN, [](boost::any value)
    { SharedMemory::TPMSUnLearned_Pop.setValue(boost::any_cast<bool>(value)); }},
    {ABS_IS_OFF, [](boost::any value)
    { SharedMemory::TPMSUnLearned_Pop.setValue(boost::any_cast<bool>(value)); }},
    {HU_BRAKELIQUIDLEVEL_POP, [](boost::any value)
    { SharedMemory::HU_brakeliquidlevel_Pop.setValue(boost::any_cast<bool>(value)); }},
    {HIGH_COOLANT_TEMPERATURE_POP, [](boost::any value)
    { SharedMemory::highCoolantTemperature_Pop.setValue(boost::any_cast<bool>(value)); }},
    {LOW_FUEL_POP, [](boost::any value)
    { SharedMemory::lowFuel_Pop.setValue(boost::any_cast<bool>(value)); }},
    {HU_MACHINE_OIL_PRE_POP, [](boost::any value)
    { SharedMemory::HU_MachineOilPre_Pop.setValue(boost::any_cast<bool>(value)); }},
    {CRUISE_CONTROL_IS_ACTIVE, [](boost::any value)
    { SharedMemory::CruiseCtrlStaActive_Pop.setValue(boost::any_cast<bool>(value)); }},
    {VSP_IS_ENABLED, [](boost::any value)
    { SharedMemory::VSPsta_Pop.setValue(boost::any_cast<bool>(value)); }},
};

//we prepare some predefined values for reset Share Memory 
const std::unordered_map<std::string, boost::any> con_signalDefaultValues = {
    {DRIVER_SIDE_IS_OPEN, false},
    {SYSTEM_STATUS_IS_READY, false},
    {ABNORMAL_TIER_STATE, std::make_tuple(v1::VSS::Chassis::Axle::TierState::NOFAILURE,
                                         v1::VSS::Chassis::Axle::TierState::NOFAILURE,
                                         v1::VSS::Chassis::Axle::TierState::NOFAILURE,
                                         v1::VSS::Chassis::Axle::TierState::NOFAILURE)},
    {SEAT_BELT_NOT_FASTENED, false},
    {BATTERY_LEVEL_IS_LOW, false},
    {TPMS_STATE_IS_ERROR, false},
    {SRS_STATUS_IS_ERROR, false},
    {ABS_IS_ERROR, false},
    {ESC_IS_ERROR, false},
    {HDC_STATUS_IS_ERROR, false},
    {EBD_IS_ERROR, false},
    {AVH_STATUS_IS_ERROR, false},
    {EPS_STATUS_IS_ERROR, false},
    {CRUISE_CONTROL_IS_ERROR, false},
    {ENGINE_STATUS_IS_ERROR, false},
    {TRANSMISSION_STATUS_IS_ERROR, false},
    {LIMP_HOME_STATUS_IS_LIMP_HOME, false},
    {TRACTION_BATTERY_TEMPERATURE_IS_WARNING, false},
    {TRACTION_BATTERY_IS_GROUND_CONNECTED, false},
    {ELECTRIC_MOTOR_TEMPERATURE_IS_WARNING, false},
    {TRACTION_BATTERY_IS_ERROR, false},
    {ELECTRIC_MOTOR_IS_ERROR, false},
    {PCU_STATUS_IS_ERROR, false},
    {INSULATION_STATUS_IS_ERROR, false},
    {PAS_IS_ERROR, false},
    {PAS_SENSOR_STATE_IS_ERROR, false},
    {PEPS_STATUS_IS_WARNING, false},
    {TIER_STATE_IS_VIRGIN, false},
    {ABS_IS_OFF, false},
    {HU_BRAKELIQUIDLEVEL_POP, false},
    {HIGH_COOLANT_TEMPERATURE_POP, false},
    {LOW_FUEL_POP, false},
    {HU_MACHINE_OIL_PRE_POP, false},
    {CRUISE_CONTROL_IS_ACTIVE, false},
    {VSP_IS_ENABLED, false},
};

WarningPopupLogic::WarningPopupLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt)
    : m_checkCurWarning(io)
    , m_sidelOpenWarningTimer(io)
    , m_readyStatusWarningTimer(io)
    , m_tierStateWarningTimer(io)
    , m_rt(rt)
    , m_curWarning()
    , m_checkCurWarningCancelCount(0)
    , m_axle(m_rt->buildProxy<v1::VSS::Chassis::AxleProxy>("local", "VSS.Chassis.Axle"))
    , m_door(m_rt->buildProxy<v1::VSS::Cabin::DoorProxy>("local", "VSS.Cabin.Door"))
    , m_systemStatus(m_rt->buildProxy<v1::VSS::Vehicle::SystemStatusProxy>("local", "VSS.Vehicle.SystemStatus"))
    , m_vehicle(m_rt->buildProxy<v1::VSS::Vehicle::VehicleProxy>("local", "VSS.Vehicle.Vehicle"))
{
    m_checkCurWarning.expires_from_now(std::chrono::milliseconds(2500));
    m_checkCurWarning.async_wait(std::bind(&WarningPopupLogic::handleCurWarningTimeout, this));

    // start the timer at app lanuch stage, after 100ms, we will call the generateSidelOpenWarning function
    m_sidelOpenWarningTimer.expires_from_now(std::chrono::milliseconds(100));
    m_sidelOpenWarningTimer.async_wait(std::bind(&WarningPopupLogic::generateSidelOpenWarning, this));

    m_readyStatusWarningTimer.expires_from_now(std::chrono::milliseconds(100));
    m_readyStatusWarningTimer.async_wait(std::bind(&WarningPopupLogic::generateReadyStatusWarning, this));
}

WarningPopupLogic::~WarningPopupLogic()
{
}
bool WarningPopupLogic::removeVehicleSignal(const VehicleSignal &signal)
{
    std::lock_guard<std::mutex> lock(getVehicleSignalQueueMutex());
    auto it = std::find(m_vehicleSignalQueue.begin(), m_vehicleSignalQueue.end(), signal);
    if (it != m_vehicleSignalQueue.end())
    {
        m_vehicleSignalQueue.erase(it);
        return true;
    }
    return false;
}
void WarningPopupLogic::enqueueVehicleSignal(const VehicleSignal &signal)
{
    std::lock_guard<std::mutex> lock(getVehicleSignalQueueMutex());
    if (m_curWarning.m_signalName == DEFAULT_SIGNAL_VALUE)
    {   // if the current warning is NULL, we will handle the signal immediately
        m_curWarning = signal;
        handleSignal(signal);
        return;
    }
    m_vehicleSignalQueue.push_back(signal);
}
void WarningPopupLogic::handleCurWarningTimeout()
{
    logDebug("handleCurWarningTimerout");

    // why we use a gruad? because we want to reset the timer when we leave this function, and we can not reset the timer in the callback function
    // why the timeout is 2500ms? because we want to handle the vehicle signal as soon as possible, and we do not want to handle the vehicle signal too frequently
    // because the minimal hint time in HMI is 2500ms, we have set the timeout to 2500ms
    auto g = gruad(m_checkCurWarning, this, 2500, &WarningPopupLogic::handleCurWarningTimeout);

    // The first step is to determine whether the current warning should be cancelled. There are two scenarios in which cancellation is necessary: 
    // firstly, when a signal with higher priority is received;
    // and secondly, when the cancellation count for the current signal is reached.
    VehicleSignal lastVehicleSignal;
    {
        // in there we lock the vehicle signal queue, because it may be modified by other thread
        // but I think should not lock it for a long time, so we just lock it for a short time
        std::lock_guard<std::mutex> lock(getVehicleSignalQueueMutex());

        if (m_vehicleSignalQueue.empty())
        {
            if (m_checkCurWarningCancelCount < m_curWarning.m_cancelCount)
            {
                //we reset current warning to null warning
                m_curWarning.clear();
            }
            logDebug("m_vehicleSignalQueue is empty");
            return;
        }
        auto hightestPrioritySignalIterator = std::max_element(m_vehicleSignalQueue.begin(), m_vehicleSignalQueue.end());
        // if current higheset priority vehicle signal's priority is lower than current warning's priority and current warning is not cancelable
        // then add current warning count. at last time, if current warning count is greater than vehicle signal's cancel count,
        // then we can cancel current warning
        if (hightestPrioritySignalIterator->m_priority <= m_curWarning.m_priority && m_checkCurWarningCancelCount < m_curWarning.m_cancelCount)
        {
            logDebug("m_checkCurWarningCancelCount: %d", m_checkCurWarningCancelCount);
            logDebug("vehicleSignal name: %s", hightestPrioritySignalIterator->m_signalName.c_str());
            m_checkCurWarningCancelCount++;
            return;
        }
        //The signal will be pushed to the end of the queue if the cancel count is -1, indicating its continuity
        if (m_curWarning.m_cancelCount == -1)
        {   //The function enqueueVehicleSignal should be avoided in that context due to its potential to cause a deadlock
            m_vehicleSignalQueue.push_back(m_curWarning);
        }
        // in there, we assign current warning to vehicle signal, and reset current warning count
        lastVehicleSignal = m_curWarning;
        m_curWarning = *hightestPrioritySignalIterator;
        m_checkCurWarningCancelCount = 0;
        // we pop the vehicle signal from queue to indicate that we have handled this vehicle signal
        m_vehicleSignalQueue.erase(hightestPrioritySignalIterator);
    }

    if (lastVehicleSignal != m_curWarning)
    {
        // if last vehicle signal is not equal to current warning, then we should reset the last vehicle signal
        auto it = con_signalSetters.find(lastVehicleSignal.m_signalName);
        if (it != con_signalSetters.end())
        {
            //we find the predefined value for reset Share Memory
            auto defaultValueIt = con_signalDefaultValues.find(lastVehicleSignal.m_signalName);
            it->second(defaultValueIt->second);
        }
        else
        {
            logError("can not find the setter for signal: %s", lastVehicleSignal.m_signalName.c_str());
        }
    }

    // in there we set the current warning
    handleSignal(m_curWarning);
}

/*
   \brief generate a warning when the sidel is open
    if the vehicle speed is greater than 5km/h, and the sidel is open, then generate a warning
*/
void WarningPopupLogic::generateSidelOpenWarning()
{
    auto g = gruad(m_checkCurWarning, this, 100, &WarningPopupLogic::generateSidelOpenWarning);

    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo(5 * 1000);

    // in there we should check current warning is SidleOpenWarning or not, if it is, then we should not generate a new one
    if (m_curWarning.m_signalName == DRIVER_SIDE_IS_OPEN)
    {
        logDebug("current warning is SidleOpenWarning, we should not generate a new one");
        return;
    }

    // in there we get all sidel status from data service one by one
    VSS::Type::Type::BooleanValue row1DriverSideIsOpen;
    m_door->getRow1DriverSideIsOpenAttribute().getValue(callStatus, row1DriverSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow1DriverSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row1DriverSideIsOpen: %s", row1DriverSideIsOpen.toString());
    }

    VSS::Type::Type::BooleanValue row1PassengerSideIsOpen;
    m_door->getRow1PassengerSideIsOpenAttribute().getValue(callStatus, row1PassengerSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow1PassengerSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row1PassengerSideIsOpen: %s", row1PassengerSideIsOpen.toString());
    }

    VSS::Type::Type::BooleanValue row2DriverSideIsOpen;
    m_door->getRow2DriverSideIsOpenAttribute().getValue(callStatus, row2DriverSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow2DriverSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row2DriverSideIsOpen: %s", row2DriverSideIsOpen.toString());
    }

    VSS::Type::Type::BooleanValue row2PassengerSideIsOpen;
    m_door->getRow2PassengerSideIsOpenAttribute().getValue(callStatus, row2PassengerSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow2PassengerSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row2PassengerSideIsOpen: %s", row2PassengerSideIsOpen.toString());
    }

    // aquire the vehicle speed from data service
    float HU_DisvehicleSpeed;
    m_vehicle->getSpeedAttribute().getValue(callStatus, HU_DisvehicleSpeed, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getSpeedAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("HU_DisvehicleSpeed: %f", HU_DisvehicleSpeed);
    }

    VehicleSignal vehicleSignal(VehicleSignal::SIDEL_OPEN_WARNING_PRIORITY, VehicleSignal::VEHICLE_SIGNAL_TYPE_MIN, true, 1, DRIVER_SIDE_IS_OPEN);
    if ((row1DriverSideIsOpen == VSS::Type::Type::BooleanValue::TRUE || row1PassengerSideIsOpen == VSS::Type::Type::BooleanValue::TRUE ||
         row2DriverSideIsOpen == VSS::Type::Type::BooleanValue::TRUE || row2PassengerSideIsOpen == VSS::Type::Type::BooleanValue::TRUE) &&
        HU_DisvehicleSpeed > 5)
    {
        logDebug("generate a SidelOpenWarning");
        enqueueVehicleSignal(vehicleSignal);
    }
    else
    {
        // remove the SidelOpenWarning from queue
        removeVehicleSignal(vehicleSignal);
    }
}

void WarningPopupLogic::generateReadyStatusWarning()
{
    auto g = gruad(m_checkCurWarning, this, 100, &WarningPopupLogic::generateReadyStatusWarning);

    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo(5 * 1000);

    // in there we should check current warning is SidleOpenWarning or not, if it is, then we should not generate a new one
    if (m_curWarning.m_signalName == SYSTEM_STATUS_IS_READY)
    {
        logDebug("current warning is SidleOpenWarning, we should not generate a new one");
        return;
    }

    // in there we get all sidel status from data service one by one
    VSS::Type::Type::BooleanValue row1DriverSideIsOpen;
    m_door->getRow1DriverSideIsOpenAttribute().getValue(callStatus, row1DriverSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow1DriverSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row1DriverSideIsOpen: %s", row1DriverSideIsOpen.toString());
    }

    VSS::Type::Type::BooleanValue row1PassengerSideIsOpen;
    m_door->getRow1PassengerSideIsOpenAttribute().getValue(callStatus, row1PassengerSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow1PassengerSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row1PassengerSideIsOpen: %s", row1PassengerSideIsOpen.toString());
    }

    VSS::Type::Type::BooleanValue row2DriverSideIsOpen;
    m_door->getRow2DriverSideIsOpenAttribute().getValue(callStatus, row2DriverSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow2DriverSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row2DriverSideIsOpen: %s", row2DriverSideIsOpen.toString());
    }

    VSS::Type::Type::BooleanValue row2PassengerSideIsOpen;
    m_door->getRow2PassengerSideIsOpenAttribute().getValue(callStatus, row2PassengerSideIsOpen, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getRow2PassengerSideIsOpenAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("row2PassengerSideIsOpen: %s", row2PassengerSideIsOpen.toString());
    }

    v1::VSS::Vehicle::SystemStatus::VehicleReadyStatus PTActlOprtMode;
    m_systemStatus->getReadyStatusAttribute().getValue(callStatus, PTActlOprtMode, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logError("getReadyStatusAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("PTActlOprtMode: %s", PTActlOprtMode.toString());
    }

    VehicleSignal vehicleSignal(VehicleSignal::READY_STATUS_WARNING_PRIORITY, VehicleSignal::VEHICLE_SIGNAL_TYPE_MIN, true, 1, SYSTEM_STATUS_IS_READY);
    if ((row1DriverSideIsOpen == VSS::Type::Type::BooleanValue::TRUE || row1PassengerSideIsOpen == VSS::Type::Type::BooleanValue::TRUE ||
         row2DriverSideIsOpen == VSS::Type::Type::BooleanValue::TRUE || row2PassengerSideIsOpen == VSS::Type::Type::BooleanValue::TRUE) &&
        PTActlOprtMode == v1::VSS::Vehicle::SystemStatus::VehicleReadyStatus::READY)
    {
        logDebug("generate a ReadyStatusWarning");
        enqueueVehicleSignal(vehicleSignal);
    }
    else
    {
        // remove the ReadyStatusWarning from queue
        removeVehicleSignal(vehicleSignal);
    }
}

void WarningPopupLogic::generateTierStateWarning()
{
    logDebug("generateTierStateWarning");
    auto g = gruad(m_checkCurWarning, this, 100, &WarningPopupLogic::generateTierStateWarning);

    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo(5 * 1000);

    // in there we should check current warning is TierStateWarning or not, if it is, then we should not generate a new one
    if (m_curWarning.m_signalName == ABNORMAL_TIER_STATE)
    {
        logDebug("current warning is TierStateWarning, we should not generate a new one");
        return;
    }

        //左前胎压状态
    v1::VSS::Chassis::Axle::TierState TPMSPressureStaFL;
    m_axle->getRow1WheelLeftTierStateAttribute().getValue(callStatus, TPMSPressureStaFL, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getRow1WheelLeftTierStateAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("TPMSPressureStaFL value: %s", TPMSPressureStaFL.toString());
    }

    //右前胎压状态
    v1::VSS::Chassis::Axle::TierState TPMSPressureStaFR;
    m_axle->getRow1WheelRightTierStateAttribute().getValue(callStatus, TPMSPressureStaFR, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getRow1WheelLeftTierStateAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("TPMSPressureStaFR value: %s", TPMSPressureStaFR.toString());
    }

    //左后胎压状态
    v1::VSS::Chassis::Axle::TierState TPMSPressureStaRL;
    m_axle->getRow2WheelLeftTierStateAttribute().getValue(callStatus, TPMSPressureStaRL, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getRow2WheelLeftTierStateAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("TPMSPressureStaRL value: %s", TPMSPressureStaRL.toString());
    }

    //右后胎压状态
    v1::VSS::Chassis::Axle::TierState TPMSPressureStaRR;
    m_axle->getRow2WheelRightTierStateAttribute().getValue(callStatus, TPMSPressureStaRR, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getRow2WheelRightTierStateAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("TPMSPressureStaRR value: %s", TPMSPressureStaRR.toString());
    }

    std::tuple<v1::VSS::Chassis::Axle::TierState, 
    v1::VSS::Chassis::Axle::TierState, 
    v1::VSS::Chassis::Axle::TierState,
    v1::VSS::Chassis::Axle::TierState> 
    tierStateTuple(TPMSPressureStaFL, TPMSPressureStaFR, TPMSPressureStaRL, TPMSPressureStaRR);

    VehicleSignal vehicleSignal(VehicleSignal::TIER_STATE_WARNING_PRIORITY, VehicleSignal::VEHICLE_SIGNAL_TYPE_MIN, true, 1, ABNORMAL_TIER_STATE);
    // If there are no failures in every tier, we should remove the TierStateWarning named TierStateWarning from the queue; 
    // otherwise, we should add the TierStateWarning with a priority of 0x14 to the queue.
    if (TPMSPressureStaFL == v1::VSS::Chassis::Axle::TierState::NOFAILURE &&
        TPMSPressureStaFR == v1::VSS::Chassis::Axle::TierState::NOFAILURE &&
        TPMSPressureStaRL == v1::VSS::Chassis::Axle::TierState::NOFAILURE &&
        TPMSPressureStaRR == v1::VSS::Chassis::Axle::TierState::NOFAILURE)
    {
        logDebug("remove the TierStateWarning from queue");
        removeVehicleSignal(vehicleSignal);
    }
    else
    {
        logDebug("add the TierStateWarning to queue");
        enqueueVehicleSignal(vehicleSignal);
    }
}

void WarningPopupLogic::handleSignal(const VehicleSignal &signal)
{
    //we find the corresponding signal setter in unordered_map and call it.
    auto it = con_signalSetters.find(signal.m_signalName);
    if (it != con_signalSetters.end())
    {
        it->second(signal.m_signalValue);
    }
    else
    {
        logError("can not find the corresponding signal setter");
    }
}