// #ifndef SIGNAL_H
// #define SIGNAL_H

// #include <chrono>

// #include <list>

// #include <mutex>
// #include <memory>

// #include <unordered_map>

// #include<boost/asio/io_context.hpp>
// #include<boost/asio/steady_timer.hpp>

// #include<boost/enable_shared_from_this.hpp>

// #include<boost/system/error_code.hpp>

// #include "log.h"
// #include "sm_telltalesm.h"

// struct ConditionSignal;

// template<typename _T>
// struct SSignal
//     : public boost::enable_shared_from_this<SSignal<_T>>
// {
// public:
//     using ValueType = _T;

// public:
//     SSignal(const std::string &name, int priority = 0, const _T defaultValue = _T()) 
//     : m_priority(priority)
//     , m_defalutValue(defaultValue)
//     , m_name(name)
//     , m_counter()
//     , m_logger(keywords::channel = name)
//     {
//         m_logger.add_attribute("SignalCount", attrs::counter< unsigned int >());
//     }
//     void setValue(const _T &value);
//     void reset();
//     void setEnabled(bool enabled = true) { m_isEnabled.store(enabled); }
//     inline my_logger_mt &logger() { return m_logger; }
//     inline std::string name() const { return m_name; }
//     inline _T value() const { m_value.load(); }
//     operator int() const { return m_priority; }
    
// private:
//     void calculateInterval();

// protected:
//     const int m_priority;
//     const _T m_defalutValue;
//     std::string m_name;
//     std::atomic<_T> m_value;
//     std::atomic<int> m_counter;
//     std::atomic<bool> m_isEnabled;
//     int m_currentInterval;
//     my_logger_mt m_logger;
// };
// template<typename _T>
// struct SSignalHash
// {
//     std::size_t operator()(const SSignal<_T> &s) const noexcept
//     {
//         return std::hash<std::string>{}(s.name());
//     }
// };

// template<typename _T>
// inline void SSignal<_T>::setValue(const _T &value)
// {
//     m_value.store(value);
//     ++m_counter;
//     BOOST_LOG_SEV(logger(), trace) << boost::format("%1% value: %2%") % m_name % value << logging::add_value("SetValue", m_counter.load());
// }

// template<typename _T>
// inline void SSignal<_T>::calculateInterval()
// {
//     static std::chrono::steady_clock::time_point sta_tp;
// }

// template<typename _T>
// inline void SSignal<_T>::reset()
// {
//     BOOST_LOG_SEV(logger(), trace) << "signal reset!!!";
//     m_value.store(m_defalutValue);
// }

// struct ConditionSignal
// {
//     ConditionSignal(boost::asio::io_context &io, const std::string &name, int priority = 0)
//     : m_lostSignalThreshold(io)
//     {

//     }
//     void resetSignals();
//     void setValue(int value)
//     {
//         m_lostSignalThreshold.cancel();
//         m_lostSignalThreshold.expires_from_now(std::chrono::milliseconds(50 * 10));
//         m_lostSignalThreshold.async_wait([this](const boost::system::error_code&){resetSignals();});
//     }
//     void insetIntSignal(std::weak_ptr<SSignal<int>> signal) { m_intSignals.emplace_back(std::move(signal)); }
//     void insetBoolSignal(std::weak_ptr<SSignal<bool>> signal ) { m_boolSignals.emplace_back(std::move(signal)); }

// private:
//     boost::asio::steady_timer m_lostSignalThreshold;
//     std::list<std::weak_ptr<SSignal<bool>>> m_boolSignals;
//     std::list<std::weak_ptr<SSignal<int>>> m_intSignals;
// };

// #endif