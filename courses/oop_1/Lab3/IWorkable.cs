﻿namespace Lab3 {
    interface IWorkable {
        string Name { get; set; }
        string Surname {get; set; }
        int HourPayRate { get; set; }
        int Work();
    }
}