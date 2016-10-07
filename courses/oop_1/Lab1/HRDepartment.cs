using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1{
    class HRDepartment {
        private static Random randomizer;
        private static string[] names = new string[] { "Noah", "Liam", "Mason", "Jacob", "William", "Ethan", "Michael", "Alexander", "James", "Daniel", "Elijah", "Benjamin", "Logan", "Aiden", "Jayden" };
        private static string[] surnames = new string[]{"Jones", "Williams", "Campbell", "Davis", "Thompson", "Kelly", "Sullivan", "O'Brien", "Evans", "Brown", "Lewis", "Wilson", "Wallace", "Ryan", "Moore", "Anderson"};
        private static string[] skills = new string[]{"Python", ".NET", "C/C++", "Java", "Swift", "Obj-C", "Scala", "NodeJS", "React/Redux", "Angular2","Haskell"};

        static HRDepartment() {
            randomizer = new Random();
        }
        
        private string randomName() {
            return names[randomizer.Next(names.Length)]; 
        }

        private string randomSurname() {
            return surnames[randomizer.Next(surnames.Length)];
        }   

        private string randomSkill() {
            return skills[randomizer.Next(skills.Length)];
        }
        
        public Programmer hireProgrammer() {
            return new Programmer(randomName(),randomSurname(), randomSkill());
        }

        public TechLead hireTechLead() {
            return new TechLead(randomName(), randomSurname());
        }

        public Tester hireTester() {
            return new Tester(randomName(), randomSurname());
        }

        public QALead hireQALead() {
            return new QALead(randomName(), randomSurname());
        }

        public Analyst hireAnalyst() {
            return new Analyst(randomName(), randomSurname());
        }

        public AnalyticsLead hireAnalyticsLead() {
            return new AnalyticsLead(randomName(), randomSurname());
        }
    }
}
