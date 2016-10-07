using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    /// <summary>
    /// Class with all information and metrics of the working project
    /// </summary>
    class Project {
        private string name;
        private HRDepartment hr;

        public string Name {
            get{return name;}
            set{
                if (!String.IsNullOrEmpty(value)){
                    name = value;
                }
            }
        }
        /// <summary>
        /// Project metrics
        /// </summary>
        public int UserStoriesGlobal { get; set; }
        public int UserStoriesImplemented { get; set; }
        public int UserStoriesToImplement { get; set; }
        public double UserStoryAnalysisProgress { get; set; }
        public int LinesOfCodeGlobal { get; set; }
        public int LinesOfCodeCurrent { get; set; }
        public int LinesOfCodeToTest { get; set; }

        public HRDepartment HR {
            get {
                return hr;
            }
            set {
                if (value != null) {
                    hr = value;
                }
            }
        }

        /// <summary>
        /// Constructor for working project
        /// </summary>
        /// <param name="name">Name of the project</param>
        /// <param name="numberOfUserStories">Number of user stories PO wants to implement</param>
        public Project(string name, int numberOfUserStories) {
            Name = name;
            UserStoriesGlobal = numberOfUserStories;
        }
        
    }
}
