using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SpeedTestApp_GUI.usercontrol
{
    /// <summary>
    /// Interaction logic for contentpane.xaml
    /// </summary>
    public partial class ContentPane : UserControl
    {
        Process _runningprocess;
        public ContentPane()
        {
            InitializeComponent();
        }

        private async void Start_button_Click(object sender, RoutedEventArgs e)
        {
            Start_button.IsEnabled = false;
            DL_only.IsEnabled = false;
            UL_only.IsEnabled = false;
            //Start_button.Content = "Restart";
            DL_Output_Text_Box.Text = "Starting Download...";

            await Task.Delay(1000);

            await RunDownloadTestApp();

            DL_Output_Text_Box.Text = "Starting Upload...";

            await Task.Delay(1000);

            await RunUploadTestApp();

            DL_Output_Text_Box.Text = "Finished...";

            Start_button.IsEnabled = true;
            UL_only.IsEnabled = true;
            DL_only.IsEnabled = true;
        }

        private async Task RunDownloadTestApp()
        {
            string downloadPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "C++ Files", "Download_Test_App.exe");
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = downloadPath,

                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            _runningprocess = new Process
            {
                StartInfo = psi,
                EnableRaisingEvents = true
            };

            _runningprocess.OutputDataReceived += (sender, e) =>
            {
                if (!string.IsNullOrWhiteSpace(e.Data))
                {
                    Dispatcher.Invoke(() =>
                    {
                        DL_Output_Text_Box.Text = "⬇ " + e.Data;
                    });
                }
            };

            _runningprocess.Start();
            _runningprocess.BeginOutputReadLine();

            await _runningprocess.WaitForExitAsync();

            Dispatcher.Invoke(() =>
            {
                DL_Final.Text = DL_Output_Text_Box.Text;
            });
        }

        private async Task RunUploadTestApp()
        {
            string uploadPath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "C++ Files", "Upload_Test_App.exe");
            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = uploadPath,
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            _runningprocess = new Process
            {
                StartInfo = psi,
                EnableRaisingEvents = true
            };

            _runningprocess.OutputDataReceived += (sender, e) =>
            {
                if (!string.IsNullOrWhiteSpace(e.Data))
                {
                    Dispatcher.Invoke(() =>
                    {
                        DL_Output_Text_Box.Text = "⬆" + e.Data;
                    });
                }
            };

            _runningprocess.Start();
            _runningprocess.BeginOutputReadLine();

            await _runningprocess.WaitForExitAsync();

            Dispatcher.Invoke(() =>
            {
                UL_Final.Text = DL_Output_Text_Box.Text;
            });
        }

        private async void Stop_button_Click(object sender, RoutedEventArgs e)
        {
            if (_runningprocess != null && !_runningprocess.HasExited)
            {
                await Task.Delay(1000);

                _runningprocess.Kill();
            }
        }

        private async void DL_only_Click(object sender, RoutedEventArgs e)
        {
            Start_button.IsEnabled = false;
            UL_only.IsEnabled = false;
            DL_only.IsEnabled = false;

            DL_Output_Text_Box.Text = "Starting Download...";

            await Task.Delay(1000);

            await RunDownloadTestApp();

            DL_Output_Text_Box.Text = "Finished...";

            Start_button.IsEnabled = true;
            UL_only.IsEnabled = true;
            DL_only.IsEnabled = true;
        }

        private async void UL_only_Click(object sender, RoutedEventArgs e)
        {
            Start_button.IsEnabled = false;
            UL_only.IsEnabled = false;
            DL_only.IsEnabled = false;

            DL_Output_Text_Box.Text = "Starting Upload...";

            await Task.Delay(1000);

            await RunUploadTestApp();

            DL_Output_Text_Box.Text = "Finished...";

            Start_button.IsEnabled = true;
            UL_only.IsEnabled = true;
            DL_only.IsEnabled = true;
        }
    }
}

