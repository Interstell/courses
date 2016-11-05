using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    /// <summary>
    /// Class to represent a Tester - member of QA Team.
    /// </summary>
    class Tester : Employee{

        private int LOCCoveredToday = 0;
        private int LOCCoverExpected = 200;

        public Tester() : base() { }
        
        public Tester(string name, string surname) : base(name, surname) { }

        /// <summary>
        /// Tester constructor
        /// </summary>
        /// <param name="name">Name</param>
        /// <param name="surname">Surname</param>
        /// <param name="hourPayRate">Payrate per hour</param>
        public Tester(string name, string surname, int hourPayRate) : base(name, surname, hourPayRate) { }

        protected override void payMoney() {
            if (LOCCoverExpected / LOCCoveredToday > 0.25) {
                base.payMoney();
            }
        }

        public override int Work() {
            LOCCoveredToday = rand.Next(1, LOCCoverExpected);
            payMoney();
            return LOCCoveredToday;
        }

        public override string ToString() {
            return String.Format("{0} {1}, tester", Name, Surname);
        }
    }
}
