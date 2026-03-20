#include "TelltaleDataModel.h"
#include <QDebug>

#define DATA_PROPERTY_EASY_IMPLEMENT(func, name, type)\
type func::get##name() const\
{\
    return m_switch;\
}


TelltaleDataModel::TelltaleDataModel(int updateInterval, QObject *parent)
    : DataModel{updateInterval, parent},
    m_index(0),
    m_switch(false),
    m_turnlamp(0),
    m_tPMSSta(0),
    m_tPMSPressurestaFL(0),
    m_tPMSPressurestaFR(0),
    m_tPMSPressurestaRL(0),
    m_tPMSPressurestaRR(0),
    m_hDCWorkSts(0),
    m_aVHSts(0),
    m_cruiseCtrlSta(0),
    m_drvSeatbeltBucklestatus(0)
{

}

void TelltaleDataModel::updateData()
{

    emit turnlampChanged();
    m_turnlamp ++;
    if(m_turnlamp >= 4)
    {
        m_turnlamp = 0;
    }

    emit TPMSPressureStaFLChanged();
    m_tPMSPressurestaFL ++;
    if(m_tPMSPressurestaFL >= 6)
    {
        m_tPMSPressurestaFL = 0;
    }

    emit TPMSPressureStaFRChanged();
    m_tPMSPressurestaFR ++;
    if(m_tPMSPressurestaFR >= 6)
    {
        m_tPMSPressurestaFR = 0;
    }

    emit TPMSPressureStaRLChanged();
    m_tPMSPressurestaRL ++;
    if(m_tPMSPressurestaRL >= 6)
    {
        m_tPMSPressurestaRL = 0;
    }

    emit TPMSPressureStaRRChanged();
    m_tPMSPressurestaRR ++;
    if(m_tPMSPressurestaRR >= 6)
    {
        m_tPMSPressurestaRR = 0;
    }

    emit DrvSeatbeltBucklestatusChanged();
    m_drvSeatbeltBucklestatus ++;
    if(m_drvSeatbeltBucklestatus >= 18)
    {
        m_drvSeatbeltBucklestatus = 0;
    }

    if(m_index < 60)
    {
        m_switch = true;
    }
    else
    {
        m_switch = false;
    }

    switch (m_index) {
    case 0:
        m_tPMSSta = 1;
        emit TPMSStaChanged();
        break;
    case 1:
        emit lowbeamChanged();
        break;
    case 2:
        emit highbeamChanged();
        break;
    case 3:
        emit FlashbeamChanged();
        break;
    case 4:
        emit positionlampChanged();
        break;
    case 5:
        emit FrontFogLampStaChanged();
        break;
    case 6:
        emit rearFogLampStaChanged();
        break;
    case 7:
        emit autohighbeamChanged();
        break;
    case 8:
        break;
    case 9:
        emit DrvSeatOccStaChanged();
        break;
    case 10:
        emit PAssSeatbeltBucklestatusChanged();
        break;
    case 11:
        emit PassSeatOccStaChanged();
        break;
    case 12:
        emit doorajarFLChanged();
        break;
    case 13:
        emit doorajarFRChanged();
        break;
    case 14:
        emit doorajarRLChanged();
        break;
    case 15:
        emit doorajarRRChanged();
        break;
    case 16:
        emit HoodStaChanged();
        break;
    case 17:
        emit TrunkStaChanged();
        break;
    case 18:
        emit FueldoorStaChanged();
        break;
    case 19:
        emit ChargeStaChanged();
        break;
    case 20:
        emit PEPSWarnStaChanged();
        break;
    case 21:
        m_tPMSSta = 2;
        emit TPMSStaChanged();
        break;
    case 22:
        m_hDCWorkSts = 1;
        emit HDCWorkStsChanged();
        break;
    case 23:
        m_aVHSts = 2;
        emit AVHStsChanged();
        break;
    case 24:
        m_cruiseCtrlSta = 2;
        emit CruiseCtrlStaChanged();
        break;
    case 25:
        emit BatSOCRptWarningChanged();
        break;
    case 26:
        emit SRSErrorChanged();
        break;
    case 27:
        emit lowbatterychargeChanged();
        break;
    case 28:
        emit HU_VehicleMainLampChanged();
        break;
    case 29:
        emit ABSfailedChanged();
        break;
    case 30:
        emit PALAresponseChanged();
        break;
    case 31:
        emit ESPActiveStaChanged();
        break;
    case 32:
        emit ESCFailedChanged();
        break;
    case 33:
        m_hDCWorkSts = 2;
        emit HDCWorkStsChanged();
        break;
    case 34:
        emit ParkLampStaChanged();
        break;
    case 35:
        emit EBDFailedChanged();
        break;
    case 36:
        m_aVHSts = 3;
        emit AVHStsChanged();
        break;
    case 37:
        emit BasicElecSteerFailedChanged();
        break;
    case 38:
        emit HU_brakeliquidlevelChanged();
        break;
    case 39:
        emit IMMOPCUauthenChanged();
        break;
    case 40:
        emit EPCwarnChanged();
        break;
    case 41:
        emit highCoolantTemperatureChanged();
        break;
    case 42:
        emit lowFuelChanged();
        break;
    case 43:
        emit HU_MachineOilPreChanged();
        break;
    case 44:
        m_cruiseCtrlSta = 3;
        emit CruiseCtrlStaChanged();
        break;
    case 45:
        emit EngineStaChanged();
        break;
    case 46:
        emit TransStaChanged();
        break;
    case 47:
        break;
    case 48:
        emit InletConnctStaChanged();
        break;
    case 49:
        break;
    case 50:
        break;
    case 51:
        emit LimpHomeStaChanged();
        break;
    case 52:
        emit PwrTrainHighTempWrningChanged();
        break;
    case 53:
        emit PwrTrainConnectStaChanged();
        break;
    case 54:
        emit MotorHighTempWrningChanged();
        break;
    case 55:
        emit BMSSysFailStaChanged();
        break;
    case 56:
        emit DrvMotorStaChanged();
        break;
    case 57:
        emit PCUFailStaChanged();
        break;
    case 58:
        emit InsulationWrningChanged();
        break;
    case 59:
        emit VSPstaChanged();
        break;
    case 60:
        break;
    case 61:
        emit lowbeamChanged();
        emit highbeamChanged();
        emit FlashbeamChanged();
        emit positionlampChanged();
        emit FrontFogLampStaChanged();
        emit rearFogLampStaChanged();
        emit autohighbeamChanged();
        emit DrvSeatOccStaChanged();
        emit PAssSeatbeltBucklestatusChanged();
        emit PassSeatOccStaChanged();
        emit doorajarFLChanged();
        emit doorajarFRChanged();
        emit doorajarRLChanged();
        emit doorajarRRChanged();
        emit HoodStaChanged();
        emit TrunkStaChanged();
        emit FueldoorStaChanged();
        emit ChargeStaChanged();
        emit PEPSWarnStaChanged();

        m_tPMSSta = 0;
        emit TPMSStaChanged();

        m_hDCWorkSts = 0;
        emit HDCWorkStsChanged();

        m_aVHSts = 0;
        emit AVHStsChanged();

        m_cruiseCtrlSta = 0;
        emit CruiseCtrlStaChanged();

        emit SRSErrorChanged();
        emit lowbatterychargeChanged();

        emit HU_VehicleMainLampChanged();
        emit ABSfailedChanged();
        emit PALAresponseChanged();
        emit ESPActiveStaChanged();
        emit ESCFailedChanged();
        emit ParkLampStaChanged();
        emit EBDFailedChanged();
        emit BasicElecSteerFailedChanged();
        emit HU_brakeliquidlevelChanged();
        emit IMMOPCUauthenChanged();
        emit EPCwarnChanged();

        emit highCoolantTemperatureChanged();
        emit lowFuelChanged();
        emit HU_MachineOilPreChanged();
        emit EngineStaChanged();
        emit TransStaChanged();

        emit InletConnctStaChanged();
        emit BatSOCRptWarningChanged();
        emit LimpHomeStaChanged();
        emit PwrTrainHighTempWrningChanged();
        emit PwrTrainConnectStaChanged();
        emit MotorHighTempWrningChanged();
        emit BMSSysFailStaChanged();
        emit DrvMotorStaChanged();
        emit PCUFailStaChanged();
        emit InsulationWrningChanged();
        emit VSPstaChanged();

        break;
    default:
        break;
    }

    m_index ++;
    if(m_index > 61)
    {
        m_index = 0;
    }
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, turnlamp, int)
{
    return m_turnlamp;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, TPMSSta, int)
{
    return m_tPMSSta;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, TPMSPressureStaFL, int)
{
    return m_tPMSPressurestaFL;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, TPMSPressureStaFR, int)
{
    return m_tPMSPressurestaFR;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, TPMSPressureStaRL, int)
{
    return m_tPMSPressurestaRL;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, TPMSPressureStaRR, int)
{
    return m_tPMSPressurestaRR;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, HDCWorkSts, int)
{
    return m_hDCWorkSts;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, AVHSts, int)
{
    return m_aVHSts;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, CruiseCtrlSta, int)
{
    return m_cruiseCtrlSta;
}

