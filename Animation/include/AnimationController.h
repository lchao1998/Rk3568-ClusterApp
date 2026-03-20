/**@file  		AnimationController.h
* @brief    	Animation controller that control the start 、stop parameters
* @details  	Create a animation by AnimationController in linux or windows.
*               AnimationController has thread types to load pictures by LoadType.
* @author		xuqiang
* @email		xu.qiang@zlingsmart.com
* @date			2023-06-20
* @version		V0.0.1
* @copyright	Copyright (c) 2023-2024  ZlingSmart Company Ltd.
**********************************************************************************
* @attention
* 硬件平台: (可选) \n
* SDK版本： (可选)
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2023/04/17  <td>1.0      <td>zlingsmart  <td>创建初始版本
* </table>
*
**********************************************************************************
*/
#pragma once
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <mutex>
#include <atomic>
#include <stdio.h>
#include <cstring>
#include <map>  

#include "ImageLoader.h"
#include "ThreadPool.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include "CommonApi.h"
#ifdef __linux__
#include "DrmController.h"
#endif
enum LoadType
{
    TYPE_SYNC_CACHE_ALL = 0,
    TYPE_SYNC_NO_CACHE,
    TYPE_ASYNC_CACHE
};

class AnimationController {
public:
    AnimationController();
    ~AnimationController();
    /**
     * @fn AnimationController
     * @brief Construction function 
     * @param pathList the animation picture resources's paths.
     * @param frameInterval the animation frame interval ,defalut is 100.
     * @param bLoop whether the animation loop playback. 
     * @param loadType the animation resources loade type. default is TYPE_ASYNC_CACHE.
     * @param threadCount the count of  animation resources loading thread . default is 4
     * @return true: success; false: failed.
     */
    AnimationController(const std::map<int, std::string>& pathList, int frameInterval = 30, bool bLoop = false, LoadType loadType = LoadType::TYPE_ASYNC_CACHE, uint8_t threadCount = 4);

    /**
     * @fn setPath
     * @brief to set animation pictures's paths.
     * @param pathList the animation picture resources's paths.
     * @return void
     */
    void setPath(const std::map<int, std::string>& pathList);

    void setLooping(bool isLooping);

    void setFrameInterval(int interval);

    void setFrameCount(int count);

    void setAyncLoadType(LoadType loadType);

    /**
     * @fn start
     * @brief to start animation.
     * @return void
     */
    void start();

    /**
     * @fn stop
     * @brief to stop animation.
     * @return void
     */
    void stop();

#ifdef _WIN32
    void setDisplyHwnd(HWND hwnd) {
        m_displayHwnd = hwnd;
    }
#endif // __WIN32

    /**
     * @brief Controller whether to show cluster
     * @param[in] bSwitch true: show false:do not show.
     * @return void
     */
    void switchClusterPlane(bool bSwitch);

    /**
     * @brief Controller whether to show IVI
     * @param[in] bSwitch true: show false:do not show.
     * @return void
     */
    void switchIviPlane(bool bSwitch);
    
    /**
     * @fn get state
     * @brief  return true / flase
     * @return return true / flase
     */
    bool getPlayState();
private:
    /**
     * @fn play
     * @brief to display animation frames.
     * @return void
     */
    void play();
    /**
     * @fn playSound
     * @brief to display animation sound.
     * @return void
     */
    void playSound();

    /**
     * @fn syncNoCacheDisplay
     * @brief load  the resources one by one to display animation frames .
     * @return void
     */
    void syncNoCacheDisplay();
    /**
     * @fn syncAllCacheDisplay
     * @brief load all the resources to display animation frames .
     * @return void
     */
    void syncAllCacheDisplay();

    /**
     * @fn syncNoCacheDisplay
     * @brief Asynchronous load some animation resources to display animation frames .
     * @return void
     */
    void asyncCacheDisplay();

    /**
     * @fn paintOnDevice
     * @brief  To paint on device content .
     * @return void
     */
    void paintOnDevice(ImageLoader& reader);

    /**
     * @fn preload
     * @brief  To preload the animation resources .
     * @return void
     * @ref asyncCacheDisplay
     */
    void preload();

private:
    /**
     * @brief Controller whether to show cluster
     * @param[in] bShow true: show false:do not show.
     * @return void
     */
    void showCluster(bool bShow);

    /**
     * @brief Controller whether to show IVI
     * @param[in] bShow true: show false:do not show.
     * @return void
     */
    void showIVI(bool bShow);
private:
    std::string m_path;
    std::map<int, std::string> m_pathList;
    bool m_isPlaying;
    bool m_isLooping;
    bool m_bExit = false;
    int m_frameInterval;
    std::atomic<int> m_currentFrame;
    int m_frameCount; // set this value based on the number of frames in the sequence
    std::thread m_threadDisPlay;
    std::thread m_preloadThread;
    std::thread m_threadPlaySound;
#ifdef _WIN32
    HWND m_displayHwnd;
#endif // _WIN32
#ifdef __linux__
    std::shared_ptr<DrmController> m_drmCtl = nullptr;
#endif // __linux__
    LoadType m_loadType;

    std::shared_ptr<ThreadPool> m_threadPool = nullptr;
    std::queue<ImageLoader*> m_imageLoaderQueue;
    std::mutex m_mutex;
    int m_queueMaxSize = 2;
    std::atomic<int> m_preloadIndex = 0;
    
    /// @brief Controller the cluster HMI display, default is true.
    bool m_displayClusterSwitch = true;
    bool m_displayIviSwitch = true;

    /// @brief Whether Cluster and Ivi is display;
    bool m_displayCluster = true;
    bool m_displayIvi = true;
};


