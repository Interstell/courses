using System;

namespace Lab3 {

    public class QALead : Lead {
        private int teamSize = 4;
        public event Action<QALead, LeadFinishEventArgs> QALeadFinishEvent;
        private TeamContainer<Tester> team;
        private int LOCAlreadyTested;
        private int LOCToBeTested;

        public QALead(string name, string surname) : base(name, surname) {
            team = new TeamContainer<Tester>();
        }
        public int MoneyPaidToTeam {
            get {
                int money = 0;
                foreach (Tester p in team.Members) {
                    money += p.MoneyEarned;
                }
                return money;
            }
        }

        public override void HireTeam() {
            for (int i = 0; i < teamSize; i++) {
                Tester tester = HRDepartment.Instance.HireTester();
                Logger.MemberHired(tester.ToString());
                team.Add(tester);
            }           
        }

        public override void SetTask(int linesOfCodeToBeTested) {
            LOCAlreadyTested = 0;
            LOCToBeTested = linesOfCodeToBeTested;
        }

        public override int Work() {
            foreach (Tester worker in team.Members) {
                LOCAlreadyTested += worker.Work();
            }
            if (LOCAlreadyTested > LOCToBeTested) {
                if (QALeadFinishEvent != null)
                    QALeadFinishEvent(this, new LeadFinishEventArgs("QADepartment task finished, lines covered: ", LOCToBeTested));
            }
            return 0;
        }
    }   
}
