#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility> 

using namespace std;

int Tit_for_tat(list<int> a, int iter)
{
    if(iter==0)
    return 1;
    else
    return a.back();
}
int Du(list<int> a, int iter)
{
    return 0;
}
int Cu(list<int> a, int iter)
{
    return 1;
}
int p(list<int> a, int iter)
{
    return 1;
}

class Strategy
{
private:

    string Name="Default"; 
    int Score=0;
    list <int> memory;
    int counter=0;

public:

    int (*Turn) (list<int> a, int b);
    void Set_Name(string NewName)
    {
        Name=NewName;
    }

    void AddCounter()
    {
        counter+=1;
    }

    void AddMemory(int OppDecision)
    {
        memory.push_back(OppDecision);
    }

    void AddScore(int number)
    {
        Score+=number;
    }
    
    int Make_Turn()
    {
        return Turn(memory, counter);
    }
    int GetScore()
    {
        return Score;
    }
    void GetName()
    {
        cout<<Name<<endl;
    }
};


vector<int>  Dilem(int FP, int SP)
{
     vector<int> Answer;
    if  (FP==0 and SP==0)
    {
        Answer={3,3};
        return Answer;
    }
    if  (FP==1 and SP==1)
    {
        Answer={5,5};
        return Answer;
    }
    if (FP==1 and SP==0)
    {
        Answer={0,10};
        return Answer;
    }
    if (FP==0 and SP==1)
    {
        Answer={10,0};
        return Answer;
    }
    cout<<"Ooops - impossible turn, look up for mistake, my dear!\n";
    system("pause");
    return Answer;
}

void Game(Strategy FirstPlayer, Strategy SecondPlayer)
{
    int FirstPlayerD;
    int SecondPlayerD;
    vector<int> answer;
    for(int i=0;i<10;i++)
    {
        FirstPlayerD=FirstPlayer.Make_Turn(); //Decisiones are made
        SecondPlayerD=SecondPlayer.Make_Turn();//
        FirstPlayer.AddMemory(SecondPlayerD);//Decisiones are remembered
        SecondPlayer.AddMemory(FirstPlayerD);
        answer=Dilem(FirstPlayerD,SecondPlayerD);
        FirstPlayer.AddScore(answer[0]);//Score is gained - game is over 
        SecondPlayer.AddScore(answer[1]);//Score is gained - game is over
        FirstPlayer.AddCounter();
        SecondPlayer.AddCounter();
        cout<<i<<" \t "<<answer[0]<<" \t "<<answer[1]<<endl;
    }
    if(FirstPlayer.GetScore()!=SecondPlayer.GetScore())
    {
        if (FirstPlayer.GetScore()>SecondPlayer.GetScore())
        {
            cout<<"Winner is First Player with Score "<<FirstPlayer.GetScore()<<endl;
            FirstPlayer.GetName();
        }
        else 
        {
            cout<<"Winner is Second Player With Score "<<SecondPlayer.GetScore()<<endl;
            SecondPlayer.GetName();
        }
    }
    else
    cout<<"No winners in this Game"<<endl;
}

int main()
{   
    Strategy TFT, DU, CU;
    TFT.Set_Name("Tit-for-Tate");
    DU.Set_Name("Traitor");
    CU.Set_Name("Cooperator");
    TFT.Turn=Tit_for_tat;
    DU.Turn=Du;
    CU.Turn=Cu;
    cout<<"Let's Play!\n";
    Game(TFT,DU);
    Game(TFT,CU);
}
