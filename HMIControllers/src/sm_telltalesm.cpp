#include "sm_telltalesm.h"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(TelltaleSm);

    SM_NUMBER_IMPLEMENTATION(leftTurnlamp, bool, TelltaleSm, false); //左转弯灯
    SM_NUMBER_IMPLEMENTATION(rightTurnlamp, bool, TelltaleSm, false); //右转弯灯
    SM_NUMBER_IMPLEMENTATION(lowbeam, bool, TelltaleSm, false); //近光灯
    SM_NUMBER_IMPLEMENTATION(highbeam, bool, TelltaleSm, false); //远光灯
    SM_NUMBER_IMPLEMENTATION(Flashbeam, bool, TelltaleSm, false); //超车灯
    SM_NUMBER_IMPLEMENTATION(positionlamp, bool, TelltaleSm, false); //位置灯
    SM_NUMBER_IMPLEMENTATION(FrontFogLampSta, bool, TelltaleSm, false); //前雾灯
    SM_NUMBER_IMPLEMENTATION(rearFogLampSta, bool, TelltaleSm, false); //后雾灯
    SM_NUMBER_IMPLEMENTATION(autohighbeam, bool, TelltaleSm, false); //自动远光灯
    SM_NUMBER_IMPLEMENTATION(DrvSeatbeltBucklestatus, int, TelltaleSm, 0); //主驾安全带未系指示灯
    SM_NUMBER_IMPLEMENTATION(DrvSeatOccSta, bool, TelltaleSm, false); //主驾座椅占用状态
    SM_NUMBER_IMPLEMENTATION(PAssSeatbeltBucklestatus , bool, TelltaleSm, false); //副驾安全带未系指示灯
    SM_NUMBER_IMPLEMENTATION(PassSeatOccSta , bool, TelltaleSm, false); //副驾座椅占用状态
    SM_NUMBER_IMPLEMENTATION(doorajarFL, bool, TelltaleSm, false); //左前门状态
    SM_NUMBER_IMPLEMENTATION(doorajarFR, bool, TelltaleSm, false); //右前门状态
    SM_NUMBER_IMPLEMENTATION(doorajarRL, bool, TelltaleSm, false); //左后门状态
    SM_NUMBER_IMPLEMENTATION(doorajarRR, bool, TelltaleSm, false); //右后门状态
    SM_NUMBER_IMPLEMENTATION(HoodSta, bool, TelltaleSm, false); //前舱盖状态
    SM_NUMBER_IMPLEMENTATION(TrunkSta, bool, TelltaleSm, false); //后背门状态
    SM_NUMBER_IMPLEMENTATION(FueldoorSta, bool, TelltaleSm, false); //加油口盖状态
    SM_NUMBER_IMPLEMENTATION(ChargeSta, bool, TelltaleSm, false); //充电口盖状态
    SM_NUMBER_IMPLEMENTATION(PEPSWarnSta, bool, TelltaleSm, false); //PEPS故障指示灯
    SM_NUMBER_IMPLEMENTATION(TPMSSta, int, TelltaleSm, 0); //胎压系统故障、未学习指示灯
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaFL, int, TelltaleSm, 0); //左前胎压状态
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaFR, int, TelltaleSm, 0); //右前胎压状态
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaRL, int, TelltaleSm, 0); //左后胎压状态
    SM_NUMBER_IMPLEMENTATION(TPMSPressureStaRR, int, TelltaleSm, 0); //右后胎压状态
    SM_NUMBER_IMPLEMENTATION(SRSError, bool, TelltaleSm, false); //安全气囊故障指示灯
    SM_NUMBER_IMPLEMENTATION(lowbatterycharge, bool, TelltaleSm, false); //蓄电池放电状态指示灯

    SM_NUMBER_IMPLEMENTATION(HU_VehicleMainLamp, bool, TelltaleSm, false); //保养指示灯
    SM_NUMBER_IMPLEMENTATION(ABSfailed, bool, TelltaleSm, false); //ABS故障指示灯
    SM_NUMBER_IMPLEMENTATION(PALAresponse, bool, TelltaleSm, false); //ESC关闭指示灯
    SM_NUMBER_IMPLEMENTATION(ESPActiveSta, bool, TelltaleSm, false); //ESC指示灯
    SM_NUMBER_IMPLEMENTATION(ESCFailed, bool, TelltaleSm, false); //ESC故障指示灯
    SM_NUMBER_IMPLEMENTATION(HDCWorkSts, int, TelltaleSm, 0); //陡坡缓降、陡坡缓降故障指示灯
    SM_NUMBER_IMPLEMENTATION(ParkLampSta, bool, TelltaleSm, false); //驻车状态指示灯
    SM_NUMBER_IMPLEMENTATION(EBDFailed, bool, TelltaleSm, false); //制动系统故障指示灯
    SM_NUMBER_IMPLEMENTATION(AVHSts, int, TelltaleSm, 0); //自动驻车、自动驻车故障指示灯
    SM_NUMBER_IMPLEMENTATION(BasicElecSteerFailed, bool, TelltaleSm, false); //EPS故障指示灯
    SM_NUMBER_IMPLEMENTATION(HU_brakeliquidlevel, bool, TelltaleSm, false); //制动液位低指示灯
    SM_NUMBER_IMPLEMENTATION(IMMOPCUauthen, bool, TelltaleSm, false); //发动机防盗指示灯
    SM_NUMBER_IMPLEMENTATION(EPCwarn, bool, TelltaleSm, false); //EPC指示灯

    SM_NUMBER_IMPLEMENTATION(highCoolantTemperature, bool, TelltaleSm, false); //冷却液温度过高指示灯
    SM_NUMBER_IMPLEMENTATION(lowFuel, bool, TelltaleSm, false); //燃油液位低指示灯
    SM_NUMBER_IMPLEMENTATION(HU_MachineOilPre, bool, TelltaleSm, false); //机油压力指示灯
    SM_NUMBER_IMPLEMENTATION(CruiseCtrlSta, int, TelltaleSm, 0); //定速巡航、定速巡航故障指示灯
    SM_NUMBER_IMPLEMENTATION(EngineSta, bool, TelltaleSm, false); //MIL发动机故障指示灯
    SM_NUMBER_IMPLEMENTATION(TransSta, bool, TelltaleSm, false); //变速器故障指示灯

    //电车特有指示灯
    SM_NUMBER_IMPLEMENTATION(InletConnctSta, bool, TelltaleSm, false); //充电线连接状态指示灯
    SM_NUMBER_IMPLEMENTATION(BatSOCRptWarning, bool, TelltaleSm, false); //动力电池电量低，默认为false
    SM_NUMBER_IMPLEMENTATION(LimpHomeSta, bool, TelltaleSm, false); //驱动功率限制指示灯
    SM_NUMBER_IMPLEMENTATION(PwrTrainHighTempWrning, bool, TelltaleSm, false); //动力电池温度过高指示灯
    SM_NUMBER_IMPLEMENTATION(PwrTrainConnectSta, bool, TelltaleSm, false); //动力电池断开指示灯
    SM_NUMBER_IMPLEMENTATION(MotorHighTempWrning, bool, TelltaleSm, false); //电机及控制器过热指示灯
    SM_NUMBER_IMPLEMENTATION(BMSSysFailSta, bool, TelltaleSm, false); //动力电池故障指示灯
    SM_NUMBER_IMPLEMENTATION(DrvMotorSta, bool, TelltaleSm, false); //电机故障指示灯
    SM_NUMBER_IMPLEMENTATION(PCUFailSta, bool, TelltaleSm, false); //动力系统故障指示灯
    SM_NUMBER_IMPLEMENTATION(InsulationWrning, bool, TelltaleSm, false); //绝缘故障指示灯
    SM_NUMBER_IMPLEMENTATION(VSPsta, bool, TelltaleSm, false); //行人提示装置关闭指示灯 

    SM_NUMBER_IMPLEMENTATION(IsHMILaunched, bool, TelltaleSm, false); //HMI是否关闭

    SM_NUMBER_IMPLEMENTATION(currentTheme, int, TelltaleSm, 0); //设置主题

    SM_NUMBER_IMPLEMENTATION(hazardIsSignaling, bool, TelltaleSm, false); //危险报警灯
}
