// Fill out your copyright notice in the Description page of Project Settings.

#include "SQLite/SQLite_Manager.h"

// Sets default values
ASQLite_Manager::ASQLite_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned.
void ASQLite_Manager::BeginPlay()
{
	Super::BeginPlay();
}

// Called when the game end or when destroyed.
void ASQLite_Manager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame.
void ASQLite_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASQLite_Manager::SQLiteOpen(const FString DB_Path, ESQLiteOpenType OpenType)
{
    ESQLiteDatabaseOpenMode OpenMode = ESQLiteDatabaseOpenMode::ReadOnly;

    switch (OpenType)
    {
        case ESQLiteOpenType::ReadOnly:
            OpenMode = ESQLiteDatabaseOpenMode::ReadOnly;
            break;

        case ESQLiteOpenType::ReadWrite:
            OpenMode = ESQLiteDatabaseOpenMode::ReadWrite;
            break;

        case ESQLiteOpenType::ReadWriteCreate:
            OpenMode = ESQLiteDatabaseOpenMode::ReadWriteCreate;
            break;

        default:
            OpenMode = ESQLiteDatabaseOpenMode::ReadOnly;
            break;
    }

    this->SQLiteDB = new FSQLiteDatabase();
    this->SQLiteDB->Open(*DB_Path, OpenMode);
    const bool bIsConnectionValid = this->SQLiteDB->IsValid();

    if (!bIsConnectionValid)
    {
        this->SQLiteDB->Close();
        delete this->SQLiteDB;
    }

    return bIsConnectionValid;
}

void ASQLite_Manager::SQLiteClose()
{
    if (this->SQLiteDB->IsValid())
    {
        this->SQLiteDB->Close();
        delete this->SQLiteDB;
    }
}

bool ASQLite_Manager::SQLiteGetColumnsNames(const FString TableName, TArray<FString>& OutColumnsNames)
{
    if (!this->SQLiteDB->IsValid())
    {
        return false;
    }

    const FString GetColumnNamesQuery = TEXT("select * from ") + TableName;
    FSQLitePreparedStatement LoadStatement;
    LoadStatement.Create(*this->SQLiteDB, *GetColumnNamesQuery, ESQLitePreparedStatementFlags::Persistent);

    OutColumnsNames = LoadStatement.GetColumnNames();

    LoadStatement.ClearBindings();
    LoadStatement.Destroy();

    return true;
}

bool ASQLite_Manager::SQLiteGetSingleRowValue(const FString TableName, const FString IDColumn, const FString IDIndex, const FString ColumnName, FString& ColumnValue)
{
    if (!this->SQLiteDB->IsValid())
    {
        return false;
    }

    const FString GetColumnValuesQuery = TEXT("SELECT * from ") + TableName + TEXT(" WHERE ") + IDColumn + TEXT(" = ") + IDIndex;
    FSQLitePreparedStatement LoadStatement;
    LoadStatement.Create(*this->SQLiteDB, *GetColumnValuesQuery, ESQLitePreparedStatementFlags::Persistent);

    const FString IDBinding = TEXT("$") + IDColumn;
    LoadStatement.SetBindingValueByName(*IDBinding, IDIndex);
    LoadStatement.Step();
    LoadStatement.GetColumnValueByName(*ColumnName, ColumnValue);

    LoadStatement.ClearBindings();
    LoadStatement.Destroy();

    return true;
}

bool ASQLite_Manager::SQLiteGetAllRowValues(const FString Query, const FString ColumnName, TArray<FString>& ColumnValues)
{
    if (!this->SQLiteDB->IsValid())
    {
        return false;
    }

    FSQLitePreparedStatement CustomQueryStatement;
    CustomQueryStatement.Create(*this->SQLiteDB, *Query, ESQLitePreparedStatementFlags::Persistent);

    FString EachColumnValue;
    while (CustomQueryStatement.Step() == ESQLitePreparedStatementStepResult::Row)
    {
        CustomQueryStatement.GetColumnValueByName(*ColumnName, EachColumnValue);
        ColumnValues.Add(EachColumnValue);
    }

    CustomQueryStatement.ClearBindings();
    CustomQueryStatement.Destroy();

    return true;
}

