/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 19238                             :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/19238                          #+#        #+#      #+#    */
/*   Solved: 2025/05/11 13:23:37 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include<bits/stdc++.h>
using namespace std;
int size_guest,size_board,fuel;
int board[22][22];
int board_start[22][22];
pair<int,int> position;
typedef struct guest{
    int x,y;
    int destx,desty;
};
guest board_guest[404];

int choice_nextguest()
{
    const int movey[4]={1,-1,0,0};
    const int movex[4]={0,0,1,-1};
    queue<pair<int,int>> q;
    int visit[22][22]={0,};
    visit[position.first][position.second]=1;
    q.push(position);
    
    while(!q.empty())
    {
        auto a=q.front();
        q.pop();

        if(board_start[a.first][a.second]!=0)
        {

        }

        for(int i=0;i<4;i++)
        {
            int X=a.second+movex[i];
            int Y=a.first+movey[i];

            if(X<0||Y<0||X>=size_board||Y>=size_board||visit[Y][X]!=0)
                continue;
            visit[Y][X]=visit[a.first][a.second]+1;
            q.push({Y,X});
        }
    }

}
int main()
{
    cin>>size_board>>size_guest>>fuel;

    for(int i=0;i<size_board;i++)
    {
        for(int j=0;j<size_board;j++)
            cin>>board[i][j];
    }
    cin>>position.first>>position.second;
    for(int i=1;i<=size_guest;i++)
    {
        cin>>board_guest[i].y>>board_guest[i].x>>board_guest[i].desty>>board_guest[i].destx;
        board_start[board_guest[i].y][board_guest[i].x]=i;
    }

}