// Animation.cpp: 定义应用程序的入口点。

#include <iostream>
#include <vector>
#include <thread>
#include <signal.h>
#ifdef __linux__
#include "appfw/application.hpp"
#endif
#include <map>

#ifdef _WIN32
    #include <windows.h>
    #include <gdiplus.h>
#elif __linux__
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
    #include <gbm.h>
    #include <zl_log.h>
#endif // _WIN32

#include "AnimationController.h"
#include "AnimationDisplayController.h"
#include "CommonApi.h"

#ifdef __linux__
extern AppFw::Application * g_App;


/**
* @fn signal_handler
* @brief catch signal callback
* @param int sig: signal id
* @return:void
*/
void signal_handler(int sig)
{
    //logInfo("[ClusterController] Catch Signal %d Stop Task", sig);

    g_App->quit();

}
#endif

using namespace std;

// Define the window size
const int WINDOW_WIDTH = 5760;
const int WINDOW_HEIGHT = 720;

// Define the frame rate
const int FRAME_RATE = 30;

// Picture resourses.
// Define the path to the image files
//const string IMAGE_PATH = "animationMin/run";
//const string IMAGE_PATH = "water/water";
//#define IMG_SIZE   37
#define IMG_SIZE   360
//const string IMAGE_PATH = "animationMiddle\\";
const string IMAGE_PATH = "animationRes\\";
//const string IMAGE_PATH = "animationMax/run";

// Define the number of images to load
const int NUM_IMAGES = 8;

// Define the current image index
int currentImageIndex = 0;

#ifdef _WIN32

//获取程序exe所在路径，字符最后没有斜杠
std::string GetExePath()
{
    char szFilePath[MAX_PATH + 1] = { 0 };
    GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
    /*
    strrchr:函数功能：查找一个字符c在另一个字符串str中末次出现的位置（也就是从str的右侧开始查找字符c首次出现的位置），
    并返回这个位置的地址。如果未能找到指定字符，那么函数将返回NULL。
    使用这个地址返回从最后一个字符c到str末尾的字符串。
    */
    (strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串//
    std::string path = szFilePath;
    return path;
}


//strSrcPath 源文件路径 strDestPath目标路径

void GetImgPathList(std::map<int, std::string>& imgPathList) {

    std::string exePath = GetExePath();
    
    
    for (int i = 0; i < IMG_SIZE; i++)
    {
        std::string imgPath = exePath + "\\" + IMAGE_PATH;
        //std::string dstPath = exePath + "\\animationMiddle\\" + std::to_string(i) + ".png";
        imgPath = imgPath + std::to_string(i) + ".png";
        imgPathList[i] = imgPath;
        //::MoveFile(LPTSTR(imgPath.c_str()), LPTSTR(dstPath.c_str()));
    }
}
//std::map<int, std::string> imgPathList;
//GetImgPathList(imgPathList);
// Init AnimationController
AnimationController* ani = nullptr;
// Define the window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        ani->start();
        ani->setDisplyHwnd(hwnd);
        break;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Display the current image
        //displayImage(hdc);

        EndPaint(hwnd, &ps);
        /*
        // Get  current start time point
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        // Cacl timestamp
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        startTime = endTime;
        // cout the duration time.
        consolePrint("OnPaint time: %d 毫秒\n", duration.count());
        */
        break;
    }
    case WM_DESTROY: {
        ani->stop();
        PostQuitMessage(0);
        break;
    }
    case WM_TIMER: {
        //InvalidateRect(hwnd, NULL, TRUE);
        break;
    }
    default: {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    }
    return 0;
}


// Define the main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    std::map<int, std::string> imgPathList;
    GetImgPathList(imgPathList);
    // Init AnimationController
    ani = new AnimationController(imgPathList, 0, false, AnimationController::LoadType::TYPE_ASYNC_CACHE);
    // Register the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WindowClass";
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        "WindowClass",
        "Animation",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // Load the images
    //loadImages();

    // Set the frame rate
    int frameTime = 1000 / FRAME_RATE;
    std::cout << "frameTime :" << frameTime << std::endl;
    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    //SetTimer(hwnd, 1, frameTime, NULL);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Update the current image index
        currentImageIndex = (currentImageIndex + 1) % NUM_IMAGES;

        // Wait for the frame time
        //Sleep(frameTime);
    }
    return 0;

    }
#elif __linux__

