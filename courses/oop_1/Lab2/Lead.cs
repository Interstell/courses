using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    /// <summary>
    /// Abstract class containing common properties of Department Heads (TechLead etc.)
    /// </summary>

    abstract class Lead : Employee, IManageable {
               
        public Lead(string name, string surname) : base(name, surname) {
            
        }

        public int MoneyPaidToTeam { get; set; }

        public abstract void hireTeam();

        public abstract void setTask(int amount);

    }
}
