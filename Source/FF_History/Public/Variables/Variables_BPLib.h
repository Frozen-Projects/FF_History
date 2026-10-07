#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Variables/Variables_Includes.h"
#include "Variables/Variables_Structs.h"
#include "Variables/Variables_Delegates.h"

#include "Variables_BPLib.generated.h"

UCLASS()
class FF_HISTORY_API UFF_History_BP_Library : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Variable by Name", Keywords = "history, serialize, property, variable, name, get"), Category = "Frozen Forest|History|Save")
	static bool GetVariableByName(FVariableContainer& Out_Container, UObject* In_Parent, FName In_Name);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get All Variables", Keywords = "history, serialize, property, variable, name, get, all"), Category = "Frozen Forest|History|Save")
	static bool GetAllVariables(FVariablePool& Out_Containers, UObject* In_Parent, bool bIncludeEditor = false, bool bIncludeNative = false, bool bIncludeRoot = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Variable", Keywords = "history, serialize, property, variable, name, set"), Category = "Frozen Forest|History|Save")
	static bool SetVariable(UObject* TargetParent, FName TargetVariable, FString NewData);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Game to File", Keywords = "history, serialize, property, variable, save, game, file"), Category = "Frozen Forest|History|Save")
	static void SaveGameToFile(FDelegateSaveToFile DelegateSave, USaveGame* Instance_Save, FString In_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Game to Memory", Keywords = "history, serialize, property, variable, save, game, memory, buffer"), Category = "Frozen Forest|History|Save")
	static void SaveGameToMemory(FDelegateSaveToMemory DelegateSave, USaveGame* Instance_Save);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Game From File", Keywords = "history, serialize, property, variable, load, game, file"), Category = "Frozen Forest|History|Save")
	static void LoadGameFromFile(FDelegateLoadSave DelegateLoad, FString In_Path, TSubclassOf<USaveGame> SaveGameClass);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Game From Location", Keywords = "history, serialize, property, variable, load, game, file"), Category = "Frozen Forest|History|Save")
	static void LoadGameFromMemory(FDelegateLoadSave DelegateLoad, TArray<uint8> In_Buffer, TSubclassOf<USaveGame> SaveGameClass);

};
