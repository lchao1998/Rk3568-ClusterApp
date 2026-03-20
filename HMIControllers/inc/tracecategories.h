/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TRACECATEGORIES_H
#define TRACECATEGORIES_H

// This source file can be built in two ways:
// 1. As part of the regular GN build, against standard includes.
// 2. To test that the amalgmated SDK works, against the perfetto.h source.
#ifdef USING_PERFETTO_LIBRARY
#include "perfetto.h"
// The set of track event categories that the example is using.
PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("dataserver")
        .SetDescription("data server"));

#endif  // TRACE_CATEGORIES_H

#endif
