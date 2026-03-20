#include "sm_warningpopupdata.h"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(WarningPopupDataSm);
            //A类报警
    SM_NUMBER_IMPLEMENTATION(door_Pop, bool, WarningPopupDataSm, false); //车门未关
    SM_NUMBER_IMPLEMENTATION(Drivable_Pop, bool, WarningPopupDataSm, false); //车辆可行驶状态
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaFL_Pop, int, WarningPopupDataSm, 0); //左前胎压状态
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaFR_Pop, int, WarningPopupDataSm, 0); //右前胎压状态
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaRL_Pop, int, WarningPopupDataSm, 0); //左后胎压状态
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaRR_Pop, int, WarningPopupDataSm, 0); //右后胎压状态
    SM_NUMBER_IMPLEMENTATION(Seatbelt_Pop, bool, WarningPopupDataSm, false); //安全带未系
    SM_NUMBER_IMPLEMENTATION(Overspeed_Pop, bool, WarningPopupDataSm, false); //超速报警

    //B类报警
    SM_NUMBER_IMPLEMENTATION(BatSOCRptWarning_Pop, bool, WarningPopupDataSm, false); //动力电池电量低
    SM_NUMBER_IMPLEMENTATION(TPMSError_Pop, bool, WarningPopupDataSm, false); //胎压系统故障
    SM_NUMBER_IMPLEMENTATION(SRSError_Pop, bool, WarningPopupDataSm, false); //安全气囊系统故障
    SM_NUMBER_IMPLEMENTATION(ABSfailed_Pop, bool, WarningPopupDataSm, false); //ABS系统故障
    SM_NUMBER_IMPLEMENTATION(ESCFailed_Pop, bool, WarningPopupDataSm, false); //ESC系统故障
    SM_NUMBER_IMPLEMENTATION(HDCWorkSts_Pop, bool, WarningPopupDataSm, false); //陡坡缓降系统故障
    SM_NUMBER_IMPLEMENTATION(EBDFailed_Pop, bool, WarningPopupDataSm, false); //制动系统故障
    SM_NUMBER_IMPLEMENTATION(AVHSts_Pop, bool, WarningPopupDataSm, false);
    SM_NUMBER_IMPLEMENTATION(BasicElecSteerFailed_Pop, bool, WarningPopupDataSm, false); //EPS电子转向系统故障
    SM_NUMBER_IMPLEMENTATION(CruiseCtrlStaError_Pop, bool, WarningPopupDataSm, false); //定速巡航系统故障
    SM_NUMBER_IMPLEMENTATION(EngineSta_Pop, bool, WarningPopupDataSm, false); //发动机系统故障
    SM_NUMBER_IMPLEMENTATION(TransSta_Pop, bool, WarningPopupDataSm, false); //变速箱故障
    SM_NUMBER_IMPLEMENTATION(LimpHomeSta_Pop, bool, WarningPopupDataSm, false); //驱动功率受限
    SM_NUMBER_IMPLEMENTATION(PwrTrainHighTempWrning_Pop, bool, WarningPopupDataSm, false); //动力电池温度过高
    SM_NUMBER_IMPLEMENTATION(PwrTrainConnectSta_Pop, bool, WarningPopupDataSm, false); //动力电池断开
    SM_NUMBER_IMPLEMENTATION(MotorHighTempWrning_Pop, bool, WarningPopupDataSm, false); //电机及控制器过热
    SM_NUMBER_IMPLEMENTATION(BMSSysFailSta_Pop, bool, WarningPopupDataSm, false); //动力电池故障
    SM_NUMBER_IMPLEMENTATION(DrvMotorSta_Pop, bool, WarningPopupDataSm, false); //电机故障
    SM_NUMBER_IMPLEMENTATION(PCUFailSta_Pop, bool, WarningPopupDataSm, false); //动力系统故障
    SM_NUMBER_IMPLEMENTATION(InsulationWrning_Pop, bool, WarningPopupDataSm, false); //绝缘故障
    SM_NUMBER_IMPLEMENTATION(PASwarn_Pop, bool, WarningPopupDataSm, false); //雷达系统故障
    SM_NUMBER_IMPLEMENTATION(PASSta_Pop, bool, WarningPopupDataSm, false); //雷达传感器故障
    SM_NUMBER_IMPLEMENTATION(PEPSWarnSta_Pop, bool, WarningPopupDataSm, false); //PEPS系统故障

    //C类报警
    SM_NUMBER_IMPLEMENTATION(TPMSUnLearned_Pop, bool, WarningPopupDataSm, false); //胎压系统未学习
    SM_NUMBER_IMPLEMENTATION(HU_brakeliquidlevel_Pop, bool, WarningPopupDataSm, false); //制动液位低
    SM_NUMBER_IMPLEMENTATION(highCoolantTemperature_Pop, bool, WarningPopupDataSm, false); //冷却液温度高
    SM_NUMBER_IMPLEMENTATION(lowFuel_Pop, bool, WarningPopupDataSm, false); //燃油液位低
    SM_NUMBER_IMPLEMENTATION(HU_MachineOilPre_Pop, bool, WarningPopupDataSm, false); //机油压力低
    SM_NUMBER_IMPLEMENTATION(CruiseCtrlStaActive_Pop, bool, WarningPopupDataSm, false); //定速巡航已激活
    SM_NUMBER_IMPLEMENTATION(VSPsta_Pop, bool, WarningPopupDataSm, false); //行人提醒装置已关闭
}

