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
    
    //Checking Player's Guess
    ProcessGuess(Input);
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

    // const TCHAR HW[] = TEXT("plums"); // Example
    // const TCHAR HW[] = {TEXT('c'), TEXT('a'), TEXT('k'), TEXT('e'), TEXT('s'), TEXT('\0') };
    // PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0] ); //prints 'c'
    // PrintLine(TEXT("The 4th character of the HW is: %c"), HW[3] ); // prints 'm'
    // PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress <ENTER> to play again.") );
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    // Check if word is guessed
    if(HiddenWord == Guess)
    {
        PrintLine("You have won!");
        UBullCowCartridge::EndGame();
        return;
    }

    // Check right number of characters
    if(Guess.Len() != HiddenWord.Len() )
    {
        PrintLine(TEXT("The hidden word is %i letters long"), Guess.Len() );
        PrintLine(TEXT("Sorry, try guessing again!\nYou have %i lives remaining"), Lives ); 
        return;
    }

    // Check if Isogram
    if(!UBullCowCartridge::IsIsogram(Guess) )
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    // Remove life
    PrintLine(TEXT("Lost a life!\nLives remaining: %i"), --Lives);

    // Check if lives is greater than zero
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left") );
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    //Show player the Bulls and Cows    
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    // For each letter 
    // Start at element [0].
    // Compare against the next letter.
    // Until we reach [Word.Len() -1]
    // If any letter are the same return false

    int32 Index=0;
    int32 Comparison = Index + 1;

    for(int32 Index=0; Index < Word.Len(); ++Index)
    {
        for(int32 Comparison=Index+1; Comparison < Word.Len(); ++Comparison)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}