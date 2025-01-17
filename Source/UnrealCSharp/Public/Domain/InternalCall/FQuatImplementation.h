﻿#pragma once

#include "mono/metadata/object-forward.h"

class FQuatImplementation
{
public:
	static void Quat_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Quat_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static bool Quat_EqualsImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static bool Quat_IsIdentityImplementation(const MonoObject* InMonoObject, float Tolerance);

	static void Quat_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Quat_MultiplyVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                              MonoObject** OutValue);

	static void Quat_MultiplyMatrixImplementation(const MonoObject* InMonoObject, const MonoObject* M,
	                                              MonoObject** OutValue);

	static void Quat_MultiplyScaleImplementation(const MonoObject* InMonoObject, float Scale, MonoObject** OutValue);

	static void Quat_DivideImplementation(const MonoObject* InMonoObject, float Scale, MonoObject** OutValue);

	static bool Quat_IdenticalImplementation(const MonoObject* InMonoObject, const MonoObject* Q, uint32 PortFlags);

	static bool Quat_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Quat_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static float Quat_DotProductImplementation(const MonoObject* A, const MonoObject* B);

	static void Quat_MakeFromEulerImplementation(const MonoObject* Euler, MonoObject** OutValue);

	static void Quat_EulerImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_NormalizeImplementation(const MonoObject* InMonoObject, float Tolerance);

	static void Quat_GetNormalizedImplementation(const MonoObject* InMonoObject, float Tolerance,
	                                             MonoObject** OutValue);

	static bool Quat_IsNormalizedImplementation(const MonoObject* InMonoObject);

	static float Quat_SizeImplementation(const MonoObject* InMonoObject);

	static float Quat_SizeSquaredImplementation(const MonoObject* InMonoObject);

	static float Quat_GetAngleImplementation(const MonoObject* InMonoObject);

	static void Quat_ToAxisAndAngleImplementation(const MonoObject* InMonoObject, MonoObject** Axis, float& Angle);

	static void Quat_ToSwingTwistImplementation(const MonoObject* InMonoObject, const MonoObject* InTwistAxis,
	                                            MonoObject** OutSwing, MonoObject** OutTwist);

	static float Quat_GetTwistAngleImplementation(const MonoObject* InMonoObject, const MonoObject* TwistAxis);

	static void Quat_RotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                            MonoObject** OutValue);

	static void Quat_UnrotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                              MonoObject** OutValue);

	static void Quat_LogImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_ExpImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_InverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_EnforceShortestArcWithImplementation(const MonoObject* InMonoObject, const MonoObject* OtherQuat);

	static void Quat_GetAxisXImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_GetAxisYImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_GetAxisZImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_GetForwardVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_GetRightVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_GetUpVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_VectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_RotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Quat_GetRotationAxisImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static float Quat_AngularDistanceImplementation(const MonoObject* InMonoObject, const MonoObject* Q);

	static bool Quat_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static void Quat_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Quat_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static void Quat_FindBetweenImplementation(const MonoObject* Vector1, const MonoObject* Vector2,
	                                           MonoObject** OutValue);

	static void Quat_FindBetweenNormalsImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
	                                                  MonoObject** OutValue);

	static void Quat_FindBetweenVectorsImplementation(const MonoObject* Vector1, const MonoObject* Vector2,
	                                                  MonoObject** OutValue);

	static float Quat_ErrorImplementation(const MonoObject* Q1, const MonoObject* Q2);

	static float Quat_ErrorAutoNormalizeImplementation(const MonoObject* Q1, const MonoObject* Q2);

	static void Quat_FastLerpImplementation(const MonoObject* A, const MonoObject* B, float Alpha,
	                                        MonoObject** OutValue);

	static void Quat_FastBilerpImplementation(const MonoObject* P00, const MonoObject* P10, const MonoObject* P01,
	                                          const MonoObject* P11, float FracX, float FracY, MonoObject** OutValue);

	static void Quat_Slerp_NotNormalizedImplementation(const MonoObject* Quat1, const MonoObject* Quat2, float Slerp,
	                                                   MonoObject** OutValue);

	static void Quat_SlerpImplementation(const MonoObject* Quat1, const MonoObject* Quat2, float Slerp,
	                                     MonoObject** OutValue);

	static void Quat_SlerpFullPath_NotNormalizedImplementation(const MonoObject* quat1, const MonoObject* quat2,
	                                                           float Alpha, MonoObject** OutValue);

	static void Quat_SlerpFullPathImplementation(const MonoObject* quat1, const MonoObject* quat2, float Alpha,
	                                             MonoObject** OutValue);

	static void Quat_SquadImplementation(const MonoObject* quat1, const MonoObject* tang1, const MonoObject* quat2,
	                                     const MonoObject* tang2, float Alpha, MonoObject** OutValue);

	static void Quat_SquadFullPathImplementation(const MonoObject* quat1, const MonoObject* tang1,
	                                             const MonoObject* quat2, const MonoObject* tang2, float Alpha,
	                                             MonoObject** OutValue);

	static void Quat_CalcTangentsImplementation(const MonoObject* PrevP, const MonoObject* P, const MonoObject* NextP,
	                                            float Tension, MonoObject** OutValue);
};
