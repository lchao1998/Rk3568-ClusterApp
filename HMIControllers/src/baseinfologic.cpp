#include "baseinfologic.h"

#ifdef USE_EASY_PROFILER
#include <easy/profiler.h>
#endif

#include <zl_log.h>

#include "tracecategories.h"
#include "sm_baseinfodata.h"
#include "sm_gaugedata.h"

BaseInfoLogic::BaseInfoLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt)
    : m_wather(io)
    , m_rt(rt)
    , m_combustionEngine(m_rt->buildProxy<v1::VSS::Powertrain::CombustionEngineProxy>("local", "VSS.Powertrain.CombustionEngine"))
    , m_exterior(m_rt->buildProxy<v1::VSS::Vehicle::ExteriorProxy>("local", "VSS.Vehicle.Exterior"))
    , m_electricMotor(m_rt->buildProxy<v1::VSS::Powertrain::ElectricMotorProxy>("local", "VSS.Powertrain.ElectricMotor"))
    , m_systemStatus(m_rt->buildProxy<v1::VSS::Vehicle::SystemStatusProxy>("local", "VSS.Vehicle.SystemStatus"))
    , m_transmission(m_rt->buildProxy<v1::VSS::Powertrain::TransmissionProxy>("local", "VSS.Powertrain.Transmission"))
    , m_vehicle(m_rt->buildProxy<v1::VSS::Vehicle::VehicleProxy>("local", "VSS.Vehicle.Vehicle"))
{
    registerProperties();
}
/*!
    \note 检查范围
*/
void BaseInfoLogic::handleHU_TotalodometerChanged(float HU_Totalodometer)
{
#ifdef USING_PERFETTO_LIBRARY
    TRACE_EVENT_BEGIN("dataserver", "HU_Totalodometer");
#endif
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HU_Totalodometer value: %f", HU_Totalodometer);
    if (HU_Totalodometer < 0)
    {
        HU_Totalodometer = 0;
    }
    else if (HU_Totalodometer > 2000000)
    {
        HU_Totalodometer = 2000000;
    }
    SharedMemory::HU_Totalodometer.setValue(HU_Totalodometer);
#ifdef USING_PERFETTO_LIBRARY
    TRACE_EVENT_END("dataserver");
#endif
}

