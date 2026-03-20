#ifndef SM_BASEINFODATA_H
#define SM_BASEINFODATA_H

#include "sharedmemory.hpp"
#include "smstructdefine.h"

using namespace SharedMemory;

namespace SharedMemory {

    SM_POOL_DEFINITION(BaseInfoData);

    SM_NUMBER_DEFINITION(HU_Totalodometer, int);//总计里程
    SM_NUMBER_DEFINITION(HU_TripAOdometer, float);//小计里程A
    SM_NUMBER_DEFINITION(HU_TripBOdometer, float);//小计里程B
    SM_NUMBER_DEFINITION(HU_TripOdometer, float);//单次行驶里程

    SM_NUMBER_DEFINITION(BJS_Time_Hour, float);//时间-小时
    SM_NUMBER_DEFINITION(BJS_Time_Min, float);//时间-分钟
    SM_NUMBER_DEFINITION(EnvirTemp, int);//室外温度
    SM_NUMBER_DEFINITION(EnvirTempV, bool);//室外温度有效性
    SM_NUMBER_DEFINITION(TranGearPos, float);//档位信息

    //油车特有
    SM_NUMBER_DEFINITION(HU_engineoil, int);//燃油液位
    SM_NUMBER_DEFINITION(HU_oilNotEnough, bool); //燃油液位低
    SM_NUMBER_DEFINITION(HU_EngCoolantTemp, int);//水温
    SM_NUMBER_DEFINITION(HU_highWaterTemp, bool); //高温警告

    //电车特有
    SM_NUMBER_DEFINITION(drivemode, int);//驾驶模式
    SM_NUMBER_DEFINITION(PTActlOprtMode, int);//Ready状态
    SM_NUMBER_DEFINITION(recupLevelSta, int);//能量回收
    SM_NUMBER_DEFINITION(MotorPower, int);//电机驱动功率(只读)
    SM_NUMBER_DEFINITION(MotorPowerType, bool);//电机驱动功率(只读)

    //电源状态
    SM_NUMBER_DEFINITION(PowerSta, int);//电源状态(只读)
    SM_NUMBER_DEFINITION(TimeFormat, int); //时间格式
}

#endif