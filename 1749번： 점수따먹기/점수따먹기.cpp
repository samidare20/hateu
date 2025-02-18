#include<bits/stdc++.h>
using namespace std;

int main()
{
    int N,M;
    int board[222][222]={0,};
    int sumboard[222][222]={0,};

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
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            cout<<sumboard[i][j]<<" ";
        cout<<"\n";
}