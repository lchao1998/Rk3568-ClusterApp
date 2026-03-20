#include "centerviewlogic.h"

#include <chrono>

#ifdef USE_EASY_PROFILER
    #include <easy/profiler.h>
#endif

#include <zl_log.h>
#include <boost/asio/post.hpp>
#include <thread>

#include "sm_centerview.h"
#include "sm_telltalesm.h"

CenterViewLogic::CenterViewLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt)
    : m_wather(io)
    , m_rt(rt)
    , m_bodyProxy(m_rt->buildProxy<v1::VSS::Body::BodyProxy>("local", "VSS.Body.Body"))
    , m_door(m_rt->buildProxy<v1::VSS::Cabin::DoorProxy>("local", "VSS.Cabin.Door"))
    , m_fuelSystem(m_rt->buildProxy<v1::VSS::Powertrain::FuelSystemProxy>("local", "VSS.Powertrain.FuelSystem"))
    , m_hardKeyProxy(m_rt->buildProxy<v1::VSS::Cabin::HardKeyProxy>("local", "VSS.Cabin.HardKey"))
    , m_pas(m_rt->buildProxy<v1::VSS::ADAS::PASProxy>("local", "VSS.ADAS.PAS"))
    , m_powertrain(m_rt->buildProxy<v1::VSS::Powertrain::PowertrainProxy>("local", "VSS.Powertrain.Powertrain"))
    , m_seat(m_rt->buildProxy<v1::VSS::Cabin::SeatProxy>("local", "VSS.Cabin.Seat"))
    , m_tractionBattery(m_rt->buildProxy<v1::VSS::Powertrain::TractionBatteryProxy>("local", "VSS.Powertrain.TractionBattery"))
    , m_vehicle(m_rt->buildProxy<v1::VSS::Vehicle::VehicleProxy>("local", "VSS.Vehicle.Vehicle"))
    , m_axle(m_rt->buildProxy<v1::VSS::Chassis::AxleProxy>("local", "VSS.Chassis.Axle"))
    , m_clusterAudioCtrl(m_rt->buildProxy<v1::ClusterAudio::ClusterAudioCtrlProxy>("local", "ClusterAudio.ClusterAudioCtrl"))
    , m_clusterAudioInfo(m_rt->buildProxy<v1::ClusterAudio::ClusterAudioInfoProxy>("local", "ClusterAudio.ClusterAudioInfo"))
    , m_transmission(m_rt->buildProxy<v1::VSS::Powertrain::TransmissionProxy>("local", "VSS.Powertrain.Transmission"))
    , m_multiDisplayProxy(m_rt->buildProxy<v1::MultiDisplayService::MultiDisplayProxy>("local", "MultiDisplayService.MultiDisplay"))
    , m_curPage(0)
    , m_isBluetoothCallHollowOutOn(false)
    , m_lastPageState(0)
    , m_isProjectingNow(false)       
{
    registerProperties();
    m_wather.expires_from_now(std::chrono::milliseconds(500));
    m_wather.async_wait(std::bind(&CenterViewLogic::updateWarningStatus, this));
}

void CenterViewLogic::handleHU_AvgVehicleSpeedChanged(int HU_AvgVehicleSpeed)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("HU_AvgVehicleSpeed value: %d", HU_AvgVehicleSpeed);
    SharedMemory::HU_AvgVehicleSpeed.setValue(HU_AvgVehicleSpeed);
}

