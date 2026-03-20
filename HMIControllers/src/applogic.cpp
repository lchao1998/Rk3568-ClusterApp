#include "applogic.h"

#include <boost/asio/signal_set.hpp>
#include <boost/format.hpp>

#include <zl_log.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#ifdef USE_EASY_PROFILER
    #include <easy/profiler.h>
#endif

#include "sm_telltalesm.h"
#include "sm_baseinfodata.h"

#define CONFIG_FILE "/etc/hmicontroller.ini"

AppLogic::AppLogic()
    : m_commonApiRT(CommonAPI::Runtime::get())
    , m_baseInfoLogic(m_io, m_commonApiRT)
    , m_centerViewLogic(m_io, m_commonApiRT)
    , m_telltalesmLogic(m_io, m_commonApiRT)
    , m_bootAnimationProxy(m_commonApiRT->buildProxy<v1::BootAnimationService::BootAnimationProxy>("local", "BootAnimationService.BootAnimation"))
    , m_themeSkincareProxy(m_commonApiRT->buildProxy<v1::ThemeSkincareService::ThemeSkincareProxy>("local", "ThemeSkincareService.ThemeSkincare"))
    , m_systemSetingSyncProxy(m_commonApiRT->buildProxy<v1::SystemSeting::SystemSetingSyncProxy>("local", "SystemSeting.SystemSetingSync"))
{
    m_sendMessageToAnimation = std::make_shared<std::thread>(
        [this](){
            CommonAPI::CallStatus callStatus;
            auto isHmiLaunched = SharedMemory::IsHMILaunched.getValue();
            while (!(isHmiLaunched && m_bootAnimationProxy->isAvailable())){
                logDebug("services is not available");
                logDebug("isHmiLaunched %d", isHmiLaunched);
                std::cout << "services is not available" << std::endl;
                std::cout << "isHmiLaunched: " << isHmiLaunched << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                isHmiLaunched = SharedMemory::IsHMILaunched.getValue();
            }

            m_bootAnimationProxy->ReportStartupStatus(v1::BootAnimationService::BootAnimation::DevType::CLUSTER, 
            v1::BootAnimationService::BootAnimation::StartupStatus::START_COMPLETE, callStatus);
            logDebug("HMI launch complete!!!");
        }
    );
    m_sendMessageToAnimation->detach();   

    m_themeSkincareProxy->getThemeSkincareModeAttribute().getChangedEvent().subscribe(std::bind(&AppLogic::currentThemeChanged, this, std::placeholders::_1));
    m_systemSetingSyncProxy->getTimeFormatAttribute().getChangedEvent().subscribe(std::bind(&AppLogic::currentSystemFormetChagned, this, std::placeholders::_1));

    boost::property_tree::ptree pt;
    try {
        boost::property_tree::ini_parser::read_ini(CONFIG_FILE, pt);
        std::string themeType = pt.get<std::string>("Theme.Type");
        std::string timeFormat = pt.get<std::string>("Time.Format");
        logDebug("init value from config file themeType: %s", themeType.c_str());
        logDebug("init value from config file timeFormat: %s", timeFormat.c_str());
        if (themeType == "night") {
            SharedMemory::currentTheme.setValue(v1::ThemeSkincareService::ThemeSkincare::ThemeMode::NIGHT_MODE);
        } else {
            SharedMemory::currentTheme.setValue(v1::ThemeSkincareService::ThemeSkincare::ThemeMode::DAY_MODE);
        }
        if (timeFormat == "12") {
            SharedMemory::TimeFormat.setValue(SystemSetingType::Types::TimeFormat::Literal::TIME_FORMAT_12);
        } else {
            SharedMemory::TimeFormat.setValue(SystemSetingType::Types::TimeFormat::Literal::TIME_FORMAT_24);
        }
    } catch (boost::property_tree::ini_parser::ini_parser_error &e) {
        logError("boost::property_tree::ini_parser::ini_parser_error: %s", e.what());
        pt.put("Theme.Type", "night");
        pt.put("Time.Format", "12");
        boost::property_tree::ini_parser::write_ini(CONFIG_FILE, pt);
        SharedMemory::currentTheme.setValue(v1::ThemeSkincareService::ThemeSkincare::ThemeMode::NIGHT_MODE);
        SharedMemory::TimeFormat.setValue(0);
    } catch (boost::property_tree::ptree_error &e) {
        logError("boost::property_tree::ptree_error: %s", e.what());
        pt.put("Theme.Type", "night");
        pt.put("Time.Format", "12");
        boost::property_tree::ini_parser::write_ini(CONFIG_FILE, pt);
        SharedMemory::currentTheme.setValue(v1::ThemeSkincareService::ThemeSkincare::ThemeMode::NIGHT_MODE);
        SharedMemory::TimeFormat.setValue(0);
    }
}

void AppLogic::currentThemeChanged(v1::ThemeSkincareService::ThemeSkincare::ThemeMode themeType)
{

    logDebug("currentThemeChanged: %d", themeType);

    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(CONFIG_FILE, pt);
    if (themeType == v1::ThemeSkincareService::ThemeSkincare::ThemeMode::NIGHT_MODE) {
        pt.put("Theme.Type", "night");
    } else if (themeType == v1::ThemeSkincareService::ThemeSkincare::ThemeMode::DAY_MODE) {
        pt.put("Theme.Type", "day");
    } else {
        return;
    }
    SharedMemory::currentTheme.setValue(themeType);
    boost::property_tree::ini_parser::write_ini(CONFIG_FILE, pt);
}

void AppLogic::currentSystemFormetChagned(SystemSetingType::Types::TimeFormat format)
{
    logDebug("currentTimeFormatChanged: %s", format.toString());
    std::cout << "currentTimeFormatChanged: " << format.toString();
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(CONFIG_FILE, pt);
    if(format == SystemSetingType::Types::TimeFormat::Literal::TIME_FORMAT_12) {
        pt.put("Time.Format", "12");
        SharedMemory::TimeFormat.setValue(0);
    } else if (format == SystemSetingType::Types::TimeFormat::Literal::TIME_FORMAT_24) {
        SharedMemory::TimeFormat.setValue(1);
        pt.put("Time.Format", "24");
    } else {
        return;
    }
    boost::property_tree::ini_parser::write_ini(CONFIG_FILE, pt);
}

void AppLogic::appRun()
{
    auto work_guard =
        boost::asio::make_work_guard(m_io);
    m_io.run();
}

