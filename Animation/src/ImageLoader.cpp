#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "libpng16/png.h"
#include <chrono>

#define RESOLUTION_1920X3 5760
#define RESOLUTION_1920X3X720 4147200

ImageLoader::ImageLoader()
{
}

ImageLoader::ImageLoader(const char *filename, int frameIndex)
{
  readPng(filename); m_index = frameIndex; 
}

ImageLoader::~ImageLoader()
{
}
bool read_png_file(const char *filename, unsigned char** image_data, int* width, int* height) {
    if(strlen(filename) == 0) return false;
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error opening PNG file %s:.\n", filename);
        return false;
    }

    png_byte header[8];
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8)) {
        consolePrint("Not a valid PNG file.");
        fclose(fp);
        return false;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        consolePrint("Error creating PNG read structure.");
        fclose(fp);
        return false;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        consolePrint("Error during PNG file reading.");
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) {
        consolePrint("Error during PNG file reading.");
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        return false;
    }

    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    int image_width = png_get_image_width(png, info);
    int image_height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    if (color_type == PNG_COLOR_TYPE_RGBA) {
        // Allocate memory for image data
        *image_data = (unsigned char*)malloc(4 * image_width * image_height);
        *width = image_width;
        *height = image_height;

        // Set up row pointers
        png_bytep row_pointers[image_height];
        for (int y = 0; y < image_height; y++) {
            row_pointers[y] = *image_data + (y * 4 * image_width);
        }

        png_read_image(png, row_pointers);

        // Clean up
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);

        return true;
    } else if (color_type == PNG_COLOR_TYPE_RGB) {
        // Allocate memory for image data
        *image_data = (unsigned char*)malloc(3 * image_width * image_height);
        *width = image_width;
        *height = image_height;

        // Set up row pointers
        png_bytep row_pointers[image_height];
        for (int y = 0; y < image_height; y++) {
            row_pointers[y] = *image_data + (y * 3 * image_width);
        }

        png_read_image(png, row_pointers);

        // Clean up
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);

        return true;
    }else {
        fprintf(stderr, "Unsupported color type (not RGBA).\n");
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        return false;
    }
}
bool ImageLoader::readPng(const char *filename, int frameIndex)
{
  auto startTime = std::chrono::high_resolution_clock::now();
  consolePrint("Loading %s ...", filename);
  unsigned error = 0;
#ifdef STB_IMAGE_IMPLEMENTATION
        int width = 0;
        int height = 0;
        int numChannels = 3;
        //unsigned char* imgData = stbi_load(filename, &width, &height, &numChannels, 3);
        
        unsigned char* imgData;
        read_png_file(filename, &imgData, &width, &height);
        //unsigned char* imgData = nullptr;
        //lodepng_decode24_file(&imgData, &width, &height, filename);
        if (imgData == nullptr)
        {
            consolePrint("Failed to load image %s", filename);
        }

        long imgSize = width * height * numChannels;
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        consolePrint("Change stbi_load file spend time : %d", duration.count());
        
        //Change the BGR to RGB
        for (size_t i = 0; i < imgSize; i += 3) {
            unsigned char temp = imgData[i];   // Keep blue channel.
            imgData[i] = imgData[i + 2];     // copy read color to blue channel.
            //imageData[i + 1] = imageData[i + 1]; // keep green channel with no change
            imgData[i + 2] = temp; // copy Alpha channel value to blue channel.
        }
        auto endTime1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime1 - endTime);
        consolePrint("Change RGBA spend time : %d", duration1.count());
        // uint8_t *pIndex = imgData;
        // /// TODO delete this  after the VGA is OK.
        // unsigned char* imgData1 = new unsigned char[RESOLUTION_1920X3X720];
        // unsigned char* imgData2 = new unsigned char[RESOLUTION_1920X3X720];
        // unsigned char* imgData3 = new unsigned char[RESOLUTION_1920X3X720];
        // void* pB0 = imgData1;
        // void* pB1 = imgData2;
        // void* pB2 = imgData3;

        // for (size_t i = 0; i < 720; i++)
        // {
        //     memcpy(pB0, pIndex, RESOLUTION_1920X3 );
        //     pIndex = (uint8_t*)pIndex + RESOLUTION_1920X3;
        //     memcpy(pB1, pIndex, RESOLUTION_1920X3 );
        //     pIndex = (uint8_t*)pIndex + RESOLUTION_1920X3;
        //     memcpy(pB2, pIndex, RESOLUTION_1920X3 );
        //     pIndex = (uint8_t*)pIndex + RESOLUTION_1920X3;
            
        //     pB0 = (uint8_t*)pB0 + RESOLUTION_1920X3;
        //     pB1 = (uint8_t*)pB1 + RESOLUTION_1920X3;
        //     pB2 = (uint8_t*)pB2 + RESOLUTION_1920X3;
        // }

        // m_imageData1.assign(imgData1, imgData1+ RESOLUTION_1920X3X720 );
        // m_imageData2.assign(imgData2, imgData2+ RESOLUTION_1920X3X720 );
        // m_imageData3.assign(imgData3, imgData3+ RESOLUTION_1920X3X720 );
        // delete imgData1;
        // delete imgData2;
        // delete imgData3;
        // consolePrint("m_imageData1 size %d", m_imageData1.size());
        // consolePrint("m_imageData2 size %d", m_imageData2.size());
        // consolePrint("m_imageData3 size %d", m_imageData3.size());

        // auto endTime2 = std::chrono::high_resolution_clock::now();
        // auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime2 - endTime1);
        // consolePrint("Change Data spend time : %d", duration2.count());
        m_imageData.assign(imgData, imgData + imgSize);
        m_width = static_cast<unsigned int>(width);
        m_height = static_cast<unsigned int>(height);
        m_numChannels = numChannels * 8;
        //stbi_image_free(imgData);
        free(imgData);
    

#elif
        unsigned error = lodepng::decode(m_imageData, m_width, m_height, png);
#endif // STB_IMAGE_IMPLEMENTATION

        //consolePrint("readPng %s [code: %d] [frame index: %d]\n", filename, error, frameIndex);

        if (error) {
            return false;
        }
        m_bLoad = true;
        m_index = frameIndex;
        auto endTime3 = std::chrono::high_resolution_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime3 - startTime);
        consolePrint("Change end spend time : %d", duration3.count());
        return true;
}

std::vector<unsigned char> &ImageLoader::getSubData(int index)
{
  consolePrint("=====index %d", index);
  if (index == 0)
  {
    consolePrint("return m_imageData1 size %d", m_imageData1.size());
    return m_imageData1;
  }else if (index == 1)
  {
    consolePrint("return m_imageData2 size %d", m_imageData2.size());
    return m_imageData2;
  } else if (index == 2)
  {
    consolePrint("return m_imageData3 size %d", m_imageData3.size());
    return m_imageData3;
  }else
  {
    consolePrint("return m_imageData----size %d", m_imageData.size());
    return m_imageData;
  }
  
}
