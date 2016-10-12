using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Class representing a Project Manager - head of the project.
    /// </summary>
    class ProjectManager : Employee {
        private Project project;
        private TechLead techLead;
        private QALead qaLead;
        private AnalyticsLead analyticsLead;

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
        public void hireLeads() {
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
    }
}
