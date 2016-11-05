using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    class WrongUserStoriesException : Exception {
        public WrongUserStoriesException(string message)
        : base(message) { }
    }
}
