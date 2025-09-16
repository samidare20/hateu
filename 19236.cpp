#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef struct shark
{
    pair<int,int> position;
    int number;
    int direction;
    bool alive;
};
const pair<int,int> moves[9]={
    {99,99},{-1,0},{-1,-1},
    {0,-1},{1,-1},{1,0},
    {1,1},{0,1},{-1,1}
};
bool shark_cmp(shark a,shark b)
{
    return a.number<b.number;
}
void pb(vector<vector<shark>>board)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(board[i][j].alive==false)
                cout<<"0 ";
            else
                cout<<board[i][j].number<<" ";
        }
        cout<<"\n";
    }
}
vector<vector<shark>> move_fish(vector<vector<shark>>board,vector<shark> shark_board,int x,int y)
{
    for(shark i:shark_board)
        cout<<i.number<<" "<<i.position.first<<" "<<i.position.second<<"\n";
    for(shark i : shark_board)
    {
        if(i.alive==false)
            continue;
        int count=0;
        while(count<8)
        {
            int Y=i.position.first+moves[i.direction].first;
            int X=i.position.second+moves[i.direction].second;
            if(!(X<0||Y<0||X>=4||Y>=4||(Y==y&&X==x)))
            {
                shark tmp=board[Y][X];
                board[Y][X]=board[i.position.first][i.position.second];
                board[i.position.first][i.position.second]=tmp;
                cout<<"changed "<<board[Y][X].number<<" "<<board[i.position.first][i.position.second].number<<"\n";

                pair<int,int> a=board[Y][X].position;
                board[Y][X].position=board[i.position.first][i.position.second].position;
                board[i.position.first][i.position.second].position=board[Y][X].position;
                
                board[Y][X].direction=i.direction;
                
                pb(board);
                
                break;
            }
            i.direction=(i.direction+1)%9;
            // board[i.position.first][i.position.second].direction=(board[i.position.first][i.position.second].direction+1)%9;
            count++;
        }
    }
    return board;
}
void solv(vector<vector<shark>> board,vector<shark> shark_board,int x,int y,int direction,int ans)
{
    
    board=move_fish(board,shark_board,x,y);
    pb(board);

    // while(x<4&&y<4&&x>=0&&y>=0)
    // {
    //     x+=moves[direction].second;
    //     y+=moves[direction].first;
    //     if(!(x<4&&y<4&&x>=0&&y>=0))
    //         break;
        
    // }
}
int main()
{
    vector<shark> shark_board;
    vector<vector<shark>> board(4,vector<shark>(4));
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            shark a;
            cin>>a.number>>a.direction;
            a.alive=true;
            board[i][j]=a;
            a.position={i,j};
            shark_board.push_back(a);
        }
    }
    sort(shark_board.begin(),shark_board.end(),shark_cmp);
    board[0][0].alive=false;
    solv(board,shark_board,0,0,board[0][0].direction,board[0][0].number);
}