﻿#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Template/TGetArrayLength.h"

EPropertyTypeExtent FTypeBridge::GetPropertyType(MonoReflectionType* InReflectionType)
{
	InReflectionType = GetType(InReflectionType);

	const auto InMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Reflection_Type_Get_Type(
		InReflectionType);

	const auto InMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Class(InMonoType);

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class())
	{
		return EPropertyTypeExtent::Byte;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt16_Class())
	{
		return EPropertyTypeExtent::UInt16;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt32_Class())
	{
		return EPropertyTypeExtent::UInt32;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt64_Class())
	{
		return EPropertyTypeExtent::UInt64;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class())
	{
		return EPropertyTypeExtent::Int8;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int16_Class())
	{
		return EPropertyTypeExtent::Int16;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int32_Class())
	{
		return EPropertyTypeExtent::Int;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int64_Class())
	{
		return EPropertyTypeExtent::Int64;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Boolean_Class())
	{
		return EPropertyTypeExtent::Bool;
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Single_Class())
	{
		return EPropertyTypeExtent::Float;
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SUB_CLASS_OF))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::ClassReference;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()),
		FUnrealCSharpFunctionLibrary::GetFullClass(UObject::StaticClass())))
	{
		if (InMonoClass == FoundMonoClass || FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(
			InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::ObjectReference;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_NAME))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Name;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SCRIPT_INTERFACE))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Interface;
		}
	}

	if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(
		InMonoClass, FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Enum_Class(), false))
	{
		return EPropertyTypeExtent::Enum;
	}

	if (const auto InType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Reflection_Type_Get_Type(
		InReflectionType))
	{
		if (const auto InClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Class(InType))
		{
			if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
				InClass, FUNCTION_STATIC_STRUCT, 0))
			{
				return EPropertyTypeExtent::Struct;
			}
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::String;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_TEXT))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Text;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_WEAK_OBJECT_PTR))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::WeakObjectReference;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_LAZY_OBJECT_PTR))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::LazyObjectReference;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SOFT_CLASS_PTR))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SoftClassReference;
		}
	}

	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SOFT_OBJECT_PTR))
	{
		if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SoftObjectReference;
		}
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Double_Class())
	{
		return EPropertyTypeExtent::Double;
	}

	return EPropertyTypeExtent::None;
}

MonoClass* FTypeBridge::GetMonoClass(FProperty* InProperty)
{
	if (const auto ByteProperty = CastField<FByteProperty>(InProperty)) return GetMonoClass(ByteProperty);

	if (CastField<FUInt16Property>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt16_Class();
	}

	if (CastField<FUInt32Property>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt32_Class();
	}

	if (CastField<FUInt64Property>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt64_Class();
	}

	if (CastField<FInt8Property>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class();
	}

	if (CastField<FInt16Property>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int16_Class();
	}

	if (CastField<FIntProperty>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int32_Class();
	}

	if (CastField<FInt64Property>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int64_Class();
	}

	if (CastField<FBoolProperty>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Boolean_Class();
	}

	if (CastField<FFloatProperty>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Single_Class();
	}

	if (const auto ClassProperty = CastField<FClassProperty>(InProperty))
	{
		return GetMonoClass(ClassProperty);
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(InProperty))
	{
		return GetMonoClass(ObjectProperty);
	}

	if (const auto NameProperty = CastField<FNameProperty>(InProperty))
	{
		return GetMonoClass(NameProperty);
	}

	if (const auto DelegateProperty = CastField<FDelegateProperty>(InProperty))
	{
		return GetMonoClass(DelegateProperty);
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(InProperty))
	{
		return GetMonoClass(InterfaceProperty);
	}

	if (const auto StructProperty = CastField<FStructProperty>(InProperty))
	{
		return GetMonoClass(StructProperty);
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(InProperty))
	{
		return GetMonoClass(ArrayProperty);
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(InProperty))
	{
		return GetMonoClass(EnumProperty);
	}

	if (const auto StrProperty = CastField<FStrProperty>(InProperty))
	{
		return GetMonoClass(StrProperty);
	}

	if (const auto TextProperty = CastField<FTextProperty>(InProperty))
	{
		return GetMonoClass(TextProperty);
	}

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(InProperty))
	{
		return GetMonoClass(MulticastDelegateProperty);
	}

	if (const auto MulticastInlineDelegateProperty = CastField<FMulticastInlineDelegateProperty>(InProperty))
	{
		return GetMonoClass(MulticastInlineDelegateProperty);
	}

	if (const auto MulticastSparseDelegateProperty = CastField<FMulticastSparseDelegateProperty>(InProperty))
	{
		return GetMonoClass(MulticastSparseDelegateProperty);
	}

	if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(InProperty))
	{
		return GetMonoClass(WeakObjectProperty);
	}

	if (const auto LazyObjectProperty = CastField<FLazyObjectProperty>(InProperty))
	{
		return GetMonoClass(LazyObjectProperty);
	}

	if (const auto SoftClassProperty = CastField<FSoftClassProperty>(InProperty))
	{
		return GetMonoClass(SoftClassProperty);
	}

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(InProperty))
	{
		return GetMonoClass(SoftObjectProperty);
	}

	if (CastField<FDoubleProperty>(InProperty))
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Double_Class();
	}

	if (const auto MapProperty = CastField<FMapProperty>(InProperty))
	{
		return GetMonoClass(MapProperty);
	}

	if (const auto SetProperty = CastField<FSetProperty>(InProperty))
	{
		return GetMonoClass(SetProperty);
	}

	// @TODO
	if (CastField<FFieldPathProperty>(InProperty))
	{
		return nullptr;
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FByteProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return InProperty->Enum != nullptr
			       ? FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				       FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->Enum),
				       FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->Enum))
			       : FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class();
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SUB_CLASS_OF);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->MetaClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->MetaClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FNameProperty*)
{
	return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_NAME);
}

