namespace UnrealBuildTool.Rules
{
    using System.IO;

    public class leveldb : ModuleRules
    {
        public leveldb(ReadOnlyTargetRules Target) : base(Target)
        {
            Type = ModuleType.External;
            UndefinedIdentifierWarningLevel = WarningLevel.Off;
            bEnableExceptions = true;

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                bUseRTTI = true;

                PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Win64", "include"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "lib", "leveldb.lib"));
            }

            if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Win64", "include"));
                PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "lib", "leveldb.a"));
            }
        }
    }
}
