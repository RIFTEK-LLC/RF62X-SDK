using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace RF62X_PROFILE_VIEWER
{
    static class Program
    {
        public static void LogException(string source, Exception ex)
        {
            try
            {
                string logPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "viewer-crash.log");
                string text =
                    "[" + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff") + "] " + source + Environment.NewLine +
                    ex + Environment.NewLine +
                    new string('-', 80) + Environment.NewLine;
                File.AppendAllText(logPath, text);
            }
            catch
            {
            }
        }

        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.ThreadException += (sender, args) =>
            {
                LogException("Application.ThreadException", args.Exception);
                MessageBox.Show(args.Exception.ToString(), "Unhandled UI exception");
            };

            AppDomain.CurrentDomain.UnhandledException += (sender, args) =>
            {
                Exception ex = args.ExceptionObject as Exception ??
                    new Exception(args.ExceptionObject != null ? args.ExceptionObject.ToString() : "Unknown unhandled exception");
                LogException("AppDomain.CurrentDomain.UnhandledException", ex);
            };

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
