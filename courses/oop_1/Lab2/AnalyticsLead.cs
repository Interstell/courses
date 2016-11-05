using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    delegate void AnalyticsFinishHandler(AnalyticsLead sender, LeadFinishEventArgs args);
    class AnalyticsLead : Lead {
        public event AnalyticsFinishHandler AnalyticsLeadFinishEvent;
        private int teamSize = 2;
        private TeamContainer<Analyst> team;
        private int tasksAlreadyDocumented;
        private int tasksToBeDocumented;
        public AnalyticsLead(string name, string surname) : base(name, surname) {
            team = new TeamContainer<Analyst>();
        }

        public int MoneyPaidToTeam {
            get {
                int money = 0;
                foreach (Analyst a in team.Members) {
                    money += a.MoneyEarned;
                }
                return money;
            }
        }
        /// <summary>
        /// Hire new analytics
        /// </summary>
        /// <remarks>
        /// Wraps a generic method from the base class.
        /// </remarks>
        public override void hireTeam() {
            for (int i = 0; i < teamSize; i++) {
                Analyst a = HRDepartment.Instance.hireAnalyst();
                Logger.memberHired(a.ToString());
                team.Add(a);
            }
        }

        public override void setTask(int tasksToBeDocumented) {
            this.tasksAlreadyDocumented = 0;
            this.tasksToBeDocumented = tasksToBeDocumented;
        }

        public override int Work() {
            foreach (Analyst worker in team.Members) {
                tasksAlreadyDocumented += worker.Work();
            }
            if (tasksAlreadyDocumented > tasksToBeDocumented) {
                if (AnalyticsLeadFinishEvent != null)
                    AnalyticsLeadFinishEvent(this, new LeadFinishEventArgs("AnalyticsDepartment task finished, tasks documented: ", tasksToBeDocumented));
            }
            return 0;
        }

    }
}
