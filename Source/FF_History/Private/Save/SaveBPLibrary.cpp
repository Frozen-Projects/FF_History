// Copyright Epic Games, Inc. All Rights Reserved.

#include "Save/SaveBPLibrary.h"
#include "FF_History.h"

UFF_SaveBPLibrary::UFF_SaveBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UFF_SaveBPLibrary::GetVariableByName(FVariableContainer& Out_Container, UObject* In_Parent, FName In_Name)
{
    if (!IsValid(In_Parent))
    {
        return false;
    }

    UClass* Class = In_Parent->GetClass();

    if (!IsValid(Class))
    {
        return false;
    }

    if (In_Name.IsNone() || !In_Name.IsValid())
    {
        return false;
    }

    const FProperty* FoundProperty = Class->FindPropertyByName(In_Name);

    if (!FoundProperty)
    {
        return false;
    }

    void* Buffer = FoundProperty->ContainerPtrToValuePtr<void>(In_Parent);
    
    if (!Buffer)
    {
        return false;
    }

    FVariableContainer TempContainer;
    TempContainer.Name = In_Name;
    TempContainer.Parent = In_Parent;
    TempContainer.RecordTime = FDateTime::Now();

    if (const FStrProperty* StrProp = CastField<FStrProperty>(FoundProperty))
    {
        TempContainer.Serialized = StrProp->GetPropertyValue(Buffer);
        TempContainer.VariableType = "FString";
        Out_Container = TempContainer;
        return true;
    }

    else if (const FTextProperty* TextProp = CastField<FTextProperty>(FoundProperty))
    {
        TempContainer.Serialized = TextProp->GetPropertyValue(Buffer).ToString();
        TempContainer.VariableType = "FText";
        Out_Container = TempContainer;
        return true;
    }

    else if (const FIntProperty* IntProp = CastField<FIntProperty>(FoundProperty))
    {
        TempContainer.Serialized = FString::FromInt(IntProp->GetPropertyValue(Buffer));
        TempContainer.VariableType = "int32";
        Out_Container = TempContainer;
        return true;
    }

    else if (const FFloatProperty* FloatProp = CastField<FFloatProperty>(FoundProperty))
    {
        TempContainer.Serialized = FString::SanitizeFloat(FloatProp->GetPropertyValue(Buffer));
        TempContainer.VariableType = "Float";
        Out_Container = TempContainer;
        return true;
    }

    else if (const FBoolProperty* BoolProp = CastField<FBoolProperty>(FoundProperty))
    {
        TempContainer.Serialized = BoolProp->GetPropertyValue(Buffer) ? "True" : "False";
        TempContainer.VariableType = "Boolean";
        Out_Container = TempContainer;
        return true;
    }

    else if (const FStructProperty* StructProp = CastField<FStructProperty>(FoundProperty))
    {
        const FString VariableType = StructProp->Struct->GetName();
        TempContainer.VariableType = VariableType;

        if (VariableType == TEXT("Vector"))
        {
            FVector* Value = reinterpret_cast<FVector*>(Buffer);
            TempContainer.Serialized = Value->ToString();
        }

        else if (VariableType == TEXT("Rotator"))
        {
            FRotator* Value = reinterpret_cast<FRotator*>(Buffer);
            TempContainer.Serialized = Value->ToString();
        }

        else if (VariableType == TEXT("Transform"))
        {
            FTransform* Value = reinterpret_cast<FTransform*>(Buffer);
            TempContainer.Serialized = Value->ToString();
        }

        Out_Container = TempContainer;
        return true;
    }

    else
    {
        return false;
    }
}

