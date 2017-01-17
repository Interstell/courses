using System;

namespace Lab4 {

    public class Tester : Employee{

        private int LOCCoveredToday = 0;
        private int LOCCoverExpected = 200;

        public Tester() : base() { }
        
        public Tester(string name, string surname) : base(name, surname) { }

        public Tester(string name, string surname, int hourPayRate) : base(name, surname, hourPayRate) { }

        protected override void PayMoney() {
            if (LOCCoverExpected / LOCCoveredToday > 0.25) {
                base.PayMoney();
            }
        }

        public override int Work() {
            LOCCoveredToday = rand.Next(1, LOCCoverExpected);
            PayMoney();
            return LOCCoveredToday;
        }

        public override string ToString() {
            return String.Format("{0} {1}, tester", Name, Surname);
        }
    }
}
