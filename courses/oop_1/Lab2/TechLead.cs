using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    /// <summary>
    /// Class representing a TechLead - head of Dev Department
    /// </summary>
    /// 
    delegate void TechLeadFinishHandler(TechLead sender, LeadFinishEventArgs args);
    class TechLead : Lead {
        private int teamSize = 3;
        public event TechLeadFinishHandler TechLeadFinishEvent;
        private TeamContainer<Programmer> team;
        private int LOCToBeWritten;
        private int LOCAlreadyWritten = 0;

        public TechLead(string name, string surname) : base(name, surname) {
            team = new TeamContainer<Programmer>();
        }

        public int MoneyPaidToTeam {
            get {
                int money = 0;
                foreach (Programmer p in team.Members) {
                    money += p.MoneyEarned;
                }
                return money;
            }
        }

        /// <summary>
        /// Hire new programmers
        /// </summary>
        public override void hireTeam() {
            for (int i = 0; i < teamSize; i++) {
                Programmer prog = HRDepartment.Instance.hireProgrammer();
                Logger.memberHired(prog.ToString());
                team.Add(prog);
            }
        }

        public override void setTask(int linesOfCodeToBeWritten) {
            LOCAlreadyWritten = 0;
            LOCToBeWritten = linesOfCodeToBeWritten;
        }
        public override int Work() {
            foreach (Programmer worker in team.Members){
                LOCAlreadyWritten += worker.Work();
            }
            if (LOCAlreadyWritten > LOCToBeWritten) {
                if (TechLeadFinishEvent != null)
                    TechLeadFinishEvent(this, new LeadFinishEventArgs("TechDepartment task finished, lines written: ", LOCToBeWritten));
            }
            return 0;
        }
    }
}
