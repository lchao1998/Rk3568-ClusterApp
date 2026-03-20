#ifndef TELLTALEDATAMODEL_H
#define TELLTALEDATAMODEL_H

#include <DataModel.h>

class TelltaleDataModel : public DataModel
{
    Q_OBJECT
public:
    explicit TelltaleDataModel(int updateInterval = 1000, QObject *parent = nullptr);

protected:
    void updateData() override;

    DATA_PROPERTY_DEFINE(turnlamp, int) //转弯灯
    DATA_PROPERTY_DEFINE(lowbeam, bool) //近光灯
    DATA_PROPERTY_DEFINE(highbeam, bool) //远光灯
    DATA_PROPERTY_DEFINE(Flashbeam, bool) //超车灯
    DATA_PROPERTY_DEFINE(positionlamp, bool) //位置灯
    DATA_PROPERTY_DEFINE(FrontFogLampSta, bool) //前雾灯
    DATA_PROPERTY_DEFINE(rearFogLampSta, bool) //后雾灯
    DATA_PROPERTY_DEFINE(autohighbeam, bool) //自动远光灯
    DATA_PROPERTY_DEFINE(DrvSeatbeltBucklestatus, int) //主驾安全带未系指示灯
    DATA_PROPERTY_DEFINE(DrvSeatOccSta, bool) //主驾座椅占用状态
    DATA_PROPERTY_DEFINE(PAssSeatbeltBucklestatus , bool) //副驾安全带未系指示灯
    DATA_PROPERTY_DEFINE(PassSeatOccSta , bool) //副驾座椅占用状态
    DATA_PROPERTY_DEFINE(doorajarFL, bool) //左前门状态
    DATA_PROPERTY_DEFINE(doorajarFR, bool) //右前门状态
    DATA_PROPERTY_DEFINE(doorajarRL, bool) //左后门状态
    DATA_PROPERTY_DEFINE(doorajarRR, bool) //右后门状态
    DATA_PROPERTY_DEFINE(HoodSta, bool) //前舱盖状态
    DATA_PROPERTY_DEFINE(TrunkSta, bool) //后背门状态
    DATA_PROPERTY_DEFINE(FueldoorSta, bool) //加油口盖状态
    DATA_PROPERTY_DEFINE(ChargeSta, bool) //充电口盖状态
    DATA_PROPERTY_DEFINE(PEPSWarnSta, bool) //PEPS故障指示灯
    DATA_PROPERTY_DEFINE(TPMSSta, int) //胎压系统故障、未学习指示灯
    DATA_PROPERTY_DEFINE(TPMSPressureStaFL, int) //左前胎压状态
    DATA_PROPERTY_DEFINE(TPMSPressureStaFR, int) //右前胎压状态
    DATA_PROPERTY_DEFINE(TPMSPressureStaRL, int) //左后胎压状态
    DATA_PROPERTY_DEFINE(TPMSPressureStaRR, int) //右后胎压状态
    DATA_PROPERTY_DEFINE(SRSError, bool) //安全气囊故障指示灯
    DATA_PROPERTY_DEFINE(lowbatterycharge, bool) //蓄电池放电状态指示灯

    DATA_PROPERTY_DEFINE(HU_VehicleMainLamp, bool) //保养指示灯
    DATA_PROPERTY_DEFINE(ABSfailed, bool) //ABS故障指示灯
    DATA_PROPERTY_DEFINE(PALAresponse, bool) //ESC关闭指示灯
    DATA_PROPERTY_DEFINE(ESPActiveSta, bool) //ESC指示灯
    DATA_PROPERTY_DEFINE(ESCFailed, bool) //ESC故障指示灯
    DATA_PROPERTY_DEFINE(HDCWorkSts, int) //陡坡缓降、陡坡缓降故障指示灯
    DATA_PROPERTY_DEFINE(ParkLampSta, bool) //驻车状态指示灯
    DATA_PROPERTY_DEFINE(EBDFailed, bool) //制动系统故障指示灯
    DATA_PROPERTY_DEFINE(AVHSts, int) //自动驻车、自动驻车故障指示灯
    DATA_PROPERTY_DEFINE(BasicElecSteerFailed, bool) //EPS故障指示灯
    DATA_PROPERTY_DEFINE(HU_brakeliquidlevel, bool) //制动液位低指示灯
    DATA_PROPERTY_DEFINE(IMMOPCUauthen, bool) //发动机防盗指示灯
    DATA_PROPERTY_DEFINE(EPCwarn, bool) //EPC指示灯

    DATA_PROPERTY_DEFINE(highCoolantTemperature, bool) //冷却液温度过高指示灯
    DATA_PROPERTY_DEFINE(lowFuel, bool) //燃油液位低指示灯
    DATA_PROPERTY_DEFINE(HU_MachineOilPre, bool) //机油压力指示灯
    DATA_PROPERTY_DEFINE(CruiseCtrlSta, int) //定速巡航、定速巡航故障指示灯
    DATA_PROPERTY_DEFINE(EngineSta, bool) //MIL发动机故障指示灯
    DATA_PROPERTY_DEFINE(TransSta, bool) //变速器故障指示灯

