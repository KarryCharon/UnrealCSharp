﻿#pragma once

#include "Misc/EngineVersionComparison.h"

#define UE_VERSION_START(MajorVersion, MinorVersion, PatchVersion) \
	UE_GREATER_SORT(ENGINE_MAJOR_VERSION, MajorVersion, UE_GREATER_SORT(ENGINE_MINOR_VERSION, MinorVersion, UE_GREATER_SORT(ENGINE_PATCH_VERSION, PatchVersion, true)))

#define UE_LINEAR_COLOR_COMPUTE_LUMINANCE !UE_VERSION_START(5, 0, 0)

#define UE_ARRAY_IS_EMPTY UE_VERSION_START(5, 0, 0)

#define UE_FILTER_CLASS_PATHS UE_VERSION_START(5, 1, 0)
