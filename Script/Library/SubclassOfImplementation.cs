﻿using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SubclassOfImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_RegisterImplementation<T>(TSubclassOf<T> InSubclassOf, UClass InClass)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_UnRegisterImplementation<T>(TSubclassOf<T> InSubclassOf) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SubclassOf_GetImplementation<T>(TSubclassOf<T> InSubclassOf, out UClass OutValue)
            where T : UObject;
    }
}