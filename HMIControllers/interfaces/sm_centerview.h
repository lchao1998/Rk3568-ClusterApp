#ifndef SM_CENTERVIEW_H
#define SM_CENTERVIEW_H

#include "sharedmemory.hpp"
#include "smstructdefine.h"

using namespace SharedMemory;

namespace SharedMemory {

    SM_POOL_DEFINITION(CenterView);

    //行车电脑
    SM_NUMBER_DEFINITION(HU_AvgVehicleSpeed, int);//平均车速
    SM_NUMBER_DEFINITION(HU_CurON, int);//瞬时油耗
    SM_NUMBER_DEFINITION(HU_Avgfuleconsump, float);//平均油耗
    SM_NUMBER_DEFINITION(HU_RemainRange, int);//续航里程
    SM_NUMBER_DEFINITION(BatSOCRpt, int);//动力电池电量
    SM_NUMBER_DEFINITION(HVBatActlVoltage, int);//动力电池电压
    SM_NUMBER_DEFINITION(ExchgCurnt, int);//动力电池电流

    //安全带状态
    SM_NUMBER_DEFINITION(SeatbeltBucklestatusRL, bool);//后左安全带状态
    SM_NUMBER_DEFINITION(RLSeatOccSta, bool);//后左座椅占用状态
    SM_NUMBER_DEFINITION(SeatbeltBucklestatusRM, bool);//后中安全带状态
    SM_NUMBER_DEFINITION(RMSeatOccSta, bool);//后中座椅占用状态
    SM_NUMBER_DEFINITION(SeatbeltBucklestatusRR, bool);//后右安全带状态
    SM_NUMBER_DEFINITION(RRSeatOccSta, bool);//后右座椅占用状态

    //雷达报警
    SM_NUMBER_DEFINITION(PASSta_RL, int);//左后雷达传感器状态
    SM_NUMBER_DEFINITION(PASSta__RML, int);//左中后雷达传感器状态
    SM_NUMBER_DEFINITION(PASSta__RMR, int);//右中后雷达传感器状态
    SM_NUMBER_DEFINITION(PASSta__RR, int);//右后雷达传感器状态
    SM_NUMBER_DEFINITION(PASDistanceRL, int);//左后雷达监测障碍物距离
    SM_NUMBER_DEFINITION(PASDistanceRML, int);//左中后雷达监测障碍物距离
    SM_NUMBER_DEFINITION(PASDistanceRMR, int);//右中后雷达监测障碍物距离
    SM_NUMBER_DEFINITION(PASDistanceRR, int);//右后雷达监测障碍物距离
 
    //当前显示模块
    SM_NUMBER_DEFINITION(currentStatus, int);   //0显示舱门，1雷达报警， 2安全带状态
    //菜单按钮
    SM_NUMBER_DEFINITION(Menu_SwSta, int);
    SM_NUMBER_DEFINITION(BMSErrorCodes, int);
}
#endif