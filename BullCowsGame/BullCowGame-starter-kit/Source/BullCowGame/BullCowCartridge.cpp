// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    UBullCowCartridge::SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
        return;
    }
    if(HiddenWord == Input)
    {
        PrintLine("You have won!");
        UBullCowCartridge::EndGame();
        return;
    }
    PrintLine(TEXT("Lost a life!\nLives remaining: %i"), --Lives);
    if (Lives > 0)
    {
        if(Input.Len() != HiddenWord.Len() )
        {
            PrintLine(TEXT("Sorry, try guessing again!\nThe Hidden Word is %i lives remaining.\nYou have lost!"), HiddenWord.Len() ); 
            UBullCowCartridge::EndGame();
        }
    }
    else
    {
        PrintLine(TEXT("You have no lives left!"));
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to the Bull Cows Game!"));
 
    //must use TEXT() macro to wrap string into FString
    HiddenWord = TEXT("cakes"); //initialise Hidden word at the beginning
    Lives = HiddenWord.Len(); //Set Lives
    bGameOver = false; //Set GameOver varibale

    PrintLine(FString::Printf(TEXT("Guess the %i letter word!"), HiddenWord.Len() )); 
    PrintLine(TEXT("You have %d Lives"), Lives);    //There can be used both %d or %i for integers
    PrintLine(TEXT("Press <TAB> so you could type text\nPress <ENTER> to enter your guess...")); // Prompt Player for Guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press <ENTER> to play again.") );
}