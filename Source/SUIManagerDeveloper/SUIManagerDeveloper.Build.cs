using UnrealBuildTool;

public class SUIManagerDeveloper : ModuleRules
{
    public SUIManagerDeveloper(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "SUIManager"
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