#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <utility> 
#include <ctime>
#include <fstream>

using namespace std;

int Tit_for_tat(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter, int & trigger)
{
    if(iter==0)
    return 1;
    else
    return OpponentTurn[iter-1];
}

int Pavlov(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter, int & trigger)
{
    if (iter==0)
    {
        return 1;
    }
    else 
    {
    if(MyTurn[iter-1]==OpponentTurn[iter-1])
    {
        return 1;
    }
    else 
        return 0;
    }
}

int Master(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter, int & trigger)
{
    vector<int> CodeWord={1,0,1,1,0,0,1};
    if(iter!=0 and iter<CodeWord.size()+1)
    {
        if(CodeWord[iter-1]!=OpponentTurn[iter-1])
        {
            //cout<<"What i See?"<<endl;
            //cout<<CodeWord[iter-1]<<"\t"<<OpponentTurn[iter-1]<<"\t"<<iter<<endl;
            trigger++;
        }
    }
    if(iter<CodeWord.size())
    {
        return CodeWord[iter];
    }
    else
    {
    if(trigger)
    {
        return Tit_for_tat(MyTurn, OpponentTurn, iter, trigger);
    }
    else
        return 0;
    }
}

int Slave(vector<int>& MyTurn, vector<int> &OpponentTurn, int iter, int & trigger)
{
    vector<int> CodeWord={1,0,1,1,0,0,1};
    if(iter!=0 and iter<CodeWord.size()+1)
    {
        if(CodeWord[iter-1]!=OpponentTurn[iter-1])
        {
            //cout<<"What i See?"<<endl;
            //cout<<CodeWord[iter-1]<<"\t"<<OpponentTurn[iter-1]<<"\t"<<iter<<endl;
            trigger++;
        }
    }
    if(iter<CodeWord.size())
    {
        return CodeWord[iter];
    }
    else
    {
    if(trigger)
    {
        return 0;
    }
    else
        return 1;
    }
}

int Grimm(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter, int & trigger)
{
    if(iter!=0 and OpponentTurn[iter-1]==0)
        trigger++;
    if(trigger==0)
    return 1;
    else 
    return 0;
}

int SoftMajor(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter, int & trigger)
{
    if(iter==0)
    return 0;
    else
    {
    if(OpponentTurn[iter-1]==0)
    {
        trigger++;
    }
    else
        trigger--;
    if(trigger>0)
        return 0;
    else
        return 1;
    }
}

int HardtMajor(vector<int>& MyTurn, vector<int> &OpponentTurn, int iter, int & trigger)
{
    if(iter==0)
    return 1;
    else
    {
    if(OpponentTurn[iter-1]==0)
    {
        ++trigger;
    }
    else
        --trigger;
    if(trigger>=0)
        return 0;
    else
        return 1;
    }
}

int Suspicious_Tit_for_tat(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter,int & trigger)//Check
{
    if(iter==0)
    return 0;
    else
    return OpponentTurn[iter-1];
}

int Generous_Tit_for_tat(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter,int & trigger)
{
    if(iter==0)
    return 1;
    else
    {
        if(OpponentTurn[iter-1]==1)
        return 1;
        else
        {
            if(rand()%100<33)
            return 1;
            else 
            return 0;
        }
    }
}

int Inperfect(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter, int & trigger)
{
    int chance=rand()%100;
    if(iter==0)
    return 1;
    else
    {
        if (chance<90)
        {
            return OpponentTurn[iter-1];
        }
        else
            return 1-OpponentTurn[iter-1];
        
    }
}

int Tit_for_Two_Tats(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter,int & trigger)
{
    if(iter==0 or iter==1)
    return 1;
    else
    {
        if(OpponentTurn[iter-1]==0 and OpponentTurn[iter-2]==0)
        return 0;
        else 
        return 1;
    }
}

int Du(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter,int & trigger)
{
    return 0;
}

int Cu(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter,int & trigger)
{
    return 1;
}

int p(vector<int> & MyTurn, vector<int> & OpponentTurn, int iter,int & trigger)
{
    if(rand()%2==0)
    return 0;
    else
    return 1;
}

class Strategy
{
private:

    string Name="Default"; 
    int Score=0;
    int counter=0;
    int trigger=0;
public:

    int (*Turn) (vector<int>& MyTurn, vector<int> &OpponentTurn, int b, int & trigger);

    void Set_Name(string NewName)
    {
        Name=NewName;
    }

    void SetCounter(int i)
    {
        counter=i;
    }

    void AddScore(int number)
    {
        Score+=number;
    }
    
    int Make_Turn(vector<int>& MyTurn, vector<int> &OpponentTurn, int & Trigger)
    {
        return Turn(MyTurn, OpponentTurn, counter, Trigger);
    }

    int GetScore()
    {
        return Score;
    }

