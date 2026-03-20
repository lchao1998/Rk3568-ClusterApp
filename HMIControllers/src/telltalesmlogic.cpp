#include "telltalesmlogic.h"

#ifdef USE_EASY_PROFILER
#include <easy/profiler.h>
#endif

#include <zl_log.h>

#include "sm_telltalesm.h"

std::shared_ptr<v1::VSS::ADAS::CruiseControlProxy<>> m_cruiseControl;

TelltalesmLogic::TelltalesmLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt)
    : m_wather(io)
    , m_rt(rt)
    , m_abs(m_rt->buildProxy<v1::VSS::ADAS::ABSProxy>("local", "VSS.ADAS.ABS"))
    , m_axle(m_rt->buildProxy<v1::VSS::Chassis::AxleProxy>("local", "VSS.Chassis.Axle"))
    , m_cruiseControl(m_rt->buildProxy<v1::VSS::ADAS::CruiseControlProxy>("local", "VSS.ADAS.CruiseControl"))
    , m_combustionEngine(m_rt->buildProxy<v1::VSS::Powertrain::CombustionEngineProxy>("local", "VSS.Powertrain.CombustionEngine"))
    , m_esc(m_rt->buildProxy<v1::VSS::ADAS::ESCProxy>("local", "VSS.ADAS.ESC"))
    , m_edb(m_rt->buildProxy<v1::VSS::ADAS::EBDProxy>("local", "VSS.ADAS.EBD"))
    , m_electricMotorProxy(m_rt->buildProxy<v1::VSS::Powertrain::ElectricMotorProxy>("local", "VSS.Powertrain.ElectricMotor"))
    , m_identifier(m_rt->buildProxy<v1::VSS::Identifier::IdentifierProxy>("local", "VSS.Identifier.Identifier"))
    , m_lights(m_rt->buildProxy<v1::VSS::Body::LightsProxy>("local", "VSS.Body.Lights"))
    , m_parkingBrake(m_rt->buildProxy<v1::VSS::Chassis::ParkingBrakeProxy>("local", "VSS.Chassis.ParkingBrake"))
    , m_seat(m_rt->buildProxy<v1::VSS::Cabin::SeatProxy>("local", "VSS.Cabin.Seat"))
    , m_systemStatus(m_rt->buildProxy<v1::VSS::Vehicle::SystemStatusProxy>("local", "VSS.Vehicle.SystemStatus"))
    , m_tractionBatteryProxy(m_rt->buildProxy<v1::VSS::Powertrain::TractionBatteryProxy>("local", "VSS.Powertrain.TractionBattery"))
    , m_vsp(m_rt->buildProxy<v1::VSS::ADAS::VSPProxy>("local", "VSS.ADAS.VSP"))
    , m_clusterAudioCtrl(m_rt->buildProxy<v1::ClusterAudio::ClusterAudioCtrlProxy>("local", "ClusterAudio.ClusterAudioCtrl"))
    , m_clusterAudioInfo(m_rt->buildProxy<v1::ClusterAudio::ClusterAudioInfoProxy>("local", "ClusterAudio.ClusterAudioInfo"))
{
    registerAttributeChanged();
    m_wather.expires_from_now(std::chrono::milliseconds(500));
    m_wather.async_wait(std::bind(&TelltalesmLogic::pullValue, this));
}

