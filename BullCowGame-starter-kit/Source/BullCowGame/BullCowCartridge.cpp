// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    PrintLine(TEXT("Welcome to my Bull & Cow game!"));
    PrintLine(TEXT("Guess hidden isogram word with 4 letters!"));
    PrintLine(TEXT("Press 'Tab' to start typing."));
}


void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    HiddenWord = TEXT("pear");

    PrintLine(Input);

    if (Input.Len() > 0) {
        if (Input == HiddenWord) {
            PrintLine(TEXT("You've found the hidden isogram word!"));
        }
        else {
            PrintLine(TEXT("You guessed the wrong word. Try again!"));
        }
    }
    else {
        PrintLine(TEXT("No input was found. Enter letters!"));
    }

    
}