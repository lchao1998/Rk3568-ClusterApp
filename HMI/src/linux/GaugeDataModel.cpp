#include "GaugeDataModel.h"
#include <QDebug>

GaugeDataModel::GaugeDataModel(int updateInterval, QObject *parent)
    : DataModel{updateInterval, parent},
    m_speed(0),
    m_tachoSpeed(0),
    m_motorPower(0),
    m_motorPowerType(false)
{

}

void GaugeDataModel::updateData()
{
    if(m_speed < 220)
    {
        m_speed ++;
    }
    else
    {
        m_speed = 0;
    }

    if(m_tachoSpeed < 8000)
    {
        m_tachoSpeed += 100.0;
    }
    else
    {
        m_tachoSpeed = 0;
    }

    if(m_motorPowerType)
    {
        if(m_motorPower < 60)
        {
            m_motorPower ++;
        }
        else
        {
            m_motorPower = 0;
            m_motorPowerType = false;
        }
    }
    else if(!m_motorPowerType)
    {
        if(m_motorPower < 200)
        {
            m_motorPower ++;
        }
        else
        {
            m_motorPower = 0;
            m_motorPowerType = true;
        }
    }

    emit HU_DisvehicleSpeedChanged();
    emit revSpeedChanged();
    emit MotorPowerChanged();
    emit MotorPowerTypeChanged();
}

DATA_PROPERTY_IMPLEMENT(GaugeDataModel, HU_DisvehicleSpeed, int)
{
    return m_speed;
}

DATA_PROPERTY_IMPLEMENT(GaugeDataModel, revSpeed, QString)
{
    return QString::number((float)(m_tachoSpeed) / 1000 , 'f', 1);
}

DATA_PROPERTY_IMPLEMENT(GaugeDataModel, MotorPower, int)
{
    return m_motorPower;
}

DATA_PROPERTY_IMPLEMENT(GaugeDataModel, MotorPowerType, bool)
{
    return m_motorPowerType;
}