bool UFF_SaveBPLibrary::GetAllVariables(FVariablePool& Out_Containers, UObject* In_Parent, bool bIncludeEditor, bool bIncludeNative, bool bIncludeRoot)
{
    if (!IsValid(In_Parent))
    {
        return false;
    }

    UClass* Class = In_Parent->GetClass();
    
    if (!IsValid(Class))
    {
        return false;
    }

    FVariablePool Temp_Pool;

    for (TFieldIterator<FProperty> EachFiled(Class); EachFiled; ++EachFiled)
    {
        const FProperty* FoundProperty = *EachFiled;

        if (!FoundProperty)
        {
            continue;
        }

        if (FoundProperty->IsEditorOnlyProperty() != bIncludeEditor)
        {
            continue;
        }

        if (FoundProperty->IsNative() != bIncludeNative)
        {
            continue;
        }

        if (FoundProperty->IsRooted() != bIncludeRoot)
        {
            continue;
        }

        void* Buffer = FoundProperty->ContainerPtrToValuePtr<void>(In_Parent);

        if (!Buffer)
        {
            continue;
        }

        FVariableContainer TempContainer;
        TempContainer.Name = *FoundProperty->GetName();
        TempContainer.Parent = In_Parent;
        TempContainer.RecordTime = FDateTime::Now();

        if (const FStrProperty* StrProp = CastField<FStrProperty>(FoundProperty))
        {
            TempContainer.Serialized = StrProp->GetPropertyValue(Buffer);
            TempContainer.VariableType = "FString";
            Temp_Pool.Containers.Add(TempContainer); 
            continue;
        }

        else if (const FTextProperty* TextProp = CastField<FTextProperty>(FoundProperty))
        {
            TempContainer.Serialized = TextProp->GetPropertyValue(Buffer).ToString();
            TempContainer.VariableType = "FText";
            Temp_Pool.Containers.Add(TempContainer);
            continue;
        }

        else if (const FIntProperty* IntProp = CastField<FIntProperty>(FoundProperty))
        {
            TempContainer.Serialized = FString::FromInt(IntProp->GetPropertyValue(Buffer));
            TempContainer.VariableType = "int32";
            Temp_Pool.Containers.Add(TempContainer);
            continue;
        }

        else if (const FFloatProperty* FloatProp = CastField<FFloatProperty>(FoundProperty))
        {
            TempContainer.Serialized = FString::SanitizeFloat(FloatProp->GetPropertyValue(Buffer));
            TempContainer.VariableType = "Float";
            Temp_Pool.Containers.Add(TempContainer);
            continue;
        }

        else if (const FBoolProperty* BoolProp = CastField<FBoolProperty>(FoundProperty))
        {
            TempContainer.Serialized = BoolProp->GetPropertyValue(Buffer) ? "True" : "False";
            TempContainer.VariableType = "Boolean";
            Temp_Pool.Containers.Add(TempContainer);
            continue;
        }

        else if (const FStructProperty* StructProp = CastField<FStructProperty>(FoundProperty))
        {
            const FString VariableType = StructProp->Struct->GetName();
            TempContainer.VariableType = VariableType;

            if (VariableType == TEXT("Vector"))
            {
                FVector* Value = reinterpret_cast<FVector*>(Buffer);
                TempContainer.Serialized = Value->ToString();
                Temp_Pool.Containers.Add(TempContainer);
                continue;
            }

            else if (VariableType == TEXT("Rotator"))
            {
                FRotator* Value = reinterpret_cast<FRotator*>(Buffer);
                TempContainer.Serialized = Value->ToString();
                Temp_Pool.Containers.Add(TempContainer);
                continue;
            }

            else if (VariableType == TEXT("Transform"))
            {
                FTransform* Value = reinterpret_cast<FTransform*>(Buffer);
                TempContainer.Serialized = Value->ToString();
                Temp_Pool.Containers.Add(TempContainer);
                continue;
            } 

            else
            {
                continue;
            }
        }

        else
        {
            continue;
        }
    }

    Out_Containers = Temp_Pool;
    return true;
}

