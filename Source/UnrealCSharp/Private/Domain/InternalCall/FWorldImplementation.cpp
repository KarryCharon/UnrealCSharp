﻿#include "Domain/InternalCall/FWorldImplementation.h"
#include "Binding/Class/TClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterWorld
{
	FRegisterWorld()
	{
		TClassBuilder<UWorld>(NAMESPACE_LIBRARY)
			.Function("SpawnActor", static_cast<void*>(FWorldImplementation::World_SpawnActorImplementation))
			.Register();
	}
};

static FRegisterWorld RegisterWorld;

void FWorldImplementation::World_SpawnActorImplementation(const MonoObject* InMonoObject, const MonoObject* Class,
                                                          const MonoObject* Transform, MonoObject** OutValue)
{
	if (const auto FoundWorld = FCSharpEnvironment::GetEnvironment()->GetObject<UWorld>(InMonoObject))
	{
		const auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetObject<UClass>(Class);

		const auto FoundTransform = FCSharpEnvironment::GetEnvironment()->GetAddress<
			UScriptStruct, FTransform>(Transform);

		const auto Actor = FoundWorld->SpawnActor(FoundClass, FoundTransform);

		*OutValue = FCSharpEnvironment::GetEnvironment()->GetObject(Actor);
	}
}
