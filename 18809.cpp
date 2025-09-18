#include<iostream>
#include <bits/stdc++.h>
using namespace std;
int height,width,count_green,count_red;
int board[55][55];
vector<pair<int,int>> plant_tile;
typedef struct board_tile
{
    char color='!';
    int turn;
};
int bfs()
{
    const int movex[4]={0,0,1,-1};
    const int movey[4]={1,-1,0,0};
    queue<pair<int,int>> q;
    board_tile visit[55][55];

    for(auto i:plant_tile)
    {
        q.push(i);
        visit[i.first][i.second].turn=0;
        if(board[i.first][i.second]==8)
            visit[i.first][i.second].color='G';
        else if(board[i.first][i.second]==9)
            visit[i.first][i.second].color='R';
    }
    // for(int i=0;i<height;i++)
    // {
    //     for(int j=0;j<width;j++)
    //         cout<<board[i][j]<<" ";
    //     cout<<"\n";
    // }
    // return 0;
    while(!q.empty())
    {
        auto a=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            int X=movex[i]+a.second;
            int Y=movey[i]+a.first;
            if(X<0||Y<0||X>=width||Y>=height||board[Y][X]==0)
                continue;
            char color_now;
            if(board[a.first][a.second]==8)
                color_now='G';
            else if(board[a.first][a.second]==9)
                color_now='R';

            if(visit[Y][X].color=='!')
            {
                if(board[a.first][a.second]==8)
                    visit[Y][X].color='G';
                else if(board[a.first][a.second]==9)
                    visit[Y][X].color='R';
                visit[Y][X].turn=visit[a.first][a.second].turn+1;
                q.push({Y,X});
            }
            else if(visit[Y][X].color==color_now)
                continue;
            else
            {
                
            }

        }
    }
}
void solv(int remain_green,int remain_red)
{
    cout<<remain_green<<" "<<remain_red<<"\n";
    if(remain_green==0&&remain_red==0)
    {
        bfs();
    }
    for(auto i :plant_tile)
    {
        if(board[i.first][i.second]!=2)
            continue;
        // cout<<i.first<<" "<<i.second<<"iiiiiiiiiii\n";
        if(remain_green>0)
        {
            int tmp=board[i.first][i.second];
            board[i.first][i.second]=8;
            solv(remain_green-1,remain_red);
            board[i.first][i.second]=tmp;
        }
        if(remain_red>0)
        {
            int tmp=board[i.first][i.second];
            board[i.first][i.second]=9;
            solv(remain_green,remain_red-1);
            board[i.first][i.second]=tmp;
        }
    }

}
int main()
{
    cin>>height>>width>>count_green>>count_red;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            cin>>board[i][j];
            if(board[i][j]==2)
            {
                plant_tile.push_back({i,j});
            }
        }
    }
    for(auto i:plant_tile)
    {
        if(count_green>0)
        {
            int tmp=board[i.first][i.second];
            board[i.first][i.second]=8;
            solv(count_green-1,count_red);
            board[i.first][i.second]=tmp;
        }
        if(count_red>0)
        {
            int tmp=board[i.first][i.second];
            board[i.first][i.second]=9;
            solv(count_green,count_red-1);
            board[i.first][i.second]=tmp;
        }
    }
    
}
