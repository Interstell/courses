using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
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

        public void hireLeads() {
            techLead = project.HR.hireTechLead() ?? null;
            techLead.hireTeam(project.HR);
            qaLead = project.HR.hireQALead() ?? null;
            qaLead.hireTeam(project.HR);
            analyticsLead = project.HR.hireAnalyticsLead() ?? null;
            analyticsLead.hireTeam(project.HR);
        }
    }
}
