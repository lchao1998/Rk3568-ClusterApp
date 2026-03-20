#include "WarningPopupDataModel.h"

WarningPopupDataModel::WarningPopupDataModel(int updateInterval, QObject *parent)
    : DataModel{updateInterval, parent},
    m_index(1)
{

}

void WarningPopupDataModel::updateData()
{
    emit door_PopChanged();
    emit Seatbelt_PopChanged();
    emit TPMSPressureStaFL_PopChanged();
    emit TPMSPressureStaFR_PopChanged();
    emit TPMSPressureStaRL_PopChanged();
    emit TPMSPressureStaRR_PopChanged();
    emit Drivable_PopChanged();
    emit Overspeed_PopChanged();

    emit ABSfailed_PopChanged();
    emit ESCFailed_PopChanged();
    emit HDCWorkSts_PopChanged();
    emit EBDFailed_PopChanged();
    emit AVHSts_PopChanged();
    emit BasicElecSteerFailed_PopChanged();
    emit CruiseCtrlStaError_PopChanged();
    emit EngineSta_PopChanged();
    emit TransSta_PopChanged();
    emit TPMSError_PopChanged();
    emit LimpHomeSta_PopChanged();
    emit PwrTrainHighTempWrning_PopChanged();
    emit PwrTrainConnectSta_PopChanged();
    emit MotorHighTempWrning_PopChanged();
    emit BMSSysFailSta_PopChanged();
    emit DrvMotorSta_PopChanged();
    emit PCUFailSta_PopChanged();
    emit InsulationWrning_PopChanged();
    emit PASwarn_PopChanged();
    emit PASSta_PopChanged();
    emit SRSError_PopChanged();
    emit BatSOCRptWarning_PopChanged();
    emit PEPSWarnSta_PopChanged();

    emit HU_VehicleMainLamp_PopChanged();
    emit HU_brakeliquidlevel_PopChanged();
    emit highCoolantTemperature_PopChanged();
    emit HU_MachineOilPre_PopChanged();
    emit lowFuel_PopChanged();
    emit PALAresponse_PopChanged();
    emit TPMSUnLearned_PopChanged();
    emit CruiseCtrlStaActive_PopChanged();
    emit VSPsta_PopChanged();

    m_index ++;

    if(m_index > 40)
    {
        m_index = 1;
    }
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, door_Pop, bool)
{
    if(m_index == 1)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, Seatbelt_Pop, bool)
{
    if(m_index == 2)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, TPMSPressureStaFL_Pop, int)
{
    if(m_index == 3)
    {
        return 1;
    }

    return 0;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, TPMSPressureStaFR_Pop, int)
{
    if(m_index == 4)
    {
        return 2;
    }

    return 0;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, TPMSPressureStaRL_Pop, int)
{
    if(m_index == 5)
    {
        return 3;
    }

    return 0;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, TPMSPressureStaRR_Pop, int)
{
    if(m_index == 6)
    {
        return 4;
    }

    return 0;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, Drivable_Pop, bool)
{
    if(m_index == 7)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, Overspeed_Pop, bool)
{
    if(m_index == 8)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, ABSfailed_Pop, bool)
{
    if(m_index == 9)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, ESCFailed_Pop, bool)
{
    if(m_index == 10)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, HDCWorkSts_Pop, bool)
{
    if(m_index == 11)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, EBDFailed_Pop, bool)
{
    if(m_index == 12)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, AVHSts_Pop, bool)
{
    if(m_index == 13)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, BasicElecSteerFailed_Pop, bool)
{
    if(m_index == 14)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, CruiseCtrlStaError_Pop, bool)
{
    if(m_index == 15)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, EngineSta_Pop, bool)
{
    if(m_index == 16)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, TransSta_Pop, bool)
{
    if(m_index == 17)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, TPMSError_Pop, bool)
{
    if(m_index == 18)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, LimpHomeSta_Pop, bool)
{
    if(m_index == 19)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, PwrTrainHighTempWrning_Pop, bool)
{
    if(m_index == 20)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, PwrTrainConnectSta_Pop, bool)
{
    if(m_index == 21)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, MotorHighTempWrning_Pop, bool)
{
    if(m_index == 22)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, BMSSysFailSta_Pop, bool)
{
    if(m_index == 23)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, DrvMotorSta_Pop, bool)
{
    if(m_index == 24)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, PCUFailSta_Pop, bool)
{
    if(m_index == 25)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, InsulationWrning_Pop, bool)
{
    if(m_index == 26)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, PASwarn_Pop, bool)
{
    if(m_index == 27)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, PASSta_Pop, bool)
{
    if(m_index == 28)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, SRSError_Pop, bool)
{
    if(m_index == 29)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, BatSOCRptWarning_Pop, bool)
{
    if(m_index == 30)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, PEPSWarnSta_Pop, bool)
{
    if(m_index == 31)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, HU_VehicleMainLamp_Pop, bool)
{
    if(m_index == 32)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, HU_brakeliquidlevel_Pop, bool)
{
    if(m_index == 33)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, highCoolantTemperature_Pop, bool)
{
    if(m_index == 34)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, HU_MachineOilPre_Pop, bool)
{
    if(m_index == 35)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, lowFuel_Pop, bool)
{
    if(m_index == 36)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, PALAresponse_Pop, bool)
{
    if(m_index == 37)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, TPMSUnLearned_Pop, bool)
{
    if(m_index == 38)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, CruiseCtrlStaActive_Pop, bool)
{
    if(m_index == 39)
    {
        return true;
    }

    return false;
}

DATA_PROPERTY_IMPLEMENT(WarningPopupDataModel, VSPsta_Pop, bool)
{
    if(m_index == 40)
    {
        return true;
    }

    return false;
}
