using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Input;

namespace Lab5 {
    public class ViewModelBase : INotifyPropertyChanged {
        #region Implementation of INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName) {
            OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        protected virtual void OnPropertyChanged(PropertyChangedEventArgs args) {
            var handler = PropertyChanged;
            if (handler != null)
                handler(this, args);
        }
        #endregion
    }

    public class DelegateCommand : ICommand {
        public delegate void ICommandOnExecute(object parameter);
        public delegate bool ICommandOnCanExecute(object parameter);

        private ICommandOnExecute _execute;
        private ICommandOnCanExecute _canExecute;

        public DelegateCommand(ICommandOnExecute onExecuteMethod, ICommandOnCanExecute onCanExecuteMethod) {
            _execute = onExecuteMethod;
            _canExecute = onCanExecuteMethod;
        }

        #region ICommand Members

        public event EventHandler CanExecuteChanged {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public bool CanExecute(object parameter) {
            return _canExecute.Invoke(parameter);
        }

        public void Execute(object parameter) {
            _execute.Invoke(parameter);
        }

        #endregion
    }

    public class MainViewModel : ViewModelBase {
        private DelegateCommand exitCommand;

        #region Constructor

        public ProgrammersModel Programmers { get; set; }
        public string ProgrammerNameToAdd { get; set; }
        public string ProgrammerSurnameToAdd { get; set; }
        public string ProgrammerSkillsToAdd { get; set; }

        private Programmer _selectedProgrammer;

        public Programmer SelectedProgrammer {
            get { return this._selectedProgrammer; }
            set {
                this._selectedProgrammer = value;
                OnPropertyChanged("SelectedProgrammer");
            }
        }


        public MainViewModel() {
            Programmers = ProgrammersModel.Current;
        }

        #endregion

        public ICommand ExitCommand {
            get {
                if (exitCommand == null) {
                    exitCommand = new DelegateCommand(Exit, CanExecuteExit);
                }
                return exitCommand;
            }
        }

        private void Exit(object parameter) {
            SaveDataToFile();
            Application.Current.Shutdown();
        }

        public bool CanExecuteExit(object parameter) {
            return true;
        }

        private ICommand _AddProgrammer;
        public ICommand AddProgrammer {
            get {
                if (_AddProgrammer == null) {
                    _AddProgrammer = new DelegateCommand(ExecuteAddProgrammer, CanExecuteAddProgrammer);
                }
                return _AddProgrammer;
            }
        }
        public void ExecuteAddProgrammer(object parameter) {
           Programmers.AddAProgrammer(ProgrammerNameToAdd,
                ProgrammerSurnameToAdd, ProgrammerSkillsToAdd, DateTime.Now);
        }
        public bool CanExecuteAddProgrammer(object parameter) {
            return !(string.IsNullOrEmpty(ProgrammerNameToAdd)
                || string.IsNullOrEmpty(ProgrammerSurnameToAdd)
                || string.IsNullOrEmpty(ProgrammerSkillsToAdd));
        }

        private ICommand _SaveProgrammer;

        public ICommand SaveProgrammer {
            get {
                if (_SaveProgrammer == null) {
                    _SaveProgrammer = new DelegateCommand(ExecuteSaveProgrammer, CanExecuteSaveProgrammer);
                }
                return _SaveProgrammer;
            }
        }

        public void ExecuteSaveProgrammer(object parameter) {
            OnPropertyChanged("Programmers");
        }
        public bool CanExecuteSaveProgrammer(object parameter) {
            return SelectedProgrammer != null;
        }

        private ICommand _DeleteProgrammer;

        public ICommand DeleteProgrammer {
            get {
                if (_DeleteProgrammer == null) {
                    _DeleteProgrammer = new DelegateCommand(ExecuteDeleteProgrammer, CanExecuteDeleteProgrammer);
                }
                return _DeleteProgrammer;
            }
        }

        public void ExecuteDeleteProgrammer(object parameter) {
            Programmer prog = Programmers.Single(p => p.ID == (int) parameter);
            if (SelectedProgrammer != null && SelectedProgrammer.ID == prog.ID) {
                SelectedProgrammer = null;
            }
            Programmers.Remove(prog);
            OnPropertyChanged("Programmers");
        }
        public bool CanExecuteDeleteProgrammer(object parameter) {
            return true;
        }

        private void SaveDataToFile() {
            List<Programmer> list = new List<Programmer>(Programmers);
            ProgrammersContainer.SerializeToFile(list);
        }

    }
}
