// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt"); // Set the abs path to txt file
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, 
        [](const FString& Word) 
        { 
            return Word.Len() > 4 && Word.Len() < 8 && UBullCowCartridge::IsIsogram(Word);
        } );   // Load words from txt file into Words array, but only words which passes this []-Lambda criteria

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
 
    // Must use TEXT() macro to wrap string into FString
    // HiddenWord = TEXT("cakes"); // Initialise Hidden word at the beginning // Hardcoded
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1) ];
    Lives = HiddenWord.Len() * 2; //Set Lives
    bGameOver = false; //Set GameOver varibale

    PrintLine(FString::Printf(TEXT("Guess the %i letter word!"), HiddenWord.Len() )); 
    // PrintLine(TEXT("Hidden word is %s."), *HiddenWord); // Debug Line
    PrintLine(TEXT("You have %d Lives"), Lives);    //There can be used both %d or %i for integers
    PrintLine(TEXT("Press <TAB> so you could type text\nPress <ENTER> to enter your guess...")); // Prompt Player for Guess

    /* const TCHAR HW[] = TEXT("plums"); // Example
    const TCHAR HW[] = {TEXT('c'), TEXT('a'), TEXT('k'), TEXT('e'), TEXT('s'), TEXT('\0') };
    PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0] ); //prints 'c'
    PrintLine(TEXT("The 4th character of the HW is: %c"), HW[3] ); // prints 'm'
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); */
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
    PrintLine(TEXT("Lost a life!"));
    Lives--;

    // Check if lives is greater than zero
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left") );
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        UBullCowCartridge::EndGame();
        return;
    }

    //Show player the Bulls and Cows    
    auto Score = UBullCowCartridge::GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for(int32 Index = 0; Index < WordList.Num(); Index++)
    {
        if(WordList[Index].Len() >= 4 && WordList[Index].Len() >= 8 && UBullCowCartridge::IsIsogram(WordList[Index]) )
        {
            ValidWords.Emplace(WordList[Index] );
        }
    }
    // for(auto Fstr : ValidWords)
    // {
    //     PrintLine(TEXT("%s."), *Fstr );
    // }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;
    Count.Bulls = 0;
    Count.Cows = 0;

    // for every index Guess is same as index Hidden -> BullCount ++
    // if not a bull was it a cow? if yes -> CowCount ++

    for(int32 GuessIndex=0; GuessIndex < Guess.Len(); ++GuessIndex)
    {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex] )
        {
            Count.Bulls++;
            continue;
        }
        for(int32 HiddenIndex=0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])       
            {
                Count.Cows++;
                break;  // Wasted effor without break
            }
        }
    }

    return Count;
}