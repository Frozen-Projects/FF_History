#pragma once

#include "CoreMinimal.h"

#include "Trash/Widgets/Widget_Trash_Enums.h"

#include "Widget_Trash_Data.generated.h"

UCLASS(BlueprintType)
class FF_HISTORY_API UTrash_Data : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FGuid ID;

	UPROPERTY(BlueprintReadWrite)
	ETrashItemTypes ItemType = ETrashItemTypes::Actor;

};