MonoClass* FTypeBridge::GetMonoClass(const FDelegateProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FInterfaceProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SCRIPT_INTERFACE);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->InterfaceClass),
			FUnrealCSharpFunctionLibrary::GetFullInterface(InProperty->InterfaceClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FStructProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->Struct),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->Struct));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FArrayProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_ARRAY);

		const auto FoundMonoClass = GetMonoClass(InProperty->Inner);

		const auto FoundMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass, ReflectionTypeMonoArray);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FEnumProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->GetEnum()),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->GetEnum()));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FStrProperty*)
{
	return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);
}

MonoClass* FTypeBridge::GetMonoClass(const FTextProperty*)
{
	return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_TEXT);
}

MonoClass* FTypeBridge::GetMonoClass(const FMulticastDelegateProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FWeakObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_WEAK_OBJECT_PTR);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FLazyObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_LAZY_OBJECT_PTR);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSoftClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SOFT_CLASS_PTR);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->MetaClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->MetaClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSoftObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SOFT_OBJECT_PTR);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FMapProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_MAP);

		const auto FoundKeyMonoClass = GetMonoClass(InProperty->KeyProp);

		const auto FoundKeyMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
			FoundKeyMonoClass);

		const auto FoundKeyReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
			FoundKeyMonoType);

		const auto FoundValueMonoClass = GetMonoClass(InProperty->ValueProp);

		const auto FoundValueMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
			FoundValueMonoClass);

		const auto FoundValueReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
			FoundValueMonoType);

		const auto ReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 2);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundKeyReflectionType);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 1, FoundValueReflectionType);

		return GetMonoClass(FoundGenericMonoClass, ReflectionTypeMonoArray, ReflectionTypeMonoArray);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSetProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SET);

		const auto FoundMonoClass = GetMonoClass(InProperty->ElementProp);

		const auto FoundMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass, ReflectionTypeMonoArray);
	}

	return nullptr;
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoObject* InMonoObject, const int32 InIndex)
{
	return ARRAY_GET(
		GetGenericArguments(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(InMonoObject)),
		MonoReflectionType*, InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoClass* InMonoClass, const int32 InIndex)
{
	return ARRAY_GET(GetGenericArguments(InMonoClass), MonoReflectionType*, InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoType* InMonoType, const int32 InIndex)
{
	return ARRAY_GET(GetGenericArguments(InMonoType), MonoReflectionType*, InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoReflectionType* InReflectionType, const int32 InIndex)
{
	return ARRAY_GET(GetGenericArguments(InReflectionType), MonoReflectionType*, InIndex);
}

MonoArray* FTypeBridge::GetGenericArguments(MonoObject* InMonoObject)
{
	return GetGenericArguments(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(InMonoObject));
}

MonoArray* FTypeBridge::GetGenericArguments(MonoClass* InMonoClass)
{
	return GetGenericArguments(FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(InMonoClass));
}

MonoArray* FTypeBridge::GetGenericArguments(MonoType* InMonoType)
{
	return GetGenericArguments(FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(InMonoType));
}

MonoArray* FTypeBridge::GetGenericArguments(MonoReflectionType* InReflectionType)
{
	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	auto InParams = static_cast<void*>(InReflectionType);

	const auto GetGenericArgumentsMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
		Class_Get_Method_From_Name(
			UtilsMonoClass, FUNCTION_UTILS_GET_GENERIC_ARGUMENTS, TGetArrayLength(InParams));

	return reinterpret_cast<MonoArray*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		GetGenericArgumentsMethod, nullptr, &InParams, nullptr));
}

MonoClass* FTypeBridge::GetMonoClass(MonoClass* InGenericMonoClass, MonoClass* InTypeMonoClass)
{
	const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		InGenericMonoClass);

	const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundGenericMonoType);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(InTypeMonoClass);

	const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundMonoType);

	void* InParams[2];

	InParams[0] = FoundGenericReflectionType;

	const auto ReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

	ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

	InParams[1] = ReflectionTypeMonoArray;

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams, nullptr);

	return FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(GenericClassMonoObject);
}

MonoClass* FTypeBridge::GetMonoClass(MonoClass* InGenericMonoClass, MonoClass* InTypeMonoClass,
                                     MonoArray* InParamsArray)
{
	const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		InGenericMonoClass);

	const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundGenericMonoType);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(InTypeMonoClass);

	const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundMonoType);

	void* InParams[3];

	InParams[0] = FoundGenericReflectionType;

	const auto ReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

	ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

	InParams[1] = ReflectionTypeMonoArray;

	InParams[2] = InParamsArray;

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams, nullptr);

	return FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(GenericClassMonoObject);
}

MonoClass* FTypeBridge::GetMonoClass(MonoClass* InGenericMonoClass, MonoArray* InTypeMonoClassArray,
                                     MonoArray* InParamsArray)
{
	const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		InGenericMonoClass);

	const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundGenericMonoType);

	void* InParams[3];

	InParams[0] = FoundGenericReflectionType;

	InParams[1] = InTypeMonoClassArray;

	InParams[2] = InParamsArray;

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams, nullptr);

	return FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(GenericClassMonoObject);
}

MonoReflectionType* FTypeBridge::GetType(MonoReflectionType* InReflectionType)
{
	auto InParams = static_cast<void*>(InReflectionType);

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	const auto GetTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_GET_TYPE, TGetArrayLength(InParams));

	return reinterpret_cast<MonoReflectionType*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		GetTypeMethod, nullptr, &InParams, nullptr));
}
