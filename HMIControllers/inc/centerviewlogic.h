#ifndef CENTERVIEW_H
#define CENTERVIEW_H

#include <boost/asio/steady_timer.hpp>

#include <CommonAPI/CommonAPI.hpp>

#include <v1/VSS/Body/BodyProxy.hpp>
#include <v1/VSS/Cabin/DoorProxy.hpp>
#include <v1/VSS/Powertrain/FuelSystemProxy.hpp>
#include <v1/VSS/Cabin/HardKeyProxy.hpp>
#include <v1/VSS/ADAS/PASProxy.hpp>
#include <v1/VSS/Powertrain/PowertrainProxy.hpp>
#include <v1/VSS/Cabin/SeatProxy.hpp>
#include <v1/VSS/Powertrain/TractionBatteryProxy.hpp>
#include <v1/VSS/Vehicle/VehicleProxy.hpp>
#include <v1/VSS/Chassis/AxleProxy.hpp>
#include <v1/ClusterAudio/ClusterAudioCtrlProxy.hpp>
#include <v1/ClusterAudio/ClusterAudioInfoProxy.hpp>
#include <v1/MultiDisplayService/MultiDisplayProxy.hpp>
#include <v1/VSS/Powertrain/TransmissionProxy.hpp>

class AppLogic;
class CenterViewLogic
{
public:
    CenterViewLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt);

private: 
    void handleHU_AvgVehicleSpeedChanged(int HU_AvgVehicleSpeed);
    void handleHU_RemainRangeChanged(int HU_RemainRange);
    void handleBatSOCRptChanged(int BatSOCRpt);
    void handleHVBatActlVoltageChanged(int HVBatActlVoltage);
    void handleExchgCurntChanged(int ExchgCurnt);
    void handleAverageConsumptionChanged(float value);
    void handleMenuSwStaIsPressedChanged(const ::VSS::Type::Type::BooleanValue &MenuSwStaIsPressed);
    void handleHU_CurONChanged(int value);
    void handlePASwarnChanged(const VSS::Type::Type::BooleanValue &PASwarn);
    void handleDisplayStateChanged(const v1::MultiDisplayService::MultiDisplay::DisplayActionType &type, 
                               const v1::MultiDisplayService::MultiDisplay::DisplayState &state);
    void handleErrorCodesChanged(const std::vector<std::string> &errorCodes);
    void handleBluetoothCallHollowOut();
    void updateWarningStatus();
    void registerProperties();

private:
    boost::asio::steady_timer m_wather;
    std::shared_ptr<CommonAPI::Runtime> m_rt;
    std::shared_ptr<v1::VSS::Body::BodyProxy<>> m_bodyProxy;
    std::shared_ptr<v1::VSS::Cabin::DoorProxy<>> m_door;
    std::shared_ptr<v1::VSS::Powertrain::FuelSystemProxy<>> m_fuelSystem;
    std::shared_ptr<v1::VSS::Cabin::HardKeyProxy<>> m_hardKeyProxy;
    std::shared_ptr<v1::VSS::ADAS::PASProxy<>> m_pas;
    std::shared_ptr<v1::VSS::Powertrain::PowertrainProxy<>> m_powertrain;
    std::shared_ptr<v1::VSS::Cabin::SeatProxy<>> m_seat;
    std::shared_ptr<v1::VSS::Powertrain::TractionBatteryProxy<>> m_tractionBattery;
    std::shared_ptr<v1::VSS::Vehicle::VehicleProxy<>> m_vehicle;    
    std::shared_ptr<v1::VSS::Chassis::AxleProxy<>> m_axle;
    std::shared_ptr<v1::ClusterAudio::ClusterAudioCtrlProxy<>> m_clusterAudioCtrl;
    std::shared_ptr<v1::ClusterAudio::ClusterAudioInfoProxy<>> m_clusterAudioInfo;
    std::shared_ptr<v1::VSS::Powertrain::TransmissionProxy<>> m_transmission;

    std::shared_ptr<v1::MultiDisplayService::MultiDisplayProxy<>> m_multiDisplayProxy;
    int m_curPage;
    bool m_isBluetoothCallHollowOutOn;
    int m_lastPageState;    
    bool m_isProjectingNow;    
};
#endif 