bool UFF_SaveBPLibrary::SetVariable(UObject* TargetParent, FName TargetVariable, FString NewData)
{
    if (!IsValid(TargetParent))
    {
        return false;
    }

    UClass* Class = TargetParent->GetClass();

    if (!IsValid(Class))
    {
        return false;
    }

    if (TargetVariable.IsNone() || !TargetVariable.IsValid())
    {
        return false;
    }

    FProperty* FoundProperty = Class->FindPropertyByName(TargetVariable);
   
    if (!FoundProperty)
    {
        return false;
    }

    void* PropertyValue = FoundProperty->ContainerPtrToValuePtr<void>(TargetParent);

    if (FStrProperty* StrProp = CastField<FStrProperty>(FoundProperty))
    {
        StrProp->SetPropertyValue(PropertyValue, NewData);
        return true;
    }

    else if (FTextProperty* TextProp = CastField<FTextProperty>(FoundProperty))
    {
        TextProp->SetPropertyValue(PropertyValue, FText::FromString(NewData));
        return true;
    }

    else if (FIntProperty* IntProp = CastField<FIntProperty>(FoundProperty))
    {
        IntProp->SetPropertyValue(PropertyValue, FCString::Atoi(*NewData));
        return true;
    }

    else if (FFloatProperty* FloatProp = CastField<FFloatProperty>(FoundProperty))
    {
        FloatProp->SetPropertyValue(PropertyValue, FCString::Atof(*NewData));
        return true;
    }

    else if (FBoolProperty* BoolProp = CastField<FBoolProperty>(FoundProperty))
    {
        if (NewData == "True" || NewData == "true")
        {
            BoolProp->SetPropertyValue(PropertyValue, true);
            return true;
        }

        else if (NewData == "False" || "false")
        {
            BoolProp->SetPropertyValue(PropertyValue, false);
            return true;
        }
        
        else
        {
            return false;
        }
    }

    else if (const FStructProperty* StructProp = CastField<FStructProperty>(FoundProperty))
    {
        const FString VariableType = StructProp->Struct->GetName();

        if (VariableType == TEXT("Vector"))
        {
            FVector NewValue;
            NewValue.InitFromString(NewData);
            
            FVector* OldValue = reinterpret_cast<FVector*>(PropertyValue);
            OldValue->X = NewValue.X;
            OldValue->Y = NewValue.Y;
            OldValue->Z = NewValue.Z;
           
            return true;
        }

        else if (VariableType == TEXT("Rotator"))
        {
            FRotator NewValue;
            NewValue.InitFromString(NewData);

            FRotator* OldValue = reinterpret_cast<FRotator*>(PropertyValue);
            OldValue->Pitch = NewValue.Pitch;
            OldValue->Yaw = NewValue.Yaw;
            OldValue->Roll = NewValue.Roll;

            return true;
        }

        else if (VariableType == TEXT("Transform"))
        {
            FTransform NewValue;
            NewValue.InitFromString(NewData);

            FTransform* OldValue = reinterpret_cast<FTransform*>(PropertyValue);
            OldValue->SetLocation(NewValue.GetLocation());
            OldValue->SetRotation(NewValue.GetRotation());
            OldValue->SetScale3D(NewValue.GetScale3D());

            return true;
        }

        else
        {
            return false;
        }
    }

    else
    {
        return false;
    }
}

void UFF_SaveBPLibrary::SaveGameToFile(FDelegateSaveToFile DelegateSave, USaveGame* Instance_Save, FString In_Path)
{
    if (!IsValid(Instance_Save))
    {
        DelegateSave.ExecuteIfBound(false, "Save instance is not valid !");
        return;
    }

    if (!FPaths::DirectoryExists(FPaths::GetPath(In_Path)))
    {
        DelegateSave.ExecuteIfBound(false, "Write directory is not exist !");
        return;
    }
    
    AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [DelegateSave, Instance_Save, In_Path]()
        {
            TArray<uint8> SaveData;
            FMemoryWriter MemoryWriter(SaveData, true);
            FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, false);
            Instance_Save->Serialize(Archive);

            if (FFileHelper::SaveArrayToFile(SaveData, *In_Path))
            {
                AsyncTask(ENamedThreads::GameThread, [DelegateSave]()
                    {
                        DelegateSave.ExecuteIfBound(true, "Save successful.");
                    }
                );

                return;
            }

            else
            {
                AsyncTask(ENamedThreads::GameThread, [DelegateSave]()
                    {
                        DelegateSave.ExecuteIfBound(false, "Save is not successful !");
                    }
                );

                return;
            }
        }
    );
}

