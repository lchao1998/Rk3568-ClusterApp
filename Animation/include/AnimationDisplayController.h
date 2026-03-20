/**@file  		AnimationDisplayController.h
* @brief    	The classs can controllers the animation image buffer in different drm display devices.
*             animation is auto run.
* @details  	
* @author		  xuqiang
* @email		  xu.qiang@zlingsmart.com
* @date			  2023-06-20
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
#ifdef __linux__
#pragma once
#include "AnimationController.h"
#include "DrmController.h"
#include "appfw/module.hpp"
//#ifdef SWITCH_SOA
#include "AnimationServiceImpl.h"
#include "CommonApi.h"
#include "BootAnimationStubDefault.hpp"
#include "BootAnimation.hpp"
//#endif
using namespace AppFw;
using namespace v1::BootAnimationService;
class AnimationServiceImpl;
//class AnimationController;
class AnimationDisplayController : public AppFw::Module
{
private:
  /* data */
public:
  AnimationDisplayController(/* args */);
  ~AnimationDisplayController();
  /**
  * @fn init
  * @brief init animation controller with init service and animation controller. 
  * @return void
  */
  bool init();
  /**
  * @fn startAnimation
  * @brief start animation 
  * @return true: success; false: failed
  */
  bool startAnimation();
  /**
  * @fn unDisplay
  * @brief set the display device with no data.
  * @return void
  */
  void unDisplay(int device);
  /**
  * @fn stopAnimation
  * @brief stop animation 
  * @return void
  */
  void stopAnimation();
  /**
  * @fn startAnimationService
  * @brief start the animation service.
  * @return true: success; false: failed
  */
  bool startAnimationService();
  /**
  * @fn OnReportStartupStatus
  * @brief Call back function.
  * @param[in] _client the client id
  * @param[in] _dev the device type
  * @param[in] _status the startup status
  * @return void
  */
 //#ifdef SWITCH_SOA
  void OnReportStartupStatus(const std::shared_ptr<CommonAPI::ClientId> _client, BootAnimation::DevType _dev, BootAnimation::StartupStatus _status);
 //#endif 
protected:
  /**
  * @fn onProcess
  * @brief main thread loop
  * @return void
  */
  virtual void onProcess();

private:
  std::shared_ptr<AnimationController> m_aniCtl;
//#ifdef SWITCH_SOA
  std::shared_ptr<AnimationServiceImpl> m_aniService;
//#endif
  const std::string m_domain = "local";
  const std::string m_instance = "BootAnimationService.BootAnimation";
  const std::string m_connection = "BootAnimationServiceApp";
};
#endif

