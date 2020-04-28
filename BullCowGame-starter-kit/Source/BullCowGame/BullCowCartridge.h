// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Standard includes
#include <iostream>
#include <string>

//Unreal includes 
#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	// Game functions 
	void SetupGame();
	void EndGame();
	bool IsIsogram(const FString& Letters) const;
	void CheckAnswer(const FString& Answer);
	TArray<FString> GetValidWords(const TArray<FString>& Words) const;
	FBullCowCount GetBullCows(const FString& Answer) const;

	// Unreal signal functions 
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void OnInput(const FString& Input) override;


	public:
		void SetParameters(FString HiddenWord) {
			_HiddenWord = HiddenWord;
		}
		// Getters and Setters
		void SetIsograms(TArray<FString> Words) {
			_Isograms = Words;
		}
		TArray<FString> GetIsograms() {
			return _Isograms;
		}
		void SetHiddenWord(FString Word) {
			_HiddenWord = Word;
		}
		FString GetHiddenWord() {
			return _HiddenWord;
		}
		void SetNumberLives(int32 Lives) {
			_NumberLives = Lives;
		}
		int32 GetNumberLives() {
			return _NumberLives;
		}
		void SetGameFinished(bool State) {
			_bGameFinished = State;
		}
		bool GetGameFinished() {
			return _bGameFinished;
		}


	private:
		TArray<FString> _Isograms;
		FString _HiddenWord;
		int32 _NumberLives;
		bool _bGameFinished;
};