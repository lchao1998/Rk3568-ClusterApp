// #include "signalvalue.h"

// void ConditionSignal::resetSignals()
// {
//     for (std::weak_ptr<SSignal<bool>> boolSignalWek : m_boolSignals) {
//         auto boolSignal = boolSignalWek.lock();
//         if (!boolSignal)
//             continue;
//         boolSignal->reset();
//     }
//     for (std::weak_ptr<SSignal<int>> boolSignalWek : m_intSignals) {
//         auto boolSignal = boolSignalWek.lock();
//         if (!boolSignal)
//             continue;
//         boolSignal->reset();
//     }
// }