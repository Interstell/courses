using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    /// <summary>
    /// Class with all information and metrics of the working project
    /// </summary>
    class Project {
        private string name;

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

        /// <summary>
        /// Constructor for working project
        /// </summary>
        /// <param name="name">Name of the project</param>
        /// <param name="numberOfUserStories">Number of user stories PO wants to implement</param>
        public Project(string name, int numberOfUserStories) {
            Name = name;
            UserStoriesGlobal = numberOfUserStories;
            Logger.newProject(Name, UserStoriesGlobal);
        }
        
    }
}
