// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "FF_History_Tools.h"

#include "FF_History_BP_Library.generated.h"

UCLASS()
class UFF_History_BP_Library : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Variable by Name", Keywords = "history, serialize, property, variable, name, get"), Category = "Frozen Forest|History|Save")
	static FF_HISTORY_API bool GetVariableByName(FVariableContainer& Out_Container, UObject* In_Parent, FName In_Name);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get All Variables", Keywords = "history, serialize, property, variable, name, get, all"), Category = "Frozen Forest|History|Save")
	static FF_HISTORY_API bool GetAllVariables(FVariablePool& Out_Containers, UObject* In_Parent, bool bIncludeEditor = false, bool bIncludeNative = false, bool bIncludeRoot = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Variable", Keywords = "history, serialize, property, variable, name, set"), Category = "Frozen Forest|History|Save")
	static FF_HISTORY_API bool SetVariable(UObject* TargetParent, FName TargetVariable, FString NewData);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Game to File", Keywords = "history, serialize, property, variable, save, game, file"), Category = "Frozen Forest|History|Save")
	static FF_HISTORY_API void SaveGameToFile(FDelegateSaveToFile DelegateSave, USaveGame* Instance_Save, FString In_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Game to Memory", Keywords = "history, serialize, property, variable, save, game, memory, buffer"), Category = "Frozen Forest|History|Save")
	static FF_HISTORY_API void SaveGameToMemory(FDelegateSaveToMemory DelegateSave, USaveGame* Instance_Save);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Game From File", Keywords = "history, serialize, property, variable, load, game, file"), Category = "Frozen Forest|History|Save")
	static FF_HISTORY_API void LoadGameFromFile(FDelegateLoadSave DelegateLoad, FString In_Path, TSubclassOf<USaveGame> SaveGameClass);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Game From Location", Keywords = "history, serialize, property, variable, load, game, file"), Category = "Frozen Forest|History|Save")
	static FF_HISTORY_API void LoadGameFromMemory(FDelegateLoadSave DelegateLoad, TArray<uint8> In_Buffer, TSubclassOf<USaveGame> SaveGameClass);

};
