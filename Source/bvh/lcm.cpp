// Fill out your copyright notice in the Description page of Project Settings.


#include "lcm.h"
#include"Editor/UnrealEd/Public/AssetImportTask.h"
#include "AssetToolsModule.h"


UAssetImportTask* Ulcm::CreateImportTask(FString SourcePath, FString DestinationPath, UFactory* ExtraFactory, UObject* ExtraOptions, bool& bOutSuccess, FString& OutInfoMessage)
{
	UAssetImportTask* RetTask = NewObject<UAssetImportTask>();

	RetTask->Filename = SourcePath;
	RetTask->DestinationPath = FPaths::GetPath(DestinationPath);
	RetTask->DestinationName = FPaths::GetCleanFilename(DestinationPath);

	RetTask->bSave = false;
	RetTask->bAutomated = true;
	RetTask->bAsync = false;
	RetTask->bReplaceExisting = true;
	RetTask->bReplaceExistingSettings = false;

	RetTask->Factory = ExtraFactory;
	RetTask->Options = ExtraOptions;

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Create Import Task Succeded - '%s'"), *SourcePath);
	return RetTask;
}

UObject* Ulcm::ProcessImportTask(UAssetImportTask* ImportTask, bool& bOutSuccess, FString& OutInfoMessage)
{
	if (ImportTask == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed"));
		return nullptr;
	}

	FAssetToolsModule* AssetTools = FModuleManager::LoadModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetTools == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed"));
		return nullptr;
	}

	AssetTools->Get().ImportAssetTasks({ ImportTask });

	if (ImportTask->GetObjects().Num() == 0)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed"));
		return nullptr;
	}
	UObject* ImportedAsset = StaticLoadObject(UObject::StaticClass(), nullptr, *FPaths::Combine(ImportTask->DestinationPath, ImportTask->DestinationName));

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed"));
	return ImportedAsset;
}

UObject* Ulcm::importAsset(FString SourcePath, FString DestinationPath, bool& bOutSuccess, FString& OutInfoMessage)
{
	UAssetImportTask* Task = CreateImportTask(SourcePath, DestinationPath, nullptr, nullptr, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	UObject* RetAsset = ProcessImportTask(Task, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Process Import Task Failed"));
	return RetAsset;
}