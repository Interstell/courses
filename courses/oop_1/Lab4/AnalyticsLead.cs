using System;

namespace Lab4 {
    public class AnalyticsLead : Lead {
        public event Action<AnalyticsLead, LeadFinishEventArgs> AnalyticsLeadFinishEvent;
        // #Rule: N6 (Избегайте кодирования)
        // Was: iTeamSize, team, tasksDocumented
        // Now: _teamSize, _tasksAlreadyDocumented, _tasksToBeDocumented
        private int _teamSize = 2;
        private TeamContainer<Analyst> _team;
        private int _tasksAlreadyDocumented;
        private int _tasksToBeDocumented;
        public AnalyticsLead(string name, string surname) : base(name, surname) {
            _team = new TeamContainer<Analyst>();
        }

        public int MoneyPaidToTeam {
            get {
                int money = 0;
                foreach (Analyst a in _team.Members) {
                    money += a.MoneyEarned;
                }
                return money;
            }
        }

        public override void HireTeam() {
            for (int i = 0; i < _teamSize; i++) {
                Analyst a = HRDepartment.Instance.HireAnalyst();
                Logger.MemberHired(a.ToString());
                _team.Add(a);
            }
        }

        public override void FireTeam() {
            _team.Dispose();
            WeakReference wr = new WeakReference(_team);
            _team = null;
            GC.Collect();
            GC.WaitForPendingFinalizers();
            Console.WriteLine(wr.IsAlive ? "\t\tTeam object is ALIVE" : "\t\tTeam object is DEAD");
        }

        public override void SetTeamTask(int amountOfWork) {
            this._tasksAlreadyDocumented = 0;
            this._tasksToBeDocumented = amountOfWork;
        }

        public override int Work() {
            foreach (Analyst worker in _team.Members) {
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