#if 0 
    #define DRM_DEVICE "/dev/dri/card0"  // DRM设备文件路径
    #define IMAGE_PATH "animationMiddle/run1.png"       // 图片路径
    int main() {
    int fd;
    int ret;
    struct drm_mode_create_dumb create_dumb;
    struct drm_mode_map_dumb map_dumb;
    struct drm_mode_fb_cmd cmd;
    uint32_t handle;
    uint8_t *buffer = NULL;
    FILE *file;
    uint32_t width, height;

    // 打开DRM设备
    fd = open(DRM_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    // 打开图片文件
    file = fopen(IMAGE_PATH, "rb");
    if (file == NULL) {
        perror("fopen");
        close(fd);
        return -1;
    }

    // 读取图片数据
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    buffer = (uint8_t*)malloc(size);
    if (buffer == NULL) {
        perror("malloc");
        fclose(file);
        close(fd);
        return -1;
    }
    fread(buffer, size, 1, file);

    // 获取图片宽度和高度
    // 这里假设图片是JPEG格式，您可以根据实际情况修改代码以适应其他格式的图片
    // 这里使用的是libjpeg库进行JPEG解码，请确保已经安装了libjpeg-dev软件包
    // 并且在编译时链接了libjpeg库
    // 如果使用其他图像库或处理其他图像格式，请相应地修改代码
    // 这里只是一个简单的示例，不涉及图像格式处理的细节
    // 实际情况可能更加复杂，需要更全面的图像处理库或技术
    // 这里只是一个概念性的示例，仅用于说明如何使用DRM库显示图像
    width = 0;  // 替换为实际的图像宽度
    height = 0; // 替换为实际的图像高度

    // 创建DRM缓冲区对象
    memset(&create_dumb, 0, sizeof(create_dumb));
    create_dumb.width = width;
    create_dumb.height = height;
    create_dumb.bpp = 32;
    ret = ioctl(fd, DRM_IOCTL_MODE_CREATE_DUMB, &create_dumb);
    if (ret < 0) {
        perror("ioctl DRM_IOCTL_MODE_CREATE_DUMB");
        free(buffer);
        fclose(file);
        close(fd);
        return -1;
    }
    handle = create_dumb.handle;

    // 将图像数据写入DRM缓冲区
    struct drm_mode_destroy_dumb destroy_dumb;
    memset(&map_dumb, 0, sizeof(map_dumb));
    map_dumb.handle = handle;
    ret = ioctl(fd, DRM_IOCTL_MODE_MAP_DUMB, &map_dumb);
    if (ret < 0) {
        perror("ioctl DRM_IOCTL_MODE_MAP_DUMB");
        memset(&destroy_dumb, 0, sizeof(destroy_dumb));
        destroy_dumb.handle = handle;
        ioctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_dumb);
        free(buffer);
        fclose(file);
        close(fd);
        return -1;
    }
    uint8_t *map = (uint8_t*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, map_dumb.offset);
    if (map == MAP_FAILED) {
        perror("mmap");
        memset(&destroy_dumb, 0, sizeof(destroy_dumb));
        destroy_dumb.handle = handle;
        ioctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_dumb);
        free(buffer);
        fclose(file);
        close(fd);
        return -1;
    }
    memcpy(map, buffer, size);
    munmap(map, size);

    // 配置DRM帧缓冲参数
    memset(&cmd, 0, sizeof(cmd));
    cmd.fb_id = 0;
    cmd.width = width;
    cmd.height = height;
    cmd.bpp = 32;
    cmd.pitch = create_dumb.pitch;
    cmd.depth = 24;
    cmd.handle = handle;
    ret = ioctl(fd, DRM_IOCTL_MODE_ADDFB, &cmd);
    if (ret < 0) {
        perror("ioctl DRM_IOCTL_MODE_ADDFB");
        memset(&destroy_dumb, 0, sizeof(destroy_dumb));
        destroy_dumb.handle = handle;
        ioctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_dumb);
        free(buffer);
        fclose(file);
        close(fd);
        return -1;
    }

    // 设置DRM CRTC
    struct drm_mode_crtc crtc;
    memset(&crtc, 0, sizeof(crtc));
    crtc.crtc_id = 0;  // 替换为您实际的CRTC ID
    crtc.fb_id = cmd.fb_id;
    crtc.set_connectors_ptr = (uint64_t)NULL;
    crtc.count_connectors = 0;
    ret = ioctl(fd, DRM_IOCTL_SET_MASTER, 0);
    if (ret < 0) {
        perror("ioctl DRM_IOCTL_SET_MASTER");
        memset(&destroy_dumb, 0, sizeof(destroy_dumb));
        destroy_dumb.handle = handle;
        ioctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_dumb);
        free(buffer);
        fclose(file);
        close(fd);
        return -1;
    }
    ret = ioctl(fd, DRM_IOCTL_MODE_SETCRTC, &crtc);
    if (ret < 0) {
        perror("ioctl DRM_IOCTL_MODE_SETCRTC");
        memset(&destroy_dumb, 0, sizeof(destroy_dumb));
        destroy_dumb.handle = handle;
        ioctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_dumb);
        free(buffer);
        fclose(file);
        close(fd);
        return -1;
    }

    // 保持显示状态，等待用户操作
    printf("Press Enter to exit...\n");
    getchar();

    // 清理资源
    memset(&destroy_dumb, 0, sizeof(destroy_dumb));
    destroy_dumb.handle = handle;
    ioctl(fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_dumb);
    free(buffer);
    fclose(file);
    close(fd);

    return 0;
    }
#endif
/**
* @fn main
* @brief main
* @param int argc 
* @param char* argv[]  
* @return:int
*/
const char* MODULE_NAME_GAUGE           = "AnimationDisplayController";
int main(int argc, char* argv[]) {

    signal(SIGINT,  &signal_handler);
    signal(SIGABRT, &signal_handler);
    signal(SIGKILL, &signal_handler);
    logInit("AnimationApp");
    consolePrint("---------------------------------------------------------------Start AnimationApp...");
    g_App = new AppFw::Application(argc, argv);
    if (g_App != NULL)
    {
        g_App->registerModule<AnimationDisplayController>(MODULE_NAME_GAUGE);
        g_App->exec();
    }
    else
    {
        consolePrint("[AnimationDisplayController] Create Application Error");
    }
}

#endif // _WIN32

