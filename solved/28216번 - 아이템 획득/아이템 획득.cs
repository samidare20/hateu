/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 28216                             :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/28216                          #+#        #+#      #+#    */
/*   Solved: 2026/02/25 10:02:01 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
class Program
{
    [Conditional("DEBUG")]
    static void DebugPrint(object o)
    {
        Console.Write(o.ToString());
    }
    [Conditional("DEBUG")]
    static void DebugPrintLine(object o)
    {
        if (o == null)
            o = "";
        Console.WriteLine(o.ToString());
    }
    static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    static (int,int)[] Direction = { (1,0),(0,1),(-1,0),(0,-1) };

    public static void Main()
    {
        int ChestCount = 0, MoveCount = 0;
        (int, int) CarPos = (1, 1);

        Input(ref ChestCount, ref MoveCount,ref CarPos);
        
        sw.Close();
    }
    /*static int Solv(int Direct,int MoveSize, int[][]Board,ref (int,int)CarPos)
    {

    }*/
    static void SortPrefixList(ref List<(int, long)>[] l, List<int>target)
    {
        foreach(var i in target)
        {
            l[i].Sort(new Comparison<(int,long)>((n1,n2)=>n1.Item1.CompareTo(n2.Item1)));
        }
        foreach(var i in target)
        {
            DebugPrintLine($"pos : {i}");
            for (int j = 1; j < l[i].Count; j++)
            {
                l[i][j] = (l[i][j].Item1, l[i][j].Item2 + l[i][j - 1].Item2);
                DebugPrint($"{l[i][j]} ");
            }
            DebugPrintLine("\n\n");
        }
    }
    static int GetIndex(List<(int, long)>l,int target,int tmp)
    {
        int i = l.BinarySearch((target,0),Comparer<(int, long)>.Create((n1, n2) =>
        {
            return n1.Item1.CompareTo(n2.Item1);
        }));
        if (i >= 0)
            return i-tmp;

        if (i < 0)
            i = ~i-1;
        return i;
    }
    static long GetCost((int,int)a,(int,int)b,int dir, List<(int, long)>[] XPrefixSum, List<(int, long)>[] YPrefixSum)
    {
        int from, to;
        long ans = 0L;
        if(dir==0)
        {
            from = GetIndex(XPrefixSum[a.Item2], a.Item1,0);
            to = GetIndex(XPrefixSum[b.Item2], b.Item1,0);
            ans = XPrefixSum[a.Item2][to].Item2 - XPrefixSum[a.Item2][from].Item2;
        }
        else if(dir==2)
        {
            to = GetIndex(XPrefixSum[a.Item2], a.Item1,1);
            from = GetIndex(XPrefixSum[b.Item2], b.Item1,1);
            ans = XPrefixSum[a.Item2][to].Item2 - XPrefixSum[a.Item2][from].Item2;
        }
        else if(dir==1)
        {
            from=GetIndex(YPrefixSum[a.Item1],a.Item2,0);
            to = GetIndex(YPrefixSum[b.Item1], b.Item2, 0);
            ans=YPrefixSum[a.Item1][to].Item2 - YPrefixSum[a.Item1][from].Item2;
        }
        else
        {
            to = GetIndex(YPrefixSum[a.Item1], a.Item2,1);
            from = GetIndex(YPrefixSum[b.Item1], b.Item2,1);
            ans = YPrefixSum[a.Item1][to].Item2 - YPrefixSum[a.Item1][from].Item2;
        }
        return ans;
    }
    static void Input(ref int ChestCount,ref int MoveCount,ref (int,int)CarPos)
    {
        List<(int, long)>[] XPrefixSum = new List<(int, long)>[200001]; //pos,sum
        List<(int, long)>[] YPrefixSum = new List<(int, long)>[200001]; //pos,sum
        for(int i=0;i<200001;i++)
        {
            XPrefixSum[i] = new List<(int, long)>() { (0,0)};
            YPrefixSum[i] = new List<(int, long)>() { (0,0)};
        }
        List<int> XSortTarget = new List<int>(200001);
        bool[] XTargetVisit = new bool[200001];
        List<int> YSortTarget = new List<int>(200001);
        bool[] YTargetVisit = new bool[200001];
        int[] tmp = Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);        
        ChestCount=tmp[0];
        MoveCount=tmp[1];

        for(int i=0;i<ChestCount;i++)
        {
            tmp= Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);
            XPrefixSum[tmp[1]].Add((tmp[0], tmp[2]));
            YPrefixSum[tmp[0]].Add((tmp[1], tmp[2]));
            if (XTargetVisit[tmp[1]] == false)
            {
                XSortTarget.Add(tmp[1]);
                XTargetVisit[tmp[1]]= true;
            }
            if (YTargetVisit[tmp[0]] == false)
            {
                YSortTarget.Add(tmp[0]);
                YTargetVisit[tmp[0]] = true;
            }
        }
        SortPrefixList(ref XPrefixSum, XSortTarget);
        SortPrefixList(ref YPrefixSum, YSortTarget);
        long sum = 0L;
        //Console.Write(GetIndex(XPrefixSum[5],10));
        //return;
        for(int i=0;i<MoveCount;i++)
        {
            tmp = Array.ConvertAll(sr.ReadLine().Split(" "), int.Parse);
            (int, int) movepos=(CarPos.Item1,CarPos.Item2);

            movepos.Item1 += Direction[tmp[0]].Item1 * tmp[1];
            movepos.Item2 += Direction[tmp[0]].Item2 * tmp[1];
            long ans= GetCost(CarPos, movepos,tmp[0],XPrefixSum,YPrefixSum);

            DebugPrintLine($"ans : {ans}");
            sum += ans;
            CarPos=(movepos.Item1,movepos.Item2);
            DebugPrintLine($"carpos : {CarPos}");

        }
        sw.Write(sum);
    }
}