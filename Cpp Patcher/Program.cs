using System.Data;
using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;

class Program
{
    struct Settings
    {
        public string newObjPath { get; set; }
        public string symbolMapPath { get; set; }
    }

    private const string MapFile = "CPP Mapping.txt";
    private static Settings settings;

    public static void Main(string[] args)
    {
        settings = GetSettings();
        Dictionary<string, string> symbolMap = GetSymbolMap();

        List<string> missingSymbols = new List<string>();

        // Compile all source files to object files
        Debug.WriteSection("Finding missing symbols");
        foreach (var file in Directory.GetFiles(settings.newObjPath))
        {
            string elfInfo = RunCommand($"elf info {file}");
            
            // Filter symbols
            var symbols = Regex.Matches(elfInfo, @"\b([A-Z]|[a-z])*__\w*", RegexOptions.IgnoreCase);
            foreach (var match in symbols)
            {
                string missingMsg =$"{match}\t in {file}"; 
                if (!symbolMap.ContainsKey(match.ToString()) && !missingSymbols.Contains(missingMsg))
                    missingSymbols.Add(missingMsg);
            }
        }

        // Link all object files
        if (missingSymbols.Count > 0)
        {
            Debug.WriteSection("Missing Symbols");
            foreach (var symbol in missingSymbols)
            {
                Debug.Writei($"Symbol map missing \"{symbol}\"");
            }
        }
        else
        {
            Debug.WriteSection("No Missing Symbols!");
        }
    }

    private static string RunCommand(string command)
    {
        System.Diagnostics.Process process = new System.Diagnostics.Process();
        System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
        startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Normal;
        startInfo.FileName = $"../dtk.exe";
        startInfo.Arguments = $"{command}";
        startInfo.RedirectStandardOutput = true;
        process.StartInfo = startInfo;
        process.Start();

        string output = process.StandardOutput.ReadToEnd();
        process.WaitForExit();
        return output;

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

    private static Dictionary<string, string> GetSymbolMap()
    {
        Dictionary<string, string> map = new Dictionary<string, string>();
        string[] lines = File.ReadAllLines(settings.symbolMapPath);
        foreach (var line in lines)
        {
            string[] segments = line.Split(' ');
            if (map.ContainsKey(segments[0]))
            {
                Console.WriteLine($"Found duplicate symbol \"{segments[0]}\"");
                continue;
            }
            map.Add(segments[0], line);
        }

        return map;
    }
}
