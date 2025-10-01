/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 20303                             :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/20303                          #+#        #+#      #+#    */
/*   Solved: 2025/09/23 23:14:30 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include<bits/stdc++.h>
using namespace std;
int many_child,many_relation,need_howl;
vector<int> board_candy;
int parent[30303];
int get_parent(int i)
{
    if(parent[i]==i)
        return i;
    return parent[i]=get_parent(parent[i]);
}
void union_parent(int a,int b)
{
    int A=get_parent(a);
    int B=get_parent(b);

    if(A==B)
        return;
    parent[B]=A;
}
void init_parent()
{
    for(int i=1;i<=many_child;i++)
        parent[i]=i;
}
typedef struct candy
{
    int many=0;
    int sum=0;
};
    int dp[30303][3030]={0,};
int solv(vector<candy> a)
{
    for(int i=1;i<=a.size();i++)
    {
        for(int j=0;j<need_howl;j++)
        {
            if(a[i-1].many>=need_howl||a[i-1].many>j)
                dp[i][j]=dp[i-1][j];
            else
                dp[i][j]=max(dp[i-1][j],a[i-1].sum+dp[i-1][j-a[i-1].many]);
        }
    }
    return dp[a.size()][need_howl-1];
}
int main()
{
    cin>>many_child>>many_relation>>need_howl;
    for(int i=1;i<=many_child;i++)
    {
        int a;
        cin>>a;
        board_candy.push_back(a);
    }
    init_parent();
    for(int i=0;i<many_relation;i++)
    {
        int a,b;
        cin>>a>>b;
        union_parent(a,b);
    }
    candy sum_candy[30303];
    vector<candy>ans_candy;
    for(int i=1;i<=many_child;i++)
    {
        int a=get_parent(i);
        sum_candy[a].many+=1;
        sum_candy[a].sum+=board_candy[i-1];
    }

    for(auto i:sum_candy)
    {
        if(i.many==0)
            continue;
        ans_candy.push_back(i);
    }
    cout<<solv(ans_candy);
    
}
