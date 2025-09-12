#include<iostream>
#include<vector>
#include<queue>

using namespace std;

typedef struct shark
{
    pair<int,int> position;
    int fast;
    int direction; //1:u 2:d 3:r 4:l
    int size;
};
int height,width;
int board[111][111];
int shark_many;
vector<shark> board_shark;
void input()
{
    cin>>height>>width>>shark_many;

    for(int i=0;i<shark_many;i++)
    {
        int a,b,c,e,d;
        cin>>a>>b>>c>>d>>e;

        board_shark.push_back({{a,b},c,d,e});
        board[a][b]=board_shark.size();
    }
}
void catch_shark(int x)
{
    for(int i=0;i<height;i++)
    {
        if(board[i][x]!=0)
        {
            board_shark[board[i][x]-1].position={-1,-1};
            board[i][x]=0;
        }
    }
}
void move_shark()
{
    for(auto i : board_shark)
    {
        if(i.position.first==-1)
            continue;

    }
}
void solv()
{
    for(int catch_x=0;catch_x<width;catch_x++)
    {
        catch_shark(catch_x);

    }
}
int main()
{
    input();
    solv();
}