#ifndef APPLOGIC_H
#define APPLOGIC_H

#include <mutex>
#include <thread>

#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <boost/static_string.hpp>

#include <CommonAPI/CommonAPI.hpp>

#include <v1/BootAnimationService/BootAnimationProxy.hpp>
#include <v1/ThemeSkincareService/ThemeSkincareProxy.hpp>
#include <v1/SystemSeting/SystemSetingSyncProxy.hpp>

#include "baseinfologic.h"
#include "centerviewlogic.h"
#include "telltalesmlogic.h"

class AppLogic
{
public:
    AppLogic();

public:
    void appRun();

private:
    void checkServiceAvaliable();
    void currentThemeChanged(v1::ThemeSkincareService::ThemeSkincare::ThemeMode themeType);
    void currentSystemFormetChagned(SystemSetingType::Types::TimeFormat format);

private:
    boost::asio::io_context m_io;
    std::shared_ptr<std::thread> m_sendMessageToAnimation;
    std::shared_ptr<CommonAPI::Runtime> m_commonApiRT;
    TelltalesmLogic m_telltalesmLogic;
    BaseInfoLogic m_baseInfoLogic;
    CenterViewLogic m_centerViewLogic;
    std::shared_ptr<v1::BootAnimationService::BootAnimationProxy<>> m_bootAnimationProxy;
    std::shared_ptr<v1::ThemeSkincareService::ThemeSkincareProxy<>> m_themeSkincareProxy;
    std::shared_ptr<v1::SystemSeting::SystemSetingSyncProxy<>> m_systemSetingSyncProxy;
};

#endif