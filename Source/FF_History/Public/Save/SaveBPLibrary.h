// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Save/Save_Includes.h"

#include "SaveBPLibrary.generated.h"

USTRUCT(BlueprintType)
struct FF_HISTORY_API FVariableContainer
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	UObject* Parent = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FName Name;

	UPROPERTY(BlueprintReadWrite)
	FString Serialized;

	UPROPERTY(BlueprintReadWrite)
	FString VariableType;

	UPROPERTY(BlueprintReadWrite)
	bool bIsNative = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsRooted = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEditorOnly = false;

	UPROPERTY(BlueprintReadWrite)
	FDateTime RecordTime;

	bool operator == (const FVariableContainer& Other) const
	{
		return Parent == Other.Parent && Name == Other.Name && Serialized == Other.Serialized && VariableType == Other.VariableType && bIsNative == Other.bIsNative && bIsRooted == Other.bIsRooted && bIsEditorOnly == Other.bIsEditorOnly && RecordTime == Other.RecordTime;
	}

	bool operator != (const FVariableContainer& Other) const
	{
		return !(*this == Other);
	}

};

FORCEINLINE uint32 GetTypeHash(const FVariableContainer& Key)
{
	uint32 Hash_Parent = GetTypeHash(Key.Parent);
	uint32 Hash_Name = GetTypeHash(Key.Name);
	uint32 Hash_Serialized = GetTypeHash(Key.Serialized);
	uint32 Hash_VariableType = GetTypeHash(Key.VariableType);
	uint32 Hash_bIsNative = GetTypeHash(Key.bIsNative);
	uint32 Hash_bIsRooted = GetTypeHash(Key.bIsRooted);
	uint32 Hash_bIsEditorOnly = GetTypeHash(Key.bIsEditorOnly);
	uint32 Hash_RecordTime = GetTypeHash(Key.RecordTime);

	uint32 GenericHash;
	FMemory::Memset(&GenericHash, 0, sizeof(uint32));
	GenericHash = HashCombine(GenericHash, Hash_Parent);
	GenericHash = HashCombine(GenericHash, Hash_Name);
	GenericHash = HashCombine(GenericHash, Hash_Serialized);
	GenericHash = HashCombine(GenericHash, Hash_VariableType);
	GenericHash = HashCombine(GenericHash, Hash_bIsNative);
	GenericHash = HashCombine(GenericHash, Hash_bIsRooted);
	GenericHash = HashCombine(GenericHash, Hash_bIsEditorOnly);
	GenericHash = HashCombine(GenericHash, Hash_RecordTime);

	return GenericHash;
}

USTRUCT(BlueprintType)
struct FF_HISTORY_API FVariablePool
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	TArray<FVariableContainer> Containers;

	bool operator == (const FVariablePool& Other) const
	{
		return Containers == Other.Containers;
	}

	bool operator != (const FVariablePool& Other) const
	{
		return !(*this == Other);
	}

};

FORCEINLINE uint32 GetTypeHash(const FVariablePool& Key)
{
	uint32 Hash_Containers = GetTypeHash(Key.Containers);

	uint32 GenericHash;
	FMemory::Memset(&GenericHash, 0, sizeof(uint32));

	return GenericHash;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateSaveToFile, bool, bIsSuccessfull, FString, ErrorCode);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateSaveToMemory, bool, bIsSuccessfull, FString, ErrorCode, const TArray<uint8>&, Out_Buffer);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateLoad, bool, bIsSuccessfull, FString, ErrorCode, USaveGame*, Instance_Load);

UCLASS()
class UFF_SaveBPLibrary : public UBlueprintFunctionLibrary
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
	static void LoadGameFromFile(FDelegateLoad DelegateLoad, FString In_Path, TSubclassOf<USaveGame> SaveGameClass);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Game From Location", Keywords = "history, serialize, property, variable, load, game, file"), Category = "Frozen Forest|History|Save")
	static void LoadGameFromMemory(FDelegateLoad DelegateLoad, TArray<uint8> In_Buffer, TSubclassOf<USaveGame> SaveGameClass);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save Widget To File", Keywords = "history, serialize, property, variable, save, widget, file"), Category = "Frozen Forest|History|Save")
	static void SaveWidgetToFile(FDelegateSaveToFile DelegateSave, FString In_Path, UUserWidget* In_Widget);

};
