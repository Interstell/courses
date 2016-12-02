using System;

namespace Lab3 {
    
    public class TechLead : Lead {
        private int teamSize = 3;
        public event Action<TechLead, LeadFinishEventArgs> TechLeadFinishEvent;
        private TeamContainer<Programmer> team;
        private int LOCToBeWritten;
        private int LOCAlreadyWritten = 0;
        private int _failuresOnThisUserStory;

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

        public override void HireTeam() {
            for (int i = 0; i < teamSize; i++) {
                Programmer prog = HRDepartment.Instance.HireProgrammer();
                prog.DelayEvent += (sender, args) => {
                    Logger.ProgrammerDelayHappened(sender, args);
                    _failuresOnThisUserStory++;
                };
                Logger.MemberHired(prog.ToString());
                team.Add(prog);
            }
        }

        public override void SetTask(int linesOfCodeToBeWritten) {
            LOCAlreadyWritten = 0;
            _failuresOnThisUserStory = 0;
            LOCToBeWritten = linesOfCodeToBeWritten;
        }
        public override int Work() {
            foreach (Programmer worker in team.Members){
                LOCAlreadyWritten += worker.Work();
            }
            if (LOCAlreadyWritten > LOCToBeWritten) {
                if (TechLeadFinishEvent != null)
                    TechLeadFinishEvent(this, new LeadFinishEventArgs("TechDepartment task finished, lines written: ", LOCToBeWritten));
                if (_failuresOnThisUserStory > 2) { 
                    foreach (Programmer programmer in team) {
                        programmer.ChangePayRate(payrate => (int)0.9*payrate);
                    }
                }
            }
            return 0;
        }
    }
}
