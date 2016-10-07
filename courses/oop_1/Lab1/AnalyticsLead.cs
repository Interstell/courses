using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class AnalyticsLead:Lead {
        private int teamSize = 2;
        public AnalyticsLead(string name, string surname) : base(name, surname) { }
        public override void hireTeam(HRDepartment hr) {
            hireMembers<Analyst>(hr, teamSize);
        }
    }
}
