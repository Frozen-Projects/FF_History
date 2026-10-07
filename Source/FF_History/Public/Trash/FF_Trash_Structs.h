#pragma once

#include "CoreMinimal.h"
#include "FF_Trash_Structs.generated.h"

USTRUCT(BlueprintType)
struct FF_HISTORY_API FTrashedActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	AActor* Actor = nullptr;

	UPROPERTY(BlueprintReadOnly)
	bool bWasTickEnabled = false;

	UPROPERTY(BlueprintReadOnly)
	bool bWasCollisionEnabled = false;

	UPROPERTY(BlueprintReadOnly)
	TMap<UActorComponent*, bool> ComponentTickStates;

	UPROPERTY(BlueprintReadOnly)
	TMap<UActorComponent*, bool> ComponentActiveStates;

	UPROPERTY(BlueprintReadOnly)
	TMap<UPrimitiveComponent*, bool> ComponentPhysicsStates;

	UPROPERTY(BlueprintReadOnly)
	TMap<UPrimitiveComponent*, bool> ComponentNavigationStates;

	bool operator == (const FTrashedActor& Other) const
	{
		return Actor == Other.Actor && 
				bWasTickEnabled == Other.bWasTickEnabled && 
				bWasCollisionEnabled == Other.bWasCollisionEnabled && 
				ComponentTickStates.OrderIndependentCompareEqual(Other.ComponentTickStates) && 
				ComponentActiveStates.OrderIndependentCompareEqual(Other.ComponentActiveStates) && 
				ComponentPhysicsStates.OrderIndependentCompareEqual(Other.ComponentPhysicsStates) && 
				ComponentNavigationStates.OrderIndependentCompareEqual(Other.ComponentNavigationStates);
	}

	bool operator != (const FTrashedActor& Other) const
	{
		return !(*this == Other);
	}
};

FORCEINLINE uint32 GetTypeHash(const FTrashedActor& Key)
{
	uint32 Hash_Actor = GetTypeHash(Key.Actor);
	uint32 Hash_bWasTickEnabled = GetTypeHash(Key.bWasTickEnabled);
	uint32 Hash_bWasCollisionEnabled = GetTypeHash(Key.bWasCollisionEnabled);

	uint32 GenericHash;
	FMemory::Memset(&GenericHash, 0, sizeof(uint32));
	GenericHash = HashCombine(GenericHash, Hash_Actor);
	GenericHash = HashCombine(GenericHash, Hash_bWasTickEnabled);
	GenericHash = HashCombine(GenericHash, Hash_bWasCollisionEnabled);

	return GenericHash;
}

USTRUCT(BlueprintType)
struct FF_HISTORY_API FTrashedObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	UObject* Object = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UObject* Parent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	bool bWasVisible = false;

	UPROPERTY(BlueprintReadOnly)
	bool bWasTickEnabled = false;

	UPROPERTY(BlueprintReadOnly)
	bool bWasActive = false;

	UPROPERTY(BlueprintReadOnly)
	bool bWasPhysicsEnabled = false;

	UPROPERTY(BlueprintReadOnly)
	bool bWasNavigationEnabled = false;

	UPROPERTY(BlueprintReadOnly)
	bool bWasCollisionEnabled = false;

	bool operator == (const FTrashedObject& Other) const
	{
		return Object == Other.Object &&
			   Parent == Other.Parent &&
			   bWasVisible == Other.bWasVisible &&
			   bWasTickEnabled == Other.bWasTickEnabled &&
			   bWasActive == Other.bWasActive &&
			   bWasPhysicsEnabled == Other.bWasPhysicsEnabled &&
			   bWasNavigationEnabled == Other.bWasNavigationEnabled &&
			   bWasCollisionEnabled == Other.bWasCollisionEnabled;
	}

	bool operator != (const FTrashedObject& Other) const
	{
		return !(*this == Other);
	}
};

FORCEINLINE uint32 GetTypeHash(const FTrashedObject& Key)
{
	uint32 Hash_Object = GetTypeHash(Key.Object);
	uint32 Hash_Parent = GetTypeHash(Key.Parent);
	uint32 Hash_bWasVisible = GetTypeHash(Key.bWasVisible);
	uint32 Hash_bWasTickEnabled = GetTypeHash(Key.bWasTickEnabled);
	uint32 Hash_bWasActive = GetTypeHash(Key.bWasActive);
	uint32 Hash_bWasPhysicsEnabled = GetTypeHash(Key.bWasPhysicsEnabled);
	uint32 Hash_bWasNavigationEnabled = GetTypeHash(Key.bWasNavigationEnabled);
	uint32 Hash_bWasCollisionEnabled = GetTypeHash(Key.bWasCollisionEnabled);

	uint32 GenericHash;
	FMemory::Memset(&GenericHash, 0, sizeof(uint32));
	GenericHash = HashCombine(GenericHash, Hash_Object);
	GenericHash = HashCombine(GenericHash, Hash_Parent);
	GenericHash = HashCombine(GenericHash, Hash_bWasVisible);
	GenericHash = HashCombine(GenericHash, Hash_bWasTickEnabled);
	GenericHash = HashCombine(GenericHash, Hash_bWasActive);
	GenericHash = HashCombine(GenericHash, Hash_bWasPhysicsEnabled);
	GenericHash = HashCombine(GenericHash, Hash_bWasNavigationEnabled);
	GenericHash = HashCombine(GenericHash, Hash_bWasCollisionEnabled);

	return GenericHash;
}