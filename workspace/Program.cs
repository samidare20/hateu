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

    public static void Main()
    {
        sr.ReadLine();
        char[] tmp = sr.ReadLine().ToCharArray();
        Dictionary<char,int>d= new Dictionary<char,int>();
        d['A'] = 0;
        d['B'] = 0;
        foreach(char i in tmp)
        {
            d[i] += 1;
        }
        if (d['A'] > d['B'])
            sw.Write("A");
        else if (d['A'] < d['B'])
            sw.Write("B");
        else
            sw.Write("Tie");
        sw.Close();
    }
}