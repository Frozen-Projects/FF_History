// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LevelDB/LevelDB_Includes.h"

#include "LevelDB_Manager.generated.h"

UCLASS()
class FF_HISTORY_API ALevelDB_Manager : public AActor
{
	GENERATED_BODY()
	
protected:

	leveldb::DB* Database = nullptr;
	leveldb::Options DB_Options;

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called when the game end or when destroyed.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	// Sets default values for this actor's properties.
	ALevelDB_Manager();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual bool LevelDB_Open_Db(FString DB_Path);

};
