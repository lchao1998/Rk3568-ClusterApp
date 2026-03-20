/**@file  		CommomApi.h
* @brief    	Common Api here like print function.
* @details  	
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

#include <string>
#include <iostream>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#elif defined __linux__
#include <unistd.h>
#include <cstdarg>
#include <zl_log.h>
#endif // _WIN32 

/**
 * @brief: console printf on windows/linux.
 * @params: (in)format input format.
 * @params: (in)... some the need to format.
 */
static void consolePrint(const char* format, ...)
{

    va_list args;
    va_start(args, format);

#ifdef _WIN32
    const int bufferSize = 1024;
    char buffer[bufferSize];
    vsnprintf_s(buffer, bufferSize, _TRUNCATE, format, args);
    OutputDebugStringA(buffer); // Windows API
    OutputDebugStringA("\n"); // add \n
#else
#ifdef CONSOLE_LOG
    vprintf(format, args); // Linux stand output
    putchar('\n'); //  add \n
#else
    logDebug(format, args);
#endif
#endif

    va_end(args);

}


#define DRM_INI_CONFIG     "/etc/animation.ini"


