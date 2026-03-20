#ifndef WARNINGPOPUPDATAMODEL_H
#define WARNINGPOPUPDATAMODEL_H

#include <DataModel.h>

class WarningPopupDataModel : public DataModel
{
    Q_OBJECT
public:
    explicit WarningPopupDataModel(int updateInterval = 1000, QObject *parent = nullptr);

protected:
    void updateData() override;

    //A类报警
    DATA_PROPERTY_DEFINE(door_Pop, bool) //车门未关
    DATA_PROPERTY_DEFINE(Seatbelt_Pop, bool) //安全带未系
    DATA_PROPERTY_DEFINE(TPMSPressureStaFL_Pop, int) //左前胎压状态
    DATA_PROPERTY_DEFINE(TPMSPressureStaFR_Pop, int) //右前胎压状态
    DATA_PROPERTY_DEFINE(TPMSPressureStaRL_Pop, int) //左后胎压状态
    DATA_PROPERTY_DEFINE(TPMSPressureStaRR_Pop, int) //右后胎压状态
    DATA_PROPERTY_DEFINE(Drivable_Pop, bool) //车辆可行驶状态
    DATA_PROPERTY_DEFINE(Overspeed_Pop, bool) //超速报警

    //B类报警
    DATA_PROPERTY_DEFINE(ABSfailed_Pop, bool) //ABS系统故障
    DATA_PROPERTY_DEFINE(ESCFailed_Pop, bool) //ESC系统故障
    DATA_PROPERTY_DEFINE(HDCWorkSts_Pop, bool) //陡坡缓降系统故障
    DATA_PROPERTY_DEFINE(EBDFailed_Pop, bool) //制动系统故障
    DATA_PROPERTY_DEFINE(AVHSts_Pop, bool) //自动驻车系统故障
    DATA_PROPERTY_DEFINE(BasicElecSteerFailed_Pop, bool) //EPS电子转向系统故障
    DATA_PROPERTY_DEFINE(CruiseCtrlStaError_Pop, bool) //定速巡航系统故障
    DATA_PROPERTY_DEFINE(EngineSta_Pop, bool) //发动机系统故障
    DATA_PROPERTY_DEFINE(TransSta_Pop, bool) //变速箱故障
    DATA_PROPERTY_DEFINE(TPMSError_Pop, bool) //胎压系统故障
    DATA_PROPERTY_DEFINE(LimpHomeSta_Pop, bool) //驱动功率受限
    DATA_PROPERTY_DEFINE(PwrTrainHighTempWrning_Pop, bool) //动力电池温度过高
    DATA_PROPERTY_DEFINE(PwrTrainConnectSta_Pop, bool) //动力电池断开
    DATA_PROPERTY_DEFINE(MotorHighTempWrning_Pop, bool) //电机及控制器过热
    DATA_PROPERTY_DEFINE(BMSSysFailSta_Pop, bool) //动力电池故障
    DATA_PROPERTY_DEFINE(DrvMotorSta_Pop, bool) //电机故障
    DATA_PROPERTY_DEFINE(PCUFailSta_Pop, bool) //动力系统故障
    DATA_PROPERTY_DEFINE(InsulationWrning_Pop, bool) //绝缘故障
    DATA_PROPERTY_DEFINE(PASwarn_Pop, bool) //雷达系统故障
    DATA_PROPERTY_DEFINE(PASSta_Pop, bool) //雷达传感器故障
    DATA_PROPERTY_DEFINE(SRSError_Pop, bool) //安全气囊系统故障
    DATA_PROPERTY_DEFINE(BatSOCRptWarning_Pop, bool) //动力电池电量低
    DATA_PROPERTY_DEFINE(PEPSWarnSta_Pop, bool) //PEPS系统故障

