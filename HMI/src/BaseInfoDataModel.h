#ifndef BASEINFODATAMODEL_H
#define BASEINFODATAMODEL_H

#include <DataModel.h>

class BaseInfoDataModel : public DataModel
{
    Q_OBJECT
public:
    explicit BaseInfoDataModel(int updateInterval = 500, QObject *parent = nullptr);

protected:
    void updateData() override;

    DATA_PROPERTY_DEFINE(HU_Totalodometer, int)//总计里程
    DATA_PROPERTY_DEFINE(HU_TripAOdometer, float)//小计里程A
    DATA_PROPERTY_DEFINE(HU_TripBOdometer, float)//小计里程B
    DATA_PROPERTY_DEFINE(HU_TripOdometer, float)//单次行驶里程

    DATA_PROPERTY_DEFINE(BJS_Time, QString)//时间-小时：分钟
    DATA_PROPERTY_DEFINE(EnvirTemp, int)//室外温度
    DATA_PROPERTY_DEFINE(EnvirTempV, bool)//室外温度有效性
    DATA_PROPERTY_DEFINE(TranGearPos, QString)//档位信息

    //油车特有
    DATA_PROPERTY_DEFINE(HU_engineoil, int)//燃油液位
    DATA_PROPERTY_DEFINE(HU_EngCoolantTemp, int)//水温

    //电车特有
    DATA_PROPERTY_DEFINE(drivemode, int)//驾驶模式
    DATA_PROPERTY_DEFINE(PTActlOprtMode, int)//Ready状态
    DATA_PROPERTY_DEFINE(recupLevelSta, int)//能量回收

    //电源状态
    DATA_PROPERTY_DEFINE(PowerSta, int)//电源状态

    DATA_PROPERTY_DEFINE(currentTheme, int)//主题切换,0深色主题，1浅色主题

signals:
    CHANGED_SIGNAL_DEFINE(HU_Totalodometer)
    CHANGED_SIGNAL_DEFINE(HU_TripAOdometer)
    CHANGED_SIGNAL_DEFINE(HU_TripBOdometer)
    CHANGED_SIGNAL_DEFINE(HU_TripOdometer)

    CHANGED_SIGNAL_DEFINE(BJS_Time)
    CHANGED_SIGNAL_DEFINE(EnvirTemp)
    CHANGED_SIGNAL_DEFINE(EnvirTempV)
    CHANGED_SIGNAL_DEFINE(TranGearPos)

    CHANGED_SIGNAL_DEFINE(HU_engineoil)
    CHANGED_SIGNAL_DEFINE(HU_EngCoolantTemp)

    CHANGED_SIGNAL_DEFINE(drivemode)
    CHANGED_SIGNAL_DEFINE(PTActlOprtMode)
    CHANGED_SIGNAL_DEFINE(recupLevelSta)

    CHANGED_SIGNAL_DEFINE(PowerSta)

    CHANGED_SIGNAL_DEFINE(currentTheme)

private:

};

#endif // BASEINFODATAMODEL_H
