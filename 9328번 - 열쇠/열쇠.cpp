/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 9328                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/9328                           #+#        #+#      #+#    */
/*   Solved: 2025/09/23 21:55:41 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef struct shark
{
    pair<int,int> position;
    int number;
    int direction;
    bool alive;
};
const pair<int,int> moves[9]={
    {99,99},{-1,0},{-1,-1},
    {0,-1},{1,-1},{1,0},
    {1,1},{0,1},{-1,1}
};
bool shark_cmp(shark a,shark b)
{
    return a.number<b.number;
}
void pb(vector<vector<int>>board)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<"\n";
    }
}
pair<vector<vector<int>>,vector<shark>> move_fish(vector<vector<int>> board,vector<shark> shark_board,int x,int y)
{
    for(shark i : shark_board)
    {
        if(i.alive==false)
            continue;
        int count=0;
        while(count<8)
        {
            int Y=i.position.first+moves[i.direction].first;
            int X=i.position.second+moves[i.direction].second;
            if(!(X<0||Y<0||X>=4||Y>=4||(Y==y&&X==x)))
            {

                pair<int,int> a=shark_board[board[Y][X]].position;
                shark_board[board[Y][X]].position=shark_board[board[i.position.first][i.position.second]].position;
                shark_board[board[i.position.first][i.position.second]].position=a;
                
                int b=board[Y][X];
                board[Y][X]=board[i.position.first][i.position.second];
                board[i.position.first][i.position.second]=b;
                break;
            }
            i.direction=(i.direction+1)%9;
            count++;
        }
    }
    return {board,shark_board};
}
int solv(vector<vector<int>> board,vector<shark> shark_board,int x,int y,int direction,int ans)
{
    cout<<ans<<": ans \n";
    cout<<y<<" "<<x<<"\n";
    auto a=move_fish(board,shark_board,x,y);
    board=a.first;
    shark_board=a.second;
    pb(board);
    int result=0;
    int X=x;
    int Y=y;
    while(0<=X&&X<4&&0<=Y&&Y<4)
    {
        X+=moves[direction].second;
        Y+=moves[direction].first;
        if(!(0<=X&&X<4&&0<=Y&&Y<4))
            break;

        if(board[Y][X]==-1)
            continue;
        shark_board[board[Y][X]].alive=false;
        int tmp=board[Y][X];
        board[Y][X]=-1;
        result=max(result,solv(board,shark_board,X,Y,shark_board[tmp].direction,ans+shark_board[tmp].number));
        shark_board[board[Y][X]].alive=true;
        board[Y][X]=tmp;
    }
    return result;
}
int main()
{
    vector<shark> shark_board;
    vector<vector<int>> board(5,vector<int>(5));
    shark t;
    t.number=0;
    t.alive=false;
    shark_board.push_back(t);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            shark a;
            cin>>a.number>>a.direction;
            a.alive=true;
            board[i][j]=a.number;
            a.position={i,j};
            shark_board.push_back(a);
        }
    }
    sort(shark_board.begin(),shark_board.end(),shark_cmp);
    shark_board[board[0][0]].alive=false;
    int d=shark_board[board[0][0]].direction;
    board[0][0]=-1;
    cout<<solv(board,shark_board,0,0,d,shark_board[board[0][0]].number);
}