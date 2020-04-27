// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    SetupGame();
}


void UBullCowCartridge::SetupGame()
{
    ClearScreen();

    SetHiddenWord("pear");

    SetNumberLives(_HiddenWord.Len());

    SetGameFinished(false);

    PrintLine(TEXT("Welcome to my Bull & Cow game!"));
    PrintLine(TEXT("Guess the hidden word of %i characters!"), _HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), _NumberLives); 
    PrintLine(TEXT("Press 'Enter' to continue..."));
}


void UBullCowCartridge::EndGame()
{
    SetGameFinished(true);
    PrintLine(TEXT("Do you want to play again?"));
}


bool UBullCowCartridge::IsIsogram(FString Letters)
{
    int32 CharCount = 0;

    while (CharCount < Letters.Len() - 1) {
        TCHAR Current = Letters[CharCount];
        TCHAR Next = Letters[CharCount + 1];

        if (Current == Next) {
            return false;
        }

        CharCount++;
    }

    /*for (TCHAR i = 0; i < Letters.Len(); i++)
    {
        TCHAR current_char = Letters[i];
        TCHAR next_char = Letters[i + 1];

        if (current_char == next_char) {
            return false;
        }
    }*/

    return true;   
}


void UBullCowCartridge::CheckAnswer(FString Answer)
{
    if (_HiddenWord == Answer) {
        ClearScreen();
        PrintLine(TEXT("You've won!"));
        EndGame();
        return;
    }

    if (Answer.Len() != _HiddenWord.Len()) {
        PrintLine(TEXT("Not correct length of answer. Please try again."));
    }

    if (!IsIsogram(Answer)) {
        PrintLine(TEXT("Found repeating letters in answer. Please try again."));
    }

    --_NumberLives;

    if (_NumberLives <= 0) {
        PrintLine(TEXT("You've lost!"));
        PrintLine(TEXT("The hidden word was: %s."), *_HiddenWord);
        EndGame();
        return;
    }

    PrintLine(TEXT("Wrong answer! Number of lives left: %i"), _NumberLives);
    PrintLine(TEXT("The hidden word is %i characters"), _HiddenWord.Len());
}


void UBullCowCartridge::OnInput(const FString& Input)
{
    if (_bGameFinished) {

        if (Input == "Yes") {
            SetupGame();
        }
        else if (Input == "No") {
            // end game?
        }
    }
    else {
        CheckAnswer(Input);
    }
}