void TelltalesmLogic::registerAttributeChanged()
{
    // new interfaces
    m_cruiseControl->getIsActiveAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleIsActiveChanged, this, std::placeholders::_1));
    m_cruiseControl->getIsErrorAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleIsErrorChanged, this, std::placeholders::_1));
    m_systemStatus->getPEPSStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handlePEPSWarnStateChanged, this, std::placeholders::_1));
    m_systemStatus->getTPMSStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleTPMSStaChanged, this, std::placeholders::_1));
    m_systemStatus->getSRSStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleSRSErrorChanged, this, std::placeholders::_1));
    m_systemStatus->getLowVoltageBatteryStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleLowbatterychargeChanged, this, std::placeholders::_1));
    m_systemStatus->getEngineStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleEngineStaChanged, this, std::placeholders::_1));
    m_systemStatus->getTransmissionStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleTransStaChanged, this, std::placeholders::_1));
    m_axle->getRow1WheelLeftTierStateAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleTPMSPressureStaFLChanged, this, std::placeholders::_1));
    m_axle->getRow2WheelRightTierStateAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleTPMSPressureStaRRChanged, this, std::placeholders::_1));
    m_abs->getIsErrorAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleABSfailedChanged, this, std::placeholders::_1));
    m_abs->getIsEnabledAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handlePALAresponseChanged, this, std::placeholders::_1));
    m_abs->getIsEngagedAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleESPActiveStaChanged, this, std::placeholders::_1));
    m_esc->getIsErrorAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleESCFailedChanged, this, std::placeholders::_1));
    m_systemStatus->getHDCStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleHDCWorkStsChanged, this, std::placeholders::_1));
    m_edb->getIsErrorAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleEBDFailedChanged, this, std::placeholders::_1));
    m_systemStatus->getAVHStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleAVHStsChanged, this, std::placeholders::_1));
    m_systemStatus->getEPSStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleBasicElecSteerFailedChanged, this, std::placeholders::_1));
    m_systemStatus->getEPCStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleEPCwarnChanged, this, std::placeholders::_1));
    m_tractionBatteryProxy->getIsChargingCableConnectedAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleInletConnctStaChanged, this, std::placeholders::_1));
    m_systemStatus->getLimpHomeStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleLimpHomeStaChanged, this, std::placeholders::_1));
    m_tractionBatteryProxy->getTemperatureIsWarningAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handlePwrTrainHighTempWrningChanged, this, std::placeholders::_1));
    m_tractionBatteryProxy->getIsPowerConnectedAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleIsPowerConnectedChanged, this, std::placeholders::_1));
    m_tractionBatteryProxy->getIsGroundConnectedAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleIsGroundConnectedChanged, this, std::placeholders::_1));
    m_electricMotorProxy->getTemperatureIsWarningAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleMotorHighTempWrningChanged, this, std::placeholders::_1));
    m_tractionBatteryProxy->getIsErrorAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleBMSSysFailStaChanged, this, std::placeholders::_1));
    m_electricMotorProxy->getIsErrorAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleDrvMotorStaChanged, this, std::placeholders::_1));
    m_systemStatus->getPCUStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handlePCUFailStaChanged, this, std::placeholders::_1));
    m_systemStatus->getInsulationStatusAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleInsulationWrningChanged, this, std::placeholders::_1));
    m_vsp->getIsEnabledAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleVSPstaChanged, this, std::placeholders::_1));
    m_lights->getBeamLowIsOnAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleLowbeamChanged, this, std::placeholders::_1));
    m_lights->getBeamHighIsOnAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleHighbeamChanged, this, std::placeholders::_1));
    m_lights->getBeamFlashIsOnAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleFlashbeamChanged, this, std::placeholders::_1));
    m_lights->getPositionLampIsOnAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handlePositionlampChanged, this, std::placeholders::_1));
    m_lights->getFogFrontIsOnAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleFrontFogLampStaChanged, this, std::placeholders::_1));
    m_lights->getFogRearIsOnAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleRearFogLampStaChanged, this, std::placeholders::_1));
    m_lights->getBeamHighAutoIsOnAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleAutohighbeamChanged, this, std::placeholders::_1));
    m_parkingBrake->getIsEngagedAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleParkLampStaChanged, this, std::placeholders::_1));
    m_identifier->getIMMOResultAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleIMMOPCUauthenChanged, this, std::placeholders::_1));
    m_axle->getRow1WheelLeftBrakeFluidLevelStateAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleHU_brakeliquidlevelChanged, this, std::placeholders::_1));
    m_axle->getRow2WheelRightTierStateAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleTPMSPressureStaRRChanged, this, std::placeholders::_1));
    m_tractionBatteryProxy->getStateOfChargeDisplayedAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleBatSOCRptChanged, this, std::placeholders::_1));
    m_combustionEngine->getEOCRAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleHU_engineoilChanged, this, std::placeholders::_1));
    m_combustionEngine->getECTAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleHU_EngCoolantTempChanged, this, std::placeholders::_1));
    m_combustionEngine->getEOPStateAttribute().getChangedEvent().subscribe(std::bind(&TelltalesmLogic::handleMachineOilPreChanged, this, std::placeholders::_1));
}

