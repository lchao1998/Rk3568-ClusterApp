#include "CenterViewDataModel.h"
#include "sm_centerview.h"
#include <QDebug>

CenterViewDataModel::CenterViewDataModel(int updateInterval, QObject *parent)
    : DataModel{updateInterval, parent},
    m_batSOCRpt(100),
    m_seatBeltIndex(0),
    m_seatOccStaIndex(0),
    m_pASSta_RL(0),
    m_pASSta_RML(0),
    m_pASSta_RMR(0),
    m_pASSta_RR(0),
    m_pASDistanceRL(0),
    m_pASDistanceRML(0),
    m_pASDistanceRMR(0),
    m_pASDistanceRR(0),
    m_currentStatus(0),
    m_index(0)
{

}

void CenterViewDataModel::updateData()
{
    m_index ++;
    if(m_index == 20)
    {
        if(m_batSOCRpt > 0)
        {
            m_batSOCRpt --;
        }
        else
        {
            m_batSOCRpt = 100;
        }

        if(m_seatBeltIndex < 2)
        {
            m_seatBeltIndex ++;
        }
        else
        {
            m_seatBeltIndex = 0;
        }

        if(m_seatOccStaIndex < 2)
        {
            m_seatOccStaIndex ++;
        }
        else
        {
            m_seatOccStaIndex = 0;
        }

        if( m_pASSta_RL < 2)
        {
            m_pASSta_RL ++;
        }
        else
        {
            m_pASSta_RL = 0;
        }

        if( m_pASSta_RML < 2)
        {
            m_pASSta_RML ++;
        }
        else
        {
            m_pASSta_RML = 0;
        }

        if( m_pASSta_RMR < 2)
        {
            m_pASSta_RMR ++;
        }
        else
        {
            m_pASSta_RMR = 0;
        }

        if( m_pASSta_RR < 2)
        {
            m_pASSta_RR ++;
        }
        else
        {
            m_pASSta_RR = 0;
        }

        if(m_pASDistanceRL < 10)
        {
            m_pASDistanceRL ++;
        }
        else
        {
            m_pASDistanceRL = 0;
        }

        if(m_pASDistanceRML < 10)
        {
            m_pASDistanceRML ++;
        }
        else
        {
            m_pASDistanceRML = 0;
        }

        if(m_pASDistanceRMR < 10)
        {
            m_pASDistanceRMR ++;
        }
        else
        {
            m_pASDistanceRMR = 0;
        }

        if(m_pASDistanceRR < 10)
        {
            m_pASDistanceRR ++;
        }
        else
        {
            m_pASDistanceRR = 0;
        }

        if(m_currentStatus < 4)
        {
            m_currentStatus ++;
        }
        else
        {
            m_currentStatus = 0;
        }

        emit HU_AvgVehicleSpeedChanged();
        emit HU_CurONChanged();
        emit HU_AvgfuleconsumpChanged();
        emit HU_RemainRangeChanged();
        emit BatSOCRptChanged();
        emit HVBatActlVoltageChanged();
        emit ExchgCurntChanged();

        emit SeatbeltBucklestatusRLChanged();
        emit RLSeatOccStaChanged();
        emit SeatbeltBucklestatusRMChanged();
        emit RMSeatOccStaChanged();
        emit SeatbeltBucklestatusRRChanged();
        emit RRSeatOccStaChanged();

        emit PASSta_RLChanged();
        emit PASSta__RMLChanged();
        emit PASSta__RMRChanged();
        emit PASSta__RRChanged();
        emit PASDistanceRLChanged();
        emit PASDistanceRMLChanged();
        emit PASDistanceRMRChanged();
        emit PASDistanceRRChanged();

        emit currentStatusChanged();
    }
    else if(m_index > 20)
    {
        m_index = 0;
    }

    DATA_PROERTY_CHECK(Menu_SwSta);
}


DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, HU_AvgVehicleSpeed, int)
{
    return 130;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, HU_CurON, int)
{
    return 15;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, HU_Avgfuleconsump, float)
{
    return 10;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, HU_RemainRange, int)
{
    return 300;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, BatSOCRpt, int)
{
    return m_batSOCRpt;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, HVBatActlVoltage, int)
{
    return 30;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, ExchgCurnt, int)
{
    return 20;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, SeatbeltBucklestatusRL, bool)
{
    return m_seatBeltIndex == 0;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, RLSeatOccSta, bool)
{
    return m_seatOccStaIndex == 0;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, SeatbeltBucklestatusRM, bool)
{
    return m_seatBeltIndex == 1;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, RMSeatOccSta, bool)
{
    return m_seatOccStaIndex == 1;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, SeatbeltBucklestatusRR, bool)
{
    return m_seatBeltIndex == 2;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, RRSeatOccSta, bool)
{
    return m_seatOccStaIndex == 2;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASSta_RL, int)
{
    return m_pASSta_RL;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASSta__RML, int)
{
    return m_pASSta_RML;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASSta__RMR, int)
{
    return m_pASSta_RMR;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASSta__RR, int)
{
    return m_pASSta_RR;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASDistanceRL, int)
{
    return m_pASDistanceRL;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASDistanceRML, int)
{
    return m_pASDistanceRML;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASDistanceRMR, int)
{
    return m_pASDistanceRMR;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, PASDistanceRR, int)
{
    return m_pASDistanceRR;
}

DATA_PROPERTY_IMPLEMENT(CenterViewDataModel, currentStatus, int)
{
    return m_currentStatus;
}

DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, Menu_SwSta, int)
