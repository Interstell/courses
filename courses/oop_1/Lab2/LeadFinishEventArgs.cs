using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    public class LeadFinishEventArgs {
        private string message;
        private int workAmount;

        public string Message {
            get { return message; }
            set {
                if (!String.IsNullOrEmpty(value)) {
                    message = value;
                }
            }
        }

        public int WorkAmount {
            get { return workAmount; }
            set { workAmount = value; }
        }

        public LeadFinishEventArgs(string message, int workAmount) {
            this.Message = message;
            this.workAmount = workAmount;
        }

        public LeadFinishEventArgs() : this("", 0) { }
    }
}
