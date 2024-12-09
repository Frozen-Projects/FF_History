// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SQLite/SQLite_Includes.h"

#include "SQLite_Manager.generated.h"

USTRUCT(BlueprintType)
struct FF_HISTORY_API FSQLiteRows
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Editanywhere)
	TArray<FString> ColumnValues;

};

UCLASS()
class FF_HISTORY_API ASQLite_Manager : public AActor
{
	GENERATED_BODY()
	
protected:

	FSQLiteDatabase* SQLiteDB = nullptr;

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called when the game end or when destroyed.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	// Sets default values for this actor's properties.
	ASQLite_Manager();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Open", ToolTip = "Description", Keywords = "sqlite, open"), Category = "SQLite")
	virtual bool SQLiteOpen(const FString DB_Path, ESQLiteOpenType OpenType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Close", ToolTip = "Description", Keywords = "sqlite, close"), Category = "SQLite")
	virtual void SQLiteClose();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Get Columns Names", ToolTip = "Description", Keywords = "sqlite, column, names, get"), Category = "SQLite")
	virtual bool SQLiteGetColumnsNames(const FString TableName, TArray<FString>& OutColumnsNames);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Get Single Row Value", ToolTip = "Description", Keywords = "sqlite, column, values, get"), Category = "SQLite")
	virtual bool SQLiteGetSingleRowValue(const FString TableName, const FString IDColumn, const FString IDIndex, const FString ColumnName, FString& ColumnValue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Get All Row Values", ToolTip = "Sample: select * from repository where id > 0", Keywords = "sqlite, column, values, get"), Category = "SQLite")
	virtual bool SQLiteGetAllRowValues(const FString Query, const FString ColumnName, TArray<FString>& ColumnValues);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Get Table Contents", ToolTip = "Description.", Keywords = "sqlite, column, values, get"), Category = "SQLite")
	virtual bool SQLiteGetAllTableContents(const FString TableName, const FString QueryCondition, TMap<FString, FSQLiteRows>& TableContents);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Write Value", ToolTip = "Description.", Keywords = "sqlite, write, value"), Category = "SQLite")
	virtual bool SQLiteWriteValue(const FString TableName, const FString ColumnName, const FString InValue);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Create Column", ToolTip = "Description.", Keywords = "sqlite, create, column"), Category = "SQLite")
	virtual bool SQLiteCreateColumn(const FString TableName, const FString ColumnName);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SQLite Create Table", ToolTip = "Description.", Keywords = "sqlite, create, table"), Category = "SQLite")
	virtual bool SQLiteCreateTable(const FString TableName);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Helper SQLite Create DB", ToolTip = "Don't use normalized UE4 paths. Use Windows paths such as \\", Keywords = "sqlite, create, database, db"), Category = "SQLite")
	virtual FString HelperSQLiteCreateDB(const FString DB_Path, const FString DB_Name);

};
