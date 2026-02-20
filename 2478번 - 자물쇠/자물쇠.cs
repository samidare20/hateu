/* ************************************************************************** */
/*                                                                            */
/*                                                      :::    :::    :::     */
/*   Problem Number: 2478                              :+:    :+:      :+:    */
/*                                                    +:+    +:+        +:+   */
/*   By: dolphine103 <boj.kr/u/dolphine103>          +#+    +#+          +#+  */
/*                                                  +#+      +#+        +#+   */
/*   https://boj.kr/2478                           #+#        #+#      #+#    */
/*   Solved: 2026/02/20 15:07:36 by dolphine103   ###          ###   ##.kr    */
/*                                                                            */
/* ************************************************************************** */
namespace boj2478;

partial class Program
{
    [System.Diagnostics.Conditional("DEBUG")]
    static void DebugPrint(object a)
    {
        Console.Write(a);
    }
    [System.Diagnostics.Conditional("DEBUG")]
    static void DebugPrintLine(object a=null)
    {
        if(a==null)
            Console.WriteLine("");
        else
            Console.WriteLine(a);
    }
    static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    static int length,head,tail;
    static int[] Board=new int[2020];
    public static int[] Swap(int[] argboard,int n,int m)
    {
        int left=n+head;
        int right=m+head;
        int []tmpboard=new int[length];
        Array.Copy(argboard,head,tmpboard,0,length);

        while(n<m)
        {
            int tmp=tmpboard[n];
            tmpboard[n]=tmpboard[m];
            tmpboard[m]=tmp;
            n+=1;
            m-=1;
        }
        // foreach(int i in tmpboard)
        //     DebugPrint(i+" ");
        return tmpboard;
    }
    public static void PushBoard(int count)
    {
        for(int i=0;i<count;i++)
        {
            Board[head-1]=Board[tail];
            head-=1;
            tail-=1;
        }
    }
    public static (int,int) GetImpurity(int[] argboard)
    {
        int tmp=argboard[0]%length+1;


        (int,int) ans=(-1,-1);
        for(int i=1;i<length;i++)
        {
            if(tmp!=argboard[i])
            {
                ans.Item1=i;
                DebugPrintLine($"tmp : {tmp}");
                for(int j=0;j<length;j++)
                {
                    DebugPrint($"{argboard[j]}  ");
                    if(argboard[j]==tmp)
                    {
                        ans.Item2=j;
                        break;
                    }
                }
                DebugPrintLine();
                break;
            }
            else
            {
                tmp=tmp%length+1;
            }
        }
        return ans;
    }
    public static void Main()
    {
        Init();
        var a = (-1, -1);
        int lastpushcount = 0;
        int firstpushcount = 0;
        for (int i = 0; i < length-1; i++)
        {
            PushBoard(1);
            lastpushcount += 1;
            DebugPrintLine($"pushed : {lastpushcount}");
            bool result=solv(ref a,ref firstpushcount);
            if(result==true)
            {
                sw.WriteLine(firstpushcount);
                sw.WriteLine($"{a.Item1+1} {a.Item2+1}");
                sw.WriteLine(lastpushcount);
                sw.Close();
                return;
            }
        }


        sw.Close();
    }
    static bool solv(ref(int,int) Origina,ref int Originfirstpushcount)
    {
        (int, int) a = (-1, -1);
#if DEBUG
        DebugPrintLine($"head : {head} tail : {tail}");
            DebugPrintLine("before");
            for (int t = head; t <= tail; t++)
                DebugPrint($"{Board[t]} ");
#endif

            DebugPrintLine();

            int[] tmpboard = new int[length];
            Array.Copy(Board, head, tmpboard, 0, length);
            a = GetImpurity(tmpboard);
            DebugPrintLine($"aitem {a.Item1} {a.Item2}");
        if (a.Item1 == -1)
            return false;

            int[] tmp = Swap(Board, a.Item1, a.Item2);

#if DEBUG
            DebugPrintLine("after");
            for (int t = 0; t < length; t++)
                DebugPrint($"{tmp[t]} ");
            DebugPrintLine();
#endif
            var b = GetImpurity(tmp);
        if (b.Item1 != -1)
            return false;
        if (tmp[0] == 1)
            return false;
        int firstpushcount = 1;
        for (firstpushcount=1; firstpushcount<length-1 && tmp[length-firstpushcount] != 1; firstpushcount++) ;
        
        Originfirstpushcount = firstpushcount;
        Origina = a;
        return true;
    }
    static void Init()
    {        
        length=int.Parse(sr.ReadLine());
        int[]tmp=Array.ConvertAll(sr.ReadLine().Split(" "),int.Parse);
        for(int i=2000-length;i<2000;i++)
        {
            Board[i]=tmp[i-2000+length];
        }
        head=2000-length;
        tail=1999;
    }
}