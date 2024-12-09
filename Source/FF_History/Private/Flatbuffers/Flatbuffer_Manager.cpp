// Fill out your copyright notice in the Description page of Project Settings.

#include "Flatbuffers/Flatbuffer_Manager.h"

// Sets default values
AFlatbuffer_Manager::AFlatbuffer_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned.
void AFlatbuffer_Manager::BeginPlay()
{
	Super::BeginPlay();
}

// Called when the game end or when destroyed.
void AFlatbuffer_Manager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame.
void AFlatbuffer_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}