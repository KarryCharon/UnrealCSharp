﻿#pragma once

#include "mono/metadata/object-forward.h"

class FVector2DImplementation
{
public:
	static void Vector2D_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector2D_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector2D_MultiplyScaleImplementation(const MonoObject* InMonoObject, float Scale,
	                                                 MonoObject** OutValue);

	static void Vector2D_DivideScaleImplementation(const MonoObject* InMonoObject, float Scale, MonoObject** OutValue);

	static void Vector2D_AddAImplementation(const MonoObject* InMonoObject, float A, MonoObject** OutValue);

	static void Vector2D_SubtractAImplementation(const MonoObject* InMonoObject, float A, MonoObject** OutValue);

	static void Vector2D_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector2D_DivideImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static float Vector2D_DotProductImplementation(const MonoObject* A, const MonoObject* B);

	static float Vector2D_CrossProductImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector2D_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector2D_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector2D_LessThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector2D_GreaterThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector2D_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector2D_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static void Vector2D_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static float Vector2D_GetComponentImplementation(const MonoObject* InMonoObject, int32 Index);

	static void Vector2D_SetComponentImplementation(const MonoObject* InMonoObject, int32 Index, float InValue);

	static float Vector2D_ComponentImplementation(const MonoObject* InMonoObject, int32 Index);

	static float Vector2D_DistSquaredImplementation(const MonoObject* A, const MonoObject* B);

	static float Vector2D_DistanceImplementation(const MonoObject* A, const MonoObject* B);

	static void Vector2D_MaxImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector2D_MinImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static bool Vector2D_EqualsImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static void Vector2D_SetImplementation(const MonoObject* InMonoObject, float InX, float InY);

	static float Vector2D_GetMaxImplementation(const MonoObject* InMonoObject);

	static float Vector2D_GetAbsMaxImplementation(const MonoObject* InMonoObject);

	static float Vector2D_GetMinImplementation(const MonoObject* InMonoObject);

	static float Vector2D_SizeImplementation(const MonoObject* InMonoObject);

	static float Vector2D_SizeSquaredImplementation(const MonoObject* InMonoObject);

	static void Vector2D_GetRotatedImplementation(const MonoObject* InMonoObject, float AngleDeg,
	                                              MonoObject** OutValue);

	static void Vector2D_GetSafeNormalImplementation(const MonoObject* InMonoObject, float Tolerance,
	                                                 MonoObject** OutValue);

	static void Vector2D_NormalizeImplementation(const MonoObject* InMonoObject, float Tolerance);

	static bool Vector2D_IsNearlyZeroImplementation(const MonoObject* InMonoObject, float Tolerance);

	static void Vector2D_IntPointImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector2D_RoundToVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector2D_ClampAxesImplementation(const MonoObject* InMonoObject, float MinAxisVal, float MaxAxisVal,
	                                             MonoObject** OutValue);

	static void Vector2D_GetSignVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector2D_GetAbsImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector2D_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Vector2D_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static bool Vector2D_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static void Vector2D_SphericalToUnitCartesianImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
