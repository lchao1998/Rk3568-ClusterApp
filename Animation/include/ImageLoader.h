/**@file  		ImageLoader.h
* @brief    	Load image wrapper
* @details  	Load image and get it's properties.
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

#include <vector>
#include "CommonApi.h"

class ImageLoader {
public:
    ImageLoader();
    ImageLoader(const char* filename, int frameIndex = -1);
    ~ImageLoader();
    /**
     * @brief: Load Png format image's data.
     * @param[in] filename image path.
     * @param[in] frameIndex image frame index.
     */
    bool readPng(const char* filename, int frameIndex = -1);
    unsigned int getWidth() { return m_width; }
    unsigned int getHeight() { return m_height; }
    bool isLoaded() { return m_bLoad; }
    std::vector<unsigned char>& getData() { return m_imageData; }
    std::vector<unsigned char>& getSubData(int index);
    void setIndex(int index) { m_index = index; }
    int getIndex() { return m_index; }
    unsigned short getChannel() { return m_numChannels; }
private:
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    unsigned short m_numChannels = 32;
    std::vector<unsigned char> m_imageData;
    bool m_bLoad = false;
    int m_index = -1; // index of sequnce frame.
    std::vector<unsigned char> m_imageData1;
    std::vector<unsigned char> m_imageData2;
    std::vector<unsigned char> m_imageData3;
};