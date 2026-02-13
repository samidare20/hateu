namespace boj14891;
using System.Security.Cryptography.X509Certificates;



partial class Program
{
    static void TestPrintAllGear()
    {
        int[][] b=new int[4][];
        for(int i=0;i<4;i++)
            b[i]=new int[9];
        for(int i=0;i<4;i++)
        {
            var iter=board[i].First;   
            for(int j=0;j<8;j++)
            {
                b[i][j]=iter.Value;
                iter=iter.Next;
            }
        }
        int[]index=[7,0,1,6,10,2,5,4,3];
        for(int i=0;i<3;i++)
        {
            for(int k=0;k<4;k++)
            {
                for(int j=0;j<3;j++)                
                {
                    if(index[j+i*3]==10)
                        sw.Write("  ");
                    else
                        sw.Write(b[k][index[j+i*3]]+" ");
                }
                sw.Write("    ");
            }
            sw.WriteLine();
        }
        sw.WriteLine();
        sw.WriteLine();
        sw.WriteLine();
    }
}