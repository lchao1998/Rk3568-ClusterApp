/**@file  		AnimationService.h
* @brief    	Animation service that can contact with IVI application and Cluster application as a server.
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
//#ifdef SWITCH_SOA
#pragma once
#include <string>
#include "CommonApi.h"
#include "BootAnimationStubDefault.hpp"
#include "BootAnimation.hpp"
#include "AnimationDisplayController.h"

class AnimationDisplayController;
using namespace v1::BootAnimationService;
class AnimationServiceImpl : public v1::BootAnimationService::BootAnimationStubDefault
{

public:
  AnimationServiceImpl(AnimationDisplayController* parent);
  virtual ~AnimationServiceImpl();
  /**
  * @brief: Event with report status.
  * @param[in] dev 设备类型
  * @param[in] status 启动状态
  */
  void ReportStartupStatus(const std::shared_ptr<CommonAPI::ClientId> _client, BootAnimation::DevType _dev, BootAnimation::StartupStatus _status);
  // Define callback function.
  using cbReportStartupStatus = void(*)(const std::shared_ptr<CommonAPI::ClientId> _client, BootAnimation::DevType _dev, BootAnimation::StartupStatus _status);
  /**
  * @brief: set call back fuction.
  * @param[in]: callBack fuction handler
  */
  void setCallback(cbReportStartupStatus callBack);
private:
  cbReportStartupStatus m_callBack = nullptr;
  AnimationDisplayController* m_aniDisplayController;
};
//#endif
