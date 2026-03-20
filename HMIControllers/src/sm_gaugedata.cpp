#include "sm_gaugedata.h"

namespace SharedMemory
{
    SM_POOL_IMPLEMENTATION(GaugeData);

    SM_NUMBER_IMPLEMENTATION(revSpeed, int, GaugeData, 0); //转速
    SM_NUMBER_IMPLEMENTATION(HU_DisvehicleSpeed, int, GaugeData, 0);//车速
}