void CenterViewLogic::handleHU_RemainRangeChanged(int HU_RemainRange)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("HU_RemainRange value: %d", HU_RemainRange);
    SharedMemory::HU_RemainRange.setValue(HU_RemainRange);
}
void CenterViewLogic::handleBatSOCRptChanged(int BatSOCRpt)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("BatSOCRpt value: %d", BatSOCRpt);
    if (BatSOCRpt < 10)
    {
        // TODO: emit warning sound
    }
    SharedMemory::BatSOCRpt.setValue(BatSOCRpt);
}
void CenterViewLogic::handleHVBatActlVoltageChanged(int HVBatActlVoltage)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("HVBatActlVoltage value: %d", HVBatActlVoltage);
    SharedMemory::HVBatActlVoltage.setValue(HVBatActlVoltage);
}
void CenterViewLogic::handleExchgCurntChanged(int ExchgCurnt)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("ExchgCurnt value: %d", ExchgCurnt);
    SharedMemory::ExchgCurnt.setValue(ExchgCurnt);
}
void CenterViewLogic::handleAverageConsumptionChanged(float value)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("HU_Avgfuleconsump value: %f", value);
    SharedMemory::HU_Avgfuleconsump.setValue(value);
}
void CenterViewLogic::handleMenuSwStaIsPressedChanged(const ::VSS::Type::Type::BooleanValue &MenuSwStaIsPressed)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    logDebug("MenuSwStaIsPressed value: %s", MenuSwStaIsPressed.toString());
    logDebug("cur page  value: %d", m_curPage);
    std::cout << "MenuSwStaIsPressed value: " << MenuSwStaIsPressed.toString() << std::endl;
    std::cout << "cur page  value: " << m_curPage << std::endl;

    //if current state is bluetooth call on, then we lock the screen
    if (m_isBluetoothCallHollowOutOn)
    {
        logDebug("bluetooth call is on, lock the screen");
        return;
    }

    if (MenuSwStaIsPressed == VSS::Type::Type::BooleanValue::Literal::TRUE)
    {
        ++m_curPage;
        if (m_curPage > 4)
            m_curPage = 0;
        if (m_curPage < 3) {
            SharedMemory::Menu_SwSta.setValue(m_curPage);
            if (m_curPage == 0)
                boost::asio::post(m_wather.get_executor(), [this](){
                    CommonAPI::CallStatus callStatus;
                    CommonAPI::CallInfo callInfo(5 * 1000);
                    bool result = false;
                    m_multiDisplayProxy->ScreenProjection(v1::MultiDisplayService::MultiDisplay::DisplayActionType::Literal::CANCEL_SCREEN, callStatus, result, &callInfo);
                    if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                        SharedMemory::Menu_SwSta.setValue(0xf2);
                    }
                });
            return;
        }
        if (m_curPage == 3)
        {
            boost::asio::post(m_wather.get_executor(), [this](){
                CommonAPI::CallStatus callStatus;
                CommonAPI::CallInfo callInfo(5 * 1000);
                bool result = false;
                m_multiDisplayProxy->ScreenProjection(v1::MultiDisplayService::MultiDisplay::DisplayActionType::Literal::MEDIA, callStatus, result, &callInfo);
                if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                    SharedMemory::Menu_SwSta.setValue(0xf2);
                } else {
                    m_isProjectingNow = true;
                }
            });
        }
        else if (m_curPage == 4)
        {
            logDebug("--------------------------m_multiDisplayProxy->ScreenProjection 4.");
            std::cout << "thread id: " << std::this_thread::get_id();
            boost::asio::post(m_wather.get_executor(), [this](){
                std::cout << "post thread id: " << std::this_thread::get_id();
                CommonAPI::CallStatus callStatus;
                CommonAPI::CallInfo callInfo(5 * 1000);
                bool result = false;
                m_multiDisplayProxy->ScreenProjection(v1::MultiDisplayService::MultiDisplay::DisplayActionType::Literal::NAVIGATION, callStatus, result, &callInfo);
                if (callStatus != CommonAPI::CallStatus::SUCCESS) {
                    SharedMemory::Menu_SwSta.setValue(0xf2);
                } else {
                    m_isProjectingNow = true;
                }
            });
        }

    }
}
void CenterViewLogic::handleHU_CurONChanged(int value)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("HU_CurON value: %d", value);
    SharedMemory::HU_CurON.setValue(value);
}
void CenterViewLogic::handlePASwarnChanged(const VSS::Type::Type::BooleanValue &PASwarn)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
        
