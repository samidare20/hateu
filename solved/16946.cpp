#include<bits/stdc++.h>
using namespace std;
int height,width;
int board[1010][1010];
int ans[1010][1010];
int group[1010][1010];
int groupid=1;
const int movex[4]={1,-1,0,0};
const int movey[4]={0,0,1,-1};

void bfs_count(int y,int x)
{
    bool visit[1010][1010]={0,};
    vector<pair<int,int>> v;
    queue<pair<int,int>> q;
    q.push({y,x});
    v.push_back({y,x});
    visit[y][x]=true;
    int count=1;

    while(!q.empty())
    {
        auto a=q.front();
        q.pop();

        for(int i=0;i<4;i++)
        {
            int X=a.second+movex[i];
            int Y=a.first+movey[i];
            if(X<0||Y<0||X>=width||Y>=height||board[Y][X]==1||visit[Y][X]==true)
                continue;
            q.push({Y,X});
            visit[Y][X]=true;
            count+=1;
            v.push_back({Y,X});
        }
    }
    for(auto a:v)
    {
        ans[a.first][a.second]=count;
        group[a.first][a.second]=groupid;
    }
    groupid+=1;
}
void init()
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(board[i][j]==0&&ans[i][j]==0)
            {
                bfs_count(i,j);
            }
        }
    }    
}
int get_ans(int y,int x)
{
    map<int,bool> m;
    int count=1;
    for(int i=0;i<4;i++)
    {
        int X=x+movex[i];
        int Y=y+movey[i];
        if(X<0||Y<0||X>=width||Y>=height||(m.find(group[Y][X])!=m.end()))
            continue;
        count+=ans[Y][X];
        m[group[Y][X]]=true;
    }
    return count;
}
void solv()
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(board[i][j]==0)
                cout<<0;
            else
                cout<<get_ans(i,j)%10;
        }
        cout<<"\n";
    }
}
int main()
{
    cin>>height>>width;
    for(int i=0;i<height;i++)
    {
        string a;
        cin>>a;
        for(int c=0;c<width;c++)
        {
            board[i][c]=a[c]-'0';
        }        
    }
    init();
    // for(int i=0;i<height;i++)
    // {
    //     for(int j=0;j<width;j++)
    //         cout<<ans[i][j]<<" ";
    //     cout<<"\n";
    // }
    // cout<<"\n\n";
    // for(int i=0;i<height;i++)
    // {
    //     for(int j=0;j<width;j++)
    //         cout<<group[i][j]<<" ";
    //     cout<<"\n";
    // }
    solv();
}