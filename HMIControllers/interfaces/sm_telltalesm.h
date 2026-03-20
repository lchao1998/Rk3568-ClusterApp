#pragma once

#include "sharedmemory.hpp"
#include "smstructdefine.h"

using namespace SharedMemory;

namespace SharedMemory {

    SM_POOL_DEFINITION(TelltaleSm);

    SM_NUMBER_DEFINITION(leftTurnlamp, bool); //左转弯灯
    SM_NUMBER_DEFINITION(rightTurnlamp, bool); //右转弯灯
    SM_NUMBER_DEFINITION(lowbeam, bool); //近光灯
    SM_NUMBER_DEFINITION(highbeam, bool); //远光灯
    SM_NUMBER_DEFINITION(Flashbeam, bool); //超车灯
    SM_NUMBER_DEFINITION(positionlamp, bool); //位置灯
    SM_NUMBER_DEFINITION(FrontFogLampSta, bool); //前雾灯
    SM_NUMBER_DEFINITION(rearFogLampSta, bool); //后雾灯
    SM_NUMBER_DEFINITION(autohighbeam, bool); //自动远光灯
    SM_NUMBER_DEFINITION(DrvSeatbeltBucklestatus, int); //主驾安全带未系指示灯
    SM_NUMBER_DEFINITION(DrvSeatOccSta, bool); //主驾座椅占用状态
    SM_NUMBER_DEFINITION(PAssSeatbeltBucklestatus , bool); //副驾安全带未系指示灯
    SM_NUMBER_DEFINITION(PassSeatOccSta , bool); //副驾座椅占用状态
    SM_NUMBER_DEFINITION(doorajarFL, bool); //左前门状态
    SM_NUMBER_DEFINITION(doorajarFR, bool); //右前门状态
    SM_NUMBER_DEFINITION(doorajarRL, bool); //左后门状态
    SM_NUMBER_DEFINITION(doorajarRR, bool); //右后门状态
    SM_NUMBER_DEFINITION(HoodSta, bool); //前舱盖状态
    SM_NUMBER_DEFINITION(TrunkSta, bool); //后背门状态
    SM_NUMBER_DEFINITION(FueldoorSta, bool); //加油口盖状态
    SM_NUMBER_DEFINITION(ChargeSta, bool); //充电口盖状态
    SM_NUMBER_DEFINITION(PEPSWarnSta, bool); //PEPS故障指示灯
    SM_NUMBER_DEFINITION(TPMSSta, int); //胎压系统故障、未学习指示灯
    SM_NUMBER_DEFINITION(TPMSPressureStaFL, int); //左前胎压状态
    SM_NUMBER_DEFINITION(TPMSPressureStaFR, int); //右前胎压状态
    SM_NUMBER_DEFINITION(TPMSPressureStaRL, int); //左后胎压状态
    SM_NUMBER_DEFINITION(TPMSPressureStaRR, int); //右后胎压状态
    SM_NUMBER_DEFINITION(SRSError, bool); //安全气囊故障指示灯
    SM_NUMBER_DEFINITION(lowbatterycharge, bool); //蓄电池放电状态指示灯

    SM_NUMBER_DEFINITION(HU_VehicleMainLamp, bool); //保养指示灯
    SM_NUMBER_DEFINITION(ABSfailed, bool); //ABS故障指示灯
    SM_NUMBER_DEFINITION(PALAresponse, bool); //ESC关闭指示灯
    SM_NUMBER_DEFINITION(ESPActiveSta, bool); //ESC指示灯
    SM_NUMBER_DEFINITION(ESCFailed, bool); //ESC故障指示灯
    SM_NUMBER_DEFINITION(HDCWorkSts, int); //陡坡缓降、陡坡缓降故障指示灯
    SM_NUMBER_DEFINITION(ParkLampSta, bool); //驻车状态指示灯
    SM_NUMBER_DEFINITION(EBDFailed, bool); //制动系统故障指示灯
    SM_NUMBER_DEFINITION(AVHSts, int); //自动驻车、自动驻车故障指示灯
    SM_NUMBER_DEFINITION(BasicElecSteerFailed, bool); //EPS故障指示灯
    SM_NUMBER_DEFINITION(HU_brakeliquidlevel, bool); //制动液位低指示灯
    SM_NUMBER_DEFINITION(IMMOPCUauthen, bool); //发动机防盗指示灯
    SM_NUMBER_DEFINITION(EPCwarn, bool); //EPC指示灯

    SM_NUMBER_DEFINITION(highCoolantTemperature, bool); //冷却液温度过高指示灯
    SM_NUMBER_DEFINITION(lowFuel, bool); //燃油液位低指示灯
    SM_NUMBER_DEFINITION(HU_MachineOilPre, bool); //机油压力指示灯
    SM_NUMBER_DEFINITION(CruiseCtrlSta, int); //定速巡航、定速巡航故障指示灯
    SM_NUMBER_DEFINITION(EngineSta, bool); //MIL发动机故障指示灯
    SM_NUMBER_DEFINITION(TransSta, bool); //变速器故障指示灯

    //电车特有指示灯
    SM_NUMBER_DEFINITION(InletConnctSta, bool); //充电线连接状态指示灯
    SM_NUMBER_DEFINITION(BatSOCRptWarning, bool); //动力电池电量低，默认为false
    SM_NUMBER_DEFINITION(LimpHomeSta, bool); //驱动功率限制指示灯
    SM_NUMBER_DEFINITION(PwrTrainHighTempWrning, bool); //动力电池温度过高指示灯
    SM_NUMBER_DEFINITION(PwrTrainConnectSta, bool); //动力电池断开指示灯
    SM_NUMBER_DEFINITION(MotorHighTempWrning, bool); //电机及控制器过热指示灯
    SM_NUMBER_DEFINITION(BMSSysFailSta, bool); //动力电池故障指示灯
    SM_NUMBER_DEFINITION(DrvMotorSta, bool); //电机故障指示灯
    SM_NUMBER_DEFINITION(PCUFailSta, bool); //动力系统故障指示灯
    SM_NUMBER_DEFINITION(InsulationWrning, bool); //绝缘故障指示灯
    SM_NUMBER_DEFINITION(VSPsta, bool); //行人提示装置关闭指示灯 

    SM_NUMBER_DEFINITION(IsHMILaunched, bool); //HMI是否关闭

    SM_NUMBER_DEFINITION(currentTheme, int); //设置主题
    SM_NUMBER_DEFINITION(hazardIsSignaling, bool); //危险报警灯

}