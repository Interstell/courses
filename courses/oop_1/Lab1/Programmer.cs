using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class Programmer : Employee {
        private string skills;

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
        
        public Programmer(string name, string surname, string skills)
            : base(name, surname) {
            this.Skills = skills;
        }
        public Programmer(string name, string surname, string skills, int hourPayRate)
            : this(name, surname, skills) {
                this.HourPayRate = hourPayRate;
        }

        public override string ToString() {
            return String.Format("{0} {1}, {2} programmer", Name, Surname, Skills);
        }
    }
}
