using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1{
    /// <summary>
    /// Technical class where new company members are "hired"(objects initialized and filled with random data)
    /// </summary>
    class HRDepartment {
        private static Random randomizer;
        private static HRDepartment instance;

        /// <summary>
        /// Lists of names, surnames and it-skills to pick from.
        /// </summary>
        private static string[] names = new string[] { "Noah", "Liam", "Mason", "Jacob", "William", "Ethan", "Michael", "Alexander", "James", "Daniel", "Elijah", "Benjamin", "Logan", "Aiden", "Jayden" };
        private static string[] surnames = new string[]{"Jones", "Williams", "Campbell", "Davis", "Thompson", "Kelly", "Sullivan", "O'Brien", "Evans", "Brown", "Lewis", "Wilson", "Wallace", "Ryan", "Moore", "Anderson"};
        private static string[] skills = new string[]{"Python", ".NET", "C/C++", "Java", "Swift", "Obj-C", "Scala", "NodeJS", "React/Redux", "Angular2","Haskell"};

        public static HRDepartment Instance {
            get {
                if (instance == null)
                    instance = new HRDepartment();
                return instance;
            }
        }

        private HRDepartment() {

        }

        static HRDepartment() {
            randomizer = new Random();
        }
        /// <summary>
        /// Picks random name from the list above
        /// </summary>
        /// <returns>random name</returns>
        private static string randomName() {
            return names[randomizer.Next(names.Length)]; 
        }

        private static string randomSurname() {
            return surnames[randomizer.Next(surnames.Length)];
        }   

        private static string randomSkill() {
            return skills[randomizer.Next(skills.Length)];
        }
        
        /// <summary>
        /// Creates a new instance of Programmer and fills it with random data
        /// </summary>
        /// <returns>new Programmer instance</returns>
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
