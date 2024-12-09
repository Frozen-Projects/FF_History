namespace UnrealBuildTool.Rules
{
    using System.IO;

    public class cista : ModuleRules
    {
        public cista(ReadOnlyTargetRules Target) : base(Target)
        {
    		Type = ModuleType.External;
            UndefinedIdentifierWarningLevel = WarningLevel.Off;
            bEnableExceptions = true;

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                bUseRTTI = true;   
            }

            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
        }
    }
}
