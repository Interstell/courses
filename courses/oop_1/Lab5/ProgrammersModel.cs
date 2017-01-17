using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

namespace Lab5 {

    [DataContract]
    public class Programmer {
        [DataMember]
        public string Name { get; set; }
        [DataMember]
        public string Surname { get; set; }
        [DataMember]
        public string Skills { get; set; }
        [DataMember]
        public DateTime TimeAdded { get; set; }
        [DataMember]
        public int ID { get; set; }

        public Programmer(string Name, string Surname,
            string Skills, DateTime TimeAdded, int ID) {
            this.Name = Name;
            this.Surname = Surname;
            this.TimeAdded = TimeAdded;
            this.Skills = Skills;
            this.ID = ID;
        }
    }

    [DataContract]
    public class ProgrammersContainer {
        [DataMember]
        public List<Programmer> programmers;

        public ProgrammersContainer() {}

        public ProgrammersContainer(List<Programmer> programmers) {
            this.programmers = programmers;
        }

        public static void SerializeToFile(List<Programmer> data) {
            ProgrammersContainer container = new ProgrammersContainer(data);
            DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(ProgrammersContainer));
            using (FileStream stream = File.Create("Programmers.json")) {
                js.WriteObject(stream, container);
                stream.Close();
            }
        }

        public void DeserializeFromFile() {
            FileStream stream = new FileStream("Programmers.json", FileMode.Open);
            DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(ProgrammersContainer));
            stream.Position = 0;

            ProgrammersContainer data = (ProgrammersContainer)js.ReadObject(stream);
            this.programmers = data.programmers;
            stream.Close();
        }
    }

    public class ProgrammersModel : ObservableCollection<Programmer> {
        private static object _threadLock = new Object();
        private static ProgrammersModel current = null;

        public static ProgrammersModel Current {
            get {
                lock (_threadLock)
                    if (current == null)
                        current = new ProgrammersModel();

                return current;
            }
        }

        private ProgrammersModel() {
            ProgrammersContainer source = new ProgrammersContainer();
            source.DeserializeFromFile();
            List<Programmer> programmers = source.programmers;
            programmers.ForEach(Add);
        }

        public void AddAProgrammer(String Name, String Surname, String Skills, DateTime TimeAdded) {
            Programmer aNewProgrammer = new Programmer(Name, Surname, Skills, TimeAdded, new Random().Next(10, 100000));
            Add(aNewProgrammer);
        }



    }
}
