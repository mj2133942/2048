#include"declaration.h"

void DF::GotoXY(int x,int y)
{
    COORD C;

    C.X=x;
    C.Y=y;
    SetConsoleCursorPosition(g_HndOut,C);
}

void DF::GotoXY(COORD crd)
{
    SetConsoleCursorPosition(g_HndOut,crd);
}

void DF::HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO cci;

    cci.dwSize=100;
    cci.bVisible=FALSE;
    SetConsoleCursorInfo(g_HndOut,&cci);
}

void DF::SetColor(int text,int _back)
{
    SetConsoleTextAttribute(g_HndOut,text+16*_back);
}

void DF::ClearConsoleScreen()
{
    DWORD dw;

    FillConsoleOutputCharacter(g_HndOut,' ',300*300,{0,0},&dw);
}

template<typename _2DVec>
void InitVec(_2DVec& TrgVec,size_t ys,size_t xs)
{
    TrgVec.resize(ys);

    for(auto &a:TrgVec)
    {
        a.resize(xs);

        for(auto b:a) b=0;
    }
}

bool IsV2dFull(v2d Map)
{
    int cnt=0;
    for(auto a:Map) for(auto b:a) cnt+=(int)(bool)b; ///���� ��ã���� Ȯ��
    return (int)(Map.size()*Map[0].size())==cnt;
}

inline int rnd2o4()
{
    return ((rand()%2)+1)*2;
}

void RandNumGen(v2d& Map)
{
    pair<int,int> tpir;
    if(IsV2dFull(Map)) return; ///�� á���� ����
    else
    {
        while(1)
        {
            tpir.first=rand()%4;
            tpir.second=rand()%4;

            if(!Map[tpir.first][tpir.second])
            {
                Map[tpir.first][tpir.second]=rnd2o4();
                return;
            }
        }
    }
}

void UpdateScreen(v2d Map)
{
    int i,j,MaxD=numeric_limits<int>::min();
    static pair<string,int> out("%3d",2);
    char tchs[100]="%\0";

    DF::ClearConsoleScreen();
    DF::GotoXY(0,0);

    for(auto a:Map) for(auto b:a) MaxD=max(MaxD,int(to_string(b).length()));
    if(MaxD>out.second) out=make_pair(string(strcat(strcat(tchs,to_string(MaxD+1).c_str()),"d")),MaxD);
    for(i=0;i<Map.size();i++)
    {
        for(j=0;j<Map[i].size();j++) printf(out.first.c_str(),Map[i][j]);
        for(j=0;j<out.second/2;j++) puts("\n");
    }
}

bool IsntGameOver(v2d Map)
{
    int i,j,cnt=0,cntB=0,cntC=0;
    for(auto a:Map) for(auto b:a) cnt+=(int)(bool)b;
    if(cnt==Map.size()*Map[0].size()) return true;
    else
    {
        for(i=0;i<Map.size();i++)
        {
            for(j=0;j<Map[i].size();j++)
            {
                cnt+=(i?(int)(Map[i-1][j]==Map[i][j]):0)+
                     (j?(int)(Map[i][j-1]==Map[i][j]):0)+
                     ((i+1<Map.size())?(int)(Map[i+1][j]==Map[i][j]):0)+
                     ((j+1<Map[i].size())?(int)(Map[i][j+1]==Map[i][j]):0);
            }
        }
        return !(bool)(cnt);
    }
    return -1;
}

