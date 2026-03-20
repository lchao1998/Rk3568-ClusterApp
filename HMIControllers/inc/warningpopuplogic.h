#ifndef WARNING_POPUP_LOGIC_H
#define WARNING_POPUP_LOGIC_H

#include <mutex>
#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/heap/priority_queue.hpp>

#include <CommonAPI/CommonAPI.hpp>

#include <v1/VSS/Chassis/AxleProxy.hpp>
#include <v1/VSS/Cabin/DoorProxy.hpp>
#include <v1/VSS/Vehicle/SystemStatusProxy.hpp>
#include <v1/VSS/Vehicle/VehicleProxy.hpp>

#define DEFAULT_SIGNAL_VALUE "Default"
#define DRIVER_SIDE_IS_OPEN "DriverSideIsOpen"
#define SYSTEM_STATUS_IS_READY "SystemStatusIsReady"
#define ABNORMAL_TIER_STATE "AbnormalTierState"
#define SEAT_BELT_NOT_FASTENED "SeatBeltNotFastened"


#define BATTERY_LEVEL_IS_LOW "BatteryLevelIsLow"
#define TPMS_STATE_IS_ERROR "TPMSStateIsError"  
#define SRS_STATUS_IS_ERROR "SRSStatusIsError"
#define ABS_IS_ERROR "ABSIsError"
#define ESC_IS_ERROR "ESCIsError"
#define HDC_STATUS_IS_ERROR "HDCStatusIsError"
#define EBD_IS_ERROR "EBDIsError"
#define AVH_STATUS_IS_ERROR "AVHStatusIsError"
#define EPS_STATUS_IS_ERROR "EPSStatusIsError"
#define CRUISE_CONTROL_IS_ERROR "CruiseControlIsError"
#define ENGINE_STATUS_IS_ERROR "EngineStatusIsError"
#define TRANSMISSION_STATUS_IS_ERROR "TransmissionStatusIsError"
#define LIMP_HOME_STATUS_IS_LIMP_HOME "LimpHomeStatusIsLimpHome"
#define TRACTION_BATTERY_TEMPERATURE_IS_WARNING "TractionBatteryTemperatureIsWarning"
#define TRACTION_BATTERY_IS_GROUND_CONNECTED "TractionBatteryIsGroundConnected"
#define ELECTRIC_MOTOR_TEMPERATURE_IS_WARNING "ElectricMotorTemperatureIsWarning"
#define TRACTION_BATTERY_IS_ERROR "TractionBatteryIsError"
#define ELECTRIC_MOTOR_IS_ERROR "ElectricMotorIsError"
#define PCU_STATUS_IS_ERROR "PCUStatusIsError"
#define INSULATION_STATUS_IS_ERROR "InsulationStatusIsError"
#define PAS_IS_ERROR "PASIsError"
#define PAS_SENSOR_STATE_IS_ERROR "PASSensorStateIsError"
#define PEPS_STATUS_IS_WARNING "PEPSStatusIsWarning"
#define TIER_STATE_IS_VIRGIN "TierStateIsVirgin"

#define ABS_IS_OFF "ABSIsOff"
#define HU_BRAKELIQUIDLEVEL_POP "HUbrakeliquidlevelPop"
#define HIGH_COOLANT_TEMPERATURE_POP "highCoolantTemperaturePop"
#define LOW_FUEL_POP "lowFuelPop"
#define HU_MACHINE_OIL_PRE_POP "HUMachineOilPrePop"
#define CRUISE_CONTROL_IS_ACTIVE "CruiseControlIsActive"
#define VSP_IS_ENABLED "VSPIsEnabled"
 
