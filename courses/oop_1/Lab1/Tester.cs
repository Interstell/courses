using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class Tester:Employee{


        public Tester() : base() { }
        
        public Tester(string name, string surname) : base(name, surname) { }

        public Tester(string name, string surname, int hourPayRate) : base(name, surname, hourPayRate) { }
        
        public override string ToString() {
            return String.Format("{0} {1}, tester", Name, Surname);
        }
    }
}
