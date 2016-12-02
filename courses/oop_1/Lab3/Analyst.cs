using System;

namespace Lab3 {
    public class Analyst : Employee {
       
        private int tasksDocumentedToday;
        private int tasksExpectedToday = 3;

        public Analyst() : base() { }
        
        public Analyst(string name, string surname) : base(name, surname) { }

        public Analyst(string name, string surname, int hourPayRate) : base(name, surname, hourPayRate) { }

        public override int Work() {
            tasksDocumentedToday = rand.Next(1, tasksExpectedToday);
            PayMoney();
            return tasksDocumentedToday;
            
        }

        public override string ToString() {
            return String.Format("{0} {1}, analyst", Name, Surname);
        }
    }
}
