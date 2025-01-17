﻿#include "Reflection/Container/FMapHelper.h"

FMapHelper::FMapHelper(FProperty* InKeyProperty, FProperty* InValueProperty, void* InData):
	KeyPropertyDescriptor(nullptr),
	ValuePropertyDescriptor(nullptr),
	ScriptMap(nullptr),
	bNeedFree(false)
{
	if (InData != nullptr)
	{
		bNeedFree = false;

		ScriptMap = static_cast<FScriptMap*>(InData);
	}
	else
	{
		bNeedFree = true;

		ScriptMap = new FScriptMap();
	}

	if (InKeyProperty != nullptr && InValueProperty != nullptr)
	{
		KeyPropertyDescriptor = FPropertyDescriptor::Factory(InKeyProperty);

		ValuePropertyDescriptor = FPropertyDescriptor::Factory(InValueProperty);

		ScriptMapLayout = FScriptMap::GetScriptLayout(InKeyProperty->GetSize(), InKeyProperty->GetMinAlignment(),
		                                              InValueProperty->GetSize(), InValueProperty->GetMinAlignment());
	}
}

FMapHelper::~FMapHelper()
{
	Deinitialize();
}

void FMapHelper::Initialize()
{
}

void FMapHelper::Deinitialize()
{
	if (bNeedFree && ScriptMap != nullptr)
	{
		delete ScriptMap;

		ScriptMap = nullptr;
	}

	if (KeyPropertyDescriptor != nullptr)
	{
		if (bNeedFree)
		{
			KeyPropertyDescriptor->DestroyProperty();
		}

		delete KeyPropertyDescriptor;

		KeyPropertyDescriptor = nullptr;
	}

	if (ValuePropertyDescriptor != nullptr)
	{
		if (bNeedFree)
		{
			ValuePropertyDescriptor->DestroyProperty();
		}

		delete ValuePropertyDescriptor;

		ValuePropertyDescriptor = nullptr;
	}
}

void FMapHelper::Empty(const int32 InExpectedNumElements) const
{
	ScriptMap->Empty(InExpectedNumElements, ScriptMapLayout);
}

int32 FMapHelper::Num() const
{
	return ScriptMap->Num();
}

void FMapHelper::Add(void* InKey, void* InValue) const
{
	Set(InKey, InValue);
}

int32 FMapHelper::Remove(const void* InKey) const
{
	auto Count = 0;

	do
	{
		const auto Index = ScriptMap->FindPairIndex(InKey,
		                                            ScriptMapLayout,
		                                            [this](const void* ElementKey)
		                                            {
			                                            return KeyPropertyDescriptor->GetValueTypeHash(ElementKey);
		                                            },
		                                            [this](const void* A, const void* B)
		                                            {
			                                            return KeyPropertyDescriptor->Identical(A, B);
		                                            }
		);

		if (Index == INDEX_NONE)
		{
			break;
		}

		++Count;

		const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));

		if (!KeyPropertyDescriptor->IsPrimitiveProperty())
		{
			KeyPropertyDescriptor->DestroyValue(Data);
		}

		if (!ValuePropertyDescriptor->IsPrimitiveProperty())
		{
			ValuePropertyDescriptor->DestroyValue(Data + ScriptMapLayout.ValueOffset);
		}

		ScriptMap->RemoveAt(Index, ScriptMapLayout);
	}
	while (true);

	return Count;
}

void* FMapHelper::FindKey(const void* InValue) const
{
	for (auto Index = 0; Index < ScriptMap->GetMaxIndex(); ++Index)
	{
		if (ScriptMap->IsValidIndex(Index))
		{
			const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));

			if (ValuePropertyDescriptor->Identical(Data + ScriptMapLayout.ValueOffset, InValue))
			{
				return Data;
			}
		}
	}

	return nullptr;
}

void* FMapHelper::Find(const void* InKey) const
{
	return Get(InKey);
}

bool FMapHelper::Contains(const void* InKey) const
{
	return Get(InKey) != nullptr;
}

void* FMapHelper::Get(const void* InKey) const
{
	return ScriptMap->FindValue(InKey,
	                            ScriptMapLayout,
	                            [this](const void* ElementKey)
	                            {
		                            return KeyPropertyDescriptor->GetValueTypeHash(ElementKey);
	                            },
	                            [this](const void* A, const void* B)
	                            {
		                            return KeyPropertyDescriptor->Identical(A, B);
	                            });
}

void FMapHelper::Set(void* InKey, void* InValue) const
{
	ScriptMap->Add(
		InKey,
		InValue,
		ScriptMapLayout,
		[this](const void* ElementKey)
		{
			return KeyPropertyDescriptor->GetValueTypeHash(ElementKey);
		},
		[this](const void* A, const void* B)
		{
			return KeyPropertyDescriptor->Identical(A, B);
		},
		[this, InKey](void* NewElementKey)
		{
			KeyPropertyDescriptor->InitializeValue_InContainer(NewElementKey);

			if (KeyPropertyDescriptor->IsPrimitiveProperty())
			{
				KeyPropertyDescriptor->Set(InKey, NewElementKey);
			}
			else
			{
				KeyPropertyDescriptor->Set(static_cast<void**>(InKey), NewElementKey);
			}
		},
		[this, InValue](void* NewElementValue)
		{
			ValuePropertyDescriptor->InitializeValue_InContainer(NewElementValue);

			if (ValuePropertyDescriptor->IsPrimitiveProperty())
			{
				ValuePropertyDescriptor->Set(InValue, NewElementValue);
			}
			else
			{
				ValuePropertyDescriptor->Set(static_cast<void**>(InValue), NewElementValue);
			}
		},
		[this, InValue](void* ExistingElementValue)
		{
			if (ValuePropertyDescriptor->IsPrimitiveProperty())
			{
				ValuePropertyDescriptor->Set(InValue, ExistingElementValue);
			}
			else
			{
				ValuePropertyDescriptor->Set(static_cast<void**>(InValue), ExistingElementValue);
			}
		},
		[this](void* ElementKey)
		{
			// @TODO
			if (!KeyPropertyDescriptor->IsPrimitiveProperty())
			{
				KeyPropertyDescriptor->DestroyValue(ElementKey);
			}
		},
		[this](void* ElementValue)
		{
			// @TODO
			if (!ValuePropertyDescriptor->IsPrimitiveProperty())
			{
				ValuePropertyDescriptor->DestroyValue(ElementValue);
			}
		}
	);
}

FPropertyDescriptor* FMapHelper::GetKeyPropertyDescriptor() const
{
	return KeyPropertyDescriptor;
}

FPropertyDescriptor* FMapHelper::GetValuePropertyDescriptor() const
{
	return ValuePropertyDescriptor;
}

FScriptMap* FMapHelper::GetScriptMap() const
{
	return ScriptMap;
}

int32 FMapHelper::GetMaxIndex() const
{
	return ScriptMap->GetMaxIndex();
}

bool FMapHelper::IsValidIndex(const int32 InIndex) const
{
	return ScriptMap->IsValidIndex(InIndex);
}

void* FMapHelper::GetEnumeratorKey(const int32 InIndex) const
{
	return ScriptMap->IsValidIndex(InIndex)
		       ? static_cast<uint8*>(ScriptMap->GetData(InIndex, ScriptMapLayout))
		       : nullptr;
}

void* FMapHelper::GetEnumeratorValue(const int32 InIndex) const
{
	return ScriptMap->IsValidIndex(InIndex)
		       ? static_cast<uint8*>(ScriptMap->GetData(InIndex, ScriptMapLayout)) + ScriptMapLayout.ValueOffset
		       : nullptr;
}