void UFF_SaveBPLibrary::SaveGameToMemory(FDelegateSaveToMemory DelegateSave, USaveGame* Instance_Save)
{
    if (!IsValid(Instance_Save))
    {
        DelegateSave.ExecuteIfBound(false, "Save instance is not valid !", TArray<uint8>());
        return;
    }

    AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [DelegateSave, Instance_Save]()
        {
            TArray<uint8> SaveData;
            FMemoryWriter MemoryWriter(SaveData, true);
            FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, false);
            Instance_Save->Serialize(Archive);

            if (SaveData.IsEmpty())
            {
                AsyncTask(ENamedThreads::GameThread, [DelegateSave]()
                    {
                        DelegateSave.ExecuteIfBound(false, "Save buffer is empty !", TArray<uint8>());
                    }
                );

                return;
            }

            else
            {
                AsyncTask(ENamedThreads::GameThread, [DelegateSave, SaveData]()
                    {
                        DelegateSave.ExecuteIfBound(true, "Save successful.", SaveData);
                    }
                );
            }
        }
    );
}

void UFF_SaveBPLibrary::LoadGameFromFile(FDelegateLoad DelegateLoad, FString In_Path, TSubclassOf<USaveGame> SaveGameClass)
{
    if (!FPaths::FileExists(In_Path))
    {
        DelegateLoad.ExecuteIfBound(false, "Save file is not exist !", nullptr);
        return;
    }

    USaveGame* LoadedGame = NewObject<USaveGame>(GetTransientPackage(), SaveGameClass);

    if (!IsValid(LoadedGame))
    {
        DelegateLoad.ExecuteIfBound(false, "There was a problem while creating empty save object with given class !", nullptr);
        return;
    }

    AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [DelegateLoad, In_Path, LoadedGame]()
        {
            TArray<uint8> LoadData;
            if (!FFileHelper::LoadFileToArray(LoadData, *In_Path))
            {
                AsyncTask(ENamedThreads::GameThread, [DelegateLoad]()
                    {
                        DelegateLoad.ExecuteIfBound(false, "There was a problem while loading save data !", nullptr);
                    }
                );

                return;
            }

            FMemoryReader MemoryReader(LoadData, true);
            FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
            LoadedGame->Serialize(Archive);

            AsyncTask(ENamedThreads::GameThread, [DelegateLoad, LoadedGame]()
                {
                    DelegateLoad.ExecuteIfBound(true, "Load successful.", LoadedGame);
                }
            );
        }
    );
}

void UFF_SaveBPLibrary::LoadGameFromMemory(FDelegateLoad DelegateLoad, TArray<uint8> In_Buffer, TSubclassOf<USaveGame> SaveGameClass)
{
    if (In_Buffer.IsEmpty())
    {
        DelegateLoad.ExecuteIfBound(false, "Buffer is empty !", nullptr);
        return;
    }

    USaveGame* LoadedGame = NewObject<USaveGame>(GetTransientPackage(), SaveGameClass);

    if (!IsValid(LoadedGame))
    {
        DelegateLoad.ExecuteIfBound(false, "There was a problem while creating empty save object with given class !", nullptr);
        return;
    }

    AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [DelegateLoad, In_Buffer, LoadedGame]()
        {
            FMemoryReader MemoryReader(In_Buffer, true);
            FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
            LoadedGame->Serialize(Archive);

            AsyncTask(ENamedThreads::GameThread, [DelegateLoad, LoadedGame]()
                {
                    DelegateLoad.ExecuteIfBound(true, "Load successful.", LoadedGame);
                }
            );
        }
    );
}

void UFF_SaveBPLibrary::SaveWidgetToFile(FDelegateSaveToFile DelegateSave, FString In_Path, UUserWidget* In_Widget)
{

}
