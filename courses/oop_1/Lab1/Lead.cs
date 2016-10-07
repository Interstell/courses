using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Abstract class containing common properties of Department Heads (TechLead etc.)
    /// </summary>
    abstract class Lead : Employee {
        protected TeamContainer team;
        
        public Lead(string name, string surname) : base(name, surname) {
            team = new TeamContainer(this);
        }
        /// <summary>
        /// Generic method to call HR "factory" and push returned values to team container
        /// </summary>
        /// <typeparam name="T">Type of Staff to hire(e.g. Tester)</typeparam>
        /// <param name="hr">Reference to HR Department instance</param>
        /// <param name="size">size of team to create</param>
        protected void hireMembers<T>(HRDepartment hr, int size) {
            for (int i = 0; i < size; i++) {
                if (typeof(T) == typeof(Programmer)) {
                    team.push(hr.hireProgrammer());
                }
                else if (typeof(T) == typeof(Tester)) {
                    team.push(hr.hireTester());
                }
                else if (typeof(T) == typeof(Analyst)) {
                    team.push(hr.hireAnalyst());
                }
            }
        }
        public abstract void hireTeam(HRDepartment hr);
    }
}
