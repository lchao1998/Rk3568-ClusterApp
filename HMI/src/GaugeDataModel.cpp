#include "GaugeDataModel.h"
#include <QDebug>
#include "sm_gaugedata.h"
#include "sm_baseinfodata.h"

GaugeDataModel::GaugeDataModel(int updateInterval, QObject *parent)
    : DataModel{updateInterval, parent}
{

}

void GaugeDataModel::updateData()
{
    DATA_PROERTY_CHECK(HU_DisvehicleSpeed);
    DATA_PROERTY_CHECK(revSpeed)
    DATA_PROERTY_CHECK(MotorPower);
    DATA_PROERTY_CHECK(MotorPowerType);
}

DATA_PROPERTY_SIMPLE_IMPLEMENT(GaugeDataModel, HU_DisvehicleSpeed, int)

DATA_PROPERTY_IMPLEMENT(GaugeDataModel, revSpeed, QString)
{
    return QString::number((float)(revSpeed.getValue()) / 1000 , 'f', 1);
}

DATA_PROPERTY_SIMPLE_IMPLEMENT(GaugeDataModel, MotorPower, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(GaugeDataModel, MotorPowerType, bool)
