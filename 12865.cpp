#include<bits/stdc++.h>
using namespace std;
int many_stuff,max_weight;
typedef struct stuff{
    int weight;
    int value;
};
vector<stuff> board(101);
int ans[101][101010];
int main()
{
    cin>>many_stuff>>max_weight;
    for(int i=1;i<=many_stuff;i++)
    {
        int a,b;
        cin>>a>>b;
        board[i]={a,b};
    }
    for(int i=1;i<=many_stuff;i++)
    {
        // cout<<i<<"\n";
        for(int j=0;j<=max_weight;j++)
        {
            if(board[i].weight>max_weight||j<board[i].weight)
                ans[i][j]=ans[i-1][j];

            // if()
            //     continue;
             else
                ans[i][j]=max(ans[i-1][j],board[i].value+ans[i-1][j-board[i].weight]);
            // cout<<"check\n";
        }
    }
    // for(int i=1;i<=many_stuff;i++)
    // {
    //     for(int j=0;j<=max_weight;j++)
    //         cout<<ans[i][j]<<" ";
    //     cout<<"\n";
    // }
    cout<<ans[many_stuff][max_weight];
}
