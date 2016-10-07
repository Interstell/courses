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
            techLead = project.HR.hireTechLead();
            techLead.hireTeam(project.HR);
            qaLead = project.HR.hireQALead();
            qaLead.hireTeam(project.HR);
            analyticsLead = project.HR.hireAnalyticsLead();
            analyticsLead.hireTeam(project.HR);
        }
    }
}
