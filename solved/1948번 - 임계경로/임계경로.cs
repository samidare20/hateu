/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 1948                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/1948                           #+#        #+#      #+#    */
/*   Solved: 2026/02/23 16:19:49 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
using System;
using System.Runtime.InteropServices;
class Program
{
    static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    public static void Main()
    {
        int node=0, edge=0,depart=0,dest=0;
        List<List<(int, int)>> Board = new List<List<(int, int)>>();
        List<List<(int, int)>> ReverseBoard = new List<List<(int, int)>>();
        int[] ParentEdge=new int[0];
        Input(ref node, ref edge, ref depart, ref dest, ref Board,ref ReverseBoard,ref ParentEdge);
        int []cost=GetCost(node, Board, depart, dest, ParentEdge);



        Solv(depart, dest, Board,ReverseBoard,node,cost);
        sw.Close();
    }
    static int[] GetCost(int node, List<List<(int, int)>> Board,int depart,int dest, int[]ParentEdge)
    {
        int[] cost = new int[node + 1];
        Queue<int> q = new Queue<int>();
        q.Enqueue(depart);
        while (q.Count > 0)
        {
            var a=q.Dequeue();
            foreach(var i in Board[a])
            {
                ParentEdge[i.Item1] -= 1;
                cost[i.Item1] = Math.Max(cost[i.Item1], cost[a] + i.Item2);
                if (ParentEdge[i.Item1] == 0)
                    q.Enqueue(i.Item1);
            }
        }
        return cost;
    }
    static void Solv(int depart,int dest,List<List<(int,int)>>Board, List<List<(int, int)>> ReverseBoard, int node, int[]cost)
    {
        int ans = 0;
        bool[] visit = new bool[node + 1];
        Queue<(int, int)> q = new Queue<(int, int)>();
        //for (int i = 1; i <= node; i++)
        //    visit[i] = new bool[node + 1];

        q.Enqueue((dest, 0));
        while(q.Count > 0)
        {
            var a = q.Dequeue();
            foreach(var i in ReverseBoard[a.Item1])
            {
                if (a.Item2 + cost[i.Item1]+i.Item2 == cost[dest])
                {
                    ans += 1;
                    if (visit[i.Item1]==false)
                    {
                        visit[i.Item1] = true;
                        q.Enqueue((i.Item1, a.Item2 + i.Item2));
                        //Console.WriteLine($"{a.Item1} {i.Item1}");
                    }
                }
            }
        }
        Console.Write($"{cost[dest]}\n{ans}");
    }
    static void Input(ref int node,ref int edge,ref int depart,ref int dest,ref List<List<(int,int)>>Board, ref List<List<(int, int)>> ReverseBoard, ref int[]ParentEdge)
    {
        node = int.Parse(sr.ReadLine());
        edge = int.Parse(sr.ReadLine());

        ParentEdge = new int[node + 1];
        for (int i = 0; i <= node; i++)
        {
            Board.Add(new List<(int, int)>());
            ReverseBoard.Add(new List<(int, int)>());
        }

        int[] tmp ;
        for(int i=0;i<edge;i++)
        {
            tmp = Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);
            Board[tmp[0]].Add((tmp[1], tmp[2]));
            ReverseBoard[tmp[1]].Add((tmp[0], tmp[2]));
            ParentEdge[tmp[1]] += 1;
        }
        tmp = Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);
        depart = tmp[0];
        dest = tmp[1];

    }
}