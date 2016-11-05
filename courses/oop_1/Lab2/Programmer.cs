using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    /// <summary>
    /// Class to represent a Programmer development team member.
    /// </summary>
    class Programmer : Employee {
        private string skills;

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
        /// <summary>
        /// Programmer constructor
        /// </summary>
        /// <param name="name">Name</param>
        /// <param name="surname">Surname</param>
        /// <param name="skills">Current skills e.g. '.NET'</param>
        /// <param name="hourPayRate">Payrate per hour</param>
        public Programmer(string name, string surname, string skills, int hourPayRate)
            : this(name, surname, skills) {
                this.HourPayRate = hourPayRate;
        }
        public Programmer(string name, string surname, string skills)
            : base(name, surname) {
            this.Skills = skills;
        }

        protected override void payMoney() {
            if (LOCExpected / LOCWrittenToday > 0.25) {
                base.payMoney();
            }   
        }

        public override int Work() {
            LOCWrittenToday = rand.Next(1, LOCExpected);
            payMoney();
            return LOCWrittenToday;
        }

        public override string ToString() {
            return String.Format("{0} {1}, {2} programmer", Name, Surname, Skills);
        }
    }
}
