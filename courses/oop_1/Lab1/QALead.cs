using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Class representing a QA Lead - head of QA Department
    /// </summary>
    class QALead:Lead {
        private int teamSize = 4;
        public QALead(string name, string surname) : base(name, surname) { }
        /// <summary>
        /// Hire new testers
        /// </summary>
        /// <remarks>
        /// Wraps a generic method from the base class.
        /// </remarks>
        /// <param name="hr">Reference to HR technical class instance</param>
        public override void hireTeam(HRDepartment hr) {
            hireMembers<Tester>(hr, teamSize);
        }
    }   
}
