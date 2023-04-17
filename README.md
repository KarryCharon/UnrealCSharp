# UnrealCSharp使用说明

[![Contributors][contributors-shield]][contributors-url]

[![Forks][forks-shield]][forks-url]

[![Stargazers][stars-shield]][stars-url]

[![Issues][issues-shield]][issues-url]



# 目录

- [简介](#简介)
- [作为使用者](#作为使用者)
  - [预备工作](#预备工作)
  - [安装](#安装)
  - [基本使用](#基本使用)
  - [例子](#例子)
  - [静态导出](#静态导出)
  - [Debug](#Debug)
- [作为开发者](#作为开发者)
  - [目录结构](#目录结构)
  - [框架说明](#框架说明)
- [FAQ](#FAQ)
- [Misc](##Misc)
- [ChangeLog](##ChangeLog)
- [Contributor](##Contributor)

## 简介

## 作为使用者

### 基本使用预备工作

1. 前置环境
   1. Visual Studio 2022
      1. 安装msvc
      2. 安装c# ??
   2. Mono
2. 推荐IDE
   1. Rider(首选)
   2. Visual Studio

### 安装

1. 使用git安装

   ```bash
   cd ProjectDirectory/Plugins
   git clone https://github.com/crazytuzi/UnrealCSharp.git
   ```

2. 下载zip安装

   1. 从https://github.com/crazytuzi/UnrealCSharp 下载对应的 zip源码包
   2. 进入工程文件夹的Plugins子文件夹,将zip全部解压到 其中

3. 安装完成后目录结构

   ```text
   ProjectDirectory
   	Binaries
   	Content
   	Plugins
   		UnrealCSharp
   			Content
   			Resources
   			Source
   			...
   			UnrealCSharp.uplugin
   	Saved
   	Source
   	ProjectName.uproject
   	....
   ```

4. 首先右键点击工程文件选择生成VisualStudio项目, 会生成ProjectName.sln 解决方案

5. 随后使用 Rider 或 VS打开 sln, 启动项目

### 基本使用

1. 如何导出蓝图到对应的 cs 脚本?

   1. 在 Map视图下 点击顶部 窗口 > UnrealCSharpEditor 导出cs脚本

      ![Export-Cs](./attachments/US-Export-Cs.png)

   2. 导出前注意事项

      1. Actor导出
      2. Struct/Enum导出
         1. 导出项名以英文本地化显示名为准
         2. 注意避免非ASCII 字符
      3. Function导出
         1. 入参无引用标记导出为C#的普通参数
         2. 入参有**引用标记**导出为C#的**ref**参数
         3. 出参默认导出为C#的**out**参数

2. 在cs脚本中编写游戏逻辑后点击运行游戏, 插件将自动编译cs为dll

### 例子

1. Method Override( 以 ReceivedBeginPlay 为例)
    1. 假定蓝图定义了一个 MyActor, 则生成的cs脚本大致如下

       ```csharp
       // 一些命名空间的引入
       using System;
       using Script.Common;
       using Script.Engine;
       using Script.Reflection.Property;
       using Script.Library;
       using Script.CoreUObject;

       namespace Script.项目名
       {
        [PathName("/Script/项目名.MyActor")]
        public partial class AMyActor : AActor
        {
           // ... 一些默认 方法
        }
       }
       ```

    2. 当我们Override已有方法时首先需要对 该class添加`[IsOverride]` 标记

       ```csharp
       namespace Script.项目名
       {
         [IsOverride] // <---这行
        [PathName("/Script/项目名.MyActor")]
        public partial class AMyActor : AActor
         // ....
       }
       ```

    3. 然后对我们需要覆写的方法也加上 该标记

       ```csharp
       namespace Script.项目名
       {
         [IsOverride] // <---这行
        [PathName("/Script/项目名.MyActor")]
        public partial class AMyActor : AActor
         {
           [IsOverride]
          public void ReceiveBeginPlay()
          {
            // do whatever you want
          }
         }
       }
       ```

2. 容器
   1. TArray

      ```csharp
      var testTArray = new TArray<FName>();
      testTArray.Add("TTT");
      var eq = testTArray[0] == new FName("TTT");
      
      // for
      for (int i = 0; i < testTArray.Num(); ++i)
      {
          Console.WriteLine(testTArray[i].ToString());
      }
      // foreach
      foreach (FName e in testTArray)
      {
          Console.WriteLine(e.ToString());
      }
      
      int max = testTArray.Max();
      int findIndex = testTArray.Find("TTT");
      testTArray.RemoveAt(0, 1);
      testTArray.Remove("TTT");
      testTArray.Empty();
      ```

   2. TMap

      ```csharp
      var testTMap = new TMap<FName, UObject>();
      testTMap.Add("Obj1", Unreal.NewObject<UObject>(this));
      var obj = testTMap.Find("Obj1");
      var key = testTMap.FindKey(obj);
      int lenTMap = testTMap.Num();
      // foreach
      foreach (var pair in testTMap)
      {
          Console.WriteLine(pair.Key.ToString());
          Console.WriteLine(pair.Value.GetName());
      }
      var name = testTMap["Obj1"].GetName();
      testTMap.Remove("Obj1");
      testTMap.Empty();
      ```

   3. TSet

      ```csharp
      var testSet = new TSet<FName>();
      testSet.Add("DDD");
      var c = testSet.Contains("DDD");
      int lenTSet = testSet.Num();
      // foreach
      foreach (FName t in testSet)
      {
          Console.WriteLine(t.ToString());
      }
      testSet.Remove("DDD");
      testSet.Empty();
      ```

3. 基本数据类型

4. UStruct
   1. FVector
   2. Rotator
   3. Matrix

5. NewObject

6. SpawnActor

7. SpawnAIFromClass

8. 延迟构造

9. CreateUserWidget

10. Button事件绑定

11. 委托绑定

12. MultiObjectChannelTrace?

13. StaticMesh
     1. SetStaticMesh
     2. SetMaterial

### Debug静态导出

1. 基本类型对应

   1. Byte

   2. Int

   3. Double

2. Mono对象类型

   1. MonoClass

   2. MonoImage

   3. MonoMethod

   4. MonoObject

   5. MonoException

   6. MonoReflectionAssembly

   7. MonoReflectionTypeBuilder

   8. --

   9. MonoString

   10. MonoArray

   11. MonoReflectionMethod

   12. MonoReflectionModule

   13. MonoReflectionField

   14. MonoReflectionProperty

   15. MonoReflectionEvent

   16. MonoReflectionType

   17. MonoDelegate

   18. MonoThreadsSync

   19. MonoThread

   20. MonoDynamicAssembly

   21. MonoDynamicImage

   22. MonoReflectionMethodBody

   23. MonoAppContext

3. 导出例子

   1. DataTableFunctionLibrary 中的 GetDataTableRowFromName 函数导出为 c# 侧的泛型模板方法

   2. c# 侧的期望签名为 `public static Boolean GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)`

   3. cpp侧签名为 `static bool GetDataTableRowFromName(UDataTable* Table, FName RowName, FTableRowBase& OutRow)`

   4. 显然 cpp侧的对应函数为非泛型版本, 这里提供两种方案

      1. åå使用 泛型版本 `static bool Generic_GetDataTableRowFromName(const UDataTable* Table, FName RowName, void* OutRowPtr)`
      2. 借助DataTable的 Find 手写 泛型版本

   5. 新建 .cpp/.h (建议存放位置 Domain/InternalCall)

      ```cpp
      // Plugins/UnrealCSharp/Source/UnrealCSharp/Public/Domain/InternalCall/UDataTableFunctionLibrary.h
      #pragma once
      #include "mono/metadata/object.h"
      
      class UDataTableFunctionLibraryImplementation
      {
      public:
      	static bool UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(MonoObject* InTable, MonoString* InRowName, MonoObject** OutRow);
      };
      
      
      // Plugins/UnrealCSharp/Source/UnrealCSharp/Private/Domain/InternalCall/UDataTableFunctionLibrary.cpp
      #include "Domain/InternalCall/UDataTableFunctionLibrary.h"
      #include "Binding/Class/FBindingClassBuilder.h"
      #include "Bridge/FTypeBridge.h"
      #include "Environment/FCSharpEnvironment.h"
      #include "Kismet/DataTableFunctionLibrary.h"
      #include "Engine/UserDefinedStruct.h"
      #include "Macro/NamespaceMacro.h"
      
      struct UDataTableRegistry
      {
      	UDataTableRegistry()
      	{
      		FBindingClassBuilder(TEXT("UDataTableFunctionLibrary"), NAMESPACE_LIBRARY)
      			.Function("GetDataTableRowFromName",
      			          static_cast<void*>(
      				          UDataTableFunctionLibraryImplementation::UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation))
      			.Register();
      	}
      };
      
      static UDataTableRegistry UDataTableRegistry;
      
      
      bool UDataTableFunctionLibraryImplementation::UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
      	MonoObject* InTable,
      	MonoString* InRowName,
      	MonoObject** OutRow)
      {
      	const FName RowName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InRowName));
      	
      	const UDataTable* DataTable = FCSharpEnvironment::GetEnvironment()->GetObject<UDataTable>(InTable);
      	
      	const auto StructDescriptor = FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(DataTable->RowStruct.Get());
      	
      	*OutRow = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(StructDescriptor->GetMonoClass());
      
        // 方案1 借助泛型函数
      	UDataTableFunctionLibrary::Generic_GetDataTableRowFromName(DataTable, RowName, FCSharpEnvironment::GetEnvironment()->GetStruct(*OutRow));
      	
        // 方案2 手写Row查找, 并通过CopyScriptStruct 把参数值copy到构造好的结构体上
      	// const auto FindRowData = *DataTable->GetRowMap().Find(RowName);
      	//
      	// const auto OutRowData = FCSharpEnvironment::GetEnvironment()->GetStruct(*OutRow);
      	//
      	// DataTable->RowStruct->CopyScriptStruct(OutRowData, FindRowData);
        return true;
      }
      
      ```

   6. c#侧

      ```csharp
      // 定义接口
      using System;
      using System.Runtime.CompilerServices;
      using Script.Engine;
      
      namespace Script.Library
      {
          public static class UDataTableFunctionLibraryImplementation
          {
              [MethodImpl(MethodImplOptions.InternalCall)]
              public static extern Boolean UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation<T>(UDataTable Table, string RowName, out T OutRow);
          }
      }
      
      // 封装
      using System;
      using Script.Common;
      using Script.Library;
      using Script.CoreUObject;
      using System.Reflection;
      using System.Runtime.CompilerServices;
      using Script.Reflection.Struct;
      using Script.Engine;
      using IntPtr = Script.Common.IntPtr;
      using Script.Reflection.Function;
      
      namespace Script.Engine
      {
          [PathName("/Script/Engine.DataTableFunctionLibrary")]
          public partial class UDataTableFunctionLibrary : UBlueprintFunctionLibrary
          {
              public static Boolean GetDataTableRowFromName<T>(UDataTable Table, FName RowName, out T OutRow)
              {
                  return UDataTableFunctionLibraryImplementation.UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(Table, RowName.ToString(), out OutRow);
              }
          }
      }
      // 使用
      using Script.Engine;
      UDataTable datatable.... // 用于测试的 datatable some datatable
      FName rowName; // 需要查找的行名
      var Exported = UDataTableFunctionLibrary.GetDataTableRowFromName<MySTC>(datatable, rowName, out var findRow); // MySTC 为对应的结构体
      
      ```

   7. 解释

      1. 静态导出使用FBindingClassBuilder来构建, 并使用一个静态结构体来决定构建时间
      2. 静态导出对应函数名和函数指针, 由虚拟机管理
      3. c#侧的托管代码由虚拟机执行, 并在调用时通过 [MethodImpl(MethodImplOptions.InternalCall)] 属性查找到对应的函数指针

   8. 需要注意的地方

      1. c#侧的out参数对应cpp侧的双重指针 MonoObject**
      2. 静态导出的函数名 / 导出函数名 / [接口定义的命名空间|类名|静态函数名] 都一一对应
      3. c# 侧的接口签名 需要标记 `extern`
      4. 上例中 FBindingClassBuilder 构建了 UDataTableFunctionLibrary 类, 对应c#侧类名为 UDataTableFunctionLibraryImplementation
         1. 命名空间 由第二个参数决定, 这里是 NAMESPACE_LIBRARY, 对应c# 侧的 Script.Library
      5. 导出函数名 GetDataTableRowFromName 对应c# 侧函数名为 UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation

### Debug

#### PIE调试

1. 使用Rider Debug

   1. 添加Rider Debug配置

      ![Export-Cs](./attachments/US-Rider-Debug-Config.png)

   2. 先启动Rider的RemoteUE配置

   3. 再启动PIE

   4. 启动顺序可以调换(不过先启动PIE会阻塞)

#### 真机调试

## 作为开发者

### 目录结构

### 框架说明

## FAQ

## Misc

### Bench



## ChangeLog


## [![Repography logo](https://images.repography.com/logo.svg)](https://repography.com) / Recent activity [![Time period](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/recent-activity/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_badge.svg)](https://repography.com)
[![Timeline graph](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/recent-activity/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_timeline.svg)](https://github.com/KarryCharon/UnrealCSharp/commits)
[![Issue status graph](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/recent-activity/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_issues.svg)](https://github.com/KarryCharon/UnrealCSharp/issues)
[![Pull request status graph](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/recent-activity/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_prs.svg)](https://github.com/KarryCharon/UnrealCSharp/pulls)
[![Trending topics](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/recent-activity/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_words.svg)](https://github.com/KarryCharon/UnrealCSharp/commits)
[![Top contributors](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/recent-activity/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_users.svg)](https://github.com/KarryCharon/UnrealCSharp/graphs/contributors)
[![Activity map](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/recent-activity/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_map.svg)](https://github.com/KarryCharon/UnrealCSharp/commits)


## Contributor

<a href="https://github.com/crazytuzi/UnrealCSharp/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=crazytuzi/UnrealCSharp" />
</a>


## [![Repography logo](https://images.repography.com/logo.svg)](https://repography.com) / Top contributors
[![Top contributors](https://images.repography.com/36525470/KarryCharon/UnrealCSharp/top-contributors/gDz1UIxOjIQ_UJ8AECDB6FFVrmvm7nRN-2plBKJB--g/pATYBux3QUiKzgioC3B8KrlJiByLeToJh98w4ozku9M_table.svg)](https://github.com/KarryCharon/UnrealCSharp/graphs/contributors)


