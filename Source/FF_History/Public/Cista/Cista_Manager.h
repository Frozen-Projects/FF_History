// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Cista/Cista_Includes.h"

#include "Cista_Manager.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateCistaSerialize, bool, bIsSuccessfull, FString, Out_Code);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateCistaBytes, bool, bIsSuccessfull, FString, Out_Code, const TArray<uint8>&, Out_Bytes);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDelegateCistaString, bool, bIsSuccessfull, FString, Out_Code, FString, Out_String);

UCLASS()
class FF_HISTORY_API ACista_Manager : public AActor
{
	GENERATED_BODY()

protected:

	cista::buf<cista::byte_buf> Buffer;

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called when the game end or when destroyed.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	// Sets default values for this actor's properties.
	ACista_Manager();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cista - Export", Keywords = "cista, buffer, export"), Category = "FF_Cista")
	virtual void Cista_Export(FDelegateCistaSerialize DelegateCista, FString In_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cista - Serialize String", Keywords = "cista, serialize, string"), Category = "FF_Cista")
	virtual void Cista_Serialize_String(FDelegateCistaSerialize DelegateCista, FString In_String);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cista - Serialize Bytes", Keywords = "cista, serialize, byte, bytes"), Category = "FF_Cista")
	virtual void Cista_Serialize_Bytes(FDelegateCistaSerialize DelegateCista, TArray<uint8> In_Bytes);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cista - Deserialize String", Keywords = "cista, deserialize, byte, string"), Category = "FF_Cista")
	virtual void Cista_Deserialize_String(FDelegateCistaString DelegateCista, FString In_Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cista - Deserialize Bytes", Keywords = "cista, deserialize, byte, bytes"), Category = "FF_Cista")
	virtual void Cista_Deserialize_Bytes(FDelegateCistaBytes DelegateCista, FString In_Path);

};
