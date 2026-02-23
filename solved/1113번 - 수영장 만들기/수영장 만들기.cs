/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 1113                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/1113                           #+#        #+#      #+#    */
/*   Solved: 2026/02/23 17:21:24 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
using System;
using System.Runtime.InteropServices;
class Program
{
    static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    static int[] movex = { 1, -1, 0, 0 };
    static int[] movey = { 0, 0, 1, -1 };

    public static void Main()
    {
        int BoardHeight=0, BoardWidth=0;
        int[][]Board= Array.Empty<int[]>();
        Input(ref BoardHeight, ref BoardWidth, ref Board);
        bool[][] Edge = GetEdge(BoardHeight, BoardWidth, Board);
#if DEBUG
        for (int i = 0; i < BoardHeight; i++)
        {
            for (int j = 0; j < BoardWidth; j++)
            {
                if (Edge[i][j] == true)
                    Console.Write("@");
                else
                    Console.Write("#");
            }
            Console.WriteLine();
        }
        Console.WriteLine();
        Console.WriteLine();
#endif
        int ans = 0;
        while(true)
        {
            int result=MakePool(BoardHeight, BoardWidth,Board,Edge);
            if (result == 0)
                break;
            ans += result;
            
        }
#if DEBUG
        for (int i = 0; i < BoardHeight; i++)
        {
            for (int j = 0; j < BoardWidth; j++)
            {
                Console.Write(Board[i][j]+" ");
            }
            Console.WriteLine();
        }
        Console.WriteLine();
        Console.WriteLine();
#endif
        sw.Write(ans);
        sw.Close();
    }
    static (int,List<(int,int)>) GetTargetList(int BoardHeight,int BoardWidth,int Y,int X, int[][] Board, bool[][]Edge)
    {
        bool[][] visit = new bool[BoardHeight][];
        for (int i = 0; i < BoardHeight; i++)
            visit[i] = new bool[BoardWidth];

        List<(int, int)>l=new List<(int, int)> ();
        Queue<(int, int)> q = new Queue<(int, int)>();
        q.Enqueue((Y, X));
        l.Add((Y, X));
        visit[Y][X] = true;
        int MinWall = 987654321;

        while(q.Count > 0)
        {
            var a = q.Dequeue();
            for (int i = 0; i < 4; i++)
            {
                int x = a.Item2 + movex[i];
                int y = a.Item1 + movey[i];
                if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight || visit[y][x] == true)
                    continue;
                if (Board[y][x] > Board[a.Item1][a.Item2] || Edge[y][x]==true)
                {
                    MinWall = Math.Min(MinWall, Board[y][x]);
                }
                else
                {
                    visit[y][x] = true;
                    q.Enqueue((y, x));
                    l.Add((y, x));
                }
            }
        }
        return (MinWall,l);
    }
    static int MakePool(int BoardHeight,int BoardWidth,int[][] Board, bool[][]Edge)
    {
        int count = 0;
        for(int i=0;i<BoardHeight;i++)
        {
            for(int j=0;j<BoardWidth;j++)
            {
                if (Edge[i][j] == true)
                    continue;
                int minwall;
                List<(int, int)> l;
               (minwall,l)=GetTargetList(BoardHeight, BoardWidth, i, j, Board, Edge);
                foreach(var v in l)
                {
                    if (minwall < Board[v.Item1][v.Item2])
                        continue;
                    count += minwall - Board[v.Item1][v.Item2];

                    Board[v.Item1][v.Item2] = minwall;
                }    
            }
        }
        return count;
    }
    static bool[][] GetEdge(int BoardHeight,int BoardWidth,int[][]Board)
    {
        bool[][] visit = new bool[BoardHeight][];
        for (int i = 0; i < BoardHeight; i++)
            visit[i] = new bool[BoardWidth];
        Queue<(int, int)> q = new Queue<(int, int)>();
        q.Enqueue((0, 0));
        while(q.Count > 0)
        {
            var a = q.Dequeue();
            for(int i=0;i<4;i++)
            {
                int x = a.Item2 + movex[i];
                int y=a.Item1+movey[i];
                if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight || visit[y][x] == true)
                    continue;
                if (y == 0 || x == 0 ||y==BoardHeight-1||x==BoardWidth-1|| Board[y][x] >= Board[a.Item1][a.Item2])
                {
                    visit[y][x] = true;
                    q.Enqueue((y, x));
                }
            }
        }
        return visit;
    }
    static void Input(ref int BoardHeight,ref int BoardWidth,ref int[][]Board)
    {
        int[] tmp = Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);        
        BoardHeight = tmp[0];
        BoardWidth = tmp[1];
        Board = new int[BoardHeight][];

        for (int i = 0; i < BoardHeight; i++)
            //Board[i]= Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);
            Board[i] = Array.ConvertAll(sr.ReadLine().ToArray(), c => c -'0'); 
        
    }
}