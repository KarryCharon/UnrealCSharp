﻿#pragma once

#include "FFunctionDescriptor.h"

class FCSharpFunctionDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FCSharpFunctionDescriptor(UFunction* InFunction);

	virtual ~FCSharpFunctionDescriptor() override;

public:
	virtual void Deinitialize() override;

private:
	friend class FCSharpBind;

	EFunctionFlags OriginalFunctionFlags;

	FNativeFuncPtr OriginalNativeFuncPtr;

	TArray<uint8> OriginalScript;
};
