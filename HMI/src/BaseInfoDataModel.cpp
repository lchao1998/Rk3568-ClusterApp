#include "BaseInfoDataModel.h"
#include <QDateTime>
#include <QLocale>

#include "sm_baseinfodata.h"
#include "sm_telltalesm.h"

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
    : DataModel{updateInterval, parent}
{

}

void BaseInfoDataModel::updateData()
{
    DATA_PROERTY_CHECK(HU_Totalodometer);
    DATA_PROERTY_CHECK(HU_TripAOdometer);
    DATA_PROERTY_CHECK(HU_TripBOdometer);
    DATA_PROERTY_CHECK(HU_TripOdometer);

    emit BJS_TimeChanged();

    DATA_PROERTY_CHECK(EnvirTemp);
    DATA_PROERTY_CHECK(EnvirTempV);
    DATA_PROERTY_CHECK(TranGearPos);

    DATA_PROERTY_CHECK(HU_engineoil);
    DATA_PROERTY_CHECK(HU_EngCoolantTemp);

    DATA_PROERTY_CHECK(drivemode);
    DATA_PROERTY_CHECK(PTActlOprtMode);
    DATA_PROERTY_CHECK(recupLevelSta);

    DATA_PROERTY_CHECK(PowerSta);

    DATA_PROERTY_CHECK(currentTheme);
}

DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, HU_Totalodometer, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, HU_TripAOdometer, float)
DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, HU_TripBOdometer, float)
DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, HU_TripOdometer, float)

 DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, BJS_Time, QString)
 {
    QDateTime dateTime = QDateTime::currentDateTime();
    QLocale locale = QLocale::English;//指定英文显示
    //QLocale locale = QLocale::Chinese;//指定中文显示
    QString Format;
    if(TimeFormat.getValue() == 0)
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

DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, EnvirTemp, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, EnvirTempV, bool)

 DATA_PROPERTY_IMPLEMENT(BaseInfoDataModel, TranGearPos, QString)
 {
     unsigned int index = TranGearPos.getValue();
     if (index >= TABLE_MAX) {
         index = 0;
     }
     return QString(gear_table[index]);
 }

DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, HU_engineoil, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, HU_EngCoolantTemp, int)

DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, drivemode, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, PTActlOprtMode, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, recupLevelSta, int)

DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, PowerSta, int)

DATA_PROPERTY_SIMPLE_IMPLEMENT(BaseInfoDataModel, currentTheme, int)
