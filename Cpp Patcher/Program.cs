﻿using System.Data;
using System.Text.Json;

class Program
{
    struct Settings
    {
        public string srcDirectory { get; set; }
        public string compilerDirectory { get; set; }
        public string outputDirectory { get; set; }
        public string includeDirectory {get;set;}
    }

    private const string MapFile = "CPP Mapping.txt";
    private static Settings settings;
    public static void Main(string[] args)
    {
        settings = GetSettings();
        Dictionary<string, string> cppToOMaps = GetCPPOMap();

        foreach (var srcPath in cppToOMaps.Keys)
        {
            if (!File.Exists(settings.srcDirectory + "/" + srcPath))
            {
                Console.WriteLine($"Could not find file with name '{srcPath}'");
                continue;
            }

            // Compile the thing
            string command = $"-c \"{settings.srcDirectory.Replace('\\','/')}/{srcPath}\" -i \"{settings.includeDirectory}\" -O4 -o \"{settings.outputDirectory}/{cppToOMaps[srcPath]}\"";
            Console.WriteLine($"Running command: \n\t{command}");
            RunCommand(command);
        }
    }

    private static void RunCommand(string command)
    {
        System.Diagnostics.Process process = new System.Diagnostics.Process();
        System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
        startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
        startInfo.FileName = $"{settings.compilerDirectory.Replace('\\', '/')}/mwcceppc.exe";
        startInfo.Arguments = $"{command}";
        process.StartInfo = startInfo;
        process.Start();
        
        while (!process.HasExited)
        {

        }
    }

    private static Settings GetSettings()
    {
        if (!File.Exists("settings.json"))
        {
            File.WriteAllText("settings.json", JsonSerializer.Serialize(new Settings(), typeof(Settings)));
            return new Settings();
        }

        return (Settings)JsonSerializer.Deserialize(File.ReadAllText("settings.json"), typeof(Settings));
    }

    private static Dictionary<string, string> GetCPPOMap()
    {
        if (!File.Exists(MapFile))
        {
            File.Create(MapFile);
            return new Dictionary<string, string>();
        }

        Dictionary<string, string> map = new Dictionary<string, string>();
        foreach (var line in File.ReadAllLines(MapFile))
        {
            string[] segs = line.Split(':');
            map.Add(segs[0], segs[1]);
        }

        return map;
    }
}