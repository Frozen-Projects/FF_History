#pragma once

#include "CoreMinimal.h"
#include "Widget_Trash_Enums.generated.h"

UENUM(BlueprintType)
enum class ETrashItemTypes : uint8
{
	None = 0		UMETA(DisplayName = "None"),
	Actor = 1		UMETA(DisplayName = "Actor"),
	Widget = 2		UMETA(DisplayName = "Widget"),
	Object = 3		UMETA(DisplayName = "Object"),
};
ENUM_CLASS_FLAGS(ETrashItemTypes)