using UnrealBuildTool;

public class sExtraUIManagerDeveloper : ModuleRules
{
    public sExtraUIManagerDeveloper(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "sExtraUIManager"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
            }
        );
        
        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "UnrealEd",
                    "Kismet",
                    "AnimGraph",
                    "BlueprintGraph",
                    "PropertyEditor",
                    "GraphEditor",
                    "ApplicationCore",
                    "KismetCompiler"
                }
            );

            if (Target.Version.MajorVersion >= 5)
            {
                PrivateDependencyModuleNames.Add("EditorFramework");
            }
        }
    }
}