#include <iostream>
#include <ctime>

void PrintIntoduction(int Difficulty);

bool PlayGame(int Difficulty)
{
    PrintIntoduction(Difficulty);

    const int CodeA=rand()%Difficulty+Difficulty, CodeB=rand()%Difficulty+Difficulty, CodeC=rand()%Difficulty+Difficulty;
    const int CodeSum = CodeA+CodeB+CodeC;
    const int CodeProduct = CodeA*CodeB*CodeC;

    //Print sum and product to the terminal
    std::cout << std::endl;
    std::cout << "+ There are 3 numbers in the code\n";
    std::cout << "\n+ The codes add-up to: " << CodeSum;
    std::cout << "\n+ The code multiply to give: "  << CodeProduct;

    // Store player guess
    int GuessA, GuessB, GuessC;
    std::cout << "\nGive me your guess: ";
    std::cin >> GuessA >> GuessB >> GuessC;
    std::cout << "\nYou entered: " << GuessA << ' ' << GuessB << ' ' << GuessC << std::endl;
    
    /*
    //my way
    bool CorrectGuess = false;

    for(int i=0; i<3; ++i)
    {
        static const int* Code = &CodeA;
        static int* Guess = &GuessA;
        if(0 == i)
        {
            ++Code = &CodeB;
            ++Code = &CodeC;

            ++Guess = &GuessB;
            ++Guess = &GuessC;
        }
        static int incr=0;
        for(int j=0; j<3; ++j)
        {
            if(Code[i] == Guess[j])
            {
                ++incr;
                break;
            }
        }
        if(3 == incr)
        {
            CorrectGuess = true;
        }
    }

    std::cout << "Guess result: " << std::boolalpha << CorrectGuess << std::endl;
    */

    //check player's guess
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;
    std::string TmpResult = "uncorrect";
    if(CodeSum == GuessSum && CodeProduct == GuessProduct)
    {
        TmpResult = "correct";
    }
    std::cout << "Guess result: " << TmpResult << "\n\n";

    return ("correct" == TmpResult) ? true : false;
}

void PrintIntoduction(int Difficulty)
{
    //Print Welcome messages to the terminal
    std::cout << "You are a secret agent breaking into a " << Difficulty;
    std::cout << " secure server room..\n" << "Enter the correct code to conitnue...\n\n";
}

int main()
{    
    srand(time(NULL)); //create new random sequence based on time of day

    int LevelDifficulty = 1;
    const int MaxDifficulty = 5;
    while(LevelDifficulty <= MaxDifficulty) // Loop game until all levels are completed
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear(); //Clears any errors
        std::cin.ignore(); //Discards the buffer
        
        if (true == bLevelComplete)
        {
            //increase the level difficulty
            ++LevelDifficulty;
        }
        //std::cin.get();
    }
    std::cout << "\n*** Great work agent! You got all the files! Now get out of here! ***\n";
    return 0;
}