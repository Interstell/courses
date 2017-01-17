using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.ExceptionServices;

namespace Lab4 {

    public static class TeamContainerExtension {
        public static int GetTeamHourPayrate<T>(this TeamContainer<T> team) where T:Employee{
            int sum = 0;
            foreach (T emp in team) {
                sum += emp.HourPayRate;
            }
            return sum;
        } 
    }

    // Refactoring #1: Инкапсуляция коллекции (Encapsulate Collection)

    public class TeamContainer<T>: IEnumerable<T>, IEnumerator<T>, IDisposable where T:Employee{
        private List<T> _team;
        private T _teamLead;
        private int position = -1;
        private bool disposed = false;
      
        public T TeamLead {
            get { return _teamLead; }
            set {
                if (value != null) {
                    _teamLead = value;
                }
            }
        }

        public List<T> Members {
            get { return _team; }
        }

        public int Count{
            get {
                return _team.Count;
            }
        }

        public TeamContainer( ) {
            _team = new List<T>();
        }

        public T this[int index] {
            get { return _team[index]; }
            set { _team[index] = value; }
        }

        public T this[string surname] {
            get { return _team.Find(member => member.Surname.Equals(surname)); }
        }

        public IEnumerator<T> GetEnumerator() {
            return _team.GetEnumerator();
        }
        
        IEnumerator IEnumerable.GetEnumerator() {
            return this.GetEnumerator();
        }

        public bool MoveNext() {
            position++;
            return (position < _team.Count);
        }

        object IEnumerator.Current {
            get {
                return Current;
            }
        }

        public T Current {
            get { return _team[position]; }
        }

        public void Reset() {
            position = -1;
        }

        public TeamContainer(T teamLead):this() {
            this._teamLead = teamLead;
        }
        
        public void Add(T member) {
            _team.Add(member);
        }

        public void Dispose() {
            Cleanup(true);
            GC.SuppressFinalize(this);
            Console.WriteLine("\tTeam was disposed.");
        }

        private void Cleanup(bool disposing) {
            if (this.disposed)
                return;
            if (disposing) {
                foreach (Employee emp in _team) {
                    emp.Dispose();
                }
            }
            disposed = true;
        }

        ~TeamContainer() {
            //Called if team was not Disposed.
            Console.WriteLine("\tTeam is finalized.");
            Cleanup(false);
        }
    }
}
