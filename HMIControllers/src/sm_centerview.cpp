#include "sm_centerview.h"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(CenterView);

    //行车电脑
    SM_NUMBER_IMPLEMENTATION(HU_AvgVehicleSpeed, int, CenterView, 0);//平均车速
    SM_NUMBER_IMPLEMENTATION(HU_CurON, int, CenterView, 0);//瞬时油耗
    SM_NUMBER_IMPLEMENTATION(HU_Avgfuleconsump, float, CenterView, 0);//平均油耗
    SM_NUMBER_IMPLEMENTATION(HU_RemainRange, int, CenterView, 0);//续航里程
    SM_NUMBER_IMPLEMENTATION(BatSOCRpt, int, CenterView, 0);//动力电池电量
    SM_NUMBER_IMPLEMENTATION(HVBatActlVoltage, int, CenterView, 0);//动力电池电压
    SM_NUMBER_IMPLEMENTATION(ExchgCurnt, int, CenterView, 0);//动力电池电流

    //安全带状态
    SM_NUMBER_IMPLEMENTATION(SeatbeltBucklestatusRL, bool, CenterView, false);//后左安全带状态
    SM_NUMBER_IMPLEMENTATION(RLSeatOccSta, bool, CenterView, false);//后左座椅占用状态
    SM_NUMBER_IMPLEMENTATION(SeatbeltBucklestatusRM, bool, CenterView, false);//后中安全带状态
    SM_NUMBER_IMPLEMENTATION(RMSeatOccSta, bool, CenterView, false);//后中座椅占用状态
    SM_NUMBER_IMPLEMENTATION(SeatbeltBucklestatusRR, bool, CenterView, false);//后右安全带状态
    SM_NUMBER_IMPLEMENTATION(RRSeatOccSta, bool, CenterView, false);//后右座椅占用状态

    //雷达报警
    SM_NUMBER_IMPLEMENTATION(PASSta_RL, int, CenterView, 0);//左后雷达传感器状态
    SM_NUMBER_IMPLEMENTATION(PASSta__RML, int, CenterView, 0);//左中后雷达传感器状态
    SM_NUMBER_IMPLEMENTATION(PASSta__RMR, int, CenterView, 0);//右中后雷达传感器状态
    SM_NUMBER_IMPLEMENTATION(PASSta__RR, int, CenterView, 0);//右后雷达传感器状态
    SM_NUMBER_IMPLEMENTATION(PASDistanceRL, int, CenterView, 0);//左后雷达监测障碍物距离
    SM_NUMBER_IMPLEMENTATION(PASDistanceRML, int, CenterView, 0);//左中后雷达监测障碍物距离
    SM_NUMBER_IMPLEMENTATION(PASDistanceRMR, int, CenterView, 0);//右中后雷达监测障碍物距离
    SM_NUMBER_IMPLEMENTATION(PASDistanceRR, int, CenterView, 0);//右后雷达监测障碍物距离

    //当前显示模块
    SM_NUMBER_IMPLEMENTATION(currentStatus, int, CenterView, 0);   //0显示舱门，1雷达报警， 2安全带状态
    //菜单按钮
    SM_NUMBER_IMPLEMENTATION(Menu_SwSta, int, CenterView, 0);
    SM_NUMBER_IMPLEMENTATION(BMSErrorCodes, int, CenterView, 0);
}
