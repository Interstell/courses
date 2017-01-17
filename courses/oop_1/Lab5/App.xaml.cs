using System.Windows;
using System.Windows.Threading;

namespace Lab5 {
    public partial class App : Application {
        private void OnStartup(object sender, StartupEventArgs e) {
            MainWindow view = new MainWindow();
            view.DataContext = new MainViewModel();
            view.Show();
        }

        private void APP_DispatcherUnhandledException(object sender,
            DispatcherUnhandledExceptionEventArgs e) {
            MessageBox.Show(e.Exception.Message);
            e.Handled = true;
        }
    }
}