    //电车特有指示灯
    DATA_PROPERTY_DEFINE(InletConnctSta, bool) //充电线连接状态指示灯
    DATA_PROPERTY_DEFINE(BatSOCRptWarning, bool) //动力电池电量指示灯
    DATA_PROPERTY_DEFINE(LimpHomeSta, bool) //驱动功率限制指示灯
    DATA_PROPERTY_DEFINE(PwrTrainHighTempWrning, bool) //动力电池温度过高指示灯
    DATA_PROPERTY_DEFINE(PwrTrainConnectSta, bool) //动力电池断开指示灯
    DATA_PROPERTY_DEFINE(MotorHighTempWrning, bool) //电机及控制器过热指示灯
    DATA_PROPERTY_DEFINE(BMSSysFailSta, bool) //动力电池故障指示灯
    DATA_PROPERTY_DEFINE(DrvMotorSta, bool) //电机故障指示灯
    DATA_PROPERTY_DEFINE(PCUFailSta, bool) //动力系统故障指示灯
    DATA_PROPERTY_DEFINE(InsulationWrning, bool) //绝缘故障指示灯
    DATA_PROPERTY_DEFINE(VSPsta, bool) //行人提示装置关闭指示灯

signals:
    CHANGED_SIGNAL_DEFINE(turnlamp)
    CHANGED_SIGNAL_DEFINE(lowbeam)
    CHANGED_SIGNAL_DEFINE(highbeam)
    CHANGED_SIGNAL_DEFINE(Flashbeam)
    CHANGED_SIGNAL_DEFINE(positionlamp)
    CHANGED_SIGNAL_DEFINE(FrontFogLampSta)
    CHANGED_SIGNAL_DEFINE(rearFogLampSta)
    CHANGED_SIGNAL_DEFINE(autohighbeam)
    CHANGED_SIGNAL_DEFINE(DrvSeatbeltBucklestatus)
    CHANGED_SIGNAL_DEFINE(DrvSeatOccSta)
    CHANGED_SIGNAL_DEFINE(PAssSeatbeltBucklestatus)
    CHANGED_SIGNAL_DEFINE(PassSeatOccSta)
    CHANGED_SIGNAL_DEFINE(doorajarFL)
    CHANGED_SIGNAL_DEFINE(doorajarFR)
    CHANGED_SIGNAL_DEFINE(doorajarRL)
    CHANGED_SIGNAL_DEFINE(doorajarRR)
    CHANGED_SIGNAL_DEFINE(HoodSta)
    CHANGED_SIGNAL_DEFINE(TrunkSta)
    CHANGED_SIGNAL_DEFINE(FueldoorSta)
    CHANGED_SIGNAL_DEFINE(ChargeSta)
    CHANGED_SIGNAL_DEFINE(PEPSWarnSta)
    CHANGED_SIGNAL_DEFINE(TPMSSta)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaFL)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaFR)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaRL)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaRR)
    CHANGED_SIGNAL_DEFINE(SRSError)
    CHANGED_SIGNAL_DEFINE(lowbatterycharge)

    CHANGED_SIGNAL_DEFINE(HU_VehicleMainLamp)
    CHANGED_SIGNAL_DEFINE(ABSfailed)
    CHANGED_SIGNAL_DEFINE(PALAresponse)
    CHANGED_SIGNAL_DEFINE(ESPActiveSta)
    CHANGED_SIGNAL_DEFINE(ESCFailed)
    CHANGED_SIGNAL_DEFINE(HDCWorkSts)
    CHANGED_SIGNAL_DEFINE(ParkLampSta)
    CHANGED_SIGNAL_DEFINE(EBDFailed)
    CHANGED_SIGNAL_DEFINE(AVHSts)
    CHANGED_SIGNAL_DEFINE(BasicElecSteerFailed)
    CHANGED_SIGNAL_DEFINE(HU_brakeliquidlevel)
    CHANGED_SIGNAL_DEFINE(IMMOPCUauthen)
    CHANGED_SIGNAL_DEFINE(EPCwarn)

    CHANGED_SIGNAL_DEFINE(highCoolantTemperature)
    CHANGED_SIGNAL_DEFINE(lowFuel)
    CHANGED_SIGNAL_DEFINE(HU_MachineOilPre)
    CHANGED_SIGNAL_DEFINE(CruiseCtrlSta)
    CHANGED_SIGNAL_DEFINE(EngineSta)
    CHANGED_SIGNAL_DEFINE(TransSta)

    CHANGED_SIGNAL_DEFINE(InletConnctSta)
    CHANGED_SIGNAL_DEFINE(BatSOCRptWarning)
    CHANGED_SIGNAL_DEFINE(LimpHomeSta)
    CHANGED_SIGNAL_DEFINE(PwrTrainHighTempWrning)
    CHANGED_SIGNAL_DEFINE(PwrTrainConnectSta)
    CHANGED_SIGNAL_DEFINE(MotorHighTempWrning)
    CHANGED_SIGNAL_DEFINE(BMSSysFailSta)
    CHANGED_SIGNAL_DEFINE(DrvMotorSta)
    CHANGED_SIGNAL_DEFINE(PCUFailSta)
    CHANGED_SIGNAL_DEFINE(InsulationWrning)
    CHANGED_SIGNAL_DEFINE(VSPsta)


private:
    int m_index;
    bool m_switch;
    int m_turnlamp;
    int m_tPMSSta;
    int m_tPMSPressurestaFL;
    int m_tPMSPressurestaFR;
    int m_tPMSPressurestaRL;
    int m_tPMSPressurestaRR;
    int m_hDCWorkSts;
    int m_aVHSts;
    int m_cruiseCtrlSta;
    int m_drvSeatbeltBucklestatus;
};

#endif // TELLTALEDATAMODEL_H
