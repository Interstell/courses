using System;

namespace Lab3 {
    public abstract class Employee : IWorkable, IComparable {
        protected string name;
        protected string surname;
        protected int hourPayRate;
        protected int workingHoursCount;
        protected int earned;

        protected static int defaultHourPayRate = 5;
        protected static int defaultWorkingHours = 8;
        protected static Random rand;

        static Employee() {
            rand = new Random();
        }
        
        public string Name {
            get { return name; }
            set {
                if (!String.IsNullOrEmpty(value)) {
                    name = value;
                }
            }
        }
        public string Surname {
            get { return surname; }
            set {
                if (!String.IsNullOrEmpty(value)) {
                    surname = value;
                }
            }
        }
        public int HourPayRate {
            get { return hourPayRate; }
            set {
                if (value >= 0) {
                    hourPayRate = value;
                }
            }
        }

        public int MoneyEarned {
            get { return earned; }
        }
        protected Employee(string name, string surname, int hourPayRate) {
            this.Name = name;
            this.Surname = surname;
            this.HourPayRate = hourPayRate;
            this.earned = 0;
            this.workingHoursCount = defaultWorkingHours;
        }

        public Employee():this(null, null, 0){ }
        public Employee(string name, string surname):this (name, surname, defaultWorkingHours){ }
        public Employee(string name, int hourPayRate) : this(name, null, defaultHourPayRate) { }
        protected virtual void PayMoney() {
            this.earned += HourPayRate * workingHoursCount;
        }
        public abstract int Work();

        public override string ToString(){
            return Name + " " + Surname;
        }

        public void ChangePayRate(Func<int, int> change) {
            HourPayRate = change(HourPayRate);
        }

        public int CompareTo(object emp) {
            if (emp is Employee)
                return this.HourPayRate.CompareTo(((Employee) emp).HourPayRate);
            else return 0;
        }
    }
}
