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
        private int teamSize;

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

        public Boolean push(Employee member) {
            if (teamSize < teamMaxSize) {
                team[teamSize++] = member;
                return true;
            }
            return false;
        }
    }
}
