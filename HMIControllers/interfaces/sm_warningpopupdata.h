#ifndef SM_WARNINGPOPUPDATA_H
#define SM_WARNINGPOPUPDATA_H

#include "sharedmemory.hpp"
#include "smstructdefine.h"

using namespace SharedMemory;

namespace SharedMemory 
{
    SM_POOL_DEFINITION(WarningPopupDataSm);

        //A类报警
    SM_NUMBER_DEFINITION(door_Pop, bool); //车门未关
    SM_NUMBER_DEFINITION(Drivable_Pop, bool); //车辆可行驶状态
    SM_NUMBER_DEFINITION(TPMSPressureStaFL_Pop, int); //左前胎压状态
    SM_NUMBER_DEFINITION(TPMSPressureStaFR_Pop, int); //右前胎压状态
    SM_NUMBER_DEFINITION(TPMSPressureStaRL_Pop, int); //左后胎压状态
    SM_NUMBER_DEFINITION(TPMSPressureStaRR_Pop, int); //右后胎压状态
    SM_NUMBER_DEFINITION(Seatbelt_Pop, bool); //安全带未系

    //B类报警
    SM_NUMBER_DEFINITION(BatSOCRptWarning_Pop, bool); //动力电池电量低
    SM_NUMBER_DEFINITION(TPMSError_Pop, bool); //胎压系统故障
    SM_NUMBER_DEFINITION(SRSError_Pop, bool); //安全气囊系统故障
    SM_NUMBER_DEFINITION(ABSfailed_Pop, bool); //ABS系统故障
    SM_NUMBER_DEFINITION(ESCFailed_Pop, bool); //ESC系统故障
    SM_NUMBER_DEFINITION(HDCWorkSts_Pop, bool); //陡坡缓降系统故障
    SM_NUMBER_DEFINITION(EBDFailed_Pop, bool); //制动系统故障
    SM_NUMBER_DEFINITION(AVHSts_Pop, bool); //自动驻车系统故障
    SM_NUMBER_DEFINITION(BasicElecSteerFailed_Pop, bool); //EPS电子转向系统故障
    SM_NUMBER_DEFINITION(CruiseCtrlStaError_Pop, bool); //定速巡航系统故障
    SM_NUMBER_DEFINITION(EngineSta_Pop, bool); //发动机系统故障
    SM_NUMBER_DEFINITION(TransSta_Pop, bool); //变速箱故障
    SM_NUMBER_DEFINITION(LimpHomeSta_Pop, bool); //驱动功率受限
    SM_NUMBER_DEFINITION(PwrTrainHighTempWrning_Pop, bool); //动力电池温度过高
    SM_NUMBER_DEFINITION(PwrTrainConnectSta_Pop, bool); //动力电池断开
    SM_NUMBER_DEFINITION(MotorHighTempWrning_Pop, bool); //电机及控制器过热
    SM_NUMBER_DEFINITION(BMSSysFailSta_Pop, bool); //动力电池故障
    SM_NUMBER_DEFINITION(DrvMotorSta_Pop, bool); //电机故障
    SM_NUMBER_DEFINITION(PCUFailSta_Pop, bool); //动力系统故障
    SM_NUMBER_DEFINITION(InsulationWrning_Pop, bool); //绝缘故障
    SM_NUMBER_DEFINITION(PASwarn_Pop, bool); //雷达系统故障
    SM_NUMBER_DEFINITION(PASSta_Pop, bool); //雷达传感器故障
    SM_NUMBER_DEFINITION(PEPSWarnSta_Pop, bool); //PEPS系统故障

    //C类报警
    SM_NUMBER_DEFINITION(TPMSUnLearned_Pop, bool); //胎压系统未学习
    SM_NUMBER_DEFINITION(HU_brakeliquidlevel_Pop, bool); //制动液位低
    SM_NUMBER_DEFINITION(highCoolantTemperature_Pop, bool); //冷却液温度高
    SM_NUMBER_DEFINITION(lowFuel_Pop, bool); //燃油液位低
    SM_NUMBER_DEFINITION(HU_MachineOilPre_Pop, bool); //机油压力低
    SM_NUMBER_DEFINITION(CruiseCtrlStaActive_Pop, bool); //定速巡航已激活
    SM_NUMBER_DEFINITION(VSPsta_Pop, bool); //行人提醒装置已关闭
}
#endif