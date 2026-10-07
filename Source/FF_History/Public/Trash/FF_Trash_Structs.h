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
};

USTRUCT(BlueprintType)
struct FF_HISTORY_API FTrashedWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* Widget = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* Parent = nullptr;

};