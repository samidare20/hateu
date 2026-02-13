namespace boj17472;
using System;
partial class Program
{
    static StreamReader sr=new StreamReader(new BufferedStream(Console.OpenStandardInput()));
    static StreamWriter sw=new StreamWriter(new BufferedStream(Console.OpenStandardOutput()));
    static int LandNumber=2;
    static int BoardY;
    static int BoardX;
    static int[][]Cost=new int[10][];
    static int[][] Board=new int[10][];
    static (int,int)[][] LandBoard=new (int,int)[10][];
    static int[] DisjointParent=new int[10];

    static void Main()
    {
        Init();
        Input();
        MakeLand();

        #if DEBUG
            TestPrintIsInLand();
        #endif

        MakeBridge();

        #if  DEBUG
            TestPrintBridge();
        #endif

        CalcCost();

        sw.Close();
    }
    static void CalcCost()
    {
        PriorityQueue<(int,int),int> pq=new PriorityQueue<(int, int), int>();
        for(int i=2;i<=LandNumber;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(Cost[i][j]!=987654321&&Cost[i][j]>0)
                    pq.Enqueue((i,j),Cost[i][j]);
            }
        }
        int connectcount=1;
        int ans=0;
        while(pq.Count>0)
        {
            if(pq.TryDequeue(out (int,int)a,out int cost))
            {
                if(DisjointUnion(a.Item1,a.Item2))
                {
                    connectcount+=1;
                    // sw.Write("Cost : {0}, {1}->{2}\n",cost,a.Item1,a.Item2);
                    ans+=cost;
                }    
            }
            
        }
        // sw.Write("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        for(int i=3;i<LandNumber;i++)
        {
            if(DisjointUnion(2,i))   
            {
                sw.Write(-1);
                return;
            }
        }
            sw.Write(ans);
    }
    static int DisjointGetParent(int i)
    {
        if(i==DisjointParent[i])
            return i;
        DisjointParent[i]=DisjointGetParent(DisjointParent[i]);
        return DisjointParent[i];
    }
    static bool DisjointUnion(int a,int b)
    {
        int pa=DisjointGetParent(a);
        int pb=DisjointGetParent(b);
        // sw.Write("pa : {0} pb : {1}\n",pa,pb);
        if(pa!=pb)
        {
            DisjointParent[pa]=pb;
            return true;
        }
        return false;
    }
    static void MakeBridge()
    {        
        int[]movex={0,0,1,-1};
        int[]movey={1,-1,0,0};
        for(int i=2;i<=LandNumber;i++)
        {
            foreach(var j in LandBoard[i])
            {
                if(j==(-1,-1))
                    break;
                for(int t=0;t<4;t++)
                {
                    int X=j.Item2;
                    int Y=j.Item1;
                    int cost=0;
                    while(true)
                    {
                        X+=movex[t];
                        Y+=movey[t];
                        cost+=1;

                        if(!(X>=0&&X<BoardX&&Y>=0&&Y<BoardY))
                            break;
                        if(Board[Y][X]==i) //self
                            break;
                        if(cost<=2&&Board[Y][X]!=0)
                            break;  
                        if(Board[Y][X]==0)
                            continue;
                        cost-=1;
                        // Console.WriteLine("going {0} {1}",movey[t],movex[t]);
                        Cost[Board[Y][X]][i]=Math.Min(Cost[Board[Y][X]][i],cost);
                        Cost[i][Board[Y][X]]=Math.Min(Cost[i][Board[Y][X]],cost);
                        // Console.WriteLine("started at {3} / {0} -> {1} , cost : {2}\n\n",Board[Y][X],i,Cost[Board[Y][X]][i],j);
                        break;
                    }

                }
            }            
        } 
    }
    static void Init()
    {
        for(int i=0;i<10;i++)
        {
            DisjointParent[i]=i;
            Board[i]=new int[10];
            LandBoard[i]=new(int,int)[100];
            Cost[i]=new int[10];
            for(int j=0;j<LandBoard[i].Length;j++)
                LandBoard[i][j]=(-1,-1);
            for(int j=0;j<10;j++)
            {
                if(i==j)
                    Cost[i][j]=0;
                else
                    Cost[i][j]=987654321;
            }   
        }
    }
    static void MakeLand()
    {
        bool[][]visit=new bool[BoardY][];
        for(int i=0;i<BoardY;i++)
        {
            visit[i]=new bool[BoardX];
            for(int j=0;j<BoardX;j++)
                visit[i][j]=false;
        }

        
        for(int i=0;i<BoardY;i++)
        {
            for(int j=0;j<BoardX;j++)
            {
                if(visit[i][j]==true)
                    continue;
                if(Board[i][j]==0)
                {
                    visit[i][j]=true;
                    continue;
                }
                visit[i][j]=true;
                FindLand(i,j,ref visit);
                LandNumber+=1;

                #if DEBUG
                    TestPrintLand();
                #endif
            }
        }
    }
    static bool IsInLand(int y,int x)
    {
        int[]movex={0,0,1,-1};
        int[]movey={1,-1,0,0};
        for(int i=0;i<4;i++)
        {
            int X=x+movex[i];
            int Y=y+movey[i];
            if(X<0||X>=BoardX||Y<0||Y>=BoardY||Board[Y][X]!=0)
                continue;
            return true;
        }
        return false;
    }
    static void FindLand(int y,int x,ref bool[][]visit)
    {
        int cnt=0;
        int[]movex={0,0,1,-1};
        int[]movey={1,-1,0,0};
        Queue<(int,int)> q=new Queue<(int, int)>();
        q.Enqueue((y,x));
        Board[y][x]=LandNumber;
        if(IsInLand(y,x))
        {
            LandBoard[LandNumber][cnt]=(y,x);
            cnt+=1;
        }
        
        while(q.Count>0)
        {
            var a=q.Dequeue();
            for(int i=0;i<4;i++)
            {
                int X=a.Item2+movex[i];
                int Y=a.Item1+movey[i];
                if(X<0||X>=BoardX||Y<0||Y>=BoardY||Board[Y][X]==0||visit[Y][X]==true)
                    continue;
                visit[Y][X]=true;
                Board[Y][X]=LandNumber;
                if(IsInLand(Y,X))
                {
                    LandBoard[LandNumber][cnt]=(Y,X);
                    cnt+=1;
                }
                q.Enqueue((Y,X));
            }
        }
        
    }
    static void Input()
    {
        int[]tmp=Array.ConvertAll(sr.ReadLine().Split(" "),int.Parse);
        BoardY=tmp[0];
        BoardX=tmp[1];

        for(int i=0;i<BoardY;i++)
        {
            Board[i]=Array.ConvertAll(sr.ReadLine().Split(" "),int.Parse);            
        }
    }
}