void TelltalesmLogic::handlePEPSWarnStateChanged(const v1::VSS::Vehicle::SystemStatus::PEPSWorkStatus& PEPSWarnSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("PEPSWarnSta-------------------------- value: %s", PEPSWarnSta.toString());
    switch (PEPSWarnSta)
    {
    case v1::VSS::Vehicle::SystemStatus::PEPSWorkStatus::Literal::WARNING:
        SharedMemory::PEPSWarnSta.setValue(true);
        break;
    default: 
        SharedMemory::PEPSWarnSta.setValue(false);
        break;
    }
    logDebug("SharedMemory::PEPSWarnSta-------------------------- value: %d", SharedMemory::PEPSWarnSta.getValue());
}

void TelltalesmLogic::handleTPMSStaChanged(const v1::VSS::Vehicle::SystemStatus::TPMSWorkStatus& TPMSSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("TPMSSta value: %s", TPMSSta.toString());

    switch (TPMSSta)
    {
    case v1::VSS::Vehicle::SystemStatus::TPMSWorkStatus::Literal::ERROR:
        SharedMemory::TPMSSta.setValue(1);
        break;
    case v1::VSS::Vehicle::SystemStatus::TPMSWorkStatus::Literal::VIRGIN:
        SharedMemory::TPMSSta.setValue(2);
        break;
    default: 
        SharedMemory::TPMSSta.setValue(0);
        break;
    }
}

void TelltalesmLogic::handleTPMSPressureStaFLChanged(const uint8_t &TPMSPressureStaFL)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("TPMSPressureStaFL value: %d", TPMSPressureStaFL);
    SharedMemory::TPMSPressureStaFL.setValue(TPMSPressureStaFL);
}

void TelltalesmLogic::handleTPMSPressureStaFRChanged(const uint8_t &TPMSPressureStaFR)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("TPMSPressureStaFR value: %d", TPMSPressureStaFR);
    SharedMemory::TPMSPressureStaFR.setValue(TPMSPressureStaFR);
}

void TelltalesmLogic::handleTPMSPressureStaRLChanged(const uint8_t &TPMSPressureStaRL)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("TPMSPressureStaRL value: %d", TPMSPressureStaRL);
    SharedMemory::TPMSPressureStaRL.setValue(TPMSPressureStaRL);
}

void TelltalesmLogic::handleTPMSPressureStaRRChanged(const uint8_t &TPMSPressureStaRR)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("TPMSPressureStaRR value: %d", TPMSPressureStaRR);
    SharedMemory::TPMSPressureStaRR.setValue(TPMSPressureStaRR);
}

void TelltalesmLogic::handleSRSErrorChanged(const v1::VSS::Vehicle::SystemStatus::SRSWorkStatus& SRSError)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("SRSError value: %s", SRSError.toString());

    switch (SRSError)
    {
    case v1::VSS::Vehicle::SystemStatus::SRSWorkStatus::Literal::ERROR:
        SharedMemory::SRSError.setValue(true);
        break;
    default: 
        SharedMemory::SRSError.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleLowbatterychargeChanged(const v1::VSS::Vehicle::SystemStatus::LowVoltageBatteryWorkStatus& lowbatterycharge)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("lowbatterycharge value: %s", lowbatterycharge.toString());

    switch (lowbatterycharge)
    {
    case v1::VSS::Vehicle::SystemStatus::LowVoltageBatteryWorkStatus::Literal::DISCHARGE:
        SharedMemory::lowbatterycharge.setValue(true);
        break;
    default: 
        SharedMemory::lowbatterycharge.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleABSfailedChanged(VSS::Type::Type::BooleanValue ABSfailed)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("ABSfailed value: %s", ABSfailed.toString());

    switch (ABSfailed)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::ABSfailed.setValue(true);
        break;
    default: 
        SharedMemory::ABSfailed.setValue(false);
        break;
    }
}

void TelltalesmLogic::handlePALAresponseChanged(VSS::Type::Type::BooleanValue PALAresponse)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("PALAresponse value: %s", PALAresponse.toString());

    switch (PALAresponse)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::PALAresponse.setValue(true);
        break;
    default: 
        SharedMemory::PALAresponse.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleESPActiveStaChanged(VSS::Type::Type::BooleanValue ESPActiveSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("ESPActiveSta value: %s", ESPActiveSta.toString());

    switch (ESPActiveSta)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::ESPActiveSta.setValue(true);
        break;
    default: 
        SharedMemory::ESPActiveSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleESCFailedChanged(VSS::Type::Type::BooleanValue ESCFailed)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("ESCFailed value: %s", ESCFailed.toString());

    switch (ESCFailed)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::ESCFailed.setValue(true);
        break;
    default: 
        SharedMemory::ESCFailed.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleHDCWorkStsChanged(const v1::VSS::Vehicle::SystemStatus::HDCWorkStatus& HDCWorkSts)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HDCWorkSts value: %s", HDCWorkSts.toString());
    
    SharedMemory::HDCWorkSts.setValue(static_cast<int>(HDCWorkSts) - 1);
}

