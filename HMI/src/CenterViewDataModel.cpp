#include "CenterViewDataModel.h"
#include "sm_centerview.h"

CenterViewDataModel::CenterViewDataModel(int updateInterval, QObject *parent)
    : DataModel{updateInterval, parent}
{

}

void CenterViewDataModel::updateData()
{
    DATA_PROERTY_CHECK(HU_AvgVehicleSpeed);
    DATA_PROERTY_CHECK(HU_CurON);
    DATA_PROERTY_CHECK(HU_Avgfuleconsump);
    DATA_PROERTY_CHECK(HU_RemainRange);
    DATA_PROERTY_CHECK(BatSOCRpt);
    DATA_PROERTY_CHECK(HVBatActlVoltage);
    DATA_PROERTY_CHECK(ExchgCurnt);

    DATA_PROERTY_CHECK(SeatbeltBucklestatusRL);
    DATA_PROERTY_CHECK(RLSeatOccSta);
    DATA_PROERTY_CHECK(SeatbeltBucklestatusRM);
    DATA_PROERTY_CHECK(RMSeatOccSta);
    DATA_PROERTY_CHECK(SeatbeltBucklestatusRR);
    DATA_PROERTY_CHECK(RRSeatOccSta);

    DATA_PROERTY_CHECK(PASSta_RL);
    DATA_PROERTY_CHECK(PASSta__RML);
    DATA_PROERTY_CHECK(PASSta__RMR);
    DATA_PROERTY_CHECK(PASSta__RR);
    DATA_PROERTY_CHECK(PASDistanceRL);
    DATA_PROERTY_CHECK(PASDistanceRML);
    DATA_PROERTY_CHECK(PASDistanceRMR);
    DATA_PROERTY_CHECK(PASDistanceRR);

    DATA_PROERTY_CHECK(currentStatus);
    DATA_PROERTY_CHECK(Menu_SwSta);

    DATA_PROERTY_CHECK(BMSErrorCodes);
}


DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, HU_AvgVehicleSpeed, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, HU_CurON, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, HU_Avgfuleconsump, float)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, HU_RemainRange, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, BatSOCRpt, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, HVBatActlVoltage, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, ExchgCurnt, int)

DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, SeatbeltBucklestatusRL, bool)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, RLSeatOccSta, bool)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, SeatbeltBucklestatusRM, bool)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, RMSeatOccSta, bool)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, SeatbeltBucklestatusRR, bool)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, RRSeatOccSta, bool)

DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASSta_RL, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASSta__RML, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASSta__RMR, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASSta__RR, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASDistanceRL, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASDistanceRML, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASDistanceRMR, int)
DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, PASDistanceRR, int)

DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, currentStatus, int)

DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, Menu_SwSta, int)

DATA_PROPERTY_SIMPLE_IMPLEMENT(CenterViewDataModel, BMSErrorCodes, int)
