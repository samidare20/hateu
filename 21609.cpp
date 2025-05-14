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
			
			if(Y<0||X<0||X>=size_board||Y>=size_board||visit[Y][X]==true||board[Y][X]==-1||board[Y][X]==987654321) //out of board||already visit||black tile
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
bool find_blockgroup()
{
	bool visit[22][22]={0,};
	pair<int,int> standard_ans={0,0};
	int rainbow_ans=0;
	vector<pair<int,int>> ans;
	for(int i=0;i<size_board;i++)
	{
		for(int j=0;j<size_board;j++)
		{
			if(visit[i][j]==false&&board[i][j]>0&&board[i][j]!=987654321)
			{			
				vector<pair<int,int>> tmp=grouping(i,j,visit);
				
				if(ans.size()<tmp.size())
				{
					pair<int,int> a={0,0};
					for(auto i:tmp)
					{
						if(i.first>a.first)
							a=i;
						else if(i.first==a.first&&i.second>a.second)
							a=i;
					}
					ans=tmp;	
				}
				
			}
		}
	}
	if(ans.size()<2)
		return false;
	for(auto i:ans)
	{
//		cout<<i.first<<" "<<i.second<<" "<<ans.size()<<"\n";
		board[i.first][i.second]=987654321;		
	}
	score+=ans.size()*ans.size();
	return true;
}
void turn_board()
{
	int tmp[22][22]={0,};
	for(int i=0;i<size_board;i++)
	{
		for(int j=0;j<size_board;j++)
		{
			tmp[size_board-1-j][i]=board[i][j];
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
	for(int y=size_board-2;y>=0;y--)
	{
		for(int x=0;x<size_board;x++)
		{
			if(board[y][x]!=-1)
			{
				int i=y;
				while(i<size_board)
				{
					if(board[i+1][x]==987654321)
						i+=1;
					else
						break;
				}
				if(i==y)
					continue;
				board[i][x]=board[y][x];
				board[y][x]=987654321;
			}
		}
	}
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
	while(1)
	{
	
	
		bool ret=find_blockgroup();
		if(ret==false)
			break;
		for(int i=0;i<size_board;i++)
		{
			for(int j=0;j<size_board;j++)
			{
				if(board[i][j]==987654321)
					cout<<"* ";
				else
					cout<<board[i][j]<<" ";
			}
			cout<<"\n";
		}
		cout<<"delte============================\n";
		gravity();
		turn_board();
		gravity();
		for(int i=0;i<size_board;i++)
		{
			for(int j=0;j<size_board;j++)
			{
				if(board[i][j]==987654321)
					cout<<"* ";
				else
					cout<<board[i][j]<<" ";
			}
			cout<<"\n";
		}
		cout<<score<<"============================\n";
	}
	cout<<score;
}
