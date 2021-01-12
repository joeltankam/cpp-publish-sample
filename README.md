# Sample project

This repository is a sample relatead to [msbuild#5968](https://github.com/dotnet/msbuild/issues/5968)

## Description

As decribed in the issue mentioned above, we have a C# project (`ProjectA`), using SDK project file format and targeting .NET Framework 4.7.1. This project depends on a v142 C++/CLI project (`ProjectB`) which depends on v142 C++ dynamic library project (`ProjectC`): 

> ProjectA [net471] <- ProjectB [v142 C++/CLI] <- ProjectC [v142 C++] (where A <- B means that A depends on B).

We are trying to publish the C# entry project, `ProjectA`, using Publish target from MSBuild (`msbuild /t:Publish`)

## Behavior

We expect the result of the publication of `ProjectA` to contain `ProjectA.exe`, `ProjectB.dll` and `ProjectC.dll`, but it doesn't contain de latter.

```cmd
msbuild /t:Build /Restore /p:Platform=x86 ProjectA/ProjectA.csproj
msbuild /t:Publish /p:Platform=x86 ProjectA\ProjectA.csproj
ls ProjectA\bin\x86\Debug\net471\publish\
```

Returns 

```
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----         1/12/2021  11:47 AM           4608 ProjectA.exe
-a----         1/12/2021  11:47 AM            176 ProjectA.exe.config
-a----         1/12/2021  11:47 AM           1392 ProjectA.pdb
-a----         1/12/2021  11:47 AM         106496 ProjectB.dll
-a----         1/12/2021  11:47 AM         798720 ProjectB.pdb
```

Resulting in execution error :

```cmd
.\ProjectA\bin\x86\Debug\net471\publish\ProjectA.exe

Unhandled Exception: System.IO.FileNotFoundException: Could not load file or assembly 'ProjectB.dll' or one of its dependencies. The specified module could not be found.
   at ProjectA.Helper.Main()
```