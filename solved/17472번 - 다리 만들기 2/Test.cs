namespace boj17472;
partial class Program
{
    static void TestPrintLand()
    {
        for(int i=0;i<BoardY;i++)
        {
            for(int j=0;j<BoardX;j++)
            {
                sw.Write(Board[i][j]+" ");
            }
            sw.WriteLine();
        }
        sw.WriteLine();
        sw.WriteLine();
    }
    static void TestPrintIsInLand()
    {
        char[][]tmp=new char[BoardY][];
        for(int i=0;i<BoardY;i++)
            tmp[i]=new char[BoardX];
        for(int i=2;i<=LandNumber;i++)
        {
            foreach(var j in LandBoard[i])
            {
                if(j==(-1,-1))
                    break;
                tmp[j.Item1][j.Item2]='*';
            }            
        }
        for(int i=0;i<BoardY;i++)
        {
            for(int j=0;j<BoardX;j++)
            {
                if(tmp[i][j]=='*')
                    sw.Write("@ ");
                else
                    sw.Write("# ");
            }
            sw.WriteLine();
        }
        sw.WriteLine();
        sw.WriteLine();
    }
    static void TestPrintBridge()
    {
        sw.Write("========cost==========\n");
        for(int i=2;i<=LandNumber;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(Cost[i][j]!=987654321)
                    sw.WriteLine("{0}->{1} : {2}\n",i,j,Cost[i][j]);
            }
        }
    }
}