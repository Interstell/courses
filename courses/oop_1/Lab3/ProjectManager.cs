using System;

namespace Lab3 {

    public class ProjectManager : Employee {
        private Project project;
        private TechLead techLead;
        private QALead qaLead;
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

        public void SubscribeOnLeadsFinish() {

            techLead.TechLeadFinishEvent += delegate(TechLead sender, LeadFinishEventArgs args) {
                progFinished = true;
                Logger.TaskDone(args);
            };
            qaLead.QALeadFinishEvent += (sender, args) => {
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

            analyticsLead.SetTask(rand.Next(8, 11));
            int locTask = rand.Next(1500, 2000);
            techLead.SetTask(locTask);
            qaLead.SetTask((int)(1.5 * locTask));
        }

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
