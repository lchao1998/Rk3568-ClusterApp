#include "sm_baseinfodata.h"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(BaseInfoData);

    //行车电脑
    SM_NUMBER_IMPLEMENTATION(HU_Totalodometer, int, BaseInfoData, 0);//总计里程
    SM_NUMBER_IMPLEMENTATION(HU_TripAOdometer, float, BaseInfoData, 0);//小计里程A
    SM_NUMBER_IMPLEMENTATION(HU_TripBOdometer, float, BaseInfoData, 0);//小计里程B
    SM_NUMBER_IMPLEMENTATION(HU_TripOdometer, float, BaseInfoData, 0);//单次行驶里程

    SM_NUMBER_IMPLEMENTATION(BJS_Time_Hour, float, BaseInfoData, 0);//时间-小时
    SM_NUMBER_IMPLEMENTATION(BJS_Time_Min, float, BaseInfoData, 0);//时间-分钟
    SM_NUMBER_IMPLEMENTATION(EnvirTemp, int, BaseInfoData, 0);//室外温度
    SM_NUMBER_IMPLEMENTATION(EnvirTempV, bool, BaseInfoData, true);//室外温度有效性
    SM_NUMBER_IMPLEMENTATION(TranGearPos, float, BaseInfoData, 0);//档位信息

    //油车特有
    SM_NUMBER_IMPLEMENTATION(HU_engineoil, int, BaseInfoData, 0);//燃油液位
    SM_NUMBER_IMPLEMENTATION(HU_oilNotEnough, bool, BaseInfoData, false); //燃油液位低
    SM_NUMBER_IMPLEMENTATION(HU_EngCoolantTemp, int, BaseInfoData, 0);//水温
    SM_NUMBER_IMPLEMENTATION(HU_highWaterTemp, bool, BaseInfoData, false); //高温警告

    //电车特有
    SM_NUMBER_IMPLEMENTATION(drivemode, int, BaseInfoData, 0);//驾驶模式
    SM_NUMBER_IMPLEMENTATION(PTActlOprtMode, int, BaseInfoData, 0);//Ready状态
    SM_NUMBER_IMPLEMENTATION(recupLevelSta, int, BaseInfoData, 0);//能量回收
    SM_NUMBER_IMPLEMENTATION(MotorPower, int, BaseInfoData, 0); //电机驱动功率(只读)
    SM_NUMBER_IMPLEMENTATION(MotorPowerType, bool, BaseInfoData, false); //电机工作模式(只读)

    //电源状态
    SM_NUMBER_IMPLEMENTATION(PowerSta, int, BaseInfoData, 0); //电源状态
    
    SM_NUMBER_IMPLEMENTATION(TimeFormat, int, BaseInfoData, 0); //时间格式
}
