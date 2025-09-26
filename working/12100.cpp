#include<bits/stdc++.h>
using namespace std;
int size_board;
void move_left(vector<vector<int>> &board)
{
    bool combined[22][22]={0,};
    for(int x=1;x<size_board;x++)
    {
        for(int y=0;y<size_board;y++)
        {
            if(board[y][x]==board[y][x-1]) //same block
            {
                if(combined[y][x-1]==true)
                    continue;
                combined[y][x-1]=true;
                board[y][x-1]*=2;
                board[y][x]=0;
            }
            else if(board[y][x-1]==0) //empty
            {
                int tmp=x-1;
                while(tmp>=0&&board[y][tmp]==0)
                    tmp-=1;
                if(tmp<0)
                    board[y][0]=board[y][x];
                else if(board[y][tmp]==board[y][x])
                {
                    if(combined[y][tmp]==true)
                        board[y][tmp+1]=board[y][x];
                    else
                    {
                        combined[y][tmp]=true;
                        board[y][tmp]*=2;
                    }
                }
                else
                    board[y][tmp+1]=board[y][x];
                board[y][x]=0;
            }
            else //other block
            {
                continue;
            }
        }
    }
}
void move_right(vector<vector<int>> &board)
{
    bool combined[22][22]={0,};
    for(int x=size_board-2;x>=0;x--)
    {
        for(int y=0;y<size_board;y++)
        {
            if(board[y][x]==board[y][x+1]) //same block
            {
                if(combined[y][x+1]==true)
                    continue;
                combined[y][x+1]=true;
                board[y][x+1]*=2;
                board[y][x]=0;
            }
            else if(board[y][x+1]==0) //empty
            {
                int tmp=x+1;
                while(tmp<size_board&&board[y][tmp]==0)
                    tmp+=1;
                if(tmp==size_board)
                    board[y][size_board-1]=board[y][x];
                else if(board[y][tmp]==board[y][x])
                {
                    if(combined[y][tmp]==true)
                        board[y][tmp-1]=board[y][x];
                    else
                    {
                        combined[y][tmp]=true;
                        board[y][tmp]*=2;
                    }
                }
                else
                    board[y][tmp-1]=board[y][x];
                board[y][x]=0;
            }
            else //other block
            {
                continue;
            }
        }
    }
}
void move_up(vector<vector<int>> &board)
{
    bool combined[22][22]={0,};
    for(int y=1;y<size_board;y++)
    {
        for(int x=0;x<size_board;x++)
        {
            if(board[y][x]==board[y-1][x]) //same block
            {
                if(combined[y-1][x]==true)
                    continue;
                combined[y-1][x]=true;
                board[y-1][x]*=2;
                board[y][x]=0;
            }
            else if(board[y-1][x]==0) //empty
            {
                int tmp=y-1;
                while(tmp>=0&&board[tmp][x]==0)
                    tmp-=1;
                if(tmp<0)
                    board[0][x]=board[y][x];
                else if(board[tmp][x]==board[y][x])
                {
                    if(combined[tmp][x]==true)
                        board[tmp+1][x]=board[y][x];
                    else
                    {
                        combined[tmp][x]=true;
                        board[tmp][x]*=2;
                    }
                }
                else
                    board[tmp+1][x]=board[y][x];
                board[y][x]=0;
            }
            else //other block
            {
                continue;
            }
        }
    }
}
void move_down(vector<vector<int>> &board)
{
    bool combined[22][22]={0,};
    for(int y=size_board-2;y>=0;y--)
    {
        for(int x=0;x<size_board;x++)
        {
            if(board[y][x]==board[y+1][x]) //same block
            {
                if(combined[y+1][x]==true)
                    continue;
                combined[y+1][x]=true;
                board[y+1][x]*=2;
                board[y][x]=0;
            }
            else if(board[y+1][x]==0) //empty
            {
                int tmp=y+1;
                while(tmp<size_board&&board[tmp][x]==0)
                    tmp+=1;
                if(tmp==size_board)
                    board[size_board-1][x]=board[y][x];
                else if(board[tmp][x]==board[y][x])
                {
                    if(combined[tmp][x]==true)
                        board[tmp-1][x]=board[y][x];
                    else
                    {
                        combined[tmp][x]=true;
                        board[tmp][x]*=2;
                    }
                }
                else
                    board[tmp-1][x]=board[y][x];
                board[y][x]=0;
            }
            else //other block
            {
                continue;
            }
        }
    }
}
int solv(int direction,vector<vector<int>> board,int count)
{
    int ans=0;
    if(direction==0)
        move_up(board);        
    else if(direction==1)
        move_left(board);
    else if(direction==2)
        move_down(board);
    else if(direction==3)
        move_right(board);

    if(count==5)
    {
        int mm=0;
        for(int i=0;i<size_board;i++)
        {
            for(int j=0;j<size_board;j++)
            {
                mm=max(mm,board[i][j]);
            }
        }
        return mm;
    }
    for(int i=0;i<4;i++)
    {
        ans=max(ans,solv(i,board,count+1));
    }
    return ans;
}
int main()
{
    cin>>size_board;    
    vector<vector<int>> board(size_board);
    int ans=0;
    for(int i=0;i<size_board;i++)
    {
        for(int j=0;j<size_board;j++)
        {
            int a;
            cin>>a;
            board[i].push_back(a);
        }
    }
    // move_left(board);
    // for(int i=0;i<size_board;i++)
    // {
    //     for(int j=0;j<size_board;j++)
    //         cout<<board[i][j]<<" ";
    //     cout<<"\n";
    // }
    // return 0;
    while(true)
    {
        int direction;
        cin>>direction;
    if(direction==0)
        move_up(board);        
    else if(direction==1)
        move_left(board);
    else if(direction==2)
        move_down(board);
    else if(direction==3)
        move_right(board);
        
    }
    for(int i=0;i<4;i++)
    {
        ans=max(ans,solv(i,board,1));
    }
    cout<<ans;

    // move_left(board);
    // move_up(board);
 
    // cout<<"\n";
    // move_right(board);
    // for(int i=0;i<size_board;i++)
    // {
    //     for(int j=0;j<size_board;j++)
    //         cout<<board[i][j]<<" ";
    //     cout<<"\n";
    // }
    // cout<<"\n";
}   