#include "Trash/Widgets/Widget_Trash.h"

void UWidget_Trash::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UWidget_Trash::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_Trash::NativeDestruct()
{
	Super::NativeDestruct();
}

void UWidget_Trash::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

TSharedRef<SWidget> UWidget_Trash::RebuildWidget()
{
	return Super::RebuildWidget();
}

ETrashItemTypes UWidget_Trash::GetEnumValueByName(const FString& InName)
{
	UEnum* EnumPtr = StaticEnum<ETrashItemTypes>();

	if (!EnumPtr)
	{
		return ETrashItemTypes::None;
	}

	const int64 EnumValue = EnumPtr->GetValueByName(FName(*InName));

	if (EnumValue == INDEX_NONE)
	{
		return ETrashItemTypes::None;
	}

	return static_cast<ETrashItemTypes>(EnumValue);
}

FString UWidget_Trash::GetEnumDisplayName(ETrashItemTypes In_Enum)
{
	const UEnum* EnumPtr = StaticEnum<ETrashItemTypes>();

	if (!EnumPtr)
	{
		return FString();
	}

	return EnumPtr->GetNameStringByValue((int64)In_Enum);
}

bool UWidget_Trash::AddItemToUi(UTrash_Data* TrashData)
{
	if (!IsValid(TrashData))
	{
		return false;
	}

	if (!IsValid(this->Hierarchy))
	{
		return false;
	}

	this->Hierarchy->AddItem(TrashData);
	this->Hierarchy->RequestRefresh();
	return true;
}

bool UWidget_Trash::RemoveItemFromUi(UTrash_Data* TrashData)
{
	if (!IsValid(TrashData))
	{
		return false;
	}

	if (!IsValid(this->Hierarchy))
	{
		return false;
	}

	this->Hierarchy->RemoveItem(TrashData);
	this->Hierarchy->RequestRefresh();
	return true;
}