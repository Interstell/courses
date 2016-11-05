using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    class TeamContainer<T> where T:Employee{
        private List<T> team;
        private T teamLead;
        

        public T TeamLead {
            get { return teamLead; }
            set {
                if (value != null) {
                    teamLead = value;
                }
            }
        }

        public List<T> Members {
            get { return team; }
        }

        public int Count{
            get {
                return team.Count;
            }
        }

        public TeamContainer() {
            team = new List<T>();
        }
        public TeamContainer(T teamLead):this() {
            this.teamLead = teamLead;
        }
        /// <summary>
        /// Adds new team member to team container
        /// </summary>
        /// <param name="member">New team member to be pushed</param>
        /// <returns>Whether push was success or not.</returns>
        public void Add(T member) {
            team.Add(member);
        }
    }
}
