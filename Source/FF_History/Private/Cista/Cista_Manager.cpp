// Fill out your copyright notice in the Description page of Project Settings.

#include "Cista/Cista_Manager.h"

// Sets default values
ACista_Manager::ACista_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned.
void ACista_Manager::BeginPlay()
{
	Super::BeginPlay();
}

// Called when the game end or when destroyed.
void ACista_Manager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	this->Buffer.reset();
	Super::EndPlay(EndPlayReason);
}

// Called every frame.
void ACista_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACista_Manager::Cista_Export(FDelegateCistaSerialize DelegateCista, FString In_Path)
{
	if (In_Path.IsEmpty())
	{
		DelegateCista.ExecuteIfBound(false, "Path is empty !");
		return;
	}

	const FString Directory = FPaths::GetPath(In_Path);

	if (!FPaths::DirectoryExists(Directory))
	{
		DelegateCista.ExecuteIfBound(false, "Given directory is not valid !");
		return;
	}

	FPaths::NormalizeFilename(In_Path);

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, DelegateCista, In_Path]()
		{
			std::ofstream out(TCHAR_TO_UTF8(*In_Path), std::ios::binary);
			out.write(reinterpret_cast<const char*>(this->Buffer.base()), this->Buffer.size());
			out.close();

			AsyncTask(ENamedThreads::GameThread, [DelegateCista]()
				{
					DelegateCista.ExecuteIfBound(true, "Buffer exported successfully.");
				}
			);
		}
	);
}

void ACista_Manager::Cista_Serialize_String(FDelegateCistaSerialize DelegateCista, FString In_String)
{
	if (In_String.IsEmpty())
	{
		DelegateCista.ExecuteIfBound(false, "Content string is empty !");
		return;
	}

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, DelegateCista, In_String]()
		{
			this->Buffer.write(TCHAR_TO_UTF8(*In_String), In_String.Len());

			AsyncTask(ENamedThreads::GameThread, [DelegateCista]()
				{
					DelegateCista.ExecuteIfBound(true, "Data added to buffer.");
				}
			);
		}
	);
}

void ACista_Manager::Cista_Serialize_Bytes(FDelegateCistaSerialize DelegateCista, TArray<uint8> In_Bytes)
{
	if (In_Bytes.IsEmpty())
	{
		DelegateCista.ExecuteIfBound(false, "Bytes is empty !");
		return;
	}

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, DelegateCista, In_Bytes]()
		{
			this->Buffer.write(In_Bytes.GetData(), In_Bytes.Num());

			AsyncTask(ENamedThreads::GameThread, [DelegateCista]()
				{
					DelegateCista.ExecuteIfBound(true, "Data added to buffer.");
				}
			);
		}
	);
}

void ACista_Manager::Cista_Deserialize_String(FDelegateCistaString DelegateCista, FString In_Path)
{
	if (In_Path.IsEmpty())
	{
		DelegateCista.ExecuteIfBound(false, "Path is empty !", FString());
		return;
	}

	if (!FPaths::FileExists(In_Path))
	{
		DelegateCista.ExecuteIfBound(false, "File is not exist !", FString());
		return;
	}

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, DelegateCista, In_Path]()
		{
			std::ifstream FileStream(TCHAR_TO_UTF8(*In_Path), std::ios::in | std::ios::ate);
			const size_t FileSize = FileStream.tellg();
			FileStream.seekg(0, std::ios::beg);

			std::string FileContents;
			FileContents.resize(FileSize);
			FileStream.read(&FileContents[0], FileSize);
			FileStream.close();

			FString RawString = UTF8_TO_TCHAR(FileContents.c_str());

			AsyncTask(ENamedThreads::GameThread, [DelegateCista, RawString]()
				{
					DelegateCista.ExecuteIfBound(true, "Deserializing bytes successful.", RawString);
				}
			);
		}
	);
}

void ACista_Manager::Cista_Deserialize_Bytes(FDelegateCistaBytes DelegateCista, FString In_Path)
{
	if (In_Path.IsEmpty())
	{
		DelegateCista.ExecuteIfBound(false, "Path is empty !", TArray<uint8>());
		return;
	}

	if (!FPaths::FileExists(In_Path))
	{
		DelegateCista.ExecuteIfBound(false, "File is not exist !", TArray<uint8>());
		return;
	}

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, DelegateCista, In_Path]()
		{
			std::ifstream FileStream(TCHAR_TO_UTF8(*In_Path), std::ios::binary | std::ios::ate);
			const size_t FileSize = FileStream.tellg();
			FileStream.seekg(0, std::ios::beg);

			std::vector<uint8> FileContents(FileSize);
			FileStream.read(reinterpret_cast<char*>(FileContents.data()), FileSize);
			FileStream.close();

			const size_t BufferSize = FileContents.size();
			
			TArray<uint8> Temp_Array;
			Temp_Array.SetNum(BufferSize);
			FMemory::Memcpy(Temp_Array.GetData(), FileContents.data(), BufferSize);

			AsyncTask(ENamedThreads::GameThread, [DelegateCista, Temp_Array]()
				{
					DelegateCista.ExecuteIfBound(true, "Deserializing bytes successful.", Temp_Array);
				}
			);
		}
	);
}