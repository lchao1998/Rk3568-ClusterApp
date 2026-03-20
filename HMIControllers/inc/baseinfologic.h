#ifndef BASEINFOLOGIC_H
#define BASEINFOLOGIC_H

#include <boost/asio/steady_timer.hpp>

#include <CommonAPI/CommonAPI.hpp>

#include <v1/VSS/Powertrain/CombustionEngineProxy.hpp>
#include <v1/VSS/Vehicle/ExteriorProxy.hpp>
#include <v1/VSS/Powertrain/ElectricMotorProxy.hpp>
#include <v1/VSS/Vehicle/SystemStatusProxy.hpp>
#include <v1/VSS/Powertrain/TransmissionProxy.hpp>
#include <v1/VSS/Vehicle/VehicleProxy.hpp>

class BaseInfoLogic
{
public:
    BaseInfoLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt);

private: 
    void handleHU_TotalodometerChanged(float HU_Totalodometer);
    void handleHU_TripAOdometerChanged(float HU_TripAOdometer);
    void handleHU_TripBOdometerChanged(float HU_TripBOdometer);
    void handleHU_TripOdometerChanged(float HU_TripOdometer);
    void handleRevSpeedChanged(int revSpeed);
    void handleEnvirTempChanged(int EnvirTemp);
    void handleEnvirTempV(VSS::Type::Type::BooleanValue EnvirTempV);
    void handleTranGearPos(float TranGearPos);
    void handleHU_engineoil(int HU_engineoil);
    void handleHU_EngCoolantTemp(int HU_EngCoolantTemp);
    void handledrivemode(const ::v1::VSS::Powertrain::Transmission::VehiclePerformanceMode & drivemode);
    void handlePTActlOprtMode(const v1::VSS::Vehicle::SystemStatus::VehicleReadyStatus &PTActlOprtMode);
    void handleMotorPowerChanged(int MotorPower);
    void handleMotorPowerTypeChanged(VSS::Type::Type::BooleanValue MotorPowerType);
    void handleRecupLevelStaChanged(const ::v1::VSS::Vehicle::SystemStatus::RECUPWorkStatus &recupLevelSta);
    void handlePowerStaChanged(const ::v1::VSS::Vehicle::Vehicle::LowVoltageSystemStateType &powerSta);
    void hanleSppedChanged(const float &HU_DisvehicleSpeed);
    void registerProperties();

private:
    boost::asio::steady_timer m_wather;
    std::shared_ptr<CommonAPI::Runtime> m_rt;
    std::shared_ptr<v1::VSS::Powertrain::CombustionEngineProxy<>> m_combustionEngine;
    std::shared_ptr<v1::VSS::Vehicle::ExteriorProxy<>> m_exterior;
    std::shared_ptr<v1::VSS::Powertrain::ElectricMotorProxy<>> m_electricMotor;
    std::shared_ptr<v1::VSS::Vehicle::SystemStatusProxy<>> m_systemStatus;
    std::shared_ptr<v1::VSS::Powertrain::TransmissionProxy<>> m_transmission;
    std::shared_ptr<v1::VSS::Vehicle::VehicleProxy<>> m_vehicle;  
};

#endif