void MoveS(v2d& Map)
{
    int i,j,l,tmp;
    bool flag;

    char str[100]={0};
    v2b chk;
    for(i=Map.size()-1;i>=0;i--)
    {
        for(j=0;j<Map[i].size();j++)
        {
            if(i+1==Map.size() || !Map[i][j] || chk[l][j]) continue;
            else
            {
                l=i+1;  ///l�� ������ ���ڰ� �ִ� ��ġ

                while(l<Map.size() && !Map[l][j]) l++;
                if(l==Map.size()) swap(Map[l-1][j],Map[i][j]);///�� ������ �� ��� ���ڸ� �ٲ۴�.
                else if(Map[l][j]!=Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� �ٸ� ��� ���� ��ġ���� �ٷ� ������ �����ش�.
                {
                    tmp=Map[i][j];
                    Map[i][j]=0;
                    Map[l-1][j]=tmp;
                }
                else if(Map[l][j]==Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� ���� ���
                {
                    Map[l][j]*=2;
                    chk[l][j]=true;
                    Map[i][j]=0;
                }
            }
        }
    }
}

void MoveW(v2d& Map)
{
    int i,j,l,tmp;
    bool flag;
    char str[100]={0};
    for(i=0;i<Map.size();i++)
    {
        for(j=0;j<Map[i].size();j++)
        {
            if(!i || !Map[i][j]) continue;
            else
            {
                l=i-1;  ///l�� ������ ���ڰ� �ִ� ��ġ

                while(l>=0 && !Map[l][j]) l--;
                if(l==-1) swap(Map[l+1][j],Map[i][j]);///�� ������ �� ��� ���ڸ� �ٲ۴�.
                else if(Map[l][j]!=Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� �ٸ� ��� ���� ��ġ���� �ٷ� ������ �����ش�.
                {
                    tmp=Map[i][j];
                    Map[i][j]=0;
                    Map[l+1][j]=tmp;
                }
                else if(Map[l][j]==Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� ���� ���
                {
                    Map[l][j]*=2;
                    Map[i][j]=0;
                }
            }
        }
    }
}

void MoveA(v2d& Map)
{
    int i,j,l,tmp;
    bool flag;
    char str[100]={0};
    for(i=0;i<Map.size();i++)
    {
        for(j=0;j<Map[i].size();j++)
        {
            if(!Map[i][j]) continue;
            else
            {
                l=j-1;  ///l�� ������ ���ڰ� �ִ� ��ġ

                while(l>=0 && !Map[i][l]) l--;
                if(l==-1) swap(Map[i][0],Map[i][j]);///�� ������ �� ��� ���ڸ� �ٲ۴�.
                else if(Map[i][l]!=Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� �ٸ� ��� ���� ��ġ���� �ٷ� ������ �����ش�.
                {
                    tmp=Map[i][j];
                    Map[i][j]=0;
                    Map[i][l+1]=tmp;
                }
                else if(Map[i][l]==Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� ���� ���
                {
                    Map[i][l]*=2;
                    Map[i][j]=0;
                }
            }
        }
    }
}

void MoveD(v2d& Map)
{
    int i,j,l,tmp;
    bool flag;
    char str[100]={0};
    for(i=0;i<Map.size();i++)
    {
        for(j=Map[i].size();j>=0;j--)
        {
            if(j+1==Map.size() || !Map[i][j]) continue;
            else
            {
                l=j+1;  ///l�� ������ ���ڰ� �ִ� ��ġ

                while(l<Map.size() && !Map[i][l]) l++;
                if(l==Map.size()) swap(Map[i][l-1],Map[i][j]);///�� ������ �� ��� ���ڸ� �ٲ۴�.
                else if(Map[i][l]!=Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� �ٸ� ��� ���� ��ġ���� �ٷ� ������ �����ش�.
                {
                    tmp=Map[i][j];
                    Map[i][j]=0;
                    Map[i][l-1]=tmp;
                }
                else if(Map[i][l]==Map[i][j])///�߰��� ã�� ���� ���� ��ġ�� ���� ���� ���
                {
                    Map[i][l]*=2;
                    Map[i][j]=0;
                }
            }
        }
    }
}

int GetDir()
{
    BYTE ch=getch();
    if(isalpha(ch))
    {
        if(islower(ch)) ch-=(int)('a'-'A');
        switch(ch)
        {
            case 'S':
                return 0;
            case 'W':
                return 1;
            case 'A':
                return 2;
            case 'D':
                return 3;
        }
    }
    else if(ch==ARROW_FIRST)
    {
        ch=getch();

        switch(ch)
        {
            case ARROW_DOWN:
                return 0;
            case ARROW_UP:
                return 1;
            case ARROW_LEFT:
                return 2;
            case ARROW_RIGHT:
                return 3;
        }
    }
    return -1;
}

void StartGame(COORD ArraySize)
{
    v2d MapArray,tMap/*�׺���̼� �ƴ�*/;
    vector<vector<int>>::iterator vit;
    void (*fpArr[])(v2d&)={MoveS,MoveW,MoveA,MoveD};
    int i,tmp,cnt=0;


    DF::ClearConsoleScreen();
    srand(time(NULL));
    MapArray.resize(ArraySize.X);

    for(i=0;i<ArraySize.X;i++) MapArray[i].resize(ArraySize.Y);
    RandNumGen(MapArray);
    RandNumGen(MapArray);
    UpdateScreen(MapArray);
    //MapArray[0][0]=1024;
    // a ㅇㄴㅁ
    while(true)
    {
        if((tmp=GetDir())==-1) continue;
        else
        {
            if(IsV2dFull(MapArray))
            {
                tMap=MapArray;
                fpArr[tmp](tMap);
                vit=tMap.begin();

                for(auto a:MapArray)
                {
                    if(equal(a.begin(),a.end(),(*vit).begin())) cnt++;
                    ++vit;
                }
                if(MapArray.size()==cnt) continue;
            }
            fpArr[tmp](MapArray);
            if(IsntGameOver(MapArray)) break;

            RandNumGen(MapArray);
            UpdateScreen(MapArray);
            Beep(80,5);
        }
    }
    // a
    return;
}

void PrintStartScreen()
{
    char ch;
    COORD tcrd;

    DF::GotoXY(10,5);
    DF::HideConsoleCursor();
    SetConsoleTitleA("Game Project 2048 | Made by et5_2");
    printf("Press \'S\'to start or \'E\'to exit the game.");

    while(true)
    {
        ch=getch();

        if(ch=='S' || ch=='s')
        {
            tcrd.X=4;
            tcrd.Y=4;
            StartGame(tcrd);

            break;
        }
        if(ch=='E' || ch=='e')
        {
            DF::ClearConsoleScreen();
            break;
        }
    }
}

int main(void)
{
    PrintStartScreen();

    return 0;
}
