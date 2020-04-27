// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Standard includes
#include <iostream>
#include <string>

//Unreal includes 
#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	void SetupGame();
	void EndGame();
	bool IsIsogram(FString Letters);
	void CheckAnswer(FString Answer);
	// Unreal signal functions 
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;


	public:
		void SetParameters(FString HiddenWord) {
			_HiddenWord = HiddenWord;
		}

		// Getters and Setters
		void SetHiddenWord(FString word) {
			_HiddenWord = word;
		}
		FString GetHiddenWord() {
			return _HiddenWord;
		}

		void SetNumberLives(int32 lives) {
			_NumberLives = lives;
		}
		int32 GetNumberLives() {
			return _NumberLives;
		}

		void SetGameFinished(bool state) {
			_bGameFinished = state;
		}
		bool GetGameFinished() {
			return _bGameFinished;
		}


	private:
		FString _HiddenWord; 
		int32 _NumberLives;
		bool _bGameFinished;
};
