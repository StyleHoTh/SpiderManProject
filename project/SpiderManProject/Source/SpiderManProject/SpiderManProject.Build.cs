// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using Tools.DotNETCommon;
using System.IO;

public class SpiderManProject : ModuleRules
{
    private string ProjectRoot
    {
        get
        {
            return System.IO.Path.GetFullPath(
                System.IO.Path.Combine(ModuleDirectory, "../../")
            );
        }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ProjectRoot, "ThirdParty/")); }
    }

    private string ProtocBuildPath
    {
        get { return Path.GetFullPath(Path.Combine(ProjectRoot, "../common/excel_format/cmake/src/")); }
    }

    private string ExcelFormatLibPath
    {
        get { return Path.GetFullPath(Path.Combine(ProjectRoot, "../common/excel_format/bin/")); }
    }

    public SpiderManProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore", "NavigationSystem", "Foliage", "PhysXVehicles" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        {
            bEnableExceptions = true;
        }

        AddDefines(Target);

        LoadProtobuf(Target);

        LoadExcelFormat(Target);
    }

    public void AddDefines(ReadOnlyTargetRules Target)
    {
        //shipping启用log
        //PublicDefinitions.Add("USE_LOGGING_IN_SHIPPING");

        string PlatformType = "";

        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64) || Target.Platform == UnrealTargetPlatform.XboxOne)
        {
            PublicDefinitions.Add("_IS_WINDOWS_");

            PlatformType = "Windows";
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDefinitions.Add("_GLIBCXX_PERMIT_BACKWARD_HASH");
            PublicDefinitions.Add("stlport_static");
            PublicDefinitions.Add("_IS_UNIX_");
            PublicDefinitions.Add("_IS_ANDROID_");

            PublicDefinitions.Add("HAVE_PTHREAD=1");
            PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
            PublicDefinitions.Add("__STDC_WANT_SECURE_LIB__=0");
            PublicDefinitions.Add("_WIN32_WCE=0");

            PlatformType = "Android";
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicDefinitions.Add("_IS_UNIX_");
            PublicDefinitions.Add("_IS_IOS_");

            PlatformType = "IOS";
        }
        else if (Target.Platform == UnrealTargetPlatform.PS4)
        {
            PublicDefinitions.Add("_IS_UNIX_");

            PlatformType = "PS4";
        }

        System.Console.WriteLine("++++++++++++ AddDefines: " + PlatformType + "\r");
    }

    //链接protobuf
    public bool LoadProtobuf(ReadOnlyTargetRules Target)
    {
        //Library path
        string PlatformString = null;
        string IncludePath = Path.Combine(ThirdPartyPath, "Protobuf-3.5.1", "Include");

        switch (Target.Platform)
        {
            case UnrealTargetPlatform.Win64:
                {
                    PlatformString = ".lib";
                    break;
                }
            case UnrealTargetPlatform.Android:
                {
                    PlatformString = "-ndk.a";
                    break;
                }
        }

        if (null != PlatformString)
        {
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Protobuf-3.5.1", "Library", "libprotobuf-lite" + PlatformString);
            PublicAdditionalLibraries.Add(LibrariesPath);

            System.Console.WriteLine("++++++++++++ Set Protobuf Libraries: " + LibrariesPath + "\r");
        }

        //Include path
        if (null != IncludePath)
        {
            PublicIncludePaths.Add(IncludePath);
        }

        System.Console.WriteLine("++++++++++++ Set Protobuf Includes: " + IncludePath + "\r");

        return true;
    }

    //链接表格对象
    public bool LoadExcelFormat(ReadOnlyTargetRules Target)
    {
        PublicIncludePaths.Add(ProtocBuildPath);

        string LibrariesPath = null;

        switch (Target.Platform)
        {
            case UnrealTargetPlatform.Win64:
                {
                    //第三方静态库使用的都是release x64，所以这里不考虑win32的情况
                    LibrariesPath = Path.Combine(ExcelFormatLibPath, "libexcelformat.lib");
                    break;
                }
            case UnrealTargetPlatform.Android:
                {
                    LibrariesPath = Path.Combine(ThirdPartyPath, "Protobuf-3.5.1", "Library", "libexcelformat-ndk.a");
                    break;
                }
            case UnrealTargetPlatform.IOS:
                {
                    LibrariesPath = Path.Combine(ThirdPartyPath, "Protobuf-3.5.1", "Library", "libexcelformat.arm64.a");
                    break;
                }
            case UnrealTargetPlatform.Mac:
                {
                    LibrariesPath = Path.Combine(ThirdPartyPath, "Protobuf-3.5.1", "Library", "libexcelformat.x86_64.a");
                    break;
                }
        }

        if (null != LibrariesPath)
        {
            PublicAdditionalLibraries.Add(LibrariesPath);
        }

        System.Console.WriteLine("++++++++++++ Set ProtocBuild includes path: " + ProtocBuildPath + "\r");
        System.Console.WriteLine("++++++++++++ Set CustomMsg Libraries: " + LibrariesPath + "\r");
        return true;
    }

    public bool LinkLibStl(ReadOnlyTargetRules Target)
    {
        string LibrariesPath = null;
        switch (Target.Platform)
        {
            case UnrealTargetPlatform.Android:
                {
                    LibrariesPath = Path.Combine(ThirdPartyPath, "stl_ndk_lib", "libstlport_static.a");
                    break;
                }
        }

        if (null != LibrariesPath)
        {
            PublicAdditionalLibraries.Add(LibrariesPath);
        }

        return true;
    }
}
