//#ifdef SWITCH_SOA
#include "AnimationServiceImpl.h"
#include "CommonAPI/CommonAPI.hpp"
#include <thread>

AnimationServiceImpl::AnimationServiceImpl(AnimationDisplayController* parent)
{
  m_aniDisplayController = parent;
}

AnimationServiceImpl::~AnimationServiceImpl()
{
}

void AnimationServiceImpl::ReportStartupStatus(const std::shared_ptr<CommonAPI::ClientId> _client, BootAnimation::DevType _dev, BootAnimation::StartupStatus _status)
{
  // (void)_client;
  // (void)_dev;
  // (void)_status;
  consolePrint("-------------------------------------------------ReportStartupStatus \n");
  //consolePrint("ReportStartupStatus client _dev %s _status %s\n", _dev.toString(), _status.toString());
  consolePrint("ReportStartupStatus client _dev %s _status %s\n", _dev.toString(), _status.toString());
  //m_callBack(_client, _dev, _status);
  if(m_aniDisplayController){
    m_aniDisplayController->OnReportStartupStatus(_client, _dev, _status);
  }
}

void AnimationServiceImpl::setCallback(cbReportStartupStatus callBack)
{
  m_callBack = callBack;
}
//#endif