void TelltalesmLogic::handleEBDFailedChanged(VSS::Type::Type::BooleanValue EBDFailed)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("EBDFailed value: %s", EBDFailed.toString());

    switch (EBDFailed)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::EBDFailed.setValue(true);
        break;
    default: 
        SharedMemory::EBDFailed.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleAVHStsChanged(const v1::VSS::Vehicle::SystemStatus::AVHWorkStatus &AVHSts)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("AVHSts value: %s", AVHSts.toString());
    SharedMemory::AVHSts.setValue(static_cast<uint>(AVHSts) - 1);
}

void TelltalesmLogic::handleBasicElecSteerFailedChanged(const v1::VSS::Vehicle::SystemStatus::EPSWorkStatus& BasicElecSteerFailed)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("BasicElecSteerFailed value: %s", BasicElecSteerFailed.toString());

    switch (BasicElecSteerFailed)
    {
    case v1::VSS::Vehicle::SystemStatus::EPSWorkStatus::FAILED:
        SharedMemory::BasicElecSteerFailed.setValue(true);
        break;
    default: 
        SharedMemory::BasicElecSteerFailed.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleEPCwarnChanged(const v1::VSS::Vehicle::SystemStatus::EPCWorkStatus& EPCwarn)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("EPCwarn value: %s", EPCwarn.toString());
    
    switch (EPCwarn)
    {
    case v1::VSS::Vehicle::SystemStatus::EPCWorkStatus::WARNING:
        SharedMemory::EPCwarn.setValue(true);
        break;
    default: 
        SharedMemory::EPCwarn.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleInletConnctStaChanged(VSS::Type::Type::BooleanValue InletConnctSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("InletConnctSta value: %s", InletConnctSta.toString());

    switch (InletConnctSta)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::InletConnctSta.setValue(true);
        break;
    default: 
        SharedMemory::InletConnctSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleLimpHomeStaChanged(const v1::VSS::Vehicle::SystemStatus::LimpHomeWorkStatus& LimpHomeSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("LimpHomeSta value: %s", LimpHomeSta.toString());

    switch (LimpHomeSta)
    {
    case v1::VSS::Vehicle::SystemStatus::LimpHomeWorkStatus::LIMPHOME:
        SharedMemory::LimpHomeSta.setValue(true);
        break;
    default: 
        SharedMemory::LimpHomeSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handlePwrTrainHighTempWrningChanged(VSS::Type::Type::BooleanValue PwrTrainHighTempWrning)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("PwrTrainHighTempWrning value: %s", PwrTrainHighTempWrning.toString());

    switch (PwrTrainHighTempWrning)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::PwrTrainHighTempWrning.setValue(true);
        break;
    default: 
        SharedMemory::PwrTrainHighTempWrning.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleIsPowerConnectedChanged(const ::VSS::Type::Type::BooleanValue &IsPowerConnected)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("IsPowerConnected value: %s", IsPowerConnected.toString());    
    switch (IsPowerConnected)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::PwrTrainConnectSta.setValue(true);
        break;
    default: 
        SharedMemory::PwrTrainConnectSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleIsGroundConnectedChanged(const ::VSS::Type::Type::BooleanValue &IsGroundConnected)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

logDebug("IsGroundConnected value: %s", IsGroundConnected.toString());
switch (IsGroundConnected)
{
case VSS::Type::Type::BooleanValue::Literal::TRUE:
    SharedMemory::PwrTrainConnectSta.setValue(false);
    break;
default: 
    SharedMemory::PwrTrainConnectSta.setValue(false);
    break;
    }
}

void TelltalesmLogic::handleMotorHighTempWrningChanged(VSS::Type::Type::BooleanValue MotorHighTempWrning)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("MotorHighTempWrning value: %s", MotorHighTempWrning.toString());

    switch (MotorHighTempWrning)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::MotorHighTempWrning.setValue(true);
        break;
    default: 
        SharedMemory::MotorHighTempWrning.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleBMSSysFailStaChanged(VSS::Type::Type::BooleanValue BMSSysFailSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("BMSSysFailSta value: %s", BMSSysFailSta.toString());

    switch (BMSSysFailSta)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::BMSSysFailSta.setValue(true);
        break;
    default: 
        SharedMemory::BMSSysFailSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleDrvMotorStaChanged(VSS::Type::Type::BooleanValue DrvMotorSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("DrvMotorSta value: %s", DrvMotorSta.toString());

    switch (DrvMotorSta)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::DrvMotorSta.setValue(true);
        break;
    default: 
        SharedMemory::DrvMotorSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handlePCUFailStaChanged(const v1::VSS::Vehicle::SystemStatus::PCUWorkStatus& PCUFailSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("PCUFailSta value: %s", PCUFailSta.toString());
    
    switch (PCUFailSta)
    {
    case v1::VSS::Vehicle::SystemStatus::PCUWorkStatus::Literal::ERROR:
        SharedMemory::PCUFailSta.setValue(true);
        break;
    default: 
        SharedMemory::PCUFailSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleInsulationWrningChanged(const v1::VSS::Vehicle::SystemStatus::InsulationWorkStatus& InsulationWrning)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("InsulationWrning value: %s", InsulationWrning.toString());

    switch (InsulationWrning)
    {
    case v1::VSS::Vehicle::SystemStatus::InsulationWorkStatus::Literal::ERROR:
        SharedMemory::InsulationWrning.setValue(true);
        break;
    default: 
        SharedMemory::InsulationWrning.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleVSPstaChanged(VSS::Type::Type::BooleanValue VSPsta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("VSPsta value: %s", VSPsta.toString());

    switch (VSPsta)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::VSPsta.setValue(true);
        break;
    default: 
        SharedMemory::VSPsta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleLowbeamChanged(VSS::Type::Type::BooleanValue lowbeam)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("lowbeam value: %s", lowbeam.toString());

    switch (lowbeam)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::lowbeam.setValue(true);
        break;
    case VSS::Type::Type::BooleanValue::Literal::FASLE:
        SharedMemory::lowbeam.setValue(false);
        break;
    default:
        break;
    }
}

void TelltalesmLogic::handleHighbeamChanged(VSS::Type::Type::BooleanValue highbeam)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("highbeam value: %s", highbeam.toString());

    switch (highbeam)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::highbeam.setValue(true);
        break;
    case VSS::Type::Type::BooleanValue::Literal::FASLE:
        SharedMemory::highbeam.setValue(false);
        break;
    default:
            break;
    }
}

void TelltalesmLogic::handleFlashbeamChanged(VSS::Type::Type::BooleanValue Flashbeam)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("Flashbeam value: %s", Flashbeam.toString());
    
    switch (Flashbeam)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::Flashbeam.setValue(true);
        break;
    default: 
        SharedMemory::Flashbeam.setValue(false);
        break;
    }
}

void TelltalesmLogic::handlePositionlampChanged(VSS::Type::Type::BooleanValue positionlamp)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("positionlamp value: %s", positionlamp.toString());

    switch (positionlamp)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::positionlamp.setValue(true);
        break;
    case VSS::Type::Type::BooleanValue::Literal::FASLE:
        SharedMemory::positionlamp.setValue(false);
        break;
    default:
        break;
    }
}

void TelltalesmLogic::handleFrontFogLampStaChanged(VSS::Type::Type::BooleanValue FrontFogLampSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("FrontFogLampSta value: %s", FrontFogLampSta.toString());

    switch (FrontFogLampSta)
    {
        case VSS::Type::Type::BooleanValue::Literal::TRUE:
            SharedMemory::FrontFogLampSta.setValue(true);
            break;
        case VSS::Type::Type::BooleanValue::Literal::FASLE:
            SharedMemory::FrontFogLampSta.setValue(false);
            break;
        default:
            break;
    }
}

void TelltalesmLogic::handleRearFogLampStaChanged(VSS::Type::Type::BooleanValue rearFogLampSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("rearFogLampSta value: %s", rearFogLampSta.toString());

    switch (rearFogLampSta)
    {
     case VSS::Type::Type::BooleanValue::Literal::TRUE:
         SharedMemory::rearFogLampSta.setValue(true);
         break;
     case VSS::Type::Type::BooleanValue::Literal::FASLE:
         SharedMemory::rearFogLampSta.setValue(false);
         break;
     default:
         break;
    }
}

void TelltalesmLogic::handleAutohighbeamChanged(VSS::Type::Type::BooleanValue autohighbeam)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("autohighbeam value: %s", autohighbeam.toString());
    
    switch (autohighbeam)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::autohighbeam.setValue(true);
        break;
    default: 
        SharedMemory::autohighbeam.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleParkLampStaChanged(VSS::Type::Type::BooleanValue ParkLampSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("ParkLampSta value: %s", ParkLampSta.toString());

    switch (ParkLampSta)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::ParkLampSta.setValue(true);
        break;
    default: 
        SharedMemory::ParkLampSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleIMMOPCUauthenChanged(const v1::VSS::Identifier::Identifier::IMMOResultType& IMMOPCUauthen)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("IMMOPCUauthen value: %s", IMMOPCUauthen.toString());

    switch (IMMOPCUauthen)
    {
    case v1::VSS::Identifier::Identifier::IMMOResultType::Literal::NOTPASS:
        SharedMemory::IMMOPCUauthen.setValue(true);
        break;
    default: 
        SharedMemory::IMMOPCUauthen.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleHU_brakeliquidlevelChanged(const v1::VSS::Chassis::Axle::FluidLevelState& HU_brakeliquidlevel)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("IMMOPCUauthen value: %s", HU_brakeliquidlevel.toString());
    
    switch (HU_brakeliquidlevel)
    {
    case v1::VSS::Chassis::Axle::FluidLevelState::Literal::LOW:
        SharedMemory::HU_brakeliquidlevel.setValue(true);
        break;
    default: 
        SharedMemory::HU_brakeliquidlevel.setValue(false);
        break;
    }
}
void TelltalesmLogic::handleBatSOCRptChanged(const uint8_t &BatSOCRpt)
{

    logDebug("BatSOCRpt value: %d", BatSOCRpt);
    if (BatSOCRpt < 10)
    {
        SharedMemory::BatSOCRptWarning.setValue(true);
    }
    else
    {
        SharedMemory::BatSOCRptWarning.setValue(false);
    }
}
void TelltalesmLogic::handleHU_engineoilChanged(const uint8_t &HU_engineoil)
{
    if (HU_engineoil <= 10)
    {
        SharedMemory::lowFuel.setValue(true);
    }
    else
    {
        SharedMemory::lowFuel.setValue(false);
    }
}
void TelltalesmLogic::handleHU_EngCoolantTempChanged(const int32_t &HU_EngCoolantTemp)
{
    static bool sta_isWarning = false;

    if (HU_EngCoolantTemp > 120)
    {
        SharedMemory::highCoolantTemperature.setValue(true);
        sta_isWarning = true;
    }
    else if (sta_isWarning && HU_EngCoolantTemp >= 100)
    {
        SharedMemory::highCoolantTemperature.setValue(true);
    }
    else
    {
        SharedMemory::highCoolantTemperature.setValue(false);
        sta_isWarning = false;
    }
}

void TelltalesmLogic::handleEngineStaChanged(const v1::VSS::Vehicle::SystemStatus::EngineWorkStatus& EngineSta)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("EngineSta value: %s", EngineSta.toString());
    
    switch (EngineSta)
    {
    case v1::VSS::Vehicle::SystemStatus::EngineWorkStatus::Literal::ERROR:
        SharedMemory::EngineSta.setValue(true);
        break;
    default: 
        SharedMemory::EngineSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleTransStaChanged(const v1::VSS::Vehicle::SystemStatus::TransmissionWorkStatus& TransSta)
{
    #ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("TransSta value: %s", TransSta.toString());
    
    switch (TransSta)
    {
    case v1::VSS::Vehicle::SystemStatus::TransmissionWorkStatus::Literal::ERROR:
        SharedMemory::TransSta.setValue(true);
        break;
    default: 
        SharedMemory::TransSta.setValue(false);
        break;
    }
}

void TelltalesmLogic::handleIsActiveChanged(VSS::Type::Type::BooleanValue isActive)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("isActive value: %s", isActive.toString());
    
    switch (isActive)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::CruiseCtrlSta.setValue(2);
        break;
    default:
        SharedMemory::CruiseCtrlSta.setValue(0); 
        break;
    }
}
void TelltalesmLogic::handleIsEnabledChanged(VSS::Type::Type::BooleanValue IsEnabled)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("IsEnabled value: %s", IsEnabled.toString());
    
    switch (IsEnabled)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::CruiseCtrlSta.setValue(1);
        break;
    default:
        SharedMemory::CruiseCtrlSta.setValue(0); 
        break;
    }
}

