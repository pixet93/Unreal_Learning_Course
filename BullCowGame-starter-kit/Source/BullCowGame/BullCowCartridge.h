// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Standard includes
#include <iostream>

//Unreal includes 
#include "CoreMinimal.h" // Access to Unreal core functionality
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:
		FString HiddenWord; 
};
