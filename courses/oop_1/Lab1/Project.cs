using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1 {
    class Project {
        private string name;
        private HRDepartment hr;

        /*private int userStoriesGlobal;
        private int userStoriesImplemented;
        private int userStoriesToImplement;
        private double userStorAnalysisProgress;

        private int linesOfCodeGlobal;
        private int linesOfCodeCurrent;
        private int linesOfCodeToTest;*/

        public string Name {
            get{return name;}
            set{
                if (!String.IsNullOrEmpty(value)){
                    name = value;
                }
            }
        }
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


        public Project(string name, int numberOfUserStories) {
            Name = name;
            UserStoriesGlobal = numberOfUserStories;
        }
        
    }
}
