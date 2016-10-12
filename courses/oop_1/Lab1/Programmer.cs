using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Class to represent a Programmer development team member.
    /// </summary>
    class Programmer : Employee {
        private string skills;
        private int linesWrittenToday;
        private int linesPlanned;

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
            this.linesWrittenToday = 0;
            this.linesPlanned = 100;
        }

        public override void Work() {
            linesWrittenToday = new Random().Next(linesPlanned);
            if (linesWrittenToday / linesPlanned > 0.5) {
                base.Work();
            }
        }

        public override string ToString() {
            return String.Format("{0} {1}, {2} programmer", Name, Surname, Skills);
        }
    }
}
