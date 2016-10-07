using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class TechLead:Lead {
        private int teamSize = 3;
        public TechLead(string name, string surname) : base(name, surname) { }

        public override void hireTeam(HRDepartment hr) {
            hireMembers<Programmer>(hr, teamSize);
        }
    }
}
