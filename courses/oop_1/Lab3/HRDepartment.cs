using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Xml.Serialization;

namespace Lab3{

    [DataContract]
    [Serializable]
    public class HRDepartmentData {
        [DataMember]
        [XmlArray("Names")]
        [XmlArrayItem("Name")]
        public List<string> names;

        [DataMember]
        [XmlArray("Surnames")]
        [XmlArrayItem("Surname")]
        public List<string> surnames;

        [DataMember]
        [XmlArray("Skills")]
        [XmlArrayItem("Skill")]
        public List<string> skills;

        enum serializingSource { JSON, XML };

        private serializingSource source = serializingSource.XML;

        public static Boolean deserializing = false;

        public HRDepartmentData() {
            if (!deserializing) {
                switch (source) {
                    case serializingSource.JSON:
                        JsonDeserialize();
                        break;
                    case serializingSource.XML:
                        XmlDeserialize();
                        break;
                }
            }
        }

        private void JsonSerialize() {
            DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(HRDepartmentData));
            using (FileStream stream = File.Create("HRSource.json")) {
                js.WriteObject(stream, this);
            }
        }

        private void XmlSerialize() {
            XmlSerializer serializer = new XmlSerializer(typeof(HRDepartmentData));
            using (FileStream stream = File.Create("HRSource.xml")) {
                serializer.Serialize(stream, this);
            }
        }

        private void JsonDeserialize() {
            deserializing = true;

            FileStream stream = new FileStream("HRSource.json", FileMode.Open);
            DataContractJsonSerializer js = new DataContractJsonSerializer(typeof(HRDepartmentData));
            stream.Position = 0;

            HRDepartmentData data = (HRDepartmentData)js.ReadObject(stream);
            names = data.names;
            surnames = data.surnames;
            skills = data.skills;
        }

        private void XmlDeserialize() {
            deserializing = true;

            XmlSerializer serializer = new XmlSerializer(typeof(HRDepartmentData));
            using (var file = File.OpenRead("HRSource.xml")) {
                HRDepartmentData data = (HRDepartmentData)serializer.Deserialize(file);
                names = data.names;
                surnames = data.surnames;
                skills = data.skills;
            }
        }

        ~HRDepartmentData() {
            switch (source) {
                case serializingSource.JSON:
                    JsonSerialize();
                    break;
                case serializingSource.XML:
                    XmlSerialize();
                    break;
            }
        }
    }

    public class HRDepartment {

        private static Random randomizer;
        private static HRDepartment instance;
        private static HRDepartmentData sourceData;

        public static HRDepartment Instance {
            get {
                if (instance == null)
                    instance = new HRDepartment();
                return instance;
            }
        }

        private HRDepartment() { }

        static HRDepartment() {
            randomizer = new Random();
            sourceData = new HRDepartmentData();
        }
       
        private static string RandomName() {
            return sourceData.names[randomizer.Next(sourceData.names.Count)]; 
        }

        private static string RandomSurname() {
            return sourceData.surnames[randomizer.Next(sourceData.surnames.Count)];
        }   

        private static string RandomSkill() {
            return sourceData.skills[randomizer.Next(sourceData.skills.Count)];
        }
        
        public Programmer HireProgrammer() {
            return new Programmer(RandomName(),RandomSurname(), RandomSkill());
        }

        public TechLead HireTechLead() {
            return new TechLead(RandomName(), RandomSurname());
        }

        public Tester HireTester() {
            return new Tester(RandomName(), RandomSurname());
        }

        public QALead HireQALead() {
            return new QALead(RandomName(), RandomSurname());
        }

        public Analyst HireAnalyst() {
            return new Analyst(RandomName(), RandomSurname());
        }

        public AnalyticsLead HireAnalyticsLead() {
            return new AnalyticsLead(RandomName(), RandomSurname());
        }
    }
}