//    logDebug("PASwarn value: %s", PASwarn.toString());
//    auto &warningpopuplogic = m_appLogic.getWarningPopupLogic();
//    VehicleSignal PASIsErrorSignal(VehicleSignal::PAS_IS_ERROR_WARNING_PRIORITY, VehicleSignal::VEHICLE_SIGNAL_TYPE_BOOL,
//        PASwarn == VSS::Type::Type::BooleanValue::Literal::TRUE, 1, PAS_IS_ERROR);
//    switch (PASwarn)
//    {
//    case VSS::Type::Type::BooleanValue::Literal::TRUE:
//        warningpopuplogic.enqueueVehicleSignal(PASIsErrorSignal);
//        break;
//    default:
//        warningpopuplogic.removeVehicleSignal(PASIsErrorSignal);
//        break;
//    }
}

void CenterViewLogic::handleDisplayStateChanged(const v1::MultiDisplayService::MultiDisplay::DisplayActionType &type, 
                               const v1::MultiDisplayService::MultiDisplay::DisplayState &state)
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif

    if (!m_isProjectingNow)
    {
        return;
    }    
    logDebug("type value: %s", type.toString());
    logDebug("state value: %s", state.toString());
    std::cout << "type value: " << type.toString() << std::endl;
    std::cout << "state value: " << state.toString() << std::endl;
    //If any state is ready, we notify the frontend to hide a part of the screen, and then we just return 
    if (state == v1::MultiDisplayService::MultiDisplay::DisplayState::Literal::READY
        &&  type == v1::MultiDisplayService::MultiDisplay::DisplayActionType::Literal::MEDIA)
    {
        SharedMemory::Menu_SwSta.setValue(4);
    } else if (state == v1::MultiDisplayService::MultiDisplay::DisplayState::Literal::READY
        &&  type == v1::MultiDisplayService::MultiDisplay::DisplayActionType::Literal::NAVIGATION) 
    {
        SharedMemory::Menu_SwSta.setValue(3);
    }

    if (state == v1::MultiDisplayService::MultiDisplay::DisplayState::Literal::FAILED
        && type == v1::MultiDisplayService::MultiDisplay::DisplayActionType::Literal::NAVIGATION)
    {
        SharedMemory::Menu_SwSta.setValue(0xf0);
    } else if (state == v1::MultiDisplayService::MultiDisplay::DisplayState::Literal::FAILED
        && type == v1::MultiDisplayService::MultiDisplay::DisplayActionType::Literal::MEDIA)
    {
        SharedMemory::Menu_SwSta.setValue(0xf1);
    }

    m_isProjectingNow = false;
}

void CenterViewLogic::handleErrorCodesChanged(const std::vector<std::string> &errorCodes)
{
    if (errorCodes.empty())
        return;
    std::string str = errorCodes[0];
    int errorLevel = 0;
    try {
        errorLevel = std::stoi(str);
        std::cout << "Converted number: " << errorLevel << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "Invalid argument exception: " << e.what() << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << "Out of range exception: " << e.what() << std::endl;
    }
    SharedMemory::BMSErrorCodes.setValue(errorLevel);

    if (!m_clusterAudioCtrl->isAvailable())
        return;

    CommonAPI::CallInfo callInfo(5 * 1000);
    auto handler = [this, errorLevel](const CommonAPI::CallStatus& callStatus, const bool& result){
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
                logWarning("invoke audio control stop failed!!!!");


        };

        std::vector<std::string> audioPath;
        CommonAPI::CallInfo callInfo(5 * 1000);
        audioPath.push_back("/usr/share/sounds/warning.wav");
        if (errorLevel != 0) {
            //warn one level.
            m_clusterAudioCtrl->PlayAsync(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                          audioPath,
                                          ::ClusterAudioType::Types::PlayType::Literal::BY_DURATION,
                                          1000,
                                          5000, handler, &callInfo);
        }
    };

    m_clusterAudioCtrl->StopAsync(::ClusterAudioType::Types::AudioType::Literal::CHIME, handler, &callInfo);
}

void CenterViewLogic::handleBluetoothCallHollowOut()
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    m_lastPageState = SharedMemory::Menu_SwSta.getValue();
    SharedMemory::Menu_SwSta.setValue(3);
    m_isBluetoothCallHollowOutOn = true;
}

