using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class TeamContainer {
        private static int teamMaxSize = 10;
        private Employee[] team;
        private Employee teamLead;
        private int teamCurrentSize;

        public Employee TeamLead {
            get { return teamLead; }
            set {
                if (value != null) {
                    teamLead = value;
                }
            }
        }

        public TeamContainer() {
            team = new Employee[teamMaxSize];
        }
        public TeamContainer(Employee teamLead):this() {
            this.teamLead = teamLead;
        }
        /// <summary>
        /// Typical array adding method with ordinary implementation.
        /// </summary>
        /// <param name="member">New team member to be pushed</param>
        /// <returns>Whether push was success or not.</returns>
        public Boolean push(Employee member) {
            if (teamCurrentSize < teamMaxSize) {
                team[teamCurrentSize++] = member;
                return true;
            }
            return false;
        }
    }
}
