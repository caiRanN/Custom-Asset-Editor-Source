// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyCustomAsset.generated.h"

/**
 * 
 */
UCLASS()
class ASSETEDITORTUTORIAL_API UMyCustomAsset : public UObject
{
	GENERATED_BODY()

public:
	UMyCustomAsset();
	
protected:
	UPROPERTY(VisibleAnywhere, Category = MyCustomAsset)
	FString Description;

	UPROPERTY(VisibleAnywhere, Category = MyCustomAsset)
	bool bIsActive;
};
