using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Class representing a TechLead - head of Dev Department
    /// </summary>
    class TechLead:Lead {
        private int teamSize = 3;
        public TechLead(string name, string surname) : base(name, surname) { }

        /// <summary>
        /// Hire new programmers
        /// </summary>
        /// <remarks>
        /// Wraps a generic method from the base class.
        /// </remarks>
        public override void hireTeam() {
            hireMembers<Programmer>(teamSize);
        }
    }
}
