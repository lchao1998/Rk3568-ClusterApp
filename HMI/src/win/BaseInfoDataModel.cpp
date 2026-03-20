#include "BaseInfoDataModel.h"
#include <QDebug>
#include <QDateTime>
#include <QLocale>

#define TABLE_MAX 11

const char* gear_table[TABLE_MAX] = {
    "R",
    "P",
    "D",
    "N",
    "M1",
    "M2",
    "M3",
    "M4",
    "M5",
    "M6",
    " ",
};

BaseInfoDataModel::BaseInfoDataModel(int updateInterval, QObject *parent)
    : DataModel{updateInterval, parent},
    m_totalOdo(0),
    m_tripOdo(0.0),
    m_envirTemp(-40),
    m_envirTempV(false),
    m_gearIndex(0),
    m_engineOil(100),
    m_waterTemp(0),
    m_driveMode(0),
    m_readyMode(0),
    m_recupLevelSta(0),
    m_powerSta(0)
{

}

void BaseInfoDataModel::updateData()
{
    if(m_totalOdo < 2000000)
    {
        m_totalOdo ++;
    }
    else
    {
        m_totalOdo = 2000000;
    }

    if(m_tripOdo < 9999.9)
    {
        m_tripOdo += 0.5;
    }
    else
    {
        m_tripOdo = 0;
    }

    if(m_envirTemp < 87)
    {
        m_envirTemp ++;
    }
    else
    {
        m_envirTemp = -40;
    }

    m_envirTempV = !m_envirTempV;

    if(m_gearIndex < 10)
    {
        m_gearIndex ++;
    }
    else
    {
        m_gearIndex = 0;
    }

    if(m_engineOil > 0)
    {
        m_engineOil --;
    }
    else
    {
        m_engineOil = 100;
    }

    if(m_waterTemp < 150)
    {
        m_waterTemp ++;
    }
    else
    {
        m_waterTemp = 0;
    }

    if(m_driveMode < 2)
    {
        m_driveMode ++;
    }
    else
    {
        m_driveMode = 0;
    }

    if(m_readyMode < 2)
    {
        m_readyMode ++;
    }
    else
    {
        m_readyMode = 0;
    }

    if(m_recupLevelSta < 2)
    {
        m_recupLevelSta ++;
    }
    else
    {
        m_recupLevelSta = 0;
    }

    if(m_powerSta < 5)
    {
        m_powerSta ++;
    }
    else
    {
        m_powerSta = 0;
    }

    emit HU_TotalodometerChanged();
    emit HU_TripAOdometerChanged();
    emit HU_TripBOdometerChanged();
    emit HU_TripOdometerChanged();

    emit BJS_TimeChanged();
    emit EnvirTempChanged();
    emit EnvirTempVChanged();
    emit TranGearPosChanged();

    emit HU_engineoilChanged();
    emit HU_EngCoolantTempChanged();

    emit drivemodeChanged();
    emit PTActlOprtModeChanged();
    emit recupLevelStaChanged();

    emit PowerStaChanged();

    emit currentThemeChanged();
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, HU_Totalodometer, int)
{
    return m_totalOdo;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, HU_TripAOdometer, float)
{
    return m_tripOdo;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, HU_TripBOdometer, float)
{
    return m_tripOdo;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, HU_TripOdometer, float)
{
    return m_tripOdo;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, BJS_Time, QString)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QLocale locale = QLocale::English;//指定英文显示
    //QLocale locale = QLocale::Chinese;//指定中文显示
    QString Format;
    if(1)
    {
        Format = "hh:mm AP";
    }
    else
    {
        Format = "hh:mm";
    }
    QString strDateTime = locale.toString(dateTime, Format);
    return  strDateTime;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, EnvirTemp, int)
{
    return m_envirTemp;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, EnvirTempV, bool)
{
    return m_envirTempV;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, TranGearPos, QString)
{
    return QString(gear_table[m_gearIndex]);
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, HU_engineoil, int)
{
    return m_engineOil;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, HU_EngCoolantTemp, int)
{
    return m_waterTemp;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, drivemode, int)
{
    return m_driveMode;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, PTActlOprtMode, int)
{
    return m_readyMode;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, recupLevelSta, int)
{
    return m_recupLevelSta;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, PowerSta, int)
{
    return 4;
}

DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, currentTheme, int)
{
    return 0;
}

