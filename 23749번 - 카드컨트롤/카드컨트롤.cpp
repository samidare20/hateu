/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 23749                             :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/23749                          #+#        #+#      #+#    */
/*   Solved: 2025/05/10 14:42:27 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
vector<char> board_origin;
int to_10(vector<char> board)
{
    int tmp=1;
    int ans=0;
    for(int i=board.size()-1;i>=0;i--)
    {
        ans+=board[i]*tmp;
        tmp*=2;
    }
    return ans;
}
bool check_board(vector<char> temp)
{
    int win=0;
    for(int i=0;i<temp.size();i+=2)
    {
        if(temp[i]==temp[i+1])
            continue;
        if(temp[i]=='O'&&temp[i+1]=='X')
            win+=1;
        else
            win-=1;
    }
    if(win>0)
        return true;
    return false;
}
int make_board()
{
    int visit[202020]={0,};
    queue<vector<char>> q;
    int answer=987654321;

    visit[to_10(board_origin)]=1;
    q.push(board_origin);

    while(!q.empty())
    {
        auto a=q.front();       
        q.pop();

        if(check_board(a)==true)
            answer=min(answer,visit[to_10(a)]);

        for(int i=1;i<a.size();i++)
        {
            vector<char> tmp;
            int tmp_ten;

            tmp.push_back(a[i]);
            for(int j=0;j<a.size();j++)
            {
                if(j==i)
                    continue;
                tmp.push_back(a[j]);
            }
            tmp_ten=to_10(tmp);
            if(visit[tmp_ten]!=0)
                continue;
            visit[tmp_ten]=visit[to_10(a)]+1;
            q.push(tmp);
        }
    }
    return answer;
}
int main()
{
    int N;
    cin>>N;
    for(int i=0;i<N*2;i++)
    {
        char a;
        cin>>a;
        board_origin.push_back(a);
    }
    int ans=make_board();
    cout<<ans-1;
}