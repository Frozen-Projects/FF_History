namespace UnrealBuildTool.Rules
{
    using System.IO;

    public class lmdb : ModuleRules
    {
        public lmdb(ReadOnlyTargetRules Target) : base(Target)
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
