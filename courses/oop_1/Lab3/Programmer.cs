using System;

namespace Lab3 {
    public enum ProgrammerDelayType { Bug = 1, Feature, MonkeyCode }
    public class Programmer : Employee {
        private string skills;
        public event Action<Programmer, ProgrammerDelayEventArgs> DelayEvent;

        private int LOCWrittenToday;
        private int LOCExpected = 200;

        public string Skills {
            get { return skills; }
            set {
                if (!String.IsNullOrEmpty(value)) {
                    skills = value;
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

        protected override void PayMoney() {
            if (LOCExpected / LOCWrittenToday > 0.25) {
                base.PayMoney();
            }   
        }

        public override int Work() {
            int behaviour = rand.Next(0, 5);
            if (behaviour == 0) {
                if (DelayEvent != null)
                    DelayEvent(this, new ProgrammerDelayEventArgs((ProgrammerDelayType) rand.Next(1, 4)));
                LOCWrittenToday = 0;
            }
            else {
                LOCWrittenToday = rand.Next(1, LOCExpected);
                PayMoney();
            }
            return LOCWrittenToday;
        }

        public override string ToString() {
            return String.Format("{0} {1}, {2} programmer", Name, Surname, Skills);
        }
    }
}
