using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    /// <summary>
    /// Class representing a Project Manager - head of the project.
    /// </summary>

    class ProjectManager : Employee {
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
        
        /// <summary>
        /// Hires 3 leads from HR "factory" and calls their methods of hiring their own teams.
        /// </summary>
        public void HireLeads() {
            techLead = HRDepartment.Instance.hireTechLead();
            Logger.leadHired("TechLead", techLead.ToString());
            techLead.hireTeam();
            qaLead = HRDepartment.Instance.hireQALead();
            Logger.leadHired("QALead", qaLead.ToString());
            qaLead.hireTeam();
            analyticsLead = HRDepartment.Instance.hireAnalyticsLead();
            Logger.leadHired("AnalyticsLead", analyticsLead.ToString());
            analyticsLead.hireTeam();
        }

        public void SubscribeOnLeadsFinish() {
            techLead.TechLeadFinishEvent += HandleProgTaskCompletion;
            qaLead.QALeadFinishEvent += HandleQATaskCompletion;
            analyticsLead.AnalyticsLeadFinishEvent += HandleAnalyticsTaskCompletion;
        }

        public void GiveOutTasks() {
            progFinished = false;
            analysisFinished = false;
            qaFinished = false;

            analyticsLead.setTask(rand.Next(8, 11));
            int locTask = rand.Next(1500, 2000);
            techLead.setTask(locTask);
            qaLead.setTask((int)(1.5 * locTask));
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
                Logger.userStoryImplemented(project.UserStoriesGlobal);
                GiveOutTasks();
            }
                      
            return 0;
        }

        public void HandleProgTaskCompletion(TechLead sender, LeadFinishEventArgs args) {
            progFinished = true;
            Logger.taskDone(args);
        }
        public void HandleQATaskCompletion(QALead sender, LeadFinishEventArgs args){
            qaFinished = true;
            Logger.taskDone(args);
        }
        public void HandleAnalyticsTaskCompletion(AnalyticsLead sender, LeadFinishEventArgs args){
            analysisFinished = true;
            Logger.taskDone(args);
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
