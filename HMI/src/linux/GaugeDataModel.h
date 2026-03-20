#ifndef GAUGEDATAMODEL_H
#define GAUGEDATAMODEL_H

#include <DataModel.h>

class GaugeDataModel : public DataModel
{
    Q_OBJECT
public:
    explicit GaugeDataModel(int updateInterval = 50, QObject *parent = nullptr);

protected:
    void updateData() override;

    DATA_PROPERTY_DEFINE(HU_DisvehicleSpeed, int)//车速

    //油车
    DATA_PROPERTY_DEFINE(revSpeed, QString)//转速

    //电车
    DATA_PROPERTY_DEFINE(MotorPower, int)//电机驱动功率
    DATA_PROPERTY_DEFINE(MotorPowerType, bool)//电机工作模式  false:驱动功率 true:能量回收

signals:
    CHANGED_SIGNAL_DEFINE(HU_DisvehicleSpeed)

    CHANGED_SIGNAL_DEFINE(revSpeed)

    CHANGED_SIGNAL_DEFINE(MotorPower)
    CHANGED_SIGNAL_DEFINE(MotorPowerType)

private:
    int m_speed;
    int m_tachoSpeed;
    int m_motorPower;
    bool m_motorPowerType;
};

#endif // GAUGEDATAMODEL_H
