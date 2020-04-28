// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWords.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    SetIsograms(GetValidWords(HiddenWords));

    SetupGame();
}


void UBullCowCartridge::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
    Super::EndPlay(EndPlayReason);
}


void UBullCowCartridge::SetupGame()
{
    int32 RandIndex = FMath::RandRange(0, _Isograms.Num() - 1);
    SetHiddenWord(_Isograms[RandIndex]);

    SetNumberLives(_HiddenWord.Len());

    SetGameFinished(false);

    PrintLine(TEXT("Hidden word: %s"), *_HiddenWord);

    PrintLine(TEXT("Welcome to my Bull & Cow game!"));
    PrintLine(TEXT("Guess the hidden word of %i characters!"), _HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), _NumberLives); 
    PrintLine(TEXT("Press 'Enter' to continue..."));
}


TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Words) const
{
    TArray<FString> ValidWords;

    for (FString CurrentWord : Words) {
        if (CurrentWord.Len() >= 4 && CurrentWord.Len() <= 11) {

            if (IsIsogram(CurrentWord)) {
                ValidWords.Add(CurrentWord);
            }
        }
    }
    return ValidWords;
}


void UBullCowCartridge::EndGame()
{
    SetGameFinished(true);
    PrintLine(TEXT("Do you want to play again?"));
}


bool UBullCowCartridge::IsIsogram(const FString& Letters) const
{
    for (int32 Index = 0; Index < Letters.Len(); Index++) {
        TCHAR CurrentChar = Letters[Index];

        for (int32 Next = Index + 1; Next < Letters.Len(); Next++) {
            TCHAR NextChar = Letters[Next];

            if (CurrentChar == NextChar) {
                return false;
            }
        }
    }

    return true;   
}


void UBullCowCartridge::CheckAnswer(const FString& Answer)
{
    if (_HiddenWord == Answer) {
        ClearScreen();
        PrintLine(TEXT("You've won!"));
        EndGame();
        return;
    }

    if (Answer.Len() != _HiddenWord.Len()) {
        PrintLine(TEXT("Length is not correct. Try again!"));
    }

    if (!IsIsogram(Answer)) {
        PrintLine(TEXT("Repeating letters in answer. Try again!"));
    }

    --_NumberLives;

    if (_NumberLives <= 0) {
        PrintLine(TEXT("You've lost!"));
        PrintLine(TEXT("The hidden word was: %s."), *_HiddenWord);
        EndGame();
        return;
    }

    // Show the count of Bulls and Cows to player
    FBullCowCount Count = GetBullCows(Answer);
    PrintLine(TEXT("There are Bulls: %i and Cows: %i"), Count.Bulls, Count.Cows);

    PrintLine(TEXT("Wrong answer! Number of lives left: %i"), _NumberLives);
    PrintLine(TEXT("The hidden word is %i characters"), _HiddenWord.Len());
}


void UBullCowCartridge::OnInput(const FString& PlayerInput)
{
    if (_bGameFinished) {

        if (PlayerInput == "Yes") {
            SetupGame();
        }
        else if (PlayerInput == "No") {
            // End game session. Go back to Editor? 
        }
    }
    else {
        CheckAnswer(PlayerInput);
    }
}


FBullCowCount UBullCowCartridge::GetBullCows(const FString& Answer) const 
{
    FBullCowCount Count; 

    for (int32 Index = 0; Index < Answer.Len(); Index++) {

        if (Answer[Index] == _HiddenWord[Index]) {
            Count.Bulls++;
            continue; 
        }
        for (int HiddenIndex = 0; HiddenIndex < _HiddenWord.Len(); HiddenIndex++) {

            if (Answer[Index] == _HiddenWord[HiddenIndex]) {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}