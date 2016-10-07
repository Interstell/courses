using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Class to represent a Tester - member of QA Team.
    /// </summary>
    class Tester:Employee{

        public Tester() : base() { }
        
        public Tester(string name, string surname) : base(name, surname) { }

        /// <summary>
        /// Tester constructor
        /// </summary>
        /// <param name="name">Name</param>
        /// <param name="surname">Surname</param>
        /// <param name="hourPayRate">Payrate per hour</param>
        public Tester(string name, string surname, int hourPayRate) : base(name, surname, hourPayRate) { }
        
        public override string ToString() {
            return String.Format("{0} {1}, tester", Name, Surname);
        }
    }
}
