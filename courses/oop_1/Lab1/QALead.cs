using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class QALead:Lead {
        private int teamSize = 4;
        public QALead(string name, string surname) : base(name, surname) { }
        public override void hireTeam(HRDepartment hr) {
            hireMembers<Tester>(hr, teamSize);
        }
    }   
}
