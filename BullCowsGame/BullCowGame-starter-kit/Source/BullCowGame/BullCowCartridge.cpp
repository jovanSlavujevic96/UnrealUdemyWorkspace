// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hi there!\nWelcome to the Bull Cows Game!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Magic Number Remove @caption
    PrintLine(TEXT("Press <TAB> to type text\nPress <ENTER> to enter text..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    static FString HiddenWord = TEXT("cake"); //must use TEXT() macro to wrap string into FString 
    // Move outside this function @caption
    if(HiddenWord == Input)
    {
        PrintLine("You have won!");
        return;
    }
    PrintLine("You have lost!");
}