/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 1113                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/1113                           #+#        #+#      #+#    */
/*   Solved: 2025/08/27 16:09:51 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include <iostream>
#include<queue>
#include<vector>
using namespace std;

bool board_edge[55][55]={0,};
int board[55][55];
int height,width;

void input_data()
{
    cin>>height>>width;
    for(int i=0;i<height;i++)
    {
        string a;
        cin>>a;
        for(int j=0;j<width;j++)
        {
            board[i][j]=(int)(a[j]-'0');
        }
        // cin.ignore();
    }
}
void bfs_board_edge(pair<int,int> start)
{
    bool visit[55][55]={0,};
    vector<pair<int,int>> v;
    queue<pair<int,int>> q;
    q.push(start);
    v.push_back(start);
    const int move_x[4]={0,0,1,-1};
    const int move_y[4]={1,-1,0,0};
    bool flag_edge=false;
    
    while(!q.empty())
    {
        auto a=q.front();
        q.pop();
        
        if(a.first==0||a.first==height-1||a.second==0||a.second==width-1)
            flag_edge=true;
        
        for(int i=0;i<4;i++)
        {
            int next_x=move_x[i]+a.second;
            int next_y=move_y[i]+a.first;
            if(next_x<0||next_x>=width||next_y<0||next_y>=height||board[next_y][next_x]<board[a.first][a.second]||visit[next_y][next_x]==true)
                continue;
            
            visit[next_y][next_x]=true;
            
            v.push_back({next_y,next_x});
            q.push({next_y,next_x});
        }
    }
    if(flag_edge==false)
        return;
    for(auto i:v)
        board_edge[i.first][i.second]=true;
}
void set_board_edge()
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(i==0||i==height-1||j==0||j==width-1){
                if(board_edge[i][j]==false)
                {
                    bfs_board_edge({i,j});
                }
            }
        }
    }
    cout<<"\n";
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
            cout<<board_edge[i][j]<<" ";
        cout<<"\n";
    }
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	
    input_data();
    
    cout<<"\n";
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
            cout<<board[i][j]<<" ";
        cout<<"\n";
    }
    set_board_edge();
    cout<<"end";
    
}