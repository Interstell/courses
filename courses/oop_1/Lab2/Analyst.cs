using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    class Analyst : Employee {
        /// <summary>
        /// Class representing an Analyst - member of Analytics Team.
        /// </summary>
        private int tasksDocumentedToday;
        private int tasksExpectedToday = 3;

        public Analyst() : base() { }
        
        public Analyst(string name, string surname) : base(name, surname) { }

        /// <summary>
        /// Analyst constructor
        /// </summary>
        /// <param name="name">Name</param>
        /// <param name="surname">Surname</param>
        /// <param name="hourPayRate">Payrate by hour</param>
        public Analyst(string name, string surname, int hourPayRate) : base(name, surname, hourPayRate) { }

        public override int Work() {
            tasksDocumentedToday = rand.Next(1, tasksExpectedToday);
            payMoney();
            return tasksDocumentedToday;
            
        }

        public override string ToString() {
            return String.Format("{0} {1}, analyst", Name, Surname);
        }
    }
}
