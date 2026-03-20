#include "AnimationController.h"
#include <fstream>
#ifdef _WIN32
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
#endif // _WIN32

#define DRM_SHOW_CLUSTER_PICTURE_INDEX    72
#define DRM_SHOW_IVI_PICTURE_INDEX        72
#define DRM_SHOW_LOOP_PICTURE_INDEX       51
#define DRM_PLAY_SOUND_PICTURE_INDEX      50


AnimationController::AnimationController()
{
}

AnimationController::~AnimationController()
{
}

AnimationController::AnimationController(const std::map<int, std::string>& pathList, int frameInterval, bool bLoop, LoadType loadType, uint8_t threadCount )
{
  m_pathList = pathList;
  m_frameCount = pathList.size();
  m_frameInterval = 1000 / frameInterval ;
  m_isLooping = bLoop;
  m_loadType = loadType;
  m_queueMaxSize = threadCount;
  if(m_frameCount <= 0){
    consolePrint("frameCount < 0");
  }
  if (m_drmCtl == nullptr)
  {
    m_drmCtl = std::make_shared<DrmController>();
  }
  consolePrint("Animation pictures count :%d frameInterval :%d loop : %d load type: %d", m_frameCount, frameInterval, bLoop, m_loadType);
}

void AnimationController::setPath(const std::map<int, std::string>& pathList)
{
   m_pathList = pathList;
}

void AnimationController::setLooping(bool isLooping)
{
  m_isLooping = isLooping;
}

void AnimationController::setFrameInterval(int interval)
{
  m_frameInterval = 1000 / interval;
}

void AnimationController::setFrameCount(int count)
{
  m_frameCount = count;
}

void AnimationController::setAyncLoadType(LoadType loadType)
{
  m_loadType = loadType;
}

void AnimationController::start()
{
  consolePrint("start Drm device success m_loadType %d! std::this_thread::get_id() %d\n", m_loadType, std::this_thread::get_id());
#ifdef __linux__
  if(!m_drmCtl->init()) {
    consolePrint("Init Drm device failed...");
    return;
  }
#endif

  consolePrint("Init Drm device success m_loadType %d! std::this_thread::get_id() %d", m_loadType, std::this_thread::get_id());
  m_isPlaying = true;
  m_currentFrame = 0;
  m_threadDisPlay = std::thread(&AnimationController::play, this);
  //m_threadPlaySound = std::thread(&AnimationController::playSound, this);

  if (m_loadType == LoadType::TYPE_ASYNC_CACHE)
  {
      m_threadPool = std::make_shared<ThreadPool>(m_queueMaxSize);
      if (m_threadPool == nullptr)
      {
          consolePrint("init thread pool failed ! \n");

      }
      m_preloadThread = std::thread(&AnimationController::preload, this);
  }
}

void AnimationController::stop()
{
  m_isPlaying = false;
  if (m_threadDisPlay.joinable()) {
      m_threadDisPlay.join();
  }
  if (m_threadPlaySound.joinable()) {
      m_threadPlaySound.join();
  }
  if (m_preloadThread.joinable()) {
      m_preloadThread.join();
  }
}

void AnimationController::play()
{
  consolePrint("-----------------m_loadType %d---LoadType::TYPE_SYNC_NO_CACHE:%d--LoadType::TYPE_ASYNC_CACHE:%d-------------", m_loadType, LoadType::TYPE_SYNC_NO_CACHE, LoadType::TYPE_ASYNC_CACHE);
  if(m_loadType == LoadType::TYPE_SYNC_CACHE_ALL) {
    syncAllCacheDisplay();
  } else if (m_loadType ==  LoadType::TYPE_SYNC_NO_CACHE) {
    syncNoCacheDisplay();
  } else if (m_loadType ==  LoadType::TYPE_ASYNC_CACHE) {
    asyncCacheDisplay();
  }else {
    asyncCacheDisplay();
  }
}

void AnimationController::playSound()
{
    std::this_thread::sleep_for(std::chrono::seconds(7));
#ifdef __linux__
  std::string soundFile = "/usr/share/sounds/start.wav";
  std::fstream file(soundFile);
  if(file) {
    std::string soundCMD = "aplay -D hw:rockchipes8388 ";
    soundCMD = soundCMD + soundFile;
    system(soundCMD.c_str());
  }else {
     consolePrint("Sound file [%s] is not exist !", soundFile.c_str());
  }
#endif
#ifdef  _WIN32
  char szFilePath[MAX_PATH + 1] = { 0 };
  GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
  (strrchr(szFilePath, '\\'))[0] = 0;
  std::string exePath = szFilePath;
  std::string soundPath = exePath + "\\sounds\\start.wav";
  PlaySound(TEXT(soundPath.c_str()), NULL, SND_FILENAME  | SND_ASYNC);
#endif //  _WIN32
}

void AnimationController::switchClusterPlane(bool bSwitch)
{
  m_displayClusterSwitch = bSwitch;
}

void AnimationController::switchIviPlane(bool bSwitch)
{
  m_displayIviSwitch = bSwitch;
}

