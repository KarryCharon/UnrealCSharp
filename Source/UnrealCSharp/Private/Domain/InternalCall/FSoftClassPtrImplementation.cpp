﻿#include "Domain/InternalCall/FSoftClassPtrImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterSoftClassPtr
{
	FRegisterSoftClassPtr()
	{
		FBindingClassBuilder(TEXT("SoftClassPtr"), NAMESPACE_LIBRARY)
			.Function("Register",
			          static_cast<void*>(FSoftClassPtrImplementation::SoftClassPtr_RegisterImplementation))
			.Function("UnRegister",
			          static_cast<void*>(FSoftClassPtrImplementation::SoftClassPtr_UnRegisterImplementation))
			.Function("Get",
			          static_cast<void*>(FSoftClassPtrImplementation::SoftClassPtr_GetImplementation))
			.Register();
	}
};

static FRegisterSoftClassPtr RegisterSoftClassPtr;

void FSoftClassPtrImplementation::SoftClassPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                      const MonoObject* InClass)
{
	const auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetObject<UClass>(InClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSoftClassPtr<UObject>>(InMonoObject, FoundClass);
}

void FSoftClassPtrImplementation::SoftClassPtr_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSoftClassPtr<UObject>>(InMonoObject);
}

void FSoftClassPtrImplementation::SoftClassPtr_GetImplementation(const MonoObject* InMonoObject,
                                                                 MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment()->GetMulti<TSoftClassPtr<UObject>>(InMonoObject);

	*OutValue = FCSharpEnvironment::GetEnvironment()->Bind(Multi.Get());
}
