namespace boj14891;
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Dynamic;
using System.ComponentModel;
using System.Collections;
using System.Threading.Tasks.Dataflow;

partial class Program
{
    static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));    

    static LinkedList<int>[] board=new LinkedList<int>[4];
    static void Main(string[] args)
    {
        Init();
        Input();
        GetAnswer();

        sw.Close();
    }
    static void Init()
    {
        for(int i=0;i<4;i++)
            board[i]=new LinkedList<int>();
    }
    static void TurnClock(ref LinkedList<int> l)
    {
        LinkedListNode<int> tmp=l.Last;
        l.RemoveLast();
        l.AddFirst(tmp);
    }
    static void TurnUnclock(ref LinkedList<int>l)
    {
        LinkedListNode<int> tmp=l.First;
        l.RemoveFirst();
        l.AddLast(tmp);
    }
    static int[] LinkedListToArray(LinkedList<int>l)
    {
        int[]a=new int[8];
        var iter=l.First;
        for(int i=0;i<8;i++)
        {
            a[i]=iter.Value;
            iter=iter.Next;
        }
        return a;
    }
    static void TurnFlowRight(int turn_where,int turn_dire)
    {
        if(turn_where<3)
        {
            int[]now=LinkedListToArray(board[turn_where]);
            int[]next=LinkedListToArray(board[turn_where+1]);

            if(now[2]!=next[6])
            {
                TurnFlowRight(turn_where+1,turn_dire*-1);
            }
        }
        Turn(turn_where,turn_dire);
    }
    static void TurnFlowLeft(int turn_where,int turn_dire)
    {
        if(turn_where>0)
        {
            int[]now=LinkedListToArray(board[turn_where]);
            int[]next=LinkedListToArray(board[turn_where-1]);

            if(now[6]!=next[2])
            {
                TurnFlowLeft(turn_where-1,turn_dire*-1);
            }
        }
        Turn(turn_where,turn_dire);
    }
    static void Turn(int turn_where,int turn_dire)
    {

        if(turn_dire==1)
            TurnClock(ref board[turn_where]);
        else
            TurnUnclock(ref board[turn_where]);
    }
    static void Input()
    {
        for(int i=0;i<4;i++)
        {
            foreach(char c in sr.ReadLine().ToCharArray())
            {
                var node=new LinkedListNode<int>(c-'0');
                board[i].AddLast(node);
            }
        }

        #if DEBUG
            TestPrintAllGear();
        #endif

        int testcase;
        testcase=int.Parse(sr.ReadLine());
        for(int i=0;i<testcase;i++)
        {
            int turn_where,turn_dire;
            int[]s=Array.ConvertAll(sr.ReadLine().Split(" "),int.Parse);
            turn_where=s[0]-1;
            turn_dire=s[1];

            TurnFlowLeft(turn_where,turn_dire);
            // TestPrintAllGear();
            Turn(turn_where,turn_dire*-1);
            // TestPrintAllGear();
            TurnFlowRight(turn_where,turn_dire);
            // TestPrintAllGear();
            // sw.WriteLine("=======================================");
            // if(i==1)
            //     return;
            #if DEBUG
                // sw.Write("turned!!");
                // TestPrintAllGear();
                // TestPrintAllGear();
            #endif
        }
    }
    static void GetAnswer()
    {
        int ans=0;
        for(int i=0;i<4;i++)
        {
            int a=board[i].First.Value;
            ans+=a*(int)Math.Pow(2,i);
        }
        sw.Write(ans);
    }

}
