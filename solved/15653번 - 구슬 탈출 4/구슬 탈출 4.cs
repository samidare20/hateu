/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 15653                             :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/15653                          #+#        #+#      #+#    */
/*   Solved: 2026/02/19 16:14:57 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
using System.Diagnostics;
using System.Reflection.Metadata;

namespace boj15653;

partial class Program
{
    [System.Diagnostics.Conditional("DEBUG")]
    static void DebugPrint(object a)
    {
        sw.Write(a);
    }
    [System.Diagnostics.Conditional("DEBUG")]
    static void DebugPrintLine(object a)
    {
        sw.WriteLine(a);
    }
    static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    public struct Pos
    {
        public int x, y;
    }
    public struct QData
    {
        public Pos B, R;
        public int count;
    }
    static Pos RPos, BPos, OPos;
    static int BoardX, BoardY;
    static char[][] Board = new char[11][];
    static bool flag = false;
    static int BallMove(ref Pos ball, Pos against, int movey, int movex)
    {
        if(ball.y==-1||ball.x==-1)
            return 0;
        Board[ball.y][ball.x] = '.';
        Pos ans = new Pos { x = ball.x, y = ball.y };
        while (true)
        {
            if (ans.y + movey == against.y && ans.x + movex == against.x)
            {
                ball = ans;
                break;
            }
            else if (Board[ans.y + movey][ans.x + movex] == '.')
            {
                ans.y += movey;
                ans.x += movex;
            }
            else if (Board[ans.y + movey][ans.x + movex] == 'O')
            {
                ans.y += movey;
                ans.x += movex;
                ball = new Pos{x=-1,y=-1};

                flag = true;
                return 1;
            }
            else
            {
                ball = ans;
                break;
            }
        }
        return 0;
    }
    public static void solv()
    {
        bool [,,,]visit=new bool[50,50,50,50];
        int []movex={0,0,1,-1};
        int[]movey={1,-1,0,0};
        Queue<QData> q = new Queue<QData>();
        q.Enqueue(new QData { R = RPos, B = BPos, count = 0 });
        visit[RPos.x,RPos.y,BPos.x,BPos.y]=true;

        while (q.Count > 0)
        {
            var a=q.Dequeue();
            // if(a.count>=10)
            //     continue;
            for(int i=0;i<4;i++)
            {
                int c=0;
                Pos tmpR=a.R;
                Pos tmpB=a.B;
                c+=BallMove(ref tmpR,tmpB,movey[i],movex[i]);
                c+=BallMove(ref tmpB,tmpR,movey[i],movex[i])*3;
                c+=BallMove(ref tmpR,tmpB,movey[i],movex[i]);

                if(c==1)
                {
                    sw.Write(a.count+1);
                    return;
                }
                else if(c==0)
                {
                    if(!visit[tmpR.x,tmpR.y,tmpB.x,tmpB.y])
                    {
                        q.Enqueue(new QData{R=tmpR,B=tmpB,count=a.count+1});
                        visit[tmpR.x,tmpR.y,tmpB.x,tmpB.y]=true;
                    }
                }
            }
        }
        sw.Write(-1);
    }
    public static void Main()
    {
        Input();


        solv();

        sw.Close();
    }
    static void Input()
    {
        int[] tmp = Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);
        BoardX = tmp[1];
        BoardY = tmp[0];

        for (int i = 0; i < BoardY; i++)
        {
            Board[i] = sr.ReadLine().ToCharArray();
            for (int j = 0; j < BoardX; j++)
            {
                if (Board[i][j] == 'R')
                    RPos = new Pos { y = i, x = j };
                else if (Board[i][j] == 'B')
                    BPos = new Pos { y = i, x = j };
                else if (Board[i][j] == 'O')
                    OPos = new Pos { y = i, x = j };
            }
        }

    }
}