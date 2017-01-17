using System;

namespace Lab4 {
    public abstract class Employee : IWorkable, IComparable, IDisposable {

        // Refactoring #5: Подъем поля (Pull Up Field)
        // Was: basic info variables & fields in derived classes
        // Now: protected variables & public fields in base class

        protected string name;
        protected string surname;
        protected int hourPayRate;
        protected int workingHoursCount;
        protected int earned;

        // #Rule: G25 (Заменяйте волшебные числа именоваными константами)
        protected static readonly int defaultHourPayRate = 5;
        protected static readonly int defaultWorkingHours = 8;
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

        //Rule: F4 (Мертвые функции)
        // Commented = deleted unused constructor with bad logic
        //public Employee(string name, int hourPayRate) : this(name, null, defaultHourPayRate) { }
        
        protected virtual void PayMoney() {
            this.earned += HourPayRate * workingHoursCount;
        }

        // #Rule: N2 (Выбирайте имена на подходящем уровне абстракции)
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

        public void Dispose() {
            GC.SuppressFinalize(this);
            Console.WriteLine("Employee {0} {1} is disposed.", name, surname);
        }

        ~Employee() {
            //Do not call Dispose to make this called.
            Console.WriteLine("Employee {0} {1} is finalized and collected.", name, surname);
        }
    }
}
