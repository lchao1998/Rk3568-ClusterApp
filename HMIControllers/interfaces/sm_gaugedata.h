#ifndef SM_GAUGEDATA_H
#define SM_GAUGEDATA_H

#include "sharedmemory.hpp"
#include "smstructdefine.h"

using namespace SharedMemory;

namespace SharedMemory {

    SM_POOL_DEFINITION(GaugeData);

    SM_NUMBER_DEFINITION(revSpeed, int);//转速
    SM_NUMBER_DEFINITION(HU_DisvehicleSpeed, int);//车速
}

#endif