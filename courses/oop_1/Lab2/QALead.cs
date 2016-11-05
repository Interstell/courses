using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    /// <summary>
    /// Class representing a QA Lead - head of QA Department
    /// </summary>

    delegate void QALeadFinishHandler(QALead sender, LeadFinishEventArgs args);
    class QALead : Lead {
        private int teamSize = 4;
        public event QALeadFinishHandler QALeadFinishEvent;
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

        /// <summary>
        /// Hire new testers
        /// </summary>
        /// <remarks>
        /// Wraps a generic method from the base class.
        /// </remarks>
        public override void hireTeam() {
            for (int i = 0; i < teamSize; i++) {
                Tester tester = HRDepartment.Instance.hireTester();
                Logger.memberHired(tester.ToString());
                team.Add(tester);
            }           
        }

        public override void setTask(int linesOfCodeToBeTested) {
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
