﻿#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Property/FPropertyDescriptor.h"

FArrayHelper::FArrayHelper(FProperty* InProperty):
	InnerPropertyDescriptor(nullptr),
	ScriptArray(nullptr)
{
	InnerPropertyDescriptor = FPropertyDescriptor::Factory(InProperty);

	ScriptArray = new FScriptArray();
}

FArrayHelper::~FArrayHelper()
{
	Deinitialize();
}

void FArrayHelper::Initialize()
{
}

void FArrayHelper::Deinitialize()
{
	// @TODO
	if (ScriptArray != nullptr)
	{
		delete ScriptArray;

		ScriptArray = nullptr;
	}

	if (InnerPropertyDescriptor != nullptr)
	{
		// @TODO
		if (auto InnerProperty = InnerPropertyDescriptor->GetProperty())
		{
			delete InnerProperty;

			InnerProperty = nullptr;
		}

		delete InnerPropertyDescriptor;

		InnerPropertyDescriptor = nullptr;
	}
}

int32 FArrayHelper::GetTypeSize() const
{
	return InnerPropertyDescriptor->GetProperty()->GetSize();
}

int32 FArrayHelper::GetSlack() const
{
	return ScriptArray->GetSlack();
}

bool FArrayHelper::IsValidIndex(const int32 InIndex) const
{
	const auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	return ScriptArrayHelper.IsValidIndex(InIndex);
}

int32 FArrayHelper::Num() const
{
	const auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	return ScriptArrayHelper.Num();
}

int32 FArrayHelper::Max() const
{
	return GetSlack() + Num();
}

void* FArrayHelper::Get(const int32 Index) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	if (ScriptArrayHelper.IsValidIndex(Index))
	{
		return ScriptArrayHelper.GetRawPtr(Index);
	}

	return nullptr;
}

void FArrayHelper::Set(const int32 Index, void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	if (ScriptArrayHelper.IsValidIndex(Index))
	{
		InnerPropertyDescriptor->Set(InValue, ScriptArrayHelper.GetRawPtr(Index));
	}
}

int32 FArrayHelper::Find(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = 0; Index < Num(); ++Index)
	{
		const auto Item = ScriptArrayHelper.GetRawPtr(Index);

		// @TODO
		if (InnerPropertyDescriptor->GetProperty()->Identical(Item, InValue))
		{
			return Index;
		}
	}

	return INDEX_NONE;
}

int32 FArrayHelper::FindLast(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = Num() - 1; Index >= 0; --Index)
	{
		const auto Item = ScriptArrayHelper.GetRawPtr(Index);

		// @TODO
		if (InnerPropertyDescriptor->GetProperty()->Identical(Item, InValue))
		{
			return Index;
		}
	}

	return 0;
}

bool FArrayHelper::Contains(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = 0; Index < Num(); ++Index)
	{
		const auto Item = ScriptArrayHelper.GetRawPtr(Index);

		// @TODO
		if (InnerPropertyDescriptor->GetProperty()->Identical(Item, InValue))
		{
			return true;
		}
	}

	return false;
}

int32 FArrayHelper::AddUninitialized(const int32 InCount) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	return ScriptArrayHelper.AddUninitializedValues(InCount);
}

void FArrayHelper::InsertZeroed(const int32 InIndex, const int32 InCount) const
{
	// @TODO
	ScriptArray->InsertZeroed(InIndex, InCount, InnerPropertyDescriptor->GetProperty()->GetSize());
}

void FArrayHelper::InsertDefaulted(const int32 InIndex, const int32 InCount) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	ScriptArrayHelper.InsertValues(InIndex, InCount);
}

void FArrayHelper::RemoveAt(const int32 InIndex, const int32 InCount, const bool bAllowShrinking) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	ScriptArrayHelper.RemoveValues(InIndex, InCount);

	if (bAllowShrinking)
	{
		// @TODO
		ScriptArray->Shrink(InnerPropertyDescriptor->GetProperty()->GetSize());
	}
}

void FArrayHelper::Reset(const int32 InNewSize) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	ScriptArrayHelper.Resize(InNewSize);
}

void FArrayHelper::Empty(int32 InSlack) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	// @TODO
	ScriptArrayHelper.Resize(InSlack);
}

void FArrayHelper::SetNum(const int32 InNewNum, const bool bAllowShrinking) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	// @TODO
	ScriptArrayHelper.Resize(InNewNum);

	if (bAllowShrinking)
	{
		// @TODO
		ScriptArray->Shrink(InnerPropertyDescriptor->GetProperty()->GetSize());
	}
}

int32 FArrayHelper::Add(void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	const auto Index = ScriptArrayHelper.AddUninitializedValue();

	InnerPropertyDescriptor->Set(InValue, ScriptArrayHelper.GetRawPtr(Index));

	return Index;
}

int32 FArrayHelper::AddZeroed(const int32 InCount) const
{
	// @TODO
	return ScriptArray->AddZeroed(InCount, InnerPropertyDescriptor->GetProperty()->GetSize());
}

int32 FArrayHelper::AddUnique(void* InValue) const
{
	const auto Index = Find(InValue);

	return Index != INDEX_NONE ? Index : Add(InValue);
}

int32 FArrayHelper::RemoveSingle(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = 0; Index < Num(); ++Index)
	{
		const auto Item = ScriptArrayHelper.GetRawPtr(Index);

		// @TODO
		if (InnerPropertyDescriptor->GetProperty()->Identical(Item, InValue))
		{
			RemoveAt(Index, 1, true);

			return 1;
		}
	}

	return 0;
}

int32 FArrayHelper::Remove(const void* InValue) const
{
	auto RemovedNum = 0;

	TArray<int32> x;

	auto Index = Find(InValue);

	while (Index != INDEX_NONE)
	{
		++RemovedNum;

		RemoveAt(Index, 1, true);

		Index = Find(InValue);
	}

	return RemovedNum;
}

void FArrayHelper::SwapMemory(const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap) const
{
	// @TODO
	ScriptArray->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap, InnerPropertyDescriptor->GetProperty()->GetSize());
}

void FArrayHelper::Swap(const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap) const
{
	// @TODO
	ScriptArray->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap, InnerPropertyDescriptor->GetProperty()->GetSize());
}

bool FArrayHelper::IsPrimitiveProperty() const
{
	return InnerPropertyDescriptor->IsPrimitiveProperty();
}

FProperty* FArrayHelper::GetInnerProperty() const
{
	return InnerPropertyDescriptor->GetProperty();
}
