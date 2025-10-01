/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 2933                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/2933                           #+#        #+#      #+#    */
/*   Solved: 2025/08/29 10:35:56 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int height,width;
string board[111];
vector<int> data_throw;

void input_data()
{
    cin>>height>>width;
    for(int i=height-1;i>=0;i--)
        cin>>board[i];
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        data_throw.push_back(a);
    }
}
vector<pair<int,int>> bfs(pair<int,int> start,bool visit[111][111])
{
    vector<pair<int,int>> tile_visited;
    const int movex[4]={0,0,1,-1};
    const int movey[4]={1,-1,0,0};
    queue<pair<int,int>> q;
    q.push(start);
    tile_visited.push_back(start);
    visit[start.first][start.second]=true;

    while(!q.empty())
    {
        auto a=q.front();
        q.pop();

        for(int i=0;i<4;i++)
        {
            int X=movex[i]+a.second;
            int Y=movey[i]+a.first;

            if(X<0||Y<0||X>=width||Y>=height||visit[Y][X]==true||board[start.first][start.second]!=board[Y][X])
            {
                continue;
            }
            q.push({Y,X});
            visit[Y][X]=true;
            tile_visited.push_back({Y,X});
        }
    }
    return tile_visited;
}
void move_down(vector<pair<int,int>> a,bool visit[111][111])
{
    string tmpb[111];
    for(int i=0;i<height;i++)
        tmpb[i]=board[i];
    int most_low=987654321;
    int tmp=1;
    int ans=0;

    for(auto i:a)
    {
        board[i.first][i.second]='.';
        most_low=min(most_low,i.first);
        tmpb[i.first][i.second]='!';
    }
    
    while(most_low>0)
    {
        bool is_ans=true;
        for(auto i:a)
        {
            if(board[i.first-tmp][i.second]=='x')
            {
                is_ans=false;
                break;
            }
        }
        if(is_ans==false)
            break;
        ans=tmp;
        tmp+=1;
        most_low-=1;
    }
    for(auto i:a)
    {
        board[i.first-ans][i.second]='x';
        visit[i.first-ans][i.second]=true;
    }
}
void check_down()
{
    bool visit[111][111]={0,};
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(visit[i][j]==true)
                continue;
            if(board[i][j]=='.')
            {
                bfs({i,j},visit);
            }
            else if(board[i][j]=='x')
            {
                auto a=bfs({i,j},visit);
                move_down(a,visit);
            }
        }
    }
}
void print_board()
{
    for(int i=height-1;i>=0;i--)
    {
        for(int j=0;j<width;j++)
            cout<<board[i][j];
        cout<<"\n";
    }
}
void break_board(int break_height,bool direction)
{
    if(direction==false)
    {
        for(int i=0;i<width;i++)
        {
            if(board[break_height][i]=='x')
            {
                board[break_height][i]='.';
                check_down();
                break;
            }
        }
    }
    else
    {
        for(int i=width-1;i>=0;i--)
        {
            if(board[break_height][i]=='x')
            {
                board[break_height][i]='.';
                check_down();
                break;
            }
        }
    }
}
int main()
{
    bool direction=false;
    input_data();
    for(int i:data_throw)
    {
        break_board(i-1,direction);
        direction=!direction;
    }
    print_board();
}