/**@file  		DrmController.h
* @brief    	Handle the DRM device 
* @details  	Wapper the libdrm to controller the display device.
* @author		  xuqiang
* @email		  xu.qiang@zlingsmart.com
* @date			  2023-07-19
* @version		V0.0.1
* @copyright	Copyright (c) 2023-2024  ZlingSmart Company Ltd.
**********************************************************************************
* @attention    linux
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
#ifdef __linux__
#include "DrmController.h"
#include "ImageLoader.h"
#include <memory>
#include <atomic>
#include <vector>
#include <mutex>

#ifdef __linux__
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <sys/mman.h>
    #include <unistd.h>
    #include <sys/mman.h>
    #include <drm/drm.h>
    #include <drm/drm_mode.h>
    #include <drm/drm_fourcc.h>
    #include <xf86drm.h>
    #include <xf86drmMode.h>
#endif // __linux__

/// DRM设备文件路径
#define DRM_DEVICE_CARD0  "/dev/dri/card0"      
#define DRM_DEVICE_CARD1  "/dev/dri/card1"   
#define DRM_DEVICE_CARD2  "/dev/dri/card2"           
//#define IMAGE_PATH "animationMiddle/run1.png"       // 图片路径

#define DRM_MAX_DISPLAY 3

struct DrmDisplayDev;
/**
* @brief  The Drm ini config value.
* @detail To set the drm parameters.
*/
struct DrmIniConfig
{
   int plane_id;
   int crtc_id;
   int plane_zpos;
};

class DrmController {
public:
  struct buffer_object {
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t handle;
    uint32_t size;
    uint8_t *vaddr;
    uint32_t fb_id;
    uint32_t plane_id;
    uint32_t crtc_id;
    uint64_t plane_zpos;
    std::atomic<bool> bShow = true;
    std::atomic<bool> bEnable = false; 
  };
public:
  DrmController();
  ~DrmController();
  DrmController(const DrmController* ) = delete ;
  DrmController& operator=(const DrmController& ) = delete;
public:
  /**
   * @brief Init DRM device
   * @detail Use to open the drm device with some paramerters.
   *
   * @return false: Init failed; true : success 
  */
  bool init();

  /**
   * @brief Inir DRM plane
   * @detail the plane for display layer.
   *
   * @return false: Init failed; true : success 
  */
  bool initPlane();
  /**
   * @brief Open DRM device
   * @detail Use to open the drm device with some paramerters.
   * 
   * @param[in] devicePath the drm device path
   * @param[in] type open style
   * @return false: open failed; true : success 
  */
  //bool openDrmDev(const char* devicePath, int type = O_RDWR);
  /**
   * @brief Create DRM Buffer
   * @detail 
   * @param[in] bo the buffer_object.
   * @return false: failed; true : success 
  */
  //bool createDumb( buffer_object* bo);
  /**
   * @brief Dispaly image data 
   * @detail 
   * @param[in] imageData the image data buffer pointer.
   * @param[in] size the image buffer size.
   * @param[in] width the screen width.
   * @param[in] height the screen height.
   * @return false: failed; true : success 
  */
  bool displayImage(ImageLoader& imageData, long size, uint32_t width,  uint32_t height);
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

  /**
   * @brief destroy the resources
   * @return void
  */
  void unInit();

private:
  /**
   * @brief Initilize Drm parameters with ini configure .
  */
  bool initWithIni();
  /**
   * @brief get the device property .
  */
  uint32_t getProperty(int fd, drmModeObjectProperties *props, const char *name);

  /**
   * @brief Find the enable crtc.
   * @param[in] fd : device id.
   * @param[in] res : mode resource.
   * @param[in] conn : mode connector.
   * @param[in] dev : the dispplay struct.
   * @return int : state
  */
  int drmdisplayFindCrtc(drmModeRes *res, drmModeConnector *conn, struct DrmDisplayDev *dev);

  /**
   * @brief Create Dump buffer.
   * @param[in] fd : device id.
   * @param[in] dev : the dispplay struct.
   * @return int : state.
  */
  int drmdisplayCreateFb(struct DrmDisplayDev *dev);

  /**
   * @brief Setup dev envirenment.
   * @param[in] res : mode resource.
   * @param[in] conn : mode connector.
   * @param[in] dev : the dispplay struct.
   * @return int : state.
  */
  int drmdisplaySetupDev(drmModeRes *res, drmModeConnector *conn, struct DrmDisplayDev *dev);

  /**
   * @brief Open device
   * @param[out] out : device id.
   * @param[in] node : device node to open.
   * @return int : state.
  */
  int drmdisplayOpen(int *out, const char *node);

  /**
   * @brief Prepare the drm envirenment.
   * @return int : state.
  */
  int drmdisplayPrepare();

  /**
   * @brief Cleanup the drm envirenment.
   * @return int : state.
  */
  void drmdisplayCleanup();
private:
  /// @brief Opened devide ID.
  int m_fd = -1;
  /// @brief drm display list.
  struct DrmDisplayDev *m_drmdisplayList = nullptr;
  /// @brief mutex for drmdisplay list.
  std::mutex m_mutex;
  /// @brief drm ini configuration. Deices: DSI-1 HDMI-1,HDMI-2
  struct DrmIniConfig m_arrayDrmIniConf[3];
  
};
#endif /// linux