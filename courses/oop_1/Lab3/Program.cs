using System;

namespace Lab3 {
    class Program {

        static int GetUserStoriesCount() {
            try {
                Console.WriteLine("User stories to implement: ");
                string s = Console.ReadLine();
                int number = int.Parse(s);
                if (number <= 0) {
                    throw new WrongUserStoriesException("Please, enter a positive value > 0.", number);
                }
                return number;
            }
            catch (WrongUserStoriesException e){
                Console.WriteLine("Error! " + e.Message);
                return -1;
            }
            catch (Exception e){
                Console.WriteLine(e.Message);
                return -1;
            }
        }

        static void Main(string[] args) {

            int userStoriesCount = 0;
            while (userStoriesCount <= 0) {
                userStoriesCount = GetUserStoriesCount();
            }

            Project proj = new Project("Lab3 App", userStoriesCount);
            ProjectManager pm = new ProjectManager("Dmitry", "Petrenko") {Project = proj};
            pm.HireLeads();
            pm.SubscribeOnLeadsFinish();
            pm.GiveOutTasks();

            int day = 1;

            while (proj.UserStoriesGlobal > 0) {
                pm.Work();
                Console.WriteLine("\n----------Day {0} [${1} spent]----------", day, pm.calculateSpentMoney());
                day++;
                
                System.Threading.Thread.Sleep(2000);
            }

            Console.WriteLine("\n\t*Project {0} successfully finished! ${1} spent.", proj.Name, pm.calculateSpentMoney());

            Console.ReadLine();
        }
    }
}

