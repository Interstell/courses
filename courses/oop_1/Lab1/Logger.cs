using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    static class Logger {
        
        public static void write(string message){
            Console.WriteLine(message);
        }

        public static void newProject(string name, int usCount) {
            Console.WriteLine("New project \"{0}\" started!\n{1} user stories are to be implemented.", name, usCount);
        }

        public static void leadHired(string position, string info) {
            Console.WriteLine("New {0} hired for project: {1}", position, info);
        }

        public static void memberHired(string info) {
            Console.WriteLine("\tNew team member hired: " + info);
        }

    }
}
