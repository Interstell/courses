using System;

namespace Lab4 {
    
    public class TechLead : Lead {
        // #Rule: N1 (Используйте содержательные имена)
        // Was: team, lWrite, lWritten, numFails
        // Now: _team, _locToBeWritten, _locAlreadyWritten, _failuresOnThisUserStory
        private int _teamSize = 3;
        public event Action<TechLead, LeadFinishEventArgs> TechLeadFinishEvent;
        private TeamContainer<Programmer> _team;
        // #Rule: N5 (Используйте длинные имена для длинных областей видимости)
        private int _locToBeWritten;
        private int _locAlreadyWritten = 0;
        private int _failuresOnThisUserStory;

        public TechLead(string name, string surname) : base(name, surname) {
            _team = new TeamContainer<Programmer>();
        }

        public int MoneyPaidToTeam {
            get {
                int money = 0;
                foreach (Programmer p in _team.Members) {
                    money += p.MoneyEarned;
                }
                return money;
            }
        }

        public override void HireTeam() {
            for (int i = 0; i < _teamSize; i++) {
                Programmer prog = HRDepartment.Instance.HireProgrammer();
                prog.DelayEvent += (sender, args) => {
                    Logger.ProgrammerDelayHappened(sender, args);
                    _failuresOnThisUserStory++;
                };
                Logger.MemberHired(prog.ToString());
                _team.Add(prog);
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
            _locAlreadyWritten = 0;
            _failuresOnThisUserStory = 0;
            _locToBeWritten = amountOfWork;
        }


        // #Rule: G28 (Инкапсулируйте условные конструкции)
        private bool _isTaskFinished() {
            return _locAlreadyWritten > _locToBeWritten;
        }


        // #Rule: G30 (Функции должны выполнять одну операцию)  
        private void _decreaseTeamPayRate(double percent) {
            foreach (Programmer programmer in _team) {
                programmer.ChangePayRate(payrate => (int)((1 - percent) * payrate));
            }
        }

        public override int Work() {
            foreach (Programmer worker in _team.Members){
                _locAlreadyWritten += worker.Work();
            }
            if (_isTaskFinished()) {
                if (TechLeadFinishEvent != null)
                    TechLeadFinishEvent(this, new LeadFinishEventArgs("TechDepartment task finished, lines written: ", _locToBeWritten));
                if (_failuresOnThisUserStory > 2) { 
                    _decreaseTeamPayRate(0.9);
                }
            }
            return 0;
        }
    }
}
