/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 7579                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/7579                           #+#        #+#      #+#    */
/*   Solved: 2025/09/27 00:44:28 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include<bits/stdc++.h>
using namespace std;
int many_data,need_size;
vector<int> board_value;
vector<int> board_cost;
int dp[101][10101]; //
void solv()
{
    for(int i=1;i<=many_data;i++)
    {
        for(int j=0;j<10001;j++)
        {
            if(j<board_cost[i-1])
                dp[i][j]=dp[i-1][j];
            else
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-board_cost[i-1]]+board_value[i-1]);
        }
    }
    for(int i=0;i<10001;i++)
    {
        if(dp[many_data][i]>=need_size)
        {
            cout<<i;
            return;
        }
    }
}
int main()
{
    cin>>many_data>>need_size;
    for(int i=0;i<many_data;i++)
    {
        int a;
        cin>>a;
        board_value.push_back(a);
    }
    for(int i=0;i<many_data;i++)
    {
        int a;
        cin>>a;
        board_cost.push_back(a);
    }
    solv();
}