void TelltalesmLogic::handleIsErrorChanged(VSS::Type::Type::BooleanValue isError)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("isError value: %s", isError.toString());
    
    switch (isError)
    {
    case VSS::Type::Type::BooleanValue::Literal::TRUE:
        SharedMemory::CruiseCtrlSta.setValue(3);
        break;
    default:
        SharedMemory::CruiseCtrlSta.setValue(0);  
        break;
    }
}

void TelltalesmLogic::handleMachineOilPreChanged(const ::v1::VSS::Powertrain::CombustionEngine::EOPStateType &HU_MachineOilPre)
{
    #ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    logDebug("HU_MachineOilPre value: %s", HU_MachineOilPre.toString());
    
    switch (HU_MachineOilPre)
    {
    case ::v1::VSS::Powertrain::CombustionEngine::EOPStateType::Literal::LOW:
        SharedMemory::HU_MachineOilPre.setValue(true);
        break;
    default:
        SharedMemory::HU_MachineOilPre.setValue(false); 
        break;
    }
}

void TelltalesmLogic::pullValue()
{
    struct gruad {
        gruad(boost::asio::steady_timer &t, TelltalesmLogic *th) : m_wather(t), m_th(th){}
        ~gruad() {
            logDebug("expires_from_now 100");
            m_wather.expires_from_now(std::chrono::milliseconds(200));
            m_wather.async_wait(std::bind(&TelltalesmLogic::pullValue, m_th));
        }
        boost::asio::steady_timer &m_wather;
        TelltalesmLogic *m_th;
    };
    auto g = gruad(m_wather, this);


    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo(5 * 1000);

    if (!m_clusterAudioCtrl->isAvailable())
        return;

    VSS::Type::Type::BooleanValue directionIndicatorLeftIsSignaling;
    m_lights->getDirectionIndicatorLeftIsSignalingAttribute().getValue(callStatus, directionIndicatorLeftIsSignaling, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getDirectionIndicatorLeftIsSignalingAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("directionIndicatorLeftIsSignaling value: %s", directionIndicatorLeftIsSignaling.toString());
    }

    bool result;
    std::vector<std::string> audioPaths;
    audioPaths.push_back("/usr/share/sounds/Turn-02-ON.wav");
    audioPaths.push_back("/usr/share/sounds/Turn-02-OFF.wav");
    if (directionIndicatorLeftIsSignaling == VSS::Type::Type::BooleanValue::Literal::TRUE) {
        SharedMemory::leftTurnlamp.setValue(true);

        auto handler = [this, audioPaths](const CommonAPI::CallStatus& callStatus, const bool& result){
            if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                logWarning("callStatus = %d", static_cast<int>(callStatus));
                return;
            }
            if (!result)
                logWarning("invoke audio control stop failed!!!!");

            auto handler = [](const CommonAPI::CallStatus& callStatus, const bool& result){
                if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                    logWarning("callStatus = %d", static_cast<int>(callStatus));
                    return;
                }
                if (!result)
                    logWarning("invoke audio control play failed!!!!");

            };

            CommonAPI::CallInfo callInfo(5 * 1000);
            //warn one level.
            m_clusterAudioCtrl->PlayAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT,
                                          audioPaths,
                                          ::ClusterAudioType::Types::PlayType::Literal::REPEAT,
                                          500,
                                          120000, handler, &callInfo);
        };

        m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT, handler, &callInfo);
    } else {
        SharedMemory::leftTurnlamp.setValue(false);

        auto handler = [this](const CommonAPI::CallStatus& callStatus, const bool& result){
            if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                logWarning("callStatus = %d", static_cast<int>(callStatus));
                return;
            }
            if (!result)
                logWarning("invoke audio control stop failed!!!!");
        };

        m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT, handler, &callInfo);
    }

    VSS::Type::Type::BooleanValue directionIndicatorRightIsSignaling;
    m_lights->getDirectionIndicatorRightIsSignalingAttribute().getValue(callStatus, directionIndicatorRightIsSignaling, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getDirectionIndicatorLeftIsSignalingAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("directionIndicatorRightIsSignaling value: %s", directionIndicatorRightIsSignaling.toString());
    }
    
    if (directionIndicatorRightIsSignaling == VSS::Type::Type::BooleanValue::Literal::TRUE) {
        SharedMemory::rightTurnlamp.setValue(true);

        auto handler = [this, audioPaths](const CommonAPI::CallStatus& callStatus, const bool& result){
            if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                logWarning("callStatus = %d", static_cast<int>(callStatus));
                return;
            }
            if (!result)
                logWarning("invoke audio control stop failed!!!!");

            auto handler = [](const CommonAPI::CallStatus& callStatus, const bool& result){
                if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                    logWarning("callStatus = %d", static_cast<int>(callStatus));
                    return;
                }
                if (!result)
                    logWarning("invoke audio control play failed!!!!");

            };

            CommonAPI::CallInfo callInfo(5 * 1000);
            //warn one level.
            m_clusterAudioCtrl->PlayAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT,
                                          audioPaths,
                                          ::ClusterAudioType::Types::PlayType::Literal::REPEAT,
                                          500,
                                          120000, handler, &callInfo);
        };

        m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT, handler, &callInfo);

    } else {
        SharedMemory::rightTurnlamp.setValue(0);

        auto handler = [this](const CommonAPI::CallStatus& callStatus, const bool& result){
            if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                logWarning("callStatus = %d", static_cast<int>(callStatus));
                return;
            }
            if (!result)
                logWarning("invoke audio control stop failed!!!!");
        };

        m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT, handler, &callInfo);
    }

    if (directionIndicatorLeftIsSignaling != VSS::Type::Type::BooleanValue::Literal::TRUE && 
        directionIndicatorRightIsSignaling != VSS::Type::Type::BooleanValue::Literal::TRUE) {
        SharedMemory::rightTurnlamp.setValue(0);

        auto handler = [this](const CommonAPI::CallStatus& callStatus, const bool& result){
            if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                logWarning("callStatus = %d", static_cast<int>(callStatus));
                return;
            }
            if (!result)
                logWarning("invoke audio control stop failed!!!!");
        };

        m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT, handler, &callInfo);
    }

    VSS::Type::Type::BooleanValue hazardIsSignaling;
    m_lights->getHazardIsSignalingAttribute().getValue(callStatus, hazardIsSignaling, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getHazardIsSignalingAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("getHazardIsSignalingAttribute value: %s", hazardIsSignaling.toString());
    }
    static VSS::Type::Type::BooleanValue sta_lastStatus;
    if (hazardIsSignaling != VSS::Type::Type::BooleanValue::Literal::UNKNOWN) {
        sta_lastStatus = hazardIsSignaling;
    } else {
        hazardIsSignaling = sta_lastStatus;
    }
    switch (hazardIsSignaling) {
        case VSS::Type::Type::BooleanValue::Literal::TRUE:
        {
            SharedMemory::hazardIsSignaling.setValue(true);

            auto handler = [this, audioPaths](const CommonAPI::CallStatus& callStatus, const bool& result){
                if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                    logWarning("callStatus = %d", static_cast<int>(callStatus));
                    return;
                }
                if (!result)
                    logWarning("invoke audio control stop failed!!!!");

                auto handler = [](const CommonAPI::CallStatus& callStatus, const bool& result){
                    if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                        logWarning("callStatus = %d", static_cast<int>(callStatus));
                        return;
                    }
                    if (!result)
                        logWarning("invoke audio control play failed!!!!");


                };

                CommonAPI::CallInfo callInfo(5 * 1000);
                //warn one level.
                m_clusterAudioCtrl->PlayAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT,
                                              audioPaths,
                                              ::ClusterAudioType::Types::PlayType::Literal::REPEAT,
                                              500,
                                              120000, handler, &callInfo);
            };

            m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT, handler, &callInfo);
            break;
        }
        case VSS::Type::Type::BooleanValue::Literal::FASLE:
        {
            SharedMemory::hazardIsSignaling.setValue(false);

            auto handler = [this](const CommonAPI::CallStatus& callStatus, const bool& result){
                if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                    logWarning("callStatus = %d", static_cast<int>(callStatus));
                    return;
                }
                if (!result)
                    logWarning("invoke audio control stop failed!!!!");
            };

            m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::DIRECTION_INDICATOR_OR_HAZARD_LIGHT, handler, &callInfo);
            break;
        }
        case VSS::Type::Type::BooleanValue::Literal::UNKNOWN:
        {
            break;
        }
    }
}