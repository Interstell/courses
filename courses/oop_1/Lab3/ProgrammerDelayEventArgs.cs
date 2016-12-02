using System;

namespace Lab3 {
    public class ProgrammerDelayEventArgs : EventArgs {
        public ProgrammerDelayType DelayType { get; set; }

        public ProgrammerDelayEventArgs(ProgrammerDelayType delayType) {
            DelayType = delayType;
        }
    }
}