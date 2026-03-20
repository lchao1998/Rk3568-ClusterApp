# CMakeList.txt: Animation 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(AnimationApp)
cmake_minimum_required (VERSION 3.10)

add_compile_options(-O0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(SWITCH_SOA "SOA switch" ON)
option(CONSOLE_LOG "SOA switch" ON)
#add_definitions(-DCONSOLE_LOG)
# set(APPFW_INCLUDE_DIRS /home/share/rk3588_sdk/aarch64-buildroot-linux-gnu/sysroot/usr/include)
# set(APPFW_LIBRARIES /home/share/rk3588_sdk/aarch64-buildroot-linux-gnu/sysroot/usr/lib/libappfw.so)


# Set the default build type to Release if none was specified  
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)  
  message(STATUS "Setting build type to 'Release' as none was specified.")  
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)  
else()
    message(STATUS "===================" + + ${CMAKE_BUILD_TYPE})
    # Create a new build type called DebugWithTrace, which enables all warnings and sets all optimization flags to -O0  
    set(CMAKE_CXX_FLAGS_DEBUGWITHTRACE "-O0 -Wall -Wextra -pedantic -fPIC")  
    set(CMAKE_C_FLAGS_DEBUGWITHTRACE "-O0 -Wall -Wextra -pedantic -fPIC")  
    set(CMAKE_EXE_LINKER_FLAGS_DEBUGWITHTRACE "-O0 -Wall -Wextra -pedantic -fPIC")  
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUGWITHTRACE "-O0 -Wall -Wextra -pedantic -fPIC")  
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUGWITHTRACE "-O0 -Wall -Wextra -pedantic -fPIC")  
    
    # Add the new build type to the list of available options  
    set(CMAKE_BUILD_TYPES "${CMAKE_BUILD_TYPES};DebugWithTrace" CACHE STRING "Choose the type of build." FORCE)
endif()  


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/animationRes DESTINATION  ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sounds DESTINATION  ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/animation.ini DESTINATION  ${CMAKE_BINARY_DIR}/)

if(DEFINED SWITCH_SOA)
    message("...........start find CommonAPI........")
    add_definitions(-DSWITCH_SOA)
    find_package(CommonAPI REQUIRED)
    find_package(CommonAPI-SomeIP REQUIRED)
    find_package(vsomeip3 REQUIRED)
    if(CommonAPI-SomeIP_FOUND)
    message(STATUS "Found CommonAPI-SomeIP: ${CommonAPI-SomeIP_INCLUDE_DIRS} ${CommonAPI-SomeIP_LIBRARIES}")
    # 可以继续配置您的项目，包含头文件和链接库等操作
    
    else()
        message(FATAL_ERROR "CommonAPI-SomeIP not found")
    endif(CommonAPI-SomeIP_FOUND)

    if(CommonAPI_FOUND)
        message(STATUS "Found CommonAPI: ${CommonAPI_INCLUDE_DIRS} ${CommonAPI_LIBRARIES}")
        # 可以继续配置您的项目，包含头文件和链接库等操作
        
    else()
        message(FATAL_ERROR "CommonAPI not found")
    endif(CommonAPI_FOUND)
endif()
#find_package(Boost REQUIRED COMPONENTS system thread)
message(STATUS "...........start find boost........")
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    FIND_PACKAGE(appfw   COMPONENTS thread REQUIRED)
    find_package(Boost REQUIRED COMPONENTS system thread)
    if(Boost_FOUND)
        message(STATUS "Found Boost: ${Boost_INCLUDE_DIRS} ${Boost_LIBRARIES}")
        # 可以继续配置您的项目，包含头文件和链接库等操作
        
    else()
        message(FATAL_ERROR "Boost not found")
    endif(Boost_FOUND)

    include_directories(${APPFW_INCLUDE_DIRS})

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBDRM REQUIRED libdrm)

    include(GNUInstallDirs)
endif()

file(GLOB  FILE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*")
file(GLOB  FILE_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SERVICE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/*.h")
foreach(header ${SERVICE_HEADERS})
    message("  ${header}")
endforeach()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/generated/BootAnimationService/core/common/v1/BootAnimationService")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/generated/BootAnimationService/core/proxy/v1/BootAnimationService")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/generated/BootAnimationService/core/skel/v1/BootAnimationService")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/generated/BootAnimationService/core/stub/v1/BootAnimationService")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/generated/BootAnimationService/someip/common/v1/BootAnimationService")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/generated/BootAnimationService/someip/proxy/v1/BootAnimationService")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/BootAnimationService/generated/BootAnimationService/someip/stub/v1/BootAnimationService")
if(SWITCH_SOA)
    find_file(CommonAPI_PATH CommonAPI-3.2)
    include_directories(${CommonAPI_PATH})
endif(SWITCH_SOA)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(BootAnimationService SERVICE_SRC)
# 将源代码添加到此项目的可执行文件。

if(WIN32) 
    # 设置编译器为MSVC（Microsoft Visual C++）
    set(CMAKE_C_COMPILER "cl")
    set(CMAKE_CXX_COMPILER "cl")
endif(WIN32)

if(WIN32)
    add_executable (${PROJECT_NAME} WIN32 ${FILE_HEADERS} ${FILE_SRCS})
else()
    add_executable (${PROJECT_NAME}  ${FILE_HEADERS} ${FILE_SRCS} ${SERVICE_SRC} ${SERVICE_HEADERS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBDRM_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${APPFW_LIBRARIES} ${LIBDRM_LIBRARIES} rt pthread png zllog)
    if(SWITCH_SOA)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${APPFW_LIBRARIES} CommonAPI CommonAPI-SomeIP)
    endif(SWITCH_SOA)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
endif(WIN32)

message(-----------------------------------${APPFW_LIBRARIES})
# TODO: 如有需要，请添加测试并安装目标。
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
