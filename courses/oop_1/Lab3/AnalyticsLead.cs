using System;

namespace Lab3 {
    public class AnalyticsLead : Lead {
        public event Action<AnalyticsLead, LeadFinishEventArgs> AnalyticsLeadFinishEvent;
        private int teamSize = 2;
        private TeamContainer<Analyst> team;
        private int _tasksAlreadyDocumented;
        private int _tasksToBeDocumented;
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

        public override void HireTeam() {
            for (int i = 0; i < teamSize; i++) {
                Analyst a = HRDepartment.Instance.HireAnalyst();
                Logger.MemberHired(a.ToString());
                team.Add(a);
            }
        }

        public override void SetTask(int tasksToBeDocumented) {
            this._tasksAlreadyDocumented = 0;
            this._tasksToBeDocumented = tasksToBeDocumented;
        }

        public override int Work() {
            foreach (Analyst worker in team.Members) {
                _tasksAlreadyDocumented += worker.Work();
            }
            if (_tasksAlreadyDocumented > _tasksToBeDocumented) {
                if (AnalyticsLeadFinishEvent != null)
                    AnalyticsLeadFinishEvent(this, new LeadFinishEventArgs("AnalyticsDepartment task finished, tasks documented: ", _tasksToBeDocumented));
            }
            return 0;
        }

    }
}
