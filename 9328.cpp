#include <iostream>
#include<vector>
#include<queue>
using namespace std;
void open_door(vector<string>&board,bool key[],vector<pair<int,int>> door_location[])
{
    for(int i=0;i<26;i++)
    {
        if(key[i]==true)
        {
            for(auto j:door_location[i])
            {
                board[j.first][j.second]='.';
            }
        }
    }
    // for(int i=0;i<board.size();i++)
    // {
    //     for(int j=0;j<board[i].size();j++) 
    //         cout<<board[i][j];
    //     cout<<"\n";
    // }
    // cout<<"@@@@@@@@@@@@@\n\n";
}
int bfs(vector<string>&board, bool key[],int height,int width)
{
    const int movex[4]={1,-1,0,0};
    const int movey[4]={0,0,1,-1};
    bool visit[111][111]={0,};
    int ans=0;
    bool flag=false;
    queue<pair<int,int>> q;

    for(int i=0;i<height;i++)
    {
        if(i==0||i==height-1)
        {
            for(int j=0;j<width;j++)
            {
                if(board[i][j]=='.')
                {
                    q.push({i,j});
                    visit[i][j]=true;
                }
                else if('a'<=board[i][j]&&board[i][j]<='z')
                {
                    q.push({i,j});
                    visit[i][j]=true;
                    key[board[i][j]-'a']=true;
                    board[i][j]='.';
                    flag=true;
                }
                else if(board[i][j]=='$')
                {
                    ans+=1;
                    q.push({i,j});
                    visit[i][j]=true;
                    board[i][j]='.';
                }
            }
        }
        else
        {            
            int tmp[2]={0,width-1};
            for(int j:tmp)
            {
                if(board[i][j]=='.')
                {
                    q.push({i,j});
                    visit[i][j]=true;
                }
                else if(board[i][j]=='$')
                {
                    ans+=1;
                    q.push({i,j});
                    visit[i][j]=true;
                    board[i][j]='.';
                }
                else if('a'<=board[i][j]&&board[i][j]<='z')
                {
                    q.push({i,j});
                    visit[i][j]=true;
                    key[board[i][j]-'a']=true;
                    flag=true;
                    board[i][j]='.';
                }
            }
        }
    }
    
    while(!q.empty())
    {
        auto a=q.front();
        // cout<<a.first<<" "<<a.second<<"\n";
        q.pop();

        for(int i=0;i<4;i++)
        {
            int X=movex[i]+a.second;
            int Y=movey[i]+a.first;
            if(X<0||Y<0||X>=width||Y>=height||visit[Y][X]==true||board[Y][X]=='*')
                continue;
            if(board[Y][X]=='$')
            {
                ans+=1;
                q.push({Y,X});
                visit[Y][X]=true;
                board[Y][X]='.';
            }
            else if('a'<=board[Y][X]&&board[Y][X]<='z')
            {
                // cout<<"13123";
                key[board[Y][X]-'a']=true;
                board[Y][X]='.';
                flag=true;
            }
            else if(board[Y][X]=='.')
            {
                visit[Y][X]=true;
                q.push({Y,X});
            }
        }
    }
    if(ans>0)
        return ans;
    if(flag==true)
        return 0;
    return -1;
}
int solv(vector<string>board, bool key[],vector<pair<int,int>>door_location[],int height,int width)
{
    int ans=0;
    while(true)
    {
        open_door(board,key,door_location);
        int a=bfs(board,key,height,width);
        if(a==-1)
            return ans;
        else if(a>0)
            ans+=a;
        else if(a==0)
            continue;
        // for(int i=0;i<height;i++)
        // {
        //     for(int j=0;j<width;j++) 
        //         cout<<board[i][j]<<" ";
        //     cout<<"\n@@@@@@@@@@@@board\n";
        // }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
	int testcase;
	cin>>testcase;
	while(testcase--)
	{
		int height,width;
		vector<string> board;
		string havekey;
		bool key[30]= {0,};
		vector<pair<int,int>> door_location[30];
		
		cin>>height>>width;
		for(int i=0; i<height; i++)
		{
			string a;
			cin>>a;
			board.push_back(a);
			for(int j=0;j<width;j++)
			{
			    if('A'<=board[i][j]&&board[i][j]<='Z')
			        door_location[board[i][j]-'A'].push_back({i,j});
			}
		}
		cin>>havekey;

		if(havekey!="0")
		{
			for(char c:havekey)
				key[c-'a']=true;
		}
		cout<<solv(board,key,door_location,height,width)<<"\n";//<<"!!!!!!!!!!!\n";
	}
}