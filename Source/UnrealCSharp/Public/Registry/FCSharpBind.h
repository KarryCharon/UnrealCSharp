﻿#pragma once

#include "Domain/FMonoDomain.h"
#include "Reflection/Class/FClassDescriptor.h"
#include "Reflection/Function/FFunctionDescriptor.h"

class FCSharpBind
{
public:
	static bool Bind(FMonoDomain* InMonoDomain, UObject* InObject);

	static bool Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	static bool Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                 MonoReflectionType* InValueReflectionType);

	static bool Bind(FMonoDomain* InMonoDomain, MonoObject* InMonoObject, const FName& InStructName);

private:
	static bool Bind(FMonoDomain* InMonoDomain, UStruct* InStruct, bool bNeedMonoClass = true);

	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

private:
	static bool BindImplementation(FMonoDomain* InMonoDomain, UObject* InObject);

	static bool BindImplementation(FMonoDomain* InMonoDomain, UStruct* InStruct);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

	static bool BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	static bool BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                               MonoReflectionType* InValueReflectionType);

	static bool BindImplementation(FMonoDomain* InMonoDomain, MonoObject* InMonoObject, const FName& InStructName);

private:
	static bool CanBind(const FMonoDomain* InMonoDomain, const UStruct* InStruct);

private:
	static UFunction* GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction);

	static bool IsCallCSharpFunction(UFunction* InFunction);

	static UFunction* DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName);

	static void UpdateCallCSharpFunction(UFunction* InFunction);

	static void UpdateCallCSharpFunctionFlags(UFunction* InFunctionCallLua);
};
