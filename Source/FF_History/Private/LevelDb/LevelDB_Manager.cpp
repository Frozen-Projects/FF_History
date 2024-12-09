// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelDB/LevelDB_Manager.h"

// Sets default values
ALevelDB_Manager::ALevelDB_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned.
void ALevelDB_Manager::BeginPlay()
{
	Super::BeginPlay();
}

// Called when the game end or when destroyed.
void ALevelDB_Manager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame.
void ALevelDB_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ALevelDB_Manager::LevelDB_Open_Db(FString DB_Path)
{
	this->DB_Options.create_if_missing = true;
	leveldb::Status DB_Status = leveldb::DB::Open(this->DB_Options, std::string(TCHAR_TO_UTF8(*DB_Path)), &this->Database);

	return DB_Status.ok();
}