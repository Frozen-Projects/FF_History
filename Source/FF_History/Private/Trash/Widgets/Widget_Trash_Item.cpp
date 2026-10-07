#include "Trash/Widgets/Widget_Trash_Item.h"
#include "Trash/Widgets/Widget_Trash.h"

void UWidget_Trash_Item::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UWidget_Trash_Item::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_Trash_Item::NativeDestruct()
{
	Super::NativeDestruct();
}

TSharedRef<SWidget> UWidget_Trash_Item::RebuildWidget()
{
	return Super::RebuildWidget();
}

void UWidget_Trash_Item::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UTrash_Data* Trash_Data = Cast<UTrash_Data>(ListItemObject);

	if (!IsValid(Trash_Data))
	{
		return;
	}

	this->ID = Trash_Data->ID;
	this->Title->SetText(FText::FromString(Trash_Data->Name));
	this->ItemType = Trash_Data->ItemType;
}

void UWidget_Trash_Item::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);
}