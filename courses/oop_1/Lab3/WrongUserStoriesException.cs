using System;

namespace Lab3 {
    public class WrongUserStoriesException : Exception {
        private int count;
        public WrongUserStoriesException(string message, int count)
        : base(message) {
            this.count = count;
        }
    }
}