void BaseInfoLogic::handleHU_TripAOdometerChanged(float HU_TripAOdometer)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HU_TripAOdometer value: %f", HU_TripAOdometer);
    SharedMemory::HU_TripAOdometer.setValue(HU_TripAOdometer);
}
void BaseInfoLogic::handleHU_TripBOdometerChanged(float HU_TripBOdometer)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HU_TripBOdometer value: %f", HU_TripBOdometer);
}
void BaseInfoLogic::handleHU_TripOdometerChanged(float HU_TripOdometer)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HU_TripOdometer value: %f", HU_TripOdometer);
}
void BaseInfoLogic::handleRevSpeedChanged(int revSpeed)
{
#ifdef USING_PERFETTO_LIBRARY
    TRACE_EVENT_BEGIN("dataserver", "revSpeed");
#endif
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("revSpeed value: %d", revSpeed);
    SharedMemory::revSpeed.setValue(revSpeed);
#ifdef USING_PERFETTO_LIBRARY
    TRACE_EVENT_END("dataserver");
#endif
}
void BaseInfoLogic::handleEnvirTempChanged(int EnvirTemp)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("EnvirTemp value: %d", EnvirTemp);
    SharedMemory::EnvirTemp.setValue(EnvirTemp);
}
void BaseInfoLogic::handleEnvirTempV(VSS::Type::Type::BooleanValue EnvirTempV)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("EnvirTempV value: %s", EnvirTempV.toString());
        if (EnvirTempV == 2) {
        SharedMemory::EnvirTempV.setValue(true);
    } else {
        SharedMemory::EnvirTempV.setValue(false);
    }
}
void BaseInfoLogic::handleTranGearPos(float TranGearPos)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    static std::unordered_map<int, int> sta_gearIndex = {
            {0xD, 0},
            {0xF, 1},
            {0xE, 2},
            {0x0, 3},
            {0x1, 4},
            {0x2, 5},
            {0x3, 6},
            {0x4, 7},
            {0x5, 8},
            {0x6, 9},
            { 16, 10},
    };

    auto it = sta_gearIndex.find(TranGearPos);
    if (it == sta_gearIndex.end())
        return;

    logDebug("TranGearPos value: %f", static_cast<float>(it->second));
    SharedMemory::TranGearPos.setValue(static_cast<float>(it->second));
}
void BaseInfoLogic::handleHU_engineoil(int HU_engineoil)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HU_engineoil value: %d", HU_engineoil);
    if (HU_engineoil < 10)
    {
        SharedMemory::HU_oilNotEnough.setValue(true);
        logDebug("oil not enough");
    }
    else
    {
        logDebug("oil availeble");
        SharedMemory::HU_oilNotEnough.setValue(false);
    }
    SharedMemory::HU_engineoil.setValue(HU_engineoil);
}
void BaseInfoLogic::handleHU_EngCoolantTemp(int HU_EngCoolantTemp)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HU_EngCoolantTemp value: %d", HU_EngCoolantTemp);
    if (HU_EngCoolantTemp < 0)
        HU_EngCoolantTemp = 0;
    if (HU_EngCoolantTemp > 150)
        HU_EngCoolantTemp = 150;
    if (HU_EngCoolantTemp > 120)
    {
        SharedMemory::HU_highWaterTemp.setValue(true);
    }
    else
    {
        SharedMemory::HU_highWaterTemp.setValue(false);
    }
    SharedMemory::HU_EngCoolantTemp.setValue(HU_EngCoolantTemp);
}
void BaseInfoLogic::handledrivemode(const ::v1::VSS::Powertrain::Transmission::VehiclePerformanceMode & drivemode)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("drivemode value: %s", drivemode.toString());
    SharedMemory::drivemode.setValue(static_cast<int>(drivemode) - 1);
}
void BaseInfoLogic::handlePTActlOprtMode(const v1::VSS::Vehicle::SystemStatus::VehicleReadyStatus &PTActlOprtMode)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("PTActlOprtMode value: %s", PTActlOprtMode.toString());

    SharedMemory::PTActlOprtMode.setValue(static_cast<int>(PTActlOprtMode) - 1);
}
void BaseInfoLogic::handleMotorPowerChanged(int MotorPower)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("MotorPower value: %d", MotorPower);
    SharedMemory::MotorPower.setValue(MotorPower);
}
void BaseInfoLogic::handleMotorPowerTypeChanged(VSS::Type::Type::BooleanValue MotorPowerType)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("MotorPowerType value: %s", MotorPowerType.toString());
    if (MotorPowerType == 2) {
        SharedMemory::MotorPowerType.setValue(true);
    } else {
        SharedMemory::MotorPowerType.setValue(false);
    }
}
void BaseInfoLogic::handleRecupLevelStaChanged(const ::v1::VSS::Vehicle::SystemStatus::RECUPWorkStatus &recupLevelSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("recupLevelSta value: %s", recupLevelSta.toString());
    SharedMemory::recupLevelSta.setValue(static_cast<int>(recupLevelSta) - 1);
}
void BaseInfoLogic::handlePowerStaChanged(const ::v1::VSS::Vehicle::Vehicle::LowVoltageSystemStateType &PowerSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("PowerSta value: %s", PowerSta.toString());
    SharedMemory::PowerSta.setValue(static_cast<int>(PowerSta) - 1);
}
void BaseInfoLogic::hanleSppedChanged(const float &HU_DisvehicleSpeed)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("HU_DisvehicleSpeed value: %f", HU_DisvehicleSpeed);
    SharedMemory::HU_DisvehicleSpeed.setValue(static_cast<int>(HU_DisvehicleSpeed));
}
void BaseInfoLogic::registerProperties()
{
    // the new interfaces
    m_vehicle->getTraveledDistanceAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleHU_TotalodometerChanged, this, std::placeholders::_1));
    m_vehicle->getTripAAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleHU_TripAOdometerChanged, this, std::placeholders::_1));
    m_vehicle->getTripBAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleHU_TripBOdometerChanged, this, std::placeholders::_1));
    m_vehicle->getTraveledDistanceSinceStartAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleHU_TripOdometerChanged, this, std::placeholders::_1));
    m_vehicle->getLowVoltageSystemStateAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handlePowerStaChanged, this, std::placeholders::_1));
    m_vehicle->getSpeedAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::hanleSppedChanged, this, std::placeholders::_1));
    m_exterior->getAirTemperatureAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleEnvirTempChanged, this, std::placeholders::_1));
    m_exterior->getAirTemperatureIsValidAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleEnvirTempV, this, std::placeholders::_1));
    m_transmission->getSelectedGearAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleTranGearPos, this, std::placeholders::_1));
    m_transmission->getPerformanceModeAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handledrivemode, this, std::placeholders::_1));
    m_combustionEngine->getEOCRAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleHU_engineoil, this, std::placeholders::_1));
    m_combustionEngine->getECTAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleHU_EngCoolantTemp, this, std::placeholders::_1));
    m_systemStatus->getReadyStatusAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handlePTActlOprtMode, this, std::placeholders::_1));
    m_systemStatus->getRECUPStatusAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleRecupLevelStaChanged, this, std::placeholders::_1));
    m_electricMotor->getPowerAttribute().getChangedEvent().subscribe(std::bind(&BaseInfoLogic::handleMotorPowerChanged, this, std::placeholders::_1));
}