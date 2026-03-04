namespace System;
class Program
{
    public static StreamReader sr = new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    public static StreamWriter sw = new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    static int[] movex={1,-1,0,0};
    static int[]movey={0,0,1,-1};
    static int maxans=0;
    public static void Main()
    {
        int BoardHeight=0,BoardWidth=0,GreenStartCount=0,RedStartCount=0;
        int[][]Board=new int[50][]; //8=green 9=red 5=flower
        (int,int)[]CanPlant=new (int, int)[10];
        for(int i=0;i<50;i++)
            Board[i]=new int[50];

        Input(ref BoardHeight,ref BoardWidth,ref GreenStartCount,ref RedStartCount,ref Board,ref CanPlant);
        Console.WriteLine("hello world");
        plant(BoardHeight,BoardWidth,GreenStartCount,RedStartCount,CanPlant,Board,0,GreenStartCount+RedStartCount);
        
    }
    static void plant(int height,int width,int green,int red,(int,int)[]canplant,int[][]board,int index,int maxindex)
    {
        if(green+red==0)
        {
            int ans=Solv(height,width,board);
            Console.WriteLine($"ans : {ans}");
            maxans=Math.Max(ans,maxans);
            return;
        }
     
        if(index==maxindex)
            return;   
        var a=canplant[index];
        if(green>0)
        {
            board[a.Item1][a.Item2]=8;
            plant(height,width,green-1,red,canplant,board,index+1,maxindex);
            board[a.Item1][a.Item2]=2;
        }
        if(red>0)
        {                
            board[a.Item1][a.Item2]=9;
            plant(height,width,green,red-1,canplant,board,index+1,maxindex);
            board[a.Item1][a.Item2]=2;
        }
        plant(height,width,green,red,canplant,board,index+1,maxindex);

    }
    static int Solv(int height,int width,int[][]boardorigin)
    {
        Console.WriteLine("======start======");
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
                Console.Write(boardorigin[i][j]+" ");
            Console.WriteLine();
        }
        Console.WriteLine("==============");
        
        int countred=0,countgreen=0;
        int ans=0;
        int[][]visit=new int[50][];
        int[][]board=new int[50][];
        for(int i=0;i<50;i++)
        {
            visit[i]=new int[50];
            board[i]=new int[50];
        }
            
        Queue<(int,int)>q=new Queue<(int, int)>();
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                board[i][j]=boardorigin[i][j];
                if(boardorigin[i][j]==9||boardorigin[i][j]==8)
                {
                    q.Enqueue((i,j));
                    visit[i][j]=1;
                    if(boardorigin[i][j]==9)
                        countred+=1;
                    else
                        countgreen+=1;
                }
            }
        }

        while(q.Count>0)
        {
            if(countgreen==0||countred==0)
                return ans;
            var a=q.Dequeue();
            Console.WriteLine($"a : {a}");
            if(board[a.Item1][a.Item2]==8)
                countgreen-=1;
            else if(board[a.Item1][a.Item2]==9)
                countred-=1;
            for(int i=0;i<4;i++)
            {
                int X=movex[i]+a.Item2;
                int Y=movey[i]+a.Item1;
                if(X<0||Y<0||X>=width||Y>=height||board[Y][X]==0||board[Y][X]==5) //범위 나갔음, 타일이 물이거나 꽃임
                    continue;
                if(board[Y][X]==board[a.Item1][a.Item2]) //같은 색으로 칠해짐
                    continue;
                if((board[Y][X]==1||board[Y][X]==2)&&visit[Y][X]==0) //방문하지 않은 땅 타일
                {
                    board[Y][X]=board[a.Item1][a.Item2];
                    visit[Y][X]=visit[a.Item1][a.Item2];
                    q.Enqueue((Y,X));                    
                    continue;
                }
                if(visit[Y][X]==visit[a.Item1][a.Item2]) //같은 시간에 서로다른 색이 만남
                {
                    ans+=1;
                    board[Y][X]=5;
                    continue;
                }
                else//다른시간에 서로다른 색이 만남
                {
                    continue;
                }
            }
            
        Console.WriteLine("======working======");
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
                Console.Write(board[i][j]+" ");
            Console.WriteLine();
        }
        Console.WriteLine("==============");
        }
        return ans;
    }
    static void Input(ref int height,ref int width,ref int green,ref int red,ref int[][]board,ref (int,int)[]canplant)
    {
        int[]tmp=Array.ConvertAll(sr.ReadLine().Split(" "),int.Parse);
        height=tmp[0];
        width=tmp[1];
        green=tmp[2];
        red=tmp[3];

        int count=0;
        for(int i=0;i<height;i++)
        {
            board[i]=Array.ConvertAll(sr.ReadLine().Split(" "),int.Parse);
            for(int j=0;j<width;j++)
            {
                if(board[i][j]==2)
                {
                    canplant[count]=(i,j);
                    count+=1;
                }
            }
        }
    }
}