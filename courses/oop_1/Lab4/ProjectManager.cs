using System;

namespace Lab4 {

    public class ProjectManager : Employee {
        private Project project;
        private TechLead techLead;
        private QaLead qaLead;
        private AnalyticsLead analyticsLead;

        private Boolean progFinished = false;
        private Boolean qaFinished = false;
        private Boolean analysisFinished = false;

        public Project Project {
            get {
                return project;
            }
            set {
                if (value != null) {
                    project = value;
                }
            }
        }

        public ProjectManager(string name, string surname)
            : base(name, surname) { }
        
        public void HireLeads() {
            techLead = HRDepartment.Instance.HireTechLead();
            Logger.LeadHired("TechLead", techLead.ToString());
            techLead.HireTeam();
            qaLead = HRDepartment.Instance.HireQALead();
            Logger.LeadHired("QALead", qaLead.ToString());
            qaLead.HireTeam();
            analyticsLead = HRDepartment.Instance.HireAnalyticsLead();
            Logger.LeadHired("AnalyticsLead", analyticsLead.ToString());
            analyticsLead.HireTeam();
        }

        public void FireLeadsAndTeams() {
            techLead.FireTeam();
            analyticsLead.FireTeam();
            qaLead.FireTeam();

            /*techLead.Dispose();
            analyticsLead.Dispose();
            qaLead.Dispose();*/

            techLead = null;
            qaLead = null;
            analyticsLead = null;
            
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }

        public void SubscribeOnLeadsFinish() {

            techLead.TechLeadFinishEvent += delegate(TechLead sender, LeadFinishEventArgs args) {
                progFinished = true;
                Logger.TaskDone(args);
            };
            qaLead.QaLeadFinishEvent += (sender, args) => {
                qaFinished = true;
                Logger.TaskDone(args);
            };
            analyticsLead.AnalyticsLeadFinishEvent += (sender, args) => {
                analysisFinished = true;
                Logger.TaskDone(args);
            };
        }

        public void GiveOutTasks() {
            progFinished = false;
            analysisFinished = false;
            qaFinished = false;


            analyticsLead.SetTeamTask(rand.Next(8, 11));
            int locTask = rand.Next(1500, 2000);
            techLead.SetTeamTask(locTask);
            qaLead.SetTeamTask((int)(1.5 * locTask));
        }

        // #Rule: G36 (Избегайте транзитивных обращений)
        // PM -> Leads -> Team Members
        public override int Work() {
            if (!analysisFinished)
                analyticsLead.Work();
            if (!progFinished)
                techLead.Work();
            if (!qaFinished)
                qaLead.Work();

            if (analysisFinished && progFinished && qaFinished) {
                project.UserStoriesGlobal--;
                Logger.UserStoryImplemented(project.UserStoriesGlobal);
                GiveOutTasks();
            }
                      
            return 0;
        }

        public int calculateSpentMoney() {
            int money = 0;
            money += analyticsLead.MoneyPaidToTeam;
            money += techLead.MoneyPaidToTeam;
            money += qaLead.MoneyPaidToTeam;
            return money;
        }
    }
}
