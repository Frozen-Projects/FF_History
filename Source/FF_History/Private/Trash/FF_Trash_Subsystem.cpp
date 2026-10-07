#include "Trash/FF_Trash_Subsystem.h"

void UFF_Trash_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFF_Trash_Subsystem::Deinitialize()
{
	this->Trash_Actors.Empty();
	this->Trash_Widgets.Empty();
	this->Trash_Objects.Empty();

	Super::Deinitialize();
}

bool UFF_Trash_Subsystem::SendActorToTrash(FGuid& TrashGuid, AActor* Target_Actor)
{
	if (!IsValid(Target_Actor))
	{
		return false;
	}

	FTrashedActor TrashedActor;
	TrashedActor.Actor = Target_Actor;
	TrashedActor.bWasTickEnabled = Target_Actor->IsActorTickEnabled();
	TrashedActor.bWasCollisionEnabled = Target_Actor->GetActorEnableCollision();

	Target_Actor->SetActorHiddenInGame(true);
	Target_Actor->SetActorTickEnabled(false);
	Target_Actor->SetActorEnableCollision(false);

	TArray<UActorComponent*> Actor_Components = Target_Actor->GetComponents().Array();

	for (UActorComponent* Component : Actor_Components)
	{
		if (IsValid(Component))
		{
			TrashedActor.ComponentTickStates.Add(Component, Component->IsComponentTickEnabled());
			TrashedActor.ComponentActiveStates.Add(Component, Component->IsActive());

			Component->SetComponentTickEnabled(false);
			Component->SetActive(false);

			if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
			{
				TrashedActor.ComponentPhysicsStates.Add(PrimComp, PrimComp->IsSimulatingPhysics());
				TrashedActor.ComponentNavigationStates.Add(PrimComp, PrimComp->CanEverAffectNavigation());

				PrimComp->SetSimulatePhysics(false);
				PrimComp->SetCanEverAffectNavigation(false);
			}
		}
	}

	FGuid NewTrashGuid = FGuid::NewGuid();
	this->Trash_Actors.Add(NewTrashGuid, TrashedActor);

	if (IsValid(this->UI_Trash))
	{
		UTrash_Data* TrashData = NewObject<UTrash_Data>();
		TrashData->Name = TrashedActor.Actor->GetName();
		TrashData->ID = NewTrashGuid;
		TrashData->ItemType = ETrashItemTypes::Actor;

		this->UI_Data_Cache.Add(TrashData);
		this->UI_Trash->AddItemToUi(TrashData);
	}

	TrashGuid = NewTrashGuid;
	return true;
}

AActor* UFF_Trash_Subsystem::RestoreActorFromTrash(const FGuid& TrashGuid)
{
	if (!this->Trash_Actors.Contains(TrashGuid))
	{
		return nullptr;
	}

	FTrashedActor* ActorContainer = this->Trash_Actors.Find(TrashGuid);

	if (!ActorContainer)
	{
		const FString ErrorString = FString::Printf(TEXT("%s - ActorContainer is null for TrashGuid: %s"), TEXT(__FUNCTION__), *TrashGuid.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ErrorString);
		return nullptr;
	}

	AActor* Actor = ActorContainer->Actor;

	if (!IsValid(Actor))
	{
		const FString ErrorString = FString::Printf(TEXT("%s - Actor is no longer valid for TrashGuid: %s"), TEXT(__FUNCTION__), *TrashGuid.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ErrorString);
		return nullptr;
	}

	Actor->SetActorHiddenInGame(false);
	Actor->SetActorTickEnabled(ActorContainer->bWasTickEnabled);
	Actor->SetActorEnableCollision(ActorContainer->bWasCollisionEnabled);

	TArray<UActorComponent*> Actor_Components = Actor->GetComponents().Array();

	for (UActorComponent* Component : Actor_Components)
	{
		if (!IsValid(Component))
		{
			continue;
		}

		Component->SetComponentTickEnabled(*ActorContainer->ComponentTickStates.Find(Component));
		Component->SetActive(*ActorContainer->ComponentActiveStates.Find(Component));

		if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
		{
			const bool bWasSimulatingPhysics = *ActorContainer->ComponentPhysicsStates.Find(PrimComp);
			PrimComp->SetSimulatePhysics(bWasSimulatingPhysics);

			const bool bWasAffectingNavigation = *ActorContainer->ComponentNavigationStates.Find(PrimComp);
			PrimComp->SetCanEverAffectNavigation(bWasAffectingNavigation);
		}
	}

	UTrash_Data* TrashDataToRemove = nullptr;
	for (UTrash_Data* TrashData : this->UI_Data_Cache)
	{
		if (IsValid(TrashData) && TrashData->ID == TrashGuid)
		{
			TrashDataToRemove = TrashData;
			break;
		}
	}

	this->Trash_Actors.Remove(TrashGuid);
	this->UI_Trash->RemoveItemFromUi(TrashDataToRemove);
	this->UI_Data_Cache.Remove(TrashDataToRemove);

	return Actor;
}
