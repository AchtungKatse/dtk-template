using System.Drawing;

public static class Debug
{
    public static void WriteSection(string name)
    {
        Console.WriteLine($"\n[ ----- {name} ----- ]");
    }

    public static void Writei(string info)
    {
        Console.ForegroundColor = ConsoleColor.White;
        Console.WriteLine(info);
    }
}
