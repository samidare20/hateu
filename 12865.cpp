#include<bits/stdc++.h>
using namespace std;
int many_stuff,max_weight;
typedef struct stuff{
    int weight;
    int value;
};
vector<stuff> board;
int ans[101][101010];
int main()
{
    cin>>many_stuff>>max_weight;
    for(int i=0;i<many_stuff;i++)
    {
        int a,b;
        cin>>a>>b;
        board.push_back({a,b});
    }
    for(int i=0;i<many_stuff;i++)
    {
        cout<<i<<"\n";
        for(int j=0;j<max_weight;j++)
        {
            cout<<j<<"\n";
            if(board[i].weight>j)
                continue;
            ans[i][j]=max(ans[i][j],board[i].value+ans[i-1][j-board[i].weight]);
            cout<<"check\n";
        }
    }
    cout<<ans[many_stuff-1][max_weight-1];
}