void AnimationController::showCluster(bool bShow)
{
#ifdef __linux__
  m_drmCtl->showCluster(bShow);
#endif
}

void AnimationController::showIVI(bool bShow)
{
#ifdef __linux__
  m_drmCtl->showIVI(bShow);
#endif
}

void AnimationController::syncNoCacheDisplay()
{
  consolePrint("------------------syncNoCacheDisplay------------------------------");
  while (m_isPlaying) {
    //std::string framePath = m_path + std::to_string(m_currentFrame.load()) + m_picSuffix;
    std::string framePath = m_pathList[m_currentFrame.load()];
    // Get  current start time point
    auto startTime = std::chrono::high_resolution_clock::now();
    ImageLoader reader(framePath.c_str());
    // Get current end time point
    auto endTime = std::chrono::high_resolution_clock::now();
    // Cacl timestamp
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // cout the duration time.
    //consolePrint("[syncNoCacheDisplay]Load the picture [%d] speend [%d] miliseconds \n", m_currentFrame.load(), duration.count());
    if (reader.isLoaded()) {
        paintOnDevice(reader); 
        m_currentFrame++;
    }
    
    if (m_currentFrame == m_frameCount) {
        if (m_isLooping) {
            m_currentFrame = 0;
        }
        else {
            m_isPlaying = false;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
  }
}

void AnimationController::syncAllCacheDisplay()
{
  consolePrint("------------------syncAllCacheDisplay------------------------------");
  std::vector<ImageLoader> frames;
  for (int i = 0; i < m_frameCount; i++) {
      std::string framePath = m_pathList[i];

      // Get  current start time point
      auto startTime = std::chrono::high_resolution_clock::now();
      ImageLoader reader(framePath.c_str());
      // Get current end time point
      auto endTime = std::chrono::high_resolution_clock::now();
      // Cacl timestamp
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

      // cout the duration time.
      consolePrint("[syncAllCacheDisplay] Load the picture [%d] spend [%d] milliseconds \n", i, duration.count());
      if (reader.isLoaded()) {
          frames.push_back(reader);
      }
  }
  while (m_isPlaying) {
      if (m_currentFrame < frames.size()) {
          // do something with the loaded frame data
          ImageLoader reader = frames[m_currentFrame];
          paintOnDevice(reader);
          m_currentFrame++;
      }
      if (m_currentFrame == m_frameCount) {
          if (m_isLooping) {
              m_currentFrame = 0;
          }
          else {
              m_isPlaying = false;
          }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval));
  }
}

void AnimationController::asyncCacheDisplay()
{
  consolePrint("-----------------------asyncCacheDisplay m_loadType %d-----------------------------------", m_loadType);
  while (m_isPlaying) {
    auto startTime = std::chrono::high_resolution_clock::now();
    if (m_imageLoaderQueue.size() > 0 && m_currentFrame < m_frameCount) {
        //std::unique_lock<std::mutex> lock(m_mutex);
        if (m_currentFrame == DRM_PLAY_SOUND_PICTURE_INDEX)
        {
          //m_threadPlaySound = std::thread(&AnimationController::playSound, this);
          
        }
        if (!m_displayClusterSwitch && m_displayCluster/* && m_currentFrame >= DRM_SHOW_CLUSTER_PICTURE_INDEX*/ )
        {
          showCluster(false);
          consolePrint("Close cluster ...m_currentFrame %d \n", m_currentFrame.load());
          printf("Close cluster ...m_currentFrame %d \n", m_currentFrame.load());
          m_displayCluster = false;
        }
        if (!m_displayIviSwitch && m_displayIvi /* && m_currentFrame >= DRM_SHOW_IVI_PICTURE_INDEX*/  )
        {
          showIVI(false);
          printf("Close IVI ...m_currentFrame %d \n", m_currentFrame.load());
          m_displayIvi = false;
        }
        m_mutex.lock();
        ImageLoader* pReader = m_imageLoaderQueue.front();       
        m_mutex.unlock();
CHECK_LOAD:
        if (pReader->isLoaded())
        {
            paintOnDevice(*pReader);
            consolePrint("--------------------Rendering frame picture is [%d] m_currentFrame is [%d] \n", pReader->getIndex(), m_currentFrame.load());
            m_mutex.lock();
            m_imageLoaderQueue.pop();
            m_mutex.unlock();
    
            if (pReader)
                delete pReader;
            m_currentFrame++;
        }
        else
        {
            //consolePrint("Wait for enable picture loaded in the cache...m_currentFrame %d m_frameCount %d m_preloadIndex %d", m_currentFrame.load(), m_frameCount, m_preloadIndex.load());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            goto CHECK_LOAD;
            continue;
        }
          
    }else {
      //consolePrint("There is no enable picture loaded in the cache...m_currentFrame %d m_frameCount %d m_preloadIndex: %d m_imageLoaderQueue.size() %d", m_currentFrame.load(), m_frameCount, m_preloadIndex.load(), m_imageLoaderQueue.size());
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      continue;
    }
   
    if (m_currentFrame == m_frameCount) {
        if (m_isLooping) {
            m_preloadIndex = DRM_SHOW_LOOP_PICTURE_INDEX;
            m_currentFrame = DRM_SHOW_LOOP_PICTURE_INDEX;
        }
        else {
            m_isPlaying = false;
            
        }
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    consolePrint("*********************************************************************************************************[asyncCacheDisplay:%d] one picture spend %d ms", m_currentFrame.load(), duration.count());
    if(duration.count() > m_frameInterval) {
      consolePrint("-------------------------[asyncCacheDisplay] one picture spend %d ms  ------------", duration.count());
    }else {
       std::this_thread::sleep_for(std::chrono::milliseconds(m_frameInterval - duration.count()));
    }

    if(!m_displayCluster && !m_displayIvi) {
      m_isPlaying = false;
    }
  }
  m_drmCtl->unInit();
  m_bExit = true;
}

void AnimationController::paintOnDevice(ImageLoader &reader)
{
#ifdef _WIN32

  // 获取图像数据
  std::vector<unsigned char>& imageData = reader.getData();

  // Paint.
  // Send the frame data to the WM_PAINT message to draw the image
  HDC hdc = GetDC(m_displayHwnd);
  BITMAPINFO bmi = { 0 };
  bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
  bmi.bmiHeader.biWidth = reader.getWidth();
  bmi.bmiHeader.biHeight = 0 - (reader.getHeight());
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = reader.getChannel();
  bmi.bmiHeader.biCompression = BI_RGB;
  SetDIBitsToDevice(hdc, 0, 0, reader.getWidth(), reader.getHeight(), 0, 0, 0, reader.getHeight(), imageData.data(), &bmi, DIB_RGB_COLORS);
  ReleaseDC(NULL, hdc);
#endif // _WIN32
  consolePrint("start play ...");
#ifdef __linux__
  //m_drmCtl->displayImage((uint8_t*)reader.getData().data(), reader.getData().size(), reader.getWidth(), reader.getHeight());
  auto startTime = std::chrono::high_resolution_clock::now();
  m_drmCtl->displayImage(reader, reader.getData().size(), reader.getWidth(), reader.getHeight());
  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
#endif
  consolePrint("end play ...duration %d", duration.count());
  if( duration.count() > 20){
    consolePrint("-----------------------------------------------------------time spend too long %d ", duration.count());
  }
#ifdef __linux__

#endif // __linux__
}

void AnimationController::preload()
{
  consolePrint("------------preload-------------");
  while (m_isPlaying) {
    if (m_isLooping && m_preloadIndex >= m_frameCount) {
        m_preloadIndex = DRM_SHOW_LOOP_PICTURE_INDEX;
    }
    else if (!m_isLooping && m_preloadIndex >= m_frameCount)
    {
      consolePrint("------------stop preload-------------");
      break;
    }
    

    //consolePrint("Png reader queue size is [%d]  current Frame is [%d]\n", m_imageLoaderQueue.size(), m_currentFrame.load());
    bool indexGreaterCurrentFrame = m_preloadIndex < m_currentFrame ? ((m_frameCount - m_currentFrame + m_preloadIndex) <= m_queueMaxSize) : true;
    bool indexLessCurrentFrame = m_preloadIndex >= m_currentFrame ? (m_preloadIndex - m_currentFrame) <= m_queueMaxSize : true;
    if (m_imageLoaderQueue.size() < m_queueMaxSize && indexGreaterCurrentFrame && indexLessCurrentFrame) {
        //std::string framePath = m_path + std::to_string(m_preloadIndex) + m_picSuffix;
        std::string framePath = m_pathList[m_preloadIndex];
        ImageLoader* pReader = new ImageLoader();
        std::unique_lock<std::mutex> lock(m_mutex);
        m_imageLoaderQueue.emplace(pReader);
        consolePrint("Frame picture [%s] is loadeding   --preloadIndex:[%d] --current Rendering Index:[%d]\n", framePath.c_str(), m_preloadIndex.load(), m_currentFrame.load());
        int tmpIndex = m_preloadIndex.load();
        m_threadPool->enqueue([=]() {
            // Get  current start time point
            auto startTime = std::chrono::high_resolution_clock::now();
            // Load frame picture.
            pReader->readPng(framePath.c_str(), tmpIndex);
            auto loadTime = std::chrono::high_resolution_clock::now();
            auto durationLoad = std::chrono::duration_cast<std::chrono::milliseconds>(loadTime - startTime);
            consolePrint("--------Load PNG %s spend time %d thread id %d-----------", framePath.c_str(), durationLoad.count(), std::this_thread::get_id());
            if (pReader->isLoaded())
            {
                // Get current end time point
                auto endTime = std::chrono::high_resolution_clock::now();
                // Cacl timestamp
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                // cout the duration time.
                consolePrint("Frame picture [%s] is loaded current frame is [%d]  spend [%d] milliseconds loadIndex:[%d]\n", framePath.c_str(), m_currentFrame.load(), duration.count(), tmpIndex);
                consolePrint("---------preload index [%d] thread id: %d---------", tmpIndex, std::this_thread::get_id());
            }
        });
        m_preloadIndex++;
        
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

bool AnimationController::getPlayState()
{
  return m_bExit;
}
