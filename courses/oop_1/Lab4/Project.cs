using System;

namespace Lab4 {
    public class Project {
        public string name;
        public string client;

        public string Name {
            get{return name;}
            set{
                if (!String.IsNullOrEmpty(value)){
                    name = value;
                }
            }
        }

        public int UserStoriesGlobal { get; set; }

        public Project() {

        }

        public Project(string name, int numberOfUserStories) {
            Name = name;
            UserStoriesGlobal = numberOfUserStories;
            Logger.NewProject(Name, UserStoriesGlobal);
        }
        
    }
}