void CenterViewLogic::updateWarningStatus()
{
#ifdef USE_EASY_PROFILER
    EASY_FUNCTION();
#endif
    
    logDebug("update warning status");

    struct gruad {
        gruad(boost::asio::steady_timer &t, CenterViewLogic *th) : m_wather(t), m_th(th){}
        ~gruad() {
            logDebug("expires_from_now 100");
            m_wather.expires_from_now(std::chrono::milliseconds(300));
            m_wather.async_wait(std::bind(&CenterViewLogic::updateWarningStatus, m_th));
        }
        boost::asio::steady_timer &m_wather;
        CenterViewLogic *m_th;
    };
    auto g = gruad(m_wather, this);

    if (!m_bodyProxy->isAvailable()) {
        return;
    }
    CommonAPI::CallStatus callStatus;
    CommonAPI::CallInfo callInfo(5 * 1000);
    // 主驾安全带状态(只读)
    VSS::Type::Type::BooleanValue DrvSeatbeltBucklestatus;
    m_seat->getRow1DriverSideIsBeltedAttribute().getValue(callStatus, DrvSeatbeltBucklestatus, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getDrvSeatbeltBucklestatusAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("DrvSeatbeltBucklestatus value: %s", DrvSeatbeltBucklestatus.toString());
    }

    signed char TranGearPos;
    m_transmission->getSelectedGearAttribute().getValue(callStatus, TranGearPos, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getSelectedGearAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("getSelectedGearAttribute value: %d", TranGearPos);
    }

    bool result;
    if (static_cast<int>(TranGearPos) == 0xD) {
        SharedMemory::DrvSeatbeltBucklestatus.setValue(0);
        logDebug("SharedMemory::DrvSeatbeltBucklestatus.setValue(1)");
        m_clusterAudioCtrl->Stop(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                 callStatus, result, &callInfo);
        if (!result)
            logWarning("invoke audio control stop failed!!!!");
        return;
    }

    std::vector<std::string> audioPath;
    audioPath.push_back("/usr/share/sounds/warning.wav");
    vector<ClusterAudioType::Types::ServiceStatus> audioStatusArray;
    m_clusterAudioInfo->getStatusAttribute().getValue(callStatus, audioStatusArray, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("audioStatus failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("audioStatus size: %d", audioStatusArray.size());
    }

    switch (DrvSeatbeltBucklestatus) {
        case VSS::Type::Type::BooleanValue::Literal::FASLE: {
            SharedMemory::DrvSeatbeltBucklestatus.setValue(0);
            logDebug("SharedMemory::DrvSeatbeltBucklestatus.setValue(0)");
            break;
        }
        default: {
            SharedMemory::DrvSeatbeltBucklestatus.setValue(1);
            logDebug("SharedMemory::DrvSeatbeltBucklestatus.setValue(1)");
            m_clusterAudioCtrl->Stop(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                     callStatus, result, &callInfo);
            if (!result)
                logWarning("invoke audio control stop failed!!!!");
            break;
        }
    }

    for (const auto &status : audioStatusArray) {
        logDebug("status.getAudioType(): %s", status.getAudioType().toString());
        logDebug("status.getPlayerState(): %s", status.getPlayerState().toString());
        if (status.getAudioType() == ::ClusterAudioType::Types::AudioType::Literal::CHIME
            && status.getPlayerState() == ::ClusterAudioType::Types::PlayerState::PLAYING) {
            SharedMemory::DrvSeatbeltBucklestatus.setValue(2);
            // We simply let the audio play without taking any action
            logDebug("level 2 audio is playing!!!");
            logDebug("SharedMemory::DrvSeatbeltBucklestatus.setValue(2-)--playing");
        }
    }

    float currentSpeed = 0;
    m_vehicle->getSpeedAttribute().getValue(callStatus, currentSpeed, &callInfo);
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        logDebug("getSpeedAttribute failed, callStatus = %d", (int32_t)callStatus);
    }
    else
    {
        logDebug("getSpeedAttribute value: %s", currentSpeed);
    }

    static int currentWarningLevel = 0;

    if(currentSpeed > 0 && currentSpeed < 10 && DrvSeatbeltBucklestatus == VSS::Type::Type::BooleanValue::Literal::FASLE) {
        logDebug("SharedMemory::DrvSeatbeltBucklestatus.setValue(2)");
        SharedMemory::DrvSeatbeltBucklestatus.setValue(2);

        m_clusterAudioCtrl->Stop(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                 callStatus, result, &callInfo);
        logDebug("stop level %d warning", currentWarningLevel);
        //warn one level.
        m_clusterAudioCtrl->Play(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                 audioPath,
                                 ::ClusterAudioType::Types::PlayType::Literal::BY_DURATION,
                                 1000,
                                 120000,
                                 callStatus,
                                 result, &callInfo);
        if (!result)
            logWarning("play audio failed!!!");
    } else if (currentSpeed >= 10 && currentSpeed < 25 && DrvSeatbeltBucklestatus == VSS::Type::Type::BooleanValue::Literal::FASLE){
        logDebug("SharedMemory::DrvSeatbeltBucklestatus.setValue(2)");
        SharedMemory::DrvSeatbeltBucklestatus.setValue(2);

        m_clusterAudioCtrl->Stop(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                 callStatus, result, &callInfo);
        //warn one level.
        m_clusterAudioCtrl->Play(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                 audioPath,
                                 ::ClusterAudioType::Types::PlayType::Literal::BY_DURATION,
                                 500,
                                 120000,
                                 callStatus,
                                 result, &callInfo);
        if (!result)
            logWarning("play audio failed!!!");
    } else if (currentSpeed >= 25 && DrvSeatbeltBucklestatus == VSS::Type::Type::BooleanValue::Literal::FASLE) {
        logDebug("SharedMemory::DrvSeatbeltBucklestatus.setValue(2)");

        SharedMemory::DrvSeatbeltBucklestatus.setValue(2);

        m_clusterAudioCtrl->Stop(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                 callStatus, result, &callInfo);

        //warn one level.
        m_clusterAudioCtrl->Play(::ClusterAudioType::Types::AudioType::Literal::CHIME,
                                 audioPath,
                                 ::ClusterAudioType::Types::PlayType::Literal::BY_DURATION,
                                 250,
                                 120000,
                                 callStatus,
                                 result, &callInfo);
        if (!result)
            logWarning("play audio failed!!!");
    }
}
void CenterViewLogic::registerProperties()
{
    //new interfaces 
    m_vehicle->getAverageSpeedAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleHU_AvgVehicleSpeedChanged, this, std::placeholders::_1));
    m_fuelSystem->getInstantConsumptionAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleHU_CurONChanged, this, std::placeholders::_1));
    m_fuelSystem->getAverageConsumptionAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleAverageConsumptionChanged, this, std::placeholders::_1));
    m_hardKeyProxy->getModeSwStaIsPressedAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleMenuSwStaIsPressedChanged, this, std::placeholders::_1));

    m_tractionBattery->getStateOfChargeDisplayedAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleBatSOCRptChanged, this, std::placeholders::_1));
    m_powertrain->getRangeAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleHU_RemainRangeChanged, this, std::placeholders::_1));
    m_tractionBattery->getErrorCodesAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleErrorCodesChanged, this, std::placeholders::_1));
    m_tractionBattery->getCurrentVoltageAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleHVBatActlVoltageChanged, this, std::placeholders::_1));
    m_tractionBattery->getCurrentCurrentAttribute().getChangedEvent().subscribe(std::bind(&CenterViewLogic::handleExchgCurntChanged, this, std::placeholders::_1));
    m_multiDisplayProxy->getBluetoothCallHollowOutEvent().subscribe(std::bind(&CenterViewLogic::handleBluetoothCallHollowOut, this));
    m_multiDisplayProxy->getDisplayStateEvent().subscribe(std::bind(&CenterViewLogic::handleDisplayStateChanged, this, std::placeholders::_1, std::placeholders::_2));
}