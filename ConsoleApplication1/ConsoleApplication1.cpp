#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

enum EnChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum EnWinner { Playar = 1, Computer = 2, Draw = 3 };

struct StRoundInfo
{
    int Rounds = 0;
    EnChoice PlayarChoice;
    EnChoice ComputerChoice;
    EnWinner Winner;
    string WinnerNameRound = "";
    string ChoiceComputerName = "";
    string ChoicePlayarName = "";
};

struct StResult
{
    int GameRound = 0;
    int Playar1WonTimes = 0;
    int Computer1WonTimes = 0;
    int DrawTimes = 0;
    EnWinner FinelWinner;
    string F_WinnerName = "";
};

int RandNumber(int From, int To)
{
    int RandNumber = rand() % (To - From + 1) + From;
    return RandNumber;
}

int ReadHowManyRounds()
{
    int Rounds = 0;
    do
    {
        cout << "How Many Rounds 1 to 10 ?";
        cin >> Rounds;

    } while (Rounds < 1  || Rounds > 10);

    return Rounds;
}

EnChoice ReadPlayarChoice()
{
    int Choice = 0;
    do
    {
        cout << "\nYour Choice : [1]:Stone, [2]:Paper, [3]:Scissors ?\n";
        cin >> Choice;

    } while (Choice < 1  || Choice > 3);

    return (EnChoice)Choice;
}

EnChoice GetComputerChoice()
{
    return (EnChoice)RandNumber(1, 3);
}

EnWinner WhoWonTheRound(StRoundInfo RoundInfo)
{
   
        if (RoundInfo.PlayarChoice == RoundInfo.ComputerChoice)
        {
            return EnWinner::Draw;
        }

        switch (RoundInfo.PlayarChoice)
        {
        case Stone:
            if (RoundInfo.ComputerChoice == EnChoice::Paper)
                return EnWinner::Computer;
            else
                return EnWinner::Playar;

        case Paper:
            if (RoundInfo.ComputerChoice == EnChoice::Scissors)
                return EnWinner::Computer;
            else
                return EnWinner::Playar;

        case Scissors:
            if (RoundInfo.ComputerChoice == EnChoice::Stone)
                return EnWinner::Computer;
            else
                return EnWinner::Playar;
        }


}

string WinnerName(EnWinner Winner)
{
    string Arr[3] = { "Playar" , "Computer" , "[No Winner]" };
    return Arr[Winner - 1];
}

string ChoiceName(EnChoice Choice)
{
    string Arr[3] = { "Stone" , "Paper" , "Scissors" };
    return Arr[Choice - 1];
}

void GetColor(EnWinner Winner)
{
    switch (Winner)
    {
    case Playar:
        system("color 2F");
        break;
    case Computer:
        system("color 4F");
        cout << '\a';
        break;
    case Draw:
        system("color 6F");
        break;
    }
}

void PrintTheRoundInfo(StRoundInfo RoundInfo)
{
    cout << "\n_______________Round [" << RoundInfo.Rounds << "] begins:_________\n\n";
    cout << "Playar Choice       : " << RoundInfo.ChoicePlayarName << endl;
    cout << "Computer Choice     : " << RoundInfo.ChoiceComputerName << endl;
    cout << "Round Winner        : " << RoundInfo.WinnerNameRound << endl;
    cout << "\n___________________________________________\n";
    GetColor(RoundInfo.Winner);

}

EnWinner WhoWonTheFinelWinner(StResult Result)
{
    if (Result.Computer1WonTimes > Result.Playar1WonTimes)
    {
        system("color 4F");
        return EnWinner::Computer;
    }

    else if (Result.Computer1WonTimes < Result.Playar1WonTimes)
    {
        system("color 4F");
        return EnWinner::Playar;
    }
    else
    {

        system("color 6F");
        return EnWinner::Draw;
    }
}

StResult FullTheReslt(int& HowManyRound, int& CountComuter, int& CountPlayar, int& CountDraw)
{
    StResult Result;
    Result.GameRound = HowManyRound;
    Result.Computer1WonTimes = CountComuter;
    Result.Playar1WonTimes = CountPlayar;
    Result.DrawTimes = CountDraw;
    Result.FinelWinner = WhoWonTheFinelWinner(Result);

    return Result;
}
StResult PlayGame(int HowManyRound)
{
    StRoundInfo RoundInfo;

    int CountComuter = 0;
    int CountPlayar = 0;
    int CountDraw = 0;

    for (int i = 1; i <= HowManyRound; i++)
    {
        RoundInfo.Rounds = i;
        RoundInfo.PlayarChoice = ReadPlayarChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerNameRound = WinnerName(RoundInfo.Winner);
        RoundInfo.ChoiceComputerName = ChoiceName(RoundInfo.ComputerChoice);
        RoundInfo.ChoicePlayarName = ChoiceName(RoundInfo.PlayarChoice);

        PrintTheRoundInfo(RoundInfo);if (RoundInfo.Winner == EnWinner::Computer)
            CountComuter++;
        else if (RoundInfo.Winner == EnWinner::Playar)
            CountPlayar++;
        else
            CountDraw++;
    }

    return FullTheReslt(HowManyRound, CountComuter, CountPlayar, CountDraw);

}

void RestartGame()
{
    system("color 0F");
    system("cls");
}

string Space(int T)
{
    string S1 = "";
    for (int i = 1; i <= T; i++)
    {
        S1 = S1 + "\t";
    }
    return S1;
}

void PrintMassge()
{
    cout << Space(6) << "\n\n\n___________________________________________________________\n";
    cout << Space(6) << "\n  +++G A M E      O V E R+++                 \n";
    cout << Space(6) << "\n___________________________________________________________\n";
}

void PrintResultGame(StResult Result)
{
    cout << Space(6) << "\n\n\n\n Game Rounds                     : " << Result.GameRound;
    cout << Space(6) << "\n\n Playar1 Won Times               : " << Result.Playar1WonTimes;
    cout << Space(6) << "\n\n Computer1 Won Times             : " << Result.Computer1WonTimes;
    cout << Space(6) << "\n\n Draw Times                      : " << Result.DrawTimes;
    cout << Space(6) << "\n\n Finel Winner                    : " << WinnerName(Result.FinelWinner) << endl << endl;
}


void StartGame()
{
    bool IsTrue = 0;

    do
    {
        RestartGame();
        StResult Result = PlayGame(ReadHowManyRounds());
        PrintMassge();
        PrintResultGame(Result);

        cout << "Do You Want Play Again ? [0]:No [1]:Yes ? \n";
        cin >> IsTrue;

    } while (IsTrue == 1);

}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();
}