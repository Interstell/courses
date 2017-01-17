using System;

namespace Lab4 {

    public class QaLead : Lead {
        // #Rule: N1 (Используйте содержательные имена)
        // #Rule: N6 (Избегайте кодирования)
        // Was: iTeamSize, team, lTested
        // Now: _teamSize, _team, _locAlreadyTested, _locToBeTested
        private int _teamSize = 4;
        public event Action<QaLead, LeadFinishEventArgs> QaLeadFinishEvent;
        private TeamContainer<Tester> _team;
        private int _locAlreadyTested;
        private int _locToBeTested;

        public QaLead(string name, string surname) : base(name, surname) {
            _team = new TeamContainer<Tester>();
        }
        public int MoneyPaidToTeam {
            get {
                int money = 0;
                foreach (Tester p in _team.Members) {
                    money += p.MoneyEarned;
                }
                return money;
            }
        }

        public override void HireTeam() {
            for (int i = 0; i < _teamSize; i++) {
                Tester tester = HRDepartment.Instance.HireTester();
                Logger.MemberHired(tester.ToString());
                _team.Add(tester);
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
            _locAlreadyTested = 0;
            _locToBeTested = amountOfWork;
        }

        public override int Work() {
            foreach (Tester worker in _team.Members) {
                _locAlreadyTested += worker.Work();
            }
            if (_locAlreadyTested > _locToBeTested) {
                if (QaLeadFinishEvent != null)
                    QaLeadFinishEvent(this, new LeadFinishEventArgs("QADepartment task finished, lines covered: ", _locToBeTested));
            }
            return 0;
        }
    }   
}
