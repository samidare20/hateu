/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 1584                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/1584                           #+#        #+#      #+#    */
/*   Solved: 2025/04/29 21:13:32 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include<iostream>
#include<queue>
using namespace std;

int board[505][505]; //-1 : cant move 1 : danger

void make_board(int x1,int y1,int x2,int y2,int type)
{
    if(y1>y2)
    {
        int tmp=y1;
        y1=y2;
        y2=tmp;
    }
    if(x1>x2)
    {
        int tmp=x1;
        x1=x2;
        x2=tmp;
    }
    for(int y=y1;y<=y2;y++)
    {
        for(int x=x1;x<=x2;x++)
        {
            board[y][x]=type;
        }
    }
}
int bfs()
{
    int ans=987654321;
    const int movex[4]={1,-1,0,0};  
    const int movey[4]={0,0,1,-1};  
    int visit[505][505]={0,};  
    visit[0][0]=1;  
    queue<pair<int,int>> q;
    q.push({0,0});

    while(!q.empty())
    {
        auto a=q.front();
        q.pop();
        if(a.first==500&&a.second==500)
        {
            ans=min(ans,visit[500][500]);
            continue;
        }
        for(int i=0;i<4;i++)
        {
            int X=a.second+movex[i];
            int Y=a.first+movey[i];
            int cost=visit[a.first][a.second];
            if(X<0||Y<0||X>500||Y>500||board[Y][X]==-1)
                continue;
            
            if(board[Y][X]==1)
                cost+=1;
            if(visit[Y][X]==0||visit[Y][X]>cost)
            {
                visit[Y][X]=cost;
                q.push({Y,X});
            }
        }
    }
    return ans;
}
int main()
{
    int many_danger;
    int many_death;

    cin>>many_danger;

    for(int i=0;i<many_danger;i++)
    {
        int x1,x2,y1,y2;

        cin>>x1>>y1>>x2>>y2;

        make_board(x1,y1,x2,y2,1);
    }
    cin>>many_death;
    for(int i=0;i<many_death;i++)
    {
        int x1,x2,y1,y2;

        cin>>x1>>y1>>x2>>y2;

        make_board(x1,y1,x2,y2,-1);
    }
    int ans=bfs();
    if(ans==987654321)
        cout<<-1;
    else        
        cout<<ans-1;

}