using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    interface IWorkable {
        string Name { get; set; }
        string Surname {get; set; }
        int HourPayRate { get; set; }
        int Work();
    }
}
