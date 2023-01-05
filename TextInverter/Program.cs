using System;
using System.IO;

namespace Sentence_Inverter
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WindowWidth = 200;
            Console.WindowHeight = 50;

            Console.Write("Input the path of the text file (.txt) of which you wish to to have the text inverted (e.g. D:\\Program Files\\config):\n\n");
            string filePath = Console.ReadLine() + "\\";
            Console.Write("\nInput the name of the file (e.g. File): ");
            string fileName = Console.ReadLine();

            string sInvertedFileName;

            StreamReader streamReader = new StreamReader(@"" + filePath + fileName + ".txt");
            string[] text = new string[System.IO.File.ReadAllLines(@"" + filePath + fileName + ".txt").Length];
            string[] invertedText = new string[text.Length];


            for (int n = 0; !streamReader.EndOfStream; n++)
            {
                text[n] = streamReader.ReadLine(); 
            }

            for (int i = 0; i < text.Length; i++)
            {
                char[] cAux = new char[text[i].Length+1];

                int j;
                for (j = 0; j < text[i].Length; j++)
                {
                    text[i].CopyTo(j, cAux, text[i].Length - j - 1, 1);
                }
                cAux[j] = '\0';

                invertedText[text.Length - i - 1 ] = new string(cAux);

            }

            Console.WriteLine("\nInverted text:\n");
            for (int i = 0; i < text.Length; i++)
            {
                Console.WriteLine(invertedText[i]);
            }

            char[] invertedFileName = new char[fileName.Length + 1];
            int r;
            for (r = 0; r < fileName.Length; r++)
            {
                fileName.CopyTo(fileName.Length - r - 1, invertedFileName, r, 1);
            }

            sInvertedFileName = filePath + new string(invertedFileName).Remove(r) + ".txt";
            invertedFileName[r] = '\0';

            if (!File.Exists(sInvertedFileName))
            {
                using (StreamWriter sw = new StreamWriter(sInvertedFileName))
                {
                    for (int l = 0; l < text.Length; l++)
                    {
                        sw.WriteLine(invertedText[l]);
                    }
                }
                Console.WriteLine("\n\n\nInverted file created at the same path as the original one.");
            }
            else
            {
                Console.WriteLine("\n\n\nThe inverted file could not be created (The desired path already exists).");
            }

            Console.WriteLine("Inverted file path: " + sInvertedFileName);
            Console.WriteLine("O Thiago lê hentai btw...");
            Console.ReadKey();
        }
    }
}