using System;

namespace Lab4 {
    public enum ProgrammerDelayType { Bug = 1, Feature, MonkeyCode }
    public class Programmer : Employee {
        private string _skills;
        public event Action<Programmer, ProgrammerDelayEventArgs> DelayEvent;

        private int _locWrittenToday;
        private int _locExpected = 200;
        private int _failsOnThisTask = 0;

        public string Skills {
            get { return _skills; }
            set {
                if (!String.IsNullOrEmpty(value)) {
                    _skills = value;
                }
            }
        }

        public Programmer() {
            
        }
        
        public Programmer(string name, string surname, string skills, int hourPayRate)
            : this(name, surname, skills) {
                this.HourPayRate = hourPayRate;
        }
        public Programmer(string name, string surname, string skills)
            : base(name, surname) {
            this.Skills = skills;
        }

        private Boolean IsAllowedToBePayedWithMoney() {
            return _locExpected/_locWrittenToday > 0.25
                   && _failsOnThisTask < 2;
        }

        // Refactoring #3: Консолидация условного выражения (Consolidate Conditional Expression)
        protected override void PayMoney() {
            if (IsAllowedToBePayedWithMoney()) {
                base.PayMoney();
            }   
        }

        public override int Work() {
            int behaviour = rand.Next(0, 5);
            if (behaviour == 0) {
                if (DelayEvent != null)
                    DelayEvent(this, new ProgrammerDelayEventArgs((ProgrammerDelayType) rand.Next(1, 4)));
                _locWrittenToday = 0;
            }
            else {
                _locWrittenToday = rand.Next(1, _locExpected);
                PayMoney();
            }
            return _locWrittenToday;
        }

        public override string ToString() {
            return String.Format("{0} {1}, {2} programmer", Name, Surname, Skills);
        }
    }
}