DATA_PROPERTY_IMPLEMENT(TelltaleDataModel, DrvSeatbeltBucklestatus, int)
{
    return m_drvSeatbeltBucklestatus/6;
}

DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, lowbeam, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, highbeam, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, Flashbeam, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, positionlamp, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, FrontFogLampSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, rearFogLampSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, autohighbeam, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, DrvSeatOccSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, PAssSeatbeltBucklestatus, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, PassSeatOccSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, doorajarFL, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, doorajarFR, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, doorajarRL, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, doorajarRR, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, HoodSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, TrunkSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, FueldoorSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, ChargeSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, PEPSWarnSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, SRSError, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, lowbatterycharge, bool)

DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, HU_VehicleMainLamp, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, ABSfailed, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, PALAresponse, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, ESPActiveSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, ESCFailed, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, ParkLampSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, EBDFailed, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, BasicElecSteerFailed, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, HU_brakeliquidlevel, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, IMMOPCUauthen, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, EPCwarn, bool)

DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, highCoolantTemperature, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, lowFuel, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, HU_MachineOilPre, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, EngineSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, TransSta, bool)

DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, InletConnctSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, BatSOCRptWarning, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, LimpHomeSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, PwrTrainHighTempWrning, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, PwrTrainConnectSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, MotorHighTempWrning, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, BMSSysFailSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, DrvMotorSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, PCUFailSta, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, InsulationWrning, bool)
DATA_PROPERTY_EASY_IMPLEMENT(TelltaleDataModel, VSPsta, bool)
