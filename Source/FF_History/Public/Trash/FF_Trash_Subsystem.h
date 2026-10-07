#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "Trash/FF_Trash_Structs.h"
#include "Trash/Widgets/Widget_Trash.h"

#include "FF_Trash_Subsystem.generated.h"

UCLASS()
class FF_HISTORY_API UFF_Trash_Subsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TMap<FGuid, FTrashedActor> Trash_Actors;

	UPROPERTY()
	TMap<FGuid, UUserWidget*> Trash_Widgets;

	UPROPERTY()
	TMap<FGuid, UObject*> Trash_Objects;

	UPROPERTY()
	TArray<UTrash_Data*> UI_Data_Cache;

protected:

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Frozen Forest | History | Trash Subsystem")
	virtual bool SendActorToTrash(FGuid& TrashGuid, AActor* Target_Actor);

	UFUNCTION(BlueprintCallable, Category = "Frozen Forest | History | Trash Subsystem")
	virtual AActor* RestoreActorFromTrash(const FGuid& TrashGuid);

	UFUNCTION(BlueprintCallable, Category = "Frozen Forest | History | Trash Subsystem")
	virtual bool SendWidgetToTrash(FGuid& TrashGuid, UUserWidget* Target_Widget);

	UFUNCTION(BlueprintCallable, Category = "Frozen Forest | History | Trash Subsystem")
	virtual UUserWidget* RestoreWidgetFromTrash(const FGuid& TrashGuid);

	UPROPERTY(BlueprintReadWrite, Category = "Frozen Forest | History | Trash Subsystem")
	UWidget_Trash* UI_Trash = nullptr;

};