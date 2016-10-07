using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class Program {
        static void Main(string[] args) {
            Project proj = new Project("Test App", 10);
            proj.HR = new HRDepartment();
            ProjectManager pm = new ProjectManager("Dmitry", "Petrenko");
            pm.Project = proj;
            pm.hireLeads();

            Console.ReadLine();
        }
    }
}
