#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int size_board,many_color;
int board[22][22];
int score=0;

vector<pair<int,int>> grouping(int y,int x,bool visit[][22])
{
	vector<pair<int,int>> board_ans;
	int nowcolor=board[y][x];
	const int movex[4]={0,0,1,-1};
	const int movey[4]={1,-1,0,0};
	queue<pair<int,int>> q;
	vector<pair<int,int>> board_usedwhite;
	
	q.push({y,x});
	visit[y][x]=true;
	board_ans.push_back({y,x});
	
	while(!q.empty())
	{
		auto a=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int Y=a.first+movey[i];
			int X=a.second+movex[i];
			
			if(Y<0||X<0||X>=size_board||Y>=size_board||visit[Y][X]==true||board[Y][X]==-1) //out of board||already visit||black tile
				continue;
				
			if(board[Y][X]!=0&&board[Y][X]!=nowcolor) //different color and its not rainbow tile
				continue;
			
			q.push({Y,X});
			visit[Y][X]=true;
			board_ans.push_back({Y,X});
			if(board[Y][X]==0)
				board_usedwhite.push_back({Y,X});
		}
	}
	for(auto i:board_usedwhite)
	{
		visit[i.first][i.second]=false;
	}
	return board_ans;
}
void find_blockgroup()
{
	bool visit[22][22]={0,};
	vector<pair<int,int>> ans;
	for(int i=0;i<size_board;i++)
	{
		for(int j=0;j<size_board;j++)
		{
			if(visit[i][j]==false&&board[i][j]>0)
			{			
				vector<pair<int,int>> tmp=grouping(i,j,visit);
				if(ans.size()<tmp.size())
					ans=tmp;
			}
		}
	}
	for(auto i:ans)
	{
//		cout<<i.first<<" "<<i.second<<" "<<ans.size()<<"\n";
		board[i.first][i.second]=987654321;		
	}
	score+=ans.size()*ans.size();

}
void turn_board()
{
	int tmp[22][22]={0,};
	for(int i=0;i<size_board;i++)
	{
		for(int j=0;j<size_board;j++)
		{
			tmp[j][i]=board[i][j];
		}
	}
	for(int i=0;i<size_board;i++)
	{
		for(int j=0;j<size_board;j++)
			board[i][j]=tmp[i][j];
	}
}
void gravity()
{
	
}
int main()
{
	cin>>size_board>>many_color;
	
	
	for(int i=0;i<size_board;i++)
	{
		for(int j=0;j<size_board;j++)
		{
			cin>>board[i][j];
		}
	}
	find_blockgroup();
	gravity();
	turn_board();
	gravity();
	cout<<score;
}
