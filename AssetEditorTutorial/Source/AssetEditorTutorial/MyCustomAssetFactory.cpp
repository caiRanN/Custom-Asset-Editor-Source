// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCustomAssetFactory.h"
#include "MyCustomAsset.h"

UMyCustomAssetFactory::UMyCustomAssetFactory()
{
	// Provide the factory with information about how to handle our asset
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMyCustomAsset::StaticClass();
}

UObject* UMyCustomAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	// Create and return a new instance of our MyCustomAsset object
	UMyCustomAsset* MyCustomAsset = NewObject<UMyCustomAsset>(InParent, Class, Name, Flags);
	return MyCustomAsset;
}
