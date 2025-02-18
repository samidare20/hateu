#include<bits/stdc++.h>
using namespace std;

int main()
{
    int N,M;
    int board[222][222]={0,};
    int sumboard[222][222]={0,};
    int ans=-987654321;

    cin>>N>>M;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++)
        {
            cin>>board[i][j];
            sumboard[i][j]=board[i][j];
        }
    }

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++)
        {
            if(i==0&&j==0)
                continue;
            if(i==0)
                sumboard[i][j]+=sumboard[i][j-1];
            else if(j==0)
                sumboard[i][j]+=sumboard[i-1][j];
            else
                sumboard[i][j]+=sumboard[i-1][j]+sumboard[i][j-1]-sumboard[i-1][j-1];
        }
    }
    // for(int i=0;i<N;i++)
    // {
    //     for(int j=0;j<M;j++)
    //         cout<<sumboard[i][j]<<" ";
    //     cout<<"\n";
    // }
    ans=sumboard[0][0];
    for(int y=0;y<N;y++)
    {
        for(int x=0;x<M;x++)
        {
            for(int i=0;i<=y;i++)
            {
                for(int j=0;j<=x;j++)
                {
                    int a;
                    if(i==0&&j==0)
                        continue;
                    else if(i==0)
                        a=sumboard[y][x]-sumboard[y][x-j];
                    else if(j==0)
                        a=sumboard[y][x]-sumboard[y-i][x];
                    else
                        a=sumboard[y][x]-sumboard[y-i][x]-sumboard[y][x-j]+sumboard[y-i][x-j];
                    ans=max(ans,a);
                    ans=max(ans,sumboard[y][x]);
                }
            }
        }
    
    }
    cout<<ans;
}