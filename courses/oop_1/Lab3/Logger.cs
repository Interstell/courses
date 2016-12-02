using System;

namespace Lab3 {
    public static class Logger {
        
        public static void Write(string message){
            Console.WriteLine(message);
        }

        public static void NewProject(string name, int usCount) {
            Console.WriteLine("New project \"{0}\" started!\n\t{1} user stories are to be implemented.", name, usCount);
        }

        public static void LeadHired(string position, string info) {
            Console.WriteLine("New {0} hired for project: {1}", position, info);
        }

        public static void MemberHired(string info) {
            Console.WriteLine("\tNew team member hired: " + info);
        }

        public static void TaskDone(LeadFinishEventArgs args) {
            Console.WriteLine(args.Message + args.WorkAmount.ToString());
        }

        public static void UserStoryImplemented(int storiesLeft) {
            if (storiesLeft > 0) {
                Console.WriteLine("\t*User story implemented! {0} left to implement!", storiesLeft);
            }
            else {
                Console.WriteLine("\t*User story implemented!", storiesLeft);
            }
        }

        public static void ProgrammerDelayHappened(Programmer programmer, ProgrammerDelayEventArgs args) {
            Console.WriteLine("Programmer {0} {1} has got a delay because of undocumented {2}.", programmer.Name, programmer.Surname, args.DelayType.ToString());
        }

    }
}
