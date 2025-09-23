/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 12865                             :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/12865                          #+#        #+#      #+#    */
/*   Solved: 2025/09/23 22:30:57 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
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
        for(int j=0;j<=max_weight;j++)
        {
            if(board[i].weight>max_weight||j<board[i].weight)
                ans[i][j]=ans[i-1][j];
             else
                ans[i][j]=max(ans[i-1][j],board[i].value+ans[i-1][j-board[i].weight]);
        }
    }
    cout<<ans[many_stuff][max_weight];
}
