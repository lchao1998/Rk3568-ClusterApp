#ifndef CENTERVIEWDATAMODEL_H
#define CENTERVIEWDATAMODEL_H

#include <DataModel.h>

class CenterViewDataModel : public DataModel
{
    Q_OBJECT
public:
    explicit CenterViewDataModel(int updateInterval = 50, QObject *parent = nullptr);

protected:
    void updateData() override;

    //行车电脑
    DATA_PROPERTY_DEFINE(HU_AvgVehicleSpeed, int)//平均车速
    DATA_PROPERTY_DEFINE(HU_CurON, int)//瞬时油耗
    DATA_PROPERTY_DEFINE(HU_Avgfuleconsump, float)//平均油耗
    DATA_PROPERTY_DEFINE(HU_RemainRange, int)//续航里程
    DATA_PROPERTY_DEFINE(BatSOCRpt, int)//动力电池电量
    DATA_PROPERTY_DEFINE(HVBatActlVoltage, int)//动力电池电压
    DATA_PROPERTY_DEFINE(ExchgCurnt, int)//动力电池电流

    //安全带状态
    DATA_PROPERTY_DEFINE(SeatbeltBucklestatusRL, bool)//后左安全带状态
    DATA_PROPERTY_DEFINE(RLSeatOccSta, bool)//后左座椅占用状态
    DATA_PROPERTY_DEFINE(SeatbeltBucklestatusRM, bool)//后中安全带状态
    DATA_PROPERTY_DEFINE(RMSeatOccSta, bool)//后中座椅占用状态
    DATA_PROPERTY_DEFINE(SeatbeltBucklestatusRR, bool)//后右安全带状态
    DATA_PROPERTY_DEFINE(RRSeatOccSta, bool)//后右座椅占用状态

    //雷达报警
    DATA_PROPERTY_DEFINE(PASSta_RL, int)//左后雷达传感器状态
    DATA_PROPERTY_DEFINE(PASSta__RML, int)//左中后雷达传感器状态
    DATA_PROPERTY_DEFINE(PASSta__RMR, int)//右中后雷达传感器状态
    DATA_PROPERTY_DEFINE(PASSta__RR, int)//右后雷达传感器状态
    DATA_PROPERTY_DEFINE(PASDistanceRL, int)//左后雷达监测障碍物距离
    DATA_PROPERTY_DEFINE(PASDistanceRML, int)//左中后雷达监测障碍物距离
    DATA_PROPERTY_DEFINE(PASDistanceRMR, int)//右中后雷达监测障碍物距离
    DATA_PROPERTY_DEFINE(PASDistanceRR, int)//右后雷达监测障碍物距离

    //显示当前模块
    DATA_PROPERTY_DEFINE(currentStatus, int)//0默认不显示，1显示门开，2雷达报警，3安全带状态, 4胎压报警

    //显示当前行车电脑模块
    DATA_PROPERTY_DEFINE(Menu_SwSta, int)//0车模，1行车电脑1页面，2行车电脑2页面，3双屏互动页面

    DATA_PROPERTY_DEFINE(BMSErrorCodes, int)//BMS故障提示等级，0无故障，1三级故障，2二级故障，3一级故障

signals:
    CHANGED_SIGNAL_DEFINE(HU_AvgVehicleSpeed)
    CHANGED_SIGNAL_DEFINE(HU_CurON)
    CHANGED_SIGNAL_DEFINE(HU_Avgfuleconsump)
    CHANGED_SIGNAL_DEFINE(HU_RemainRange)
    CHANGED_SIGNAL_DEFINE(BatSOCRpt)
    CHANGED_SIGNAL_DEFINE(HVBatActlVoltage)
    CHANGED_SIGNAL_DEFINE(ExchgCurnt)

    CHANGED_SIGNAL_DEFINE(SeatbeltBucklestatusRL)
    CHANGED_SIGNAL_DEFINE(RLSeatOccSta)
    CHANGED_SIGNAL_DEFINE(SeatbeltBucklestatusRM)
    CHANGED_SIGNAL_DEFINE(RMSeatOccSta)
    CHANGED_SIGNAL_DEFINE(SeatbeltBucklestatusRR)
    CHANGED_SIGNAL_DEFINE(RRSeatOccSta)

    CHANGED_SIGNAL_DEFINE(PASSta_RL)
    CHANGED_SIGNAL_DEFINE(PASSta__RML)
    CHANGED_SIGNAL_DEFINE(PASSta__RMR)
    CHANGED_SIGNAL_DEFINE(PASSta__RR)
    CHANGED_SIGNAL_DEFINE(PASDistanceRL)
    CHANGED_SIGNAL_DEFINE(PASDistanceRML)
    CHANGED_SIGNAL_DEFINE(PASDistanceRMR)
    CHANGED_SIGNAL_DEFINE(PASDistanceRR)

    CHANGED_SIGNAL_DEFINE(currentStatus)

    CHANGED_SIGNAL_DEFINE(Menu_SwSta)

    CHANGED_SIGNAL_DEFINE(BMSErrorCodes)

private:

};

#endif // CENTERVIEWDATAMODEL_H