struct VehicleSignal {
    enum VehicleSignalType {
        VEHICLE_SIGNAL_TYPE_MIN = -1,
        VEHICLE_SIGNAL_TYPE_BOOL = 0,
        VEHICLE_SIGNAL_TYPE_INT,
        VEHICLE_SIGNAL_TYPE_FLOAT,
        VEHICLE_SIGNAL_TYPE_STRING,
        VEHICLE_SIGNAL_TYPE_ENUM,
        Vehicle_SIGNAL_TYPE_TIER_STATE,
        VEHICLE_SIGNAL_TYPE_MAX
    };
    enum VehicleSignalPriority {
        VEHICLE_SIGNAL_PRIORITY_MIN = -1,
        SIDEL_OPEN_WARNING_PRIORITY = 0,
        READY_STATUS_WARNING_PRIORITY,
        TIER_STATE_WARNING_PRIORITY,
        DRIVER_SIDE_IS_BElTED_WARNING_PRIORITY,
        STATE_OF_CHARGE_IS_LOW_PRIORITY,    
        PEPS_STATUES_WARNING_PRIORITY,
        SRS_STATUES_WARNING_PRIORITY,
        ABS_IS_ERROR_WARNING_PRIORITY,
        ESC_IS_ERROR_WARNING_PRIORITY,
        HDC_STATUS_WARNING_PRIORITY,
        EBD_IS_ERROR_WARNING_PRIORITY,
        AVH_STATUS_WARNING_PRIORITY,
        EPS_STATUS_WARNING_PRIORITY,
        CRUISE_CONTROL_IS_ERROR_WARNING_PRIORITY,
        ENGINE_STATUS_WARNING_PRIORITY,
        TRANSMISSION_STATUS_WARNING_PRIORITY,
        TRACTION_BATTERY_IS_GROUND_CONNECTED_WARNING_PRIORITY,
        ELECTRIC_MOTOR_TEMPERATURE_IS_WARNING_PRIORITY,
        TRACTION_BATTERY_ISERROR_WARNING_PRIORITY,
        ELECTRIC_MOTOR_IS_ERROR_WARNING_PRIORITY,
        PCU_STATUS_WARNING_PRIORITY,
        INSULATION_STATUS_WARNING_PRIORITY,
        PAS_IS_ERROR_WARNING_PRIORITY,
        PAS_STATE_ERROR_WARNING_PRIORITY,
        PEPS_STATUS_WARNING_PRIORITY,
        TPMS_ERROR_WARNING_PRIORITY,
        TPMS_UNLEARNED_POP_WARNING_PRIORITY,
        HU_BRAKELIQUIDLEVEL_POP_WARNING_PRIORITY,
        HIGHCOOLANTTEMPERATURE_POP_WARNING_PRIORITY,
        LOWFUEL_POP_WARNING_PRIORITY,
        HU_MACHINEOILPRE_POP_WARNING_PRIORITY,
        CRUISE_CONTROL_IS_ACTIVE_WARNING_PRIORITY,
        VSP_ISENABLED_WARNING_PRIORITY,
        VEHICLE_SIGNAL_PRIORITY_MAX
    };
    VehicleSignal()
        : m_priority(VEHICLE_SIGNAL_PRIORITY_MIN)
        , m_type(VEHICLE_SIGNAL_TYPE_MIN)
        , m_signalValue(0)
        , m_cancelCount(0)
        , m_signalName(DEFAULT_SIGNAL_VALUE)
    {
    }
    VehicleSignal(VehicleSignalPriority priority, VehicleSignalType type, boost::any signalValue, int cancelCount, std::string signalName = DEFAULT_SIGNAL_VALUE)
        : m_priority(priority)
        , m_type(type)
        , m_signalValue(signalValue)
        , m_cancelCount(cancelCount)
        , m_signalName(signalName)
    {
    }
    VehicleSignal(const VehicleSignal &other)
        : m_priority(other.m_priority)
        , m_type(other.m_type)
        , m_signalValue(other.m_signalValue)
        , m_cancelCount(other.m_cancelCount)
        , m_signalName(other.m_signalName)
    {
    }
    VehicleSignal(VehicleSignal &&other)
        : m_priority(other.m_priority)
        , m_type(other.m_type)
        , m_signalValue(other.m_signalValue)
        , m_cancelCount(other.m_cancelCount)
        , m_signalName(other.m_signalName)
    {
    }
    ~VehicleSignal() {}
    void clear()
    {
        m_priority = VEHICLE_SIGNAL_PRIORITY_MIN;
        m_type = VEHICLE_SIGNAL_TYPE_MIN;
        m_signalValue = 0;
        m_cancelCount = 0;
        m_signalName = DEFAULT_SIGNAL_VALUE;
    }
    bool isBool() const { return m_type == VEHICLE_SIGNAL_TYPE_BOOL; }
    bool isInt() const { return m_type == VEHICLE_SIGNAL_TYPE_INT; }
    bool isFloat() const { return m_type == VEHICLE_SIGNAL_TYPE_FLOAT; }
    bool isString() const { return m_type == VEHICLE_SIGNAL_TYPE_STRING; }
    bool toBool() const { return boost::any_cast<bool>(m_signalValue); }
    int toInt() const { return boost::any_cast<int>(m_signalValue); }
    float toFloat() const { return boost::any_cast<float>(m_signalValue); }
    std::string toString() const { return boost::any_cast<std::string>(m_signalValue); }
    VehicleSignal &operator=(const VehicleSignal &other)
    {
        m_priority = other.m_priority;
        m_type = other.m_type;
        m_signalValue = other.m_signalValue;
        m_signalName = other.m_signalName;
        m_cancelCount = other.m_cancelCount;
        return *this;
    }
    bool operator==(const VehicleSignal &other) const;
    bool operator!=(const VehicleSignal &other) const { return !(*this == other); }
    bool operator<(const VehicleSignal &other) const { return m_priority < other.m_priority; }
    bool operator>(const VehicleSignal &other) const { return m_priority > other.m_priority; }
    VehicleSignalPriority m_priority;
    VehicleSignalType m_type;
    boost::any m_signalValue;
    int m_cancelCount;
    std::string m_signalName;
};