    void GetName()
    {
        cout<<Name<<endl;
    }

    void Zero()
    {
        counter=0;
        trigger=0;
    }
    void ToTrig()
    {
        trigger++;
    }

    Strategy operator&= (Strategy a)
    {
        this->Name=a.Name;
        this->Score=a.Score;
        this->Turn=a.Turn;
        return *this;
    }
    void Reset()
    {
        Score=0;
    }
    string NameR()
    {
        return Name;
    }
    
};


vector<int>  Dilem(int FP, int SP)
{
     vector<int> Answer;
    if  (FP==0 and SP==0)
    {
        Answer={1,1};
        return Answer;
    }
    if  (FP==1 and SP==1)
    {
        Answer={3,3};
        return Answer;
    }
    if (FP==1 and SP==0)
    {
        Answer={0,5};
        return Answer;
    }
    if (FP==0 and SP==1)
    {
        Answer={5,0};
        return Answer;
    }
    cout<<"Ooops - impossible turn, look up for mistake, my dear!\n";
    system("pause");
    return Answer;
}

void Game(Strategy& FirstPlayer, Strategy& SecondPlayer)
{
    vector<int> Right(200);
    vector<int> Left(200);
    int TriggerR=0;
    int TriggerL=0;
    vector<int> answer;
    for(int i=0;i<200;i++)
    {
        Right[i]=FirstPlayer.Make_Turn(Right, Left, TriggerR); //Decisiones are made
        Left[i]=SecondPlayer.Make_Turn(Left, Right, TriggerL);//
        //Decisiones are remembered
        answer=Dilem(Right[i],Left[i]);
        FirstPlayer.AddScore(answer[0]);//Score is gained - game is over 
        SecondPlayer.AddScore(answer[1]);//Score is gained - game is over
        FirstPlayer.SetCounter(i+1);
        SecondPlayer.SetCounter(i+1);
        //cout<<i<<" \t "<<answer[0]<<" \t "<<answer[1]<<endl;
        //cout<<i<<" \t "<<Right[i]<<" \t "<<Left[i]<<endl;
    }
    FirstPlayer.Zero();
    SecondPlayer.Zero();
    //cout<<FirstPlayer.GetScore()<<"\t"<<SecondPlayer.GetScore()<<endl;
    /*
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
    */
}
void NoisyGame(Strategy& FirstPlayer, Strategy& SecondPlayer)
{
    vector<int> Right(200);
    vector<int> Left(200);
    int TriggerR=0;
    int TriggerL=0;
    vector<int> answer;
    int NoiseR, NoiseL;
    for(int i=0;i<200;i++)
    {

        Right[i]=FirstPlayer.Make_Turn(Right, Left, TriggerR); //Decisiones are made
        Left[i]=SecondPlayer.Make_Turn(Left, Right, TriggerL);//

        NoiseR=rand()%20;
        NoiseL=rand()%20;

        if(NoiseR==1)
        {
            Right[i]=1-Right[i];
        }
        if(NoiseL==1)
        {
            Left[i]=1-Left[i];
        }
        //Decisiones are remembered
        answer=Dilem(Right[i],Left[i]);
        FirstPlayer.AddScore(answer[0]);//Score is gained - game is over 
        SecondPlayer.AddScore(answer[1]);//Score is gained - game is over
        FirstPlayer.SetCounter(i+1);
        SecondPlayer.SetCounter(i+1);
        //cout<<i<<" \t "<<answer[0]<<" \t "<<answer[1]<<endl;
        //cout<<i<<" \t "<<Right[i]<<" \t "<<Left[i]<<endl;
    }
    FirstPlayer.Zero();
    SecondPlayer.Zero();
    //cout<<FirstPlayer.GetScore()<<"\t"<<SecondPlayer.GetScore()<<endl;
    /*
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
    */
}
void SimpleTournament(vector<Strategy> & Set, int S)
{
    if(S<=Set.size())
    for(int i = 0 ; i < S ; i++)
        {
            for(int j = i; j < S ; j++)
            {
                Game(Set[i],Set[j]);
            }
        }
    else
    cout<<"To play more than availabe"<<endl;
}
void FindLoser(vector<Strategy> & Set, int ToLook, string path)
{
    ofstream out(path, ios::app);
    int m=10000, nm=10000;
    int remember=-1;
    if( Set.size() < ToLook )
    {
        cout<<"You"<<endl;
    }
    else
    {
        Strategy Tempo;
        for(int i=0; i<ToLook;i++)
        {
        nm=min(m, Set[i].GetScore());
            if(nm!=m)
            {
                m=nm;
                remember=i;
            }
        }
        out<<"Strategy with lowest score\t"<<Set[remember].NameR()<<"\t"<<m<<endl;
        Tempo=Set[remember];
        Set[remember]=Set[ToLook-1];
        Set[ToLook-1]=Tempo;
    }
}
void SeveralTournament(vector<Strategy> Set, int Number, int Rounds, string path, string ForWorste)
{
    ofstream out(path, ios::app);
    vector<vector<int> > Results (Number, vector<int> (Rounds));
    int summ;
    for (size_t i = 0; i < Rounds; i++)
    {
        SimpleTournament(Set, Number);
        for (size_t j = 0; j < Number; j++)
        {
            Results[j][i]=Set[j].GetScore();
            Set[j].Reset();
        }
    }
    for(int i=0;i<Number;i++)
    {
        out<<Set[i].NameR()<<"\t";
        for (size_t j = 0; j < Rounds; j++)
        {
            out<<Results[i][j]<<"\t";
        }
        out<<endl;
    }
    for(int i=0;i<Number;i++)
    {
        out<<Set[i].NameR()<<"\t";
        for (size_t j = 0; j < Rounds; j++)
        {
            summ+=Results[i][j];   
        }
        out<<summ/Rounds<<"\t"<<summ/(Rounds*(Number+1)*200.0)<<endl;
        summ=0;
    }
    
}
void EvolutionTournament(vector<Strategy> Set, int Tostay, string path)
{
    //vector<vector<pair<string, int> > > FuckedMemory;
    ofstream out(path, ios::app);
    int Totall=Tostay;
    for(;Tostay>1;--Tostay)
    {
    SimpleTournament(Set, Tostay);
    FindLoser(Set, Tostay, "Lost.txt");
        for(int i=0;i<Totall;i++)
        {
            out<<"\t"<<Set[i].NameR()<<"\t"<<Totall-Tostay<<"\t"<<"["<<Set[i].GetScore()/(200.0*(Tostay+1))<<"]"<<"\t"<<Set[i].GetScore()/(Tostay+1)<<"\t"<<endl;
            Set[i].Reset();
        }
    }
}
int main()
{   
    srand((unsigned)time(0)); 
    vector<Strategy> Set(16);
    Strategy TFT, DU, CU, Random, ImpTFT, TFTT, WSLS, GTFT, STFT, GR, HMAJ, SMAJ, MA, SL;
    TFT.Set_Name("Tit-for-Tat");
    DU.Set_Name("Traitor");
    CU.Set_Name("Cooperator");
    ImpTFT.Set_Name("Imperfect Tit-for-Tat");
    Random.Set_Name("Random");
    TFTT.Set_Name("Tit-for-two-Tates");
    WSLS.Set_Name("Pavlov");
    GTFT.Set_Name("Generous");
    STFT.Set_Name("Suspicious Tit-for-Tat");
    GR.Set_Name("Grimm");
    HMAJ.Set_Name("Hard Majority");
    SMAJ.Set_Name("Soft Majority");
    MA.Set_Name("Master");
    SL.Set_Name("Slave");

    TFT.Turn=Tit_for_tat;
    DU.Turn=Du;
    CU.Turn=Cu;
    ImpTFT.Turn=Inperfect;
    Random.Turn=p;
    TFTT.Turn=Tit_for_Two_Tats;
    WSLS.Turn=Pavlov;
    GTFT.Turn=Generous_Tit_for_tat;
    STFT.Turn=Suspicious_Tit_for_tat;
    GR.Turn=Grimm;
    HMAJ.Turn=HardtMajor;
    SMAJ.Turn=SoftMajor;
    MA.Turn=Master;
    SL.Turn=Slave;

    Set[0]=TFT;
    Set[1]=DU;
    Set[2]=CU;
    Set[3]=ImpTFT;
    Set[4]=Random;
    Set[5]=TFTT;
    Set[6]=WSLS;
    Set[7]=GTFT;
    Set[8]=STFT;
    Set[9]=GR;
    Set[10]=HMAJ;
    Set[11]=SMAJ;
    Set[12]=MA;
    Set[13]=SL;
    Set[14]=SL;
    Set[15]=SL;

    int size=20;
    int Toplay=12;

    cout<<"Let's Play!\n";
    cout<<"------------------------"<<endl;
    Game(DU, CU);
    cout<<DU.GetScore();
    //SeveralTournament(Set, 12, 10, "Results.txt", "Worste.txt");
    EvolutionTournament(Set, 12, "EvolCoop.txt");
    /*
    cout<<"Let's Play with Noise!\n";
    cout<<"------------------------"<<endl;
    
    for(int i = 0 ; i < 12 ; i++)
    {
        for(int j = i+1; j < 12 ; j++)
        {
            Game(Set[i],Set[j]);
        }
    }
        for (size_t i = 0; i < 12 ; i++)
    {
            Set[i].GetName();
            out<<"\t"<<Set[i].GetScore()<<"\t"<<endl;
    }
  */
}
