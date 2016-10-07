using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    abstract class Lead : Employee {
        protected TeamContainer team;
        
        public Lead(string name, string surname) : base(name, surname) {
            team = new TeamContainer(this);
        }

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