bool ASQLite_Manager::SQLiteGetAllTableContents(const FString TableName, const FString QueryCondition, TMap<FString, FSQLiteRows>& TableContents)
{
    if (!this->SQLiteDB->IsValid())
    {
        return false;
    }

    // Create SQLite query.
    const FString Query = TEXT("SELECT * from ") + TableName + TEXT(" WHERE ") + QueryCondition;

    // Get column names.
    TArray<FString> ColumnNames;
    ASQLite_Manager::SQLiteGetColumnsNames(TableName, ColumnNames);

    FSQLiteRows STR_RowValues;
    for (int32 ColumnIndex = 0; ColumnIndex < ColumnNames.Num(); ColumnIndex++)
    {
        TArray<FString> RowValues;
        ASQLite_Manager::SQLiteGetAllRowValues(Query, ColumnNames[ColumnIndex], RowValues);
        STR_RowValues.ColumnValues = RowValues;

        TableContents.Add(ColumnNames[ColumnIndex], STR_RowValues);
    }

    return true;
}

bool ASQLite_Manager::SQLiteWriteValue(const FString TableName, const FString ColumnName, const FString InValue)
{
    if (!this->SQLiteDB->IsValid())
    {
        return false;
    }

    const FString WriteQuery = TEXT("INSERT INTO ") + TableName + TEXT(" (") + ColumnName + TEXT(") VALUES ('") + InValue + TEXT("')");

    FSQLitePreparedStatement StatementWriteValue;
    StatementWriteValue.Reset();
    StatementWriteValue.Create(*this->SQLiteDB, *WriteQuery, ESQLitePreparedStatementFlags::Persistent);
    StatementWriteValue.SetBindingValueByName(*ColumnName, *InValue);
    StatementWriteValue.Execute();

    StatementWriteValue.ClearBindings();
    StatementWriteValue.Destroy();

    return true;
}

bool ASQLite_Manager::SQLiteCreateColumn(const FString TableName, const FString ColumnName)
{
    if (!this->SQLiteDB->IsValid())
    {
        return false;
    }

    const FString QueryCreateColumn = TEXT("ALTER TABLE ") + TableName + TEXT(" ADD ") + ColumnName + TEXT(" TEXT");

    FSQLitePreparedStatement StatementCreateColumn;
    StatementCreateColumn.Reset();
    StatementCreateColumn.Create(*this->SQLiteDB, *QueryCreateColumn, ESQLitePreparedStatementFlags::Persistent);
    StatementCreateColumn.Execute();

    StatementCreateColumn.ClearBindings();
    StatementCreateColumn.Destroy();

    return true;
}

bool ASQLite_Manager::SQLiteCreateTable(const FString TableName)
{
    if (!this->SQLiteDB->IsValid())
    {
        return false;
    }

    const FString QueryCreateTable = TEXT("CREATE TABLE IF NOT EXISTS ") + TableName + TEXT(" (id INTEGER PRIMARY KEY)");

    FSQLitePreparedStatement StatementCreateTable;
    StatementCreateTable.Reset();
    StatementCreateTable.Create(*this->SQLiteDB, *QueryCreateTable, ESQLitePreparedStatementFlags::Persistent);
    StatementCreateTable.Execute();

    StatementCreateTable.ClearBindings();
    StatementCreateTable.Destroy();

    return true;
}

FString ASQLite_Manager::HelperSQLiteCreateDB(const FString DB_Path, const FString DB_Name)
{
    return TEXT("sqlite3 ") + DB_Path + DB_Name + TEXT(".db") + TEXT(" \"VACCUUM;\"");
}