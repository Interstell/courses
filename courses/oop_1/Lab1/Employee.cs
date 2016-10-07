using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Abstract class with basic information about employee to be inherited.
    /// </summary>
    abstract class Employee {
        private string name;
        private string surname;
        private int hourPayRate;

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

        protected Employee(string name, string surname, int hourPayRate) {
            this.Name = name;
            this.Surname = surname;
            this.HourPayRate = hourPayRate;
        }

        public Employee():this(null, null, 0){ }
        public Employee(string name, string surname):this (name, surname, 0){ }

        public Employee(string name, int hourPayRate) : this(name, null, hourPayRate) { }

        public override string ToString(){
            return Name + " " + Surname;
        }
    }
}
