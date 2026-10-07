#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "Trash/Widgets/Widget_Trash_Includes.h"
#include "Trash/Widgets/Widget_Trash_Data.h"

#include "Widget_Trash_Item.generated.h"

// Forward Declarations.
class UWidget_Trash;

UCLASS(Abstract, meta = (DisableNativeTick))
class FF_HISTORY_API UWidget_Trash_Item : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:

	UFUNCTION()
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	virtual void NativeOnItemExpansionChanged(bool bIsExpanded) override;

public:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Title = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	FGuid ID;

	UPROPERTY(BlueprintReadWrite)
	ETrashItemTypes ItemType = ETrashItemTypes::Actor;

};