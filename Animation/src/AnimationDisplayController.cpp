#ifdef __linux__
#include "AnimationDisplayController.h"
#ifdef SWITCH_SOA
  #include "CommonApi.h"
  #include "CommonAPI/CommonAPI.hpp"
#endif

#ifdef __linux__
#include "appfw/application.hpp"
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>  
#endif

#define ANIMATION_IMAGE_PATH "/etc/animationRes/"
#define ANIMATION_IMAGE_COUNT  146
#define ANIMATION_IMAGE_SUFFIX ".png"
AppFw::Application * g_App = NULL;
AnimationDisplayController::AnimationDisplayController():Module()
{
  if(!init()){
    consolePrint("init AnimationDisplayController failed...");
  }
  consolePrint("-----------------------------------------------Init AnimationDisplayController ok...");
}

AnimationDisplayController::~AnimationDisplayController()
{
}

bool AnimationDisplayController::init()
{
//#ifdef SWITCH_SOA
  if(!startAnimationService()){
    consolePrint("startAnimation Service failed ...");
  }else {
    consolePrint("init startAnimation Service successfully...");
  }
  
  //m_aniService->setCallback(&AnimationDisplayController::OnReportStartupStatus);
//#endif
  startAnimation();
  return true;
}

bool AnimationDisplayController::startAnimation()
{
  std::map<int, std::string> imgPathList;
  int imgIndex = 0;
  for (int i = 1; i < ANIMATION_IMAGE_COUNT; )
  {
      std::string tmp = ANIMATION_IMAGE_PATH + std::to_string(i);
      imgPathList[imgIndex] = std::string(tmp + ANIMATION_IMAGE_SUFFIX);
      consolePrint("img[%d] path %s ... \n",imgIndex,  imgPathList[imgIndex].c_str());
      i += 2;
      imgIndex++;
      
  }

  std::fstream file(DRM_INI_CONFIG);
  if(!file) {
    consolePrint("File is not exist...");
    return false;
   }
   boost::property_tree::ptree pt;  
   boost::property_tree::ini_parser::read_ini(DRM_INI_CONFIG, pt); 

   int frameInterval = 30;
   auto fieldValue = pt.get_optional<std::string>("ANI.FrameInterval");
   if (fieldValue){
      frameInterval = pt.get<int>("ANI.FrameInterval");
      fprintf(stderr, "find frameInterval: %d\n", frameInterval);
   }else {
      fprintf(stderr, "not find frameInterval: %d\n", frameInterval);
   }

   bool loop = true;
   fieldValue = pt.get_optional<std::string>("ANI.Loop");
   if (fieldValue){
      loop = pt.get<bool>("ANI.Loop");
      fprintf(stderr, "find frameInterval: %s\n", loop?"true":"false");
   }else {
      fprintf(stderr, "not find loop: %s\n", loop?"true":"false");
   }

   int threadCount = 4;
   fieldValue = pt.get_optional<std::string>("ANI.ThreadCount");
   if (fieldValue){
      threadCount = pt.get<int>("ANI.ThreadCount");
      fprintf(stderr, "find ThreadCount: %d\n", threadCount);
   }else {
      fprintf(stderr, "not find ThreadCount: %d\n", threadCount);
   }

  m_aniCtl = std::make_shared<AnimationController>(imgPathList, frameInterval, true, LoadType::TYPE_ASYNC_CACHE, threadCount);
  if(!m_aniCtl) {
    consolePrint("Create AnimationController object failed !");
    return false;
  }
  m_aniCtl->start();
  consolePrint("******************************************************************start animation end********************************************************************");
  return true;
}

void AnimationDisplayController::unDisplay(int device)
{
}

void AnimationDisplayController::stopAnimation()
{
}

bool AnimationDisplayController::startAnimationService()
{
  //#ifdef SWITCH_SOA
    m_aniService = std::make_shared<AnimationServiceImpl>(this);
    if (!m_aniService)
    {
      consolePrint("alloc AnimationServiceImpl failed ...");
      return false;
    }
    
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    if(runtime){
      bool ret = false;
      uint8_t retryCount = 0;
      while (retryCount < 10 && !ret)
      {
        ret = runtime->registerService(m_domain, m_instance, m_aniService, m_connection);
        if (!ret)
        {
          consolePrint("register service failed ... retry count %d", retryCount);
        }else{
          consolePrint("register service successfully ...");
          return true;
        }
        retryCount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
    }
  //#endif
    return false;
}

void AnimationDisplayController::onProcess()
{
  //consolePrint("AnimationDisplayController onProcess ...");
  if(m_aniCtl->getPlayState()) {
    g_App->quit();
  }
}

//#ifdef SWITCH_SOA
void AnimationDisplayController::OnReportStartupStatus(const std::shared_ptr<CommonAPI::ClientId> _client, BootAnimation::DevType _dev, BootAnimation::StartupStatus _status)
{
    consolePrint("OnReportStartupStatus client _dev %s _status %s\n", _dev.toString(), _status.toString());
    printf("-------------------------------------OnReportStartupStatus client _dev %s _status %s\n", _dev.toString(), _status.toString());
    if (_dev == BootAnimation::DevType::CLUSTER)
    {
      m_aniCtl->switchClusterPlane(false);
    }else if(_dev == BootAnimation::DevType::CABIN) {
      m_aniCtl->switchIviPlane(false);
    }
    
}
//#endif
#endif
