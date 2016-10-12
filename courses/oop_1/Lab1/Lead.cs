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
        /// <param name="size">size of team to create</param>
        protected void hireMembers<T>(int size) {
            for (int i = 0; i < size; i++) {
                if (typeof(T) == typeof(Programmer)) {
                    Programmer prog = HRDepartment.Instance.hireProgrammer();
                    Logger.memberHired(prog.ToString());
                    team.push(prog);
                }
                else if (typeof(T) == typeof(Tester)) {
                    Tester tester = HRDepartment.Instance.hireTester();
                    Logger.memberHired(tester.ToString());
                    team.push(tester);
                }
                else if (typeof(T) == typeof(Analyst)) {
                    Analyst a = HRDepartment.Instance.hireAnalyst();
                    Logger.memberHired(a.ToString());
                    team.push(a);
                }
            }
        }
        public abstract void hireTeam();

    }
}