    //C类报警
    DATA_PROPERTY_DEFINE(HU_VehicleMainLamp_Pop, bool) //车辆保养提示
    DATA_PROPERTY_DEFINE(HU_brakeliquidlevel_Pop, bool) //制动液位低
    DATA_PROPERTY_DEFINE(highCoolantTemperature_Pop, bool) //冷却液温度高
    DATA_PROPERTY_DEFINE(HU_MachineOilPre_Pop, bool) //机油压力低
    DATA_PROPERTY_DEFINE(lowFuel_Pop, bool) //燃油液位低
    DATA_PROPERTY_DEFINE(PALAresponse_Pop, bool) //ESC系统已关闭
    DATA_PROPERTY_DEFINE(TPMSUnLearned_Pop, bool) //胎压系统未学习
    DATA_PROPERTY_DEFINE(CruiseCtrlStaActive_Pop, bool) //定速巡航已激活
    DATA_PROPERTY_DEFINE(VSPsta_Pop, bool) //行人提醒装置已关闭

signals:
    CHANGED_SIGNAL_DEFINE(door_Pop)
    CHANGED_SIGNAL_DEFINE(Seatbelt_Pop)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaFL_Pop)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaFR_Pop)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaRL_Pop)
    CHANGED_SIGNAL_DEFINE(TPMSPressureStaRR_Pop)
    CHANGED_SIGNAL_DEFINE(Drivable_Pop)
    CHANGED_SIGNAL_DEFINE(Overspeed_Pop)

    CHANGED_SIGNAL_DEFINE(ABSfailed_Pop)
    CHANGED_SIGNAL_DEFINE(ESCFailed_Pop)
    CHANGED_SIGNAL_DEFINE(HDCWorkSts_Pop)
    CHANGED_SIGNAL_DEFINE(EBDFailed_Pop)
    CHANGED_SIGNAL_DEFINE(AVHSts_Pop)
    CHANGED_SIGNAL_DEFINE(BasicElecSteerFailed_Pop)
    CHANGED_SIGNAL_DEFINE(CruiseCtrlStaError_Pop)
    CHANGED_SIGNAL_DEFINE(EngineSta_Pop)
    CHANGED_SIGNAL_DEFINE(TransSta_Pop)
    CHANGED_SIGNAL_DEFINE(TPMSError_Pop)
    CHANGED_SIGNAL_DEFINE(LimpHomeSta_Pop)
    CHANGED_SIGNAL_DEFINE(PwrTrainHighTempWrning_Pop)
    CHANGED_SIGNAL_DEFINE(PwrTrainConnectSta_Pop)
    CHANGED_SIGNAL_DEFINE(MotorHighTempWrning_Pop)
    CHANGED_SIGNAL_DEFINE(BMSSysFailSta_Pop)
    CHANGED_SIGNAL_DEFINE(DrvMotorSta_Pop)
    CHANGED_SIGNAL_DEFINE(PCUFailSta_Pop)
    CHANGED_SIGNAL_DEFINE(InsulationWrning_Pop)
    CHANGED_SIGNAL_DEFINE(PASwarn_Pop)
    CHANGED_SIGNAL_DEFINE(PASSta_Pop)
    CHANGED_SIGNAL_DEFINE(SRSError_Pop)
    CHANGED_SIGNAL_DEFINE(BatSOCRptWarning_Pop)
    CHANGED_SIGNAL_DEFINE(PEPSWarnSta_Pop)


    CHANGED_SIGNAL_DEFINE(HU_VehicleMainLamp_Pop)
    CHANGED_SIGNAL_DEFINE(HU_brakeliquidlevel_Pop)
    CHANGED_SIGNAL_DEFINE(highCoolantTemperature_Pop)
    CHANGED_SIGNAL_DEFINE(HU_MachineOilPre_Pop)
    CHANGED_SIGNAL_DEFINE(lowFuel_Pop)
    CHANGED_SIGNAL_DEFINE(PALAresponse_Pop)
    CHANGED_SIGNAL_DEFINE(TPMSUnLearned_Pop)
    CHANGED_SIGNAL_DEFINE(CruiseCtrlStaActive_Pop)
    CHANGED_SIGNAL_DEFINE(VSPsta_Pop)

private:
    int m_index;
};

#endif // WARNINGPOPUPDATAMODEL_H