using VehicleSignalQueue = std::list<VehicleSignal>;

class WarningPopupLogic
{
private:
    /* data */
public:
    WarningPopupLogic(boost::asio::io_context &io, std::shared_ptr<CommonAPI::Runtime> rt);
    ~WarningPopupLogic();

public:
    VehicleSignalQueue &getVehicleSignalQueue() { return m_vehicleSignalQueue; }
    std::mutex &getVehicleSignalQueueMutex() { return m_vehicleSignalQueueMutex; }
    bool removeVehicleSignal(const VehicleSignal &signal);
    void enqueueVehicleSignal(const VehicleSignal &signal);

private:
    void handleCurWarningTimeout();
    void generateSidelOpenWarning();
    void generateReadyStatusWarning();
    void generateTierStateWarning();
    void handleSignal(const VehicleSignal &signal);

private:
    boost::asio::steady_timer m_checkCurWarning;
    boost::asio::steady_timer m_sidelOpenWarningTimer;
    boost::asio::steady_timer m_readyStatusWarningTimer;
    boost::asio::steady_timer m_tierStateWarningTimer;
    
    VehicleSignalQueue m_vehicleSignalQueue;
    std::mutex m_vehicleSignalQueueMutex;
    std::shared_ptr<CommonAPI::Runtime> m_rt;
    VehicleSignal m_curWarning;
    int m_checkCurWarningCancelCount;

    std::shared_ptr<v1::VSS::Chassis::AxleProxy<>> m_axle;
    std::shared_ptr<v1::VSS::Cabin::DoorProxy<>> m_door;
    std::shared_ptr<v1::VSS::Vehicle::SystemStatusProxy<>> m_systemStatus;
    std::shared_ptr<v1::VSS::Vehicle::VehicleProxy<>> m_vehicle;

    struct gruad {
        using UCallback = std::function<void(WarningPopupLogic *)> ;
        gruad(boost::asio::steady_timer &t, WarningPopupLogic *th, int interval, UCallback func) 
        : m_wather(t)
        , m_th(th)
        , m_func(func)
        , m_interval(interval)
        {}
        ~gruad() {
            m_wather.expires_from_now(std::chrono::milliseconds(m_interval));
            m_wather.async_wait(std::bind(m_func, m_th));
        }
        boost::asio::steady_timer &m_wather;
        WarningPopupLogic *m_th;
        UCallback m_func;
        int m_interval;
    };
};

#endif