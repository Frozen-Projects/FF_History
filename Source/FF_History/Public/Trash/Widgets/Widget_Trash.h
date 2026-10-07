#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "Trash/Widgets/Widget_Trash_Item.h"

#include "Widget_Trash.generated.h"

UCLASS()
class FF_HISTORY_API UWidget_Trash : public UUserWidget
{
	GENERATED_BODY()

private:

	static ETrashItemTypes GetEnumValueByName(const FString& InName);

	UFUNCTION()
	static FString GetEnumDisplayName(ETrashItemTypes In_Enum);

public:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual TSharedRef<SWidget> RebuildWidget() override;

	UFUNCTION()
	virtual bool AddItemToUi(UTrash_Data* TrashData);

	UFUNCTION()
	virtual bool RemoveItemFromUi(UTrash_Data* TrashData);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTreeView* Hierarchy = nullptr;
	
};
