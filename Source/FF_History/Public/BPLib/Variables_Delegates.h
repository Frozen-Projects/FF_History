#pragma once
#include "CoreMinimal.h"
#include "Variables_Delegates.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateSaveToFile, bool, bIsSuccessfull, FString, ErrorCode);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateSaveToMemory, bool, bIsSuccessfull, FString, ErrorCode, const TArray<uint8>&, Out_Buffer);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateLoadSave, bool, bIsSuccessfull, FString, ErrorCode, USaveGame*, Out_Save);