#ifndef TELLTALESM_LOGIC_H
#define TELLTALESM_LOGIC_H

#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

#include <CommonAPI/CommonAPI.hpp>

#include <v1/ClusterAudio/ClusterAudioCtrlProxy.hpp>
#include <v1/ClusterAudio/ClusterAudioInfoProxy.hpp>

#include <v1/VSS/ADAS/ABSProxy.hpp>
#include <v1/VSS/Chassis/AxleProxy.hpp>
#include <v1/VSS/ADAS/CruiseControlProxy.hpp>
#include <v1/VSS/Powertrain/CombustionEngineProxy.hpp>
#include <v1/VSS/ADAS/ESCProxy.hpp>
#include <v1/VSS/ADAS/EBDProxy.hpp>
#include <v1/VSS/Powertrain/ElectricMotorProxy.hpp>
#include <v1/VSS/Identifier/IdentifierProxy.hpp>
#include <v1/VSS/Body/LightsProxy.hpp>
#include <v1/VSS/Chassis/ParkingBrakeProxy.hpp>
#include <v1/VSS/Cabin/SeatProxy.hpp>
#include <v1/VSS/Vehicle/SystemStatusProxy.hpp>
#include <v1/VSS/Powertrain/TractionBatteryProxy.hpp>
#include <v1/VSS/ADAS/VSPProxy.hpp>

class TelltalesmLogic
{
public:
    TelltalesmLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt);

public:
    void registerAttributeChanged();
    void handlePEPSWarnStateChanged(const v1::VSS::Vehicle::SystemStatus::PEPSWorkStatus& PEPSWarnSta);
    void handleTPMSStaChanged(const v1::VSS::Vehicle::SystemStatus::TPMSWorkStatus& TPMSSta);
    void handleTPMSPressureStaFLChanged(const uint8_t &TPMSPressureStaFL); 
    void handleTPMSPressureStaFRChanged(const uint8_t &TPMSPressureStaFR);
    void handleTPMSPressureStaRLChanged(const uint8_t &TPMSPressureStaRL);
    void handleTPMSPressureStaRRChanged(const uint8_t &TPMSPressureStaRR);
    void handleSRSErrorChanged(const v1::VSS::Vehicle::SystemStatus::SRSWorkStatus& SRSError);
    void handleLowbatterychargeChanged(const v1::VSS::Vehicle::SystemStatus::LowVoltageBatteryWorkStatus& lowbatterycharge);
    void handleABSfailedChanged(VSS::Type::Type::BooleanValue ABSfailed);
    void handlePALAresponseChanged(VSS::Type::Type::BooleanValue PALAresponse);
    void handleESPActiveStaChanged(VSS::Type::Type::BooleanValue ESPActiveSta);
    void handleESCFailedChanged(VSS::Type::Type::BooleanValue ESCFailed);
    void handleHDCWorkStsChanged(const v1::VSS::Vehicle::SystemStatus::HDCWorkStatus& HDCWorkSts);
    void handleEBDFailedChanged(VSS::Type::Type::BooleanValue EBDFailed);
    void handleAVHStsChanged(const v1::VSS::Vehicle::SystemStatus::AVHWorkStatus &AVHSts);
    void handleBasicElecSteerFailedChanged(const v1::VSS::Vehicle::SystemStatus::EPSWorkStatus& BasicElecSteerFailed);
    void handleEPCwarnChanged(const v1::VSS::Vehicle::SystemStatus::EPCWorkStatus& EPCwarn);
    void handleInletConnctStaChanged(VSS::Type::Type::BooleanValue InletConnctSta);
    void handleBatSOCRptChanged(const uint8_t &BatSOCRpt);
    void handlePTActlOprtModeChanged(const uint8_t &PTActlOprtMode);
    void handleHU_brakeliquidlevelChanged(const v1::VSS::Chassis::Axle::FluidLevelState& HU_brakeliquidlevel);
    void handleHU_engineoilChanged(const uint8_t &HU_engineoil);
    void handleHU_EngCoolantTempChanged(const int32_t &HU_EngCoolantTemp);
    void handleHU_VehicleMainLampChanged(VSS::Type::Type::BooleanValue HU_VehicleMainLamp);
    void handleLimpHomeStaChanged(const v1::VSS::Vehicle::SystemStatus::LimpHomeWorkStatus& LimpHomeSta);
    void handlePwrTrainHighTempWrningChanged(VSS::Type::Type::BooleanValue PwrTrainHighTempWrning);
    void handlePwrTrainConnectStaChanged(VSS::Type::Type::BooleanValue PwrTrainConnectSta);
    void handleIsPowerConnectedChanged(const ::VSS::Type::Type::BooleanValue &IsPowerConnected);
    void handleIsGroundConnectedChanged(const ::VSS::Type::Type::BooleanValue &IsGroundConnected);

    void handleMotorHighTempWrningChanged(VSS::Type::Type::BooleanValue MotorHighTempWrning);
    void handleBMSSysFailStaChanged(VSS::Type::Type::BooleanValue BMSSysFailSta);
    void handleDrvMotorStaChanged(VSS::Type::Type::BooleanValue DrvMotorSta);
    void handlePCUFailStaChanged(const v1::VSS::Vehicle::SystemStatus::PCUWorkStatus& PCUFailSta);
    void handleInsulationWrningChanged(const v1::VSS::Vehicle::SystemStatus::InsulationWorkStatus& InsulationWrning);
    void handleVSPstaChanged(VSS::Type::Type::BooleanValue VSPsta);
    void handleLowbeamChanged(VSS::Type::Type::BooleanValue lowbeam);
    void handleHighbeamChanged(VSS::Type::Type::BooleanValue highbeam);
    void handleFlashbeamChanged(VSS::Type::Type::BooleanValue Flashbeam);
    void handlePositionlampChanged(VSS::Type::Type::BooleanValue positionlamp);
    void handleFrontFogLampStaChanged(VSS::Type::Type::BooleanValue FrontFogLampSta);
    void handleRearFogLampStaChanged(VSS::Type::Type::BooleanValue rearFogLampSta);
    void handleAutohighbeamChanged(VSS::Type::Type::BooleanValue autohighbeam);
    void handleParkLampStaChanged(VSS::Type::Type::BooleanValue ParkLampSta);
    void handleIMMOPCUauthenChanged(const v1::VSS::Identifier::Identifier::IMMOResultType& IMMOPCUauthen);
    void handleEngineStaChanged(const v1::VSS::Vehicle::SystemStatus::EngineWorkStatus& EngineSta);
    void handleTransStaChanged(const v1::VSS::Vehicle::SystemStatus::TransmissionWorkStatus& transSta);
    void handleIsActiveChanged(VSS::Type::Type::BooleanValue isActive);
    void handleIsEnabledChanged(VSS::Type::Type::BooleanValue isActive);
    void handleIsErrorChanged(VSS::Type::Type::BooleanValue isError);
    void handleMachineOilPreChanged(const ::v1::VSS::Powertrain::CombustionEngine::EOPStateType &MachineOilPre);
    void pullValue();

private:
    boost::asio::steady_timer m_wather;
    std::shared_ptr<CommonAPI::Runtime> m_rt;
    std::shared_ptr<v1::VSS::ADAS::ABSProxy<>> m_abs;
    std::shared_ptr<v1::VSS::Chassis::AxleProxy<>> m_axle;
    std::shared_ptr<v1::VSS::ADAS::CruiseControlProxy<>> m_cruiseControl;
    std::shared_ptr<v1::VSS::Powertrain::CombustionEngineProxy<>> m_combustionEngine;
    std::shared_ptr<v1::VSS::ADAS::ESCProxy<>> m_esc;
    std::shared_ptr<v1::VSS::ADAS::EBDProxy<>> m_edb;
    std::shared_ptr<v1::VSS::Powertrain::ElectricMotorProxy<>> m_electricMotorProxy;
    std::shared_ptr<v1::VSS::Identifier::IdentifierProxy<>> m_identifier;
    std::shared_ptr<v1::VSS::Body::LightsProxy<>> m_lights;
    std::shared_ptr<v1::VSS::Chassis::ParkingBrakeProxy<>> m_parkingBrake;
    std::shared_ptr<v1::VSS::Cabin::SeatProxy<>> m_seat;
    std::shared_ptr<v1::VSS::Vehicle::SystemStatusProxy<>> m_systemStatus;
    std::shared_ptr<v1::VSS::Powertrain::TractionBatteryProxy<>> m_tractionBatteryProxy;
    std::shared_ptr<v1::VSS::ADAS::VSPProxy<>> m_vsp;
    std::shared_ptr<v1::ClusterAudio::ClusterAudioCtrlProxy<>> m_clusterAudioCtrl;
    std::shared_ptr<v1::ClusterAudio::ClusterAudioInfoProxy<>> m_clusterAudioInfo;
};

#endif