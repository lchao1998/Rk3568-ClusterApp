cmake_minimum_required(VERSION 3.0.0)
project(HMIControllers VERSION 0.1.0 LANGUAGES C CXX)

option(USING_PERTETTO_TRACE "using google perfetto" OFF)
option(USE_EASY_PROFILER "use easy profiler" OFF)

add_definitions(-Wall -Wextra)

find_package(CommonAPI REQUIRED HINTS )
find_package(CommonAPI-SomeIP REQUIRED)
find_package(vsomeip3 REQUIRED)

macro(search_all_header_directories directory_path retrun_list)
    file(GLOB_RECURSE NEW_LIST LIST_DIRECTORIES true ${directory_path}/*)
    list(APPEND DIR_LIST "")
    foreach(FILENAME ${NEW_LIST})
        if (IS_DIRECTORY ${FILENAME})
            list(APPEND DIR_LIST ${FILENAME})
        endif()
    endforeach(FILENAME NEW_LIST)
    list(REMOVE_DUPLICATES DIR_LIST)
    set(${retrun_list} ${DIR_LIST})
endmacro(search_all_header_directories retrun_list)

# search_all_header_directories(/home/liuzuyang/MyProject/${CMAKE_PROJECT_NAME}/RK3568 RE)
# include_directories(${RE})

# include_directories(/home/liuzuyang/CompanyCode/RK3568/generated/VehicleSignalService/core/proxy/v1/VehicleSignal/)
# include_directories(/home/liuzuyang/CompanyCode/RK3568/generated/VehicleSignalService/core/proxy)
# include_directories(/home/liuzuyang/CompanyCode/RK3568/generated/VehicleSignalService/core/common)

# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/common)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/ADAS)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/Body)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/Cabin)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/Chassis)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/Identifier)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/Powertrain)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/Service)
# include_directories(/home/liuzuyang/CompanyCode/VehicleSigService/generated/core/proxy/v1/VSS/Vehicle)

find_file(SOA_IDL_PATH soa-idl)
if (NOT EXISTS ${SOA_IDL_PATH})
    message(FATAL_ERROR "Can't find soa-idl dir: ${SOA_IDL_PATH}")
endif ()

# add include path
include_directories(${SOA_IDL_PATH})

include_directories(inc/ interfaces/)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)
file(GLOB HEADERS inc/* interfaces/*)
file(GLOB SOURCES src/*)
add_executable(${CMAKE_PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES}) 

if (USING_PERTETTO_TRACE)
    add_subdirectory(perfetto)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE perfetto)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/perfetto/)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE USING_PERFETTO_LIBRARY)
endif(USING_PERTETTO_TRACE)

if (USE_EASY_PROFILER)
    find_package(easy_profiler REQUIRED)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE easy_profiler)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE USE_EASY_PROFILER)
endif(USE_EASY_PROFILER)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE pthread)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE rt zllog)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE CommonAPI)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE CommonAPI-SomeIP)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${COMMONAPI_INCLUDE_DIRS})
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -O0)

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)




