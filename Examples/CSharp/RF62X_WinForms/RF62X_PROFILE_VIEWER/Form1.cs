using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.Reflection;
using SDK.SCANNERS;
using MessagePack;
using System.Collections;

namespace RF62X_PROFILE_VIEWER
{
    public partial class Form1 : Form
    {
        // RF627smart devices list
        public List<RF62X.RF627smart> Scanners { get; set; }
        public RF62X.Profile2D profile { get; set; }

        public Thread TmpThread { get; set; }
        public bool stop { get; set; }
        public System.Windows.Forms.Timer t { get; set; }
        public System.Windows.Forms.Timer t2 { get; set; }
        public string CurrentProfileTypeLabel { get; set; }
        public string LastViewerStatus { get; set; }

        private readonly object profileSync = new object();
        private Label labelCurrentProfileType;
        private Label labelCurrentProfileTypeValue;
        private Label labelStreamStatus;
        private Label labelStreamStatusValue;

        public Form1()
        {
            InitializeComponent();

            // Start initialization of the library core
            RF62X.SdkInit();
            chart1.ChartAreas[0].AxisX.Maximum = 648;
            chart1.ChartAreas[0].AxisX.Minimum = 0;
            chart1.ChartAreas[0].AxisX.Enabled = AxisEnabled.True;
            chart1.ChartAreas[0].AxisY.Maximum = 50;
            chart1.ChartAreas[0].AxisY.Minimum = 0;
            chart1.ChartAreas[0].AxisY.Enabled = AxisEnabled.True;

            //ParamDescriptionList = RF62X.Params.GetParamsDescriptionList();

            //foreach (RF62X.Params.Description param in ParamDescriptionList)
            //{
            //    paramsComboBox.Items.Add(param.Key);
            //}

            stop = false;
            CurrentProfileTypeLabel = "UNKNOWN";
            LastViewerStatus = "Idle";
            TmpThread = new Thread(ReadData);
            TmpThread.IsBackground = true;
           
            t = new System.Windows.Forms.Timer();
            t2 = new System.Windows.Forms.Timer();

            t.Tick += T_Tick1;
            t2.Tick += T_Tick2;
            t.Interval = 30;
            t2.Interval = 1000;

            InitializeStatusArea();
        }

        private void InitializeStatusArea()
        {
            labelCurrentProfileType = new Label();
            labelCurrentProfileType.AutoSize = true;
            labelCurrentProfileType.Font = new Font("Microsoft Sans Serif", 11.25F, FontStyle.Regular, GraphicsUnit.Point, ((byte)(204)));
            labelCurrentProfileType.Location = new Point(12, 174);
            labelCurrentProfileType.Name = "labelCurrentProfileType";
            labelCurrentProfileType.Size = new Size(103, 18);
            labelCurrentProfileType.Text = "Current profile:";

            labelCurrentProfileTypeValue = new Label();
            labelCurrentProfileTypeValue.AutoSize = true;
            labelCurrentProfileTypeValue.Font = new Font("Microsoft Sans Serif", 11.25F, FontStyle.Bold, GraphicsUnit.Point, ((byte)(204)));
            labelCurrentProfileTypeValue.Location = new Point(126, 174);
            labelCurrentProfileTypeValue.Name = "labelCurrentProfileTypeValue";
            labelCurrentProfileTypeValue.Size = new Size(86, 18);
            labelCurrentProfileTypeValue.Text = CurrentProfileTypeLabel;

            labelStreamStatus = new Label();
            labelStreamStatus.AutoSize = true;
            labelStreamStatus.Font = new Font("Microsoft Sans Serif", 11.25F, FontStyle.Regular, GraphicsUnit.Point, ((byte)(204)));
            labelStreamStatus.Location = new Point(12, 196);
            labelStreamStatus.Name = "labelStreamStatus";
            labelStreamStatus.Size = new Size(52, 18);
            labelStreamStatus.Text = "Status:";

            labelStreamStatusValue = new Label();
            labelStreamStatusValue.AutoSize = true;
            labelStreamStatusValue.Font = new Font("Microsoft Sans Serif", 11.25F, FontStyle.Bold, GraphicsUnit.Point, ((byte)(204)));
            labelStreamStatusValue.Location = new Point(126, 196);
            labelStreamStatusValue.Name = "labelStreamStatusValue";
            labelStreamStatusValue.Size = new Size(29, 18);
            labelStreamStatusValue.Text = LastViewerStatus;

            Controls.Add(labelCurrentProfileType);
            Controls.Add(labelCurrentProfileTypeValue);
            Controls.Add(labelStreamStatus);
            Controls.Add(labelStreamStatusValue);

            label1.Top += 48;
            treeView1.Top += 48;
            label2.Top += 48;
            comboBox1.Top += 48;
            label3.Top += 48;
            label4.Top += 48;
            label5.Top += 48;
            label6.Top += 48;
            labelName.Top += 48;
            labelType.Top += 48;
            labelValue.Top += 48;
        }

        public static byte[] HexStringToByteArray(string hex)
        {
            var result = new byte[hex.Length / 2];
            for (var i = 0; i < result.Length; i++)
            {
                result[i] = System.Convert.ToByte(hex.Substring(i * 2, 2), 16);
            }
            return result;
        }

        private TreeNode[] RecurseTree(Dictionary<object, object> dic)
        {
            List<TreeNode> branch = new List<TreeNode>();

            foreach (KeyValuePair<object, object> kvp in dic)
            {
                TreeNode twig = new TreeNode(kvp.Key.ToString());
                if (!(kvp.Value is object[]))
                {
                    if (kvp.Key.ToString() == "name")
                        comboBox1.Items.Add(kvp.Value);
                    twig.Nodes.Add(new TreeNode(kvp.Value.ToString()));
                }
                else if (kvp.Value is Dictionary<object, object>)
                {
                    twig.Nodes.AddRange(RecurseTree((Dictionary<object, object>)kvp.Value));
                }
                else
                {
                    IEnumerable enumerable = (kvp.Value as IEnumerable);
                    if (enumerable != null)
                    {
                        int count = 0;
                        foreach (var item in enumerable)
                        {
                            if (!(item is Dictionary<object, object>))
                            {
                                twig.Nodes.Add(new TreeNode(item.ToString()));
                            }
                            else if (item is Dictionary<object, object>)
                            {
                                TreeNode twig2 = new TreeNode(count.ToString());
                                twig2.Nodes.AddRange(RecurseTree((Dictionary<object, object>)item));
                                twig.Nodes.Add(twig2);
                                count++;
                            }
                        }
                    }
                }
                branch.Add(twig);
            }

            return branch.ToArray();
        }

        private void buttonForSearch_Click(object sender, EventArgs e)
        {
            listScanners.Items.Clear();
            treeView1.Nodes.Clear();
            comboBox1.Items.Clear();

            Scanners = RF62X.RF627smart.Search();
            LastViewerStatus = "Scanners found: " + Scanners.Count.ToString();

            for (int i = 0; i < Scanners.Count; i++)
            {
                if (!Scanners[i].Connect())
                    continue;

                if (!Scanners[i].ReadParams())
                    continue;

                RF62X.Parameter<string> name = Scanners[i].GetParam("user_general_deviceName");
                listScanners.Items.Add(name.GetValue());

                List<byte> outData = new List<byte>();
                Scanners[i].SendCustomCommand("GET_PARAMS_DESCRIPTION\0", ref outData);

                if (outData.Count() > 0)
                {
                    var hexUtf8 = Encoding.UTF8.GetString(outData.ToArray());
                    //var bytesUtf8 = HexStringToByteArray(hexUtf8);

                    var test = MessagePackSerializer.Deserialize<dynamic>(outData.ToArray());

                    treeView1.Nodes.AddRange(RecurseTree(test));
                }
            }
           
        }

        private int currentScanner { get; set; }
        private bool currentScannerChanged { get; set; }
        private void listScanners_SelectedIndexChanged(object sender, EventArgs e)
        {
            
            for (int i = 0; i < listScanners.Items.Count; i++)
            {
                if (listScanners.Items[i].Selected)
                {
                    currentScanner = i;
                    currentScannerChanged = true;
                    count = 0;
                    lock (profileSync)
                    {
                        profile = null;
                    }
                    CurrentProfileTypeLabel = "WAITING";
                    LastViewerStatus = "Starting profile stream...";

                    if (TmpThread.IsAlive)
                    {
                        if (!Scanners[currentScanner].Connect())
                            LastViewerStatus = "Connect failed";
                    }
                    else
                    {
                        if (!Scanners[currentScanner].Connect())
                        {
                            LastViewerStatus = "Connect failed";
                            return;
                        }

                        TmpThread.Start();

                        t.Start();
                        t2.Start();

                    }
                                       
                }
            }        

        }
        public int count { get; set; }
        private void ReadData()
        {
            while(!stop)
            {
                try
                {
                    if (Scanners == null || currentScanner < 0 || currentScanner >= Scanners.Count)
                    {
                        Thread.Sleep(50);
                        continue;
                    }

                    RF62X.Profile2D nextProfile = Scanners[currentScanner].GetProfile();
                    if (nextProfile != null)
                    {
                        lock (profileSync)
                        {
                            profile = nextProfile;
                            count++;
                        }
                        LastViewerStatus = "Streaming";
                    }
                    else
                    {
                        LastViewerStatus = "No profile received";
                    }
                }
                catch (Exception ex)
                {
                    LastViewerStatus = ex.GetType().Name + ": " + ex.Message;
                    Program.LogException("Form1.ReadData", ex);
                    Thread.Sleep(100);
                }

            }
        }

        private void T_Tick1(object sender, EventArgs e)
        {
            RF62X.Profile2D currentProfile = null;
            lock (profileSync)
            {
                currentProfile = profile;
            }

            if(currentProfile != null && currentProfile.header != null)
            {
                chart1.Series[0].Points.Clear();

                var data = chart1.Series[0].Points;
                data.SuspendUpdates();

                CurrentProfileTypeLabel = GetProfileTypeLabel(currentProfile.header.data_type);

                switch (currentProfile.header.data_type)
                {
                    case RF62X.PROFILE_DATA_TYPES.PIXELS:
                    case RF62X.PROFILE_DATA_TYPES.PIXELS_INTRP:
                        DrawPixelsProfile(currentProfile, data);
                        break;

                    case RF62X.PROFILE_DATA_TYPES.PROFILE:
                    case RF62X.PROFILE_DATA_TYPES.PROFILE_INTRP:
                    case RF62X.PROFILE_DATA_TYPES.PROFILE_POLYNOMIAL:
                        DrawMetricProfile(currentProfile, data);
                        break;

                    default:
                        DrawFallbackProfile(currentProfile, data);
                        break;
                }

                data.ResumeUpdates();
            }
        }
        private void T_Tick2(object sender, EventArgs e)
        {
            // Receive profile
            string scannerName = (listScanners.Items.Count > currentScanner && currentScanner >= 0)
                ? listScanners.Items[currentScanner].Text
                : "...";

            chart1.Titles[0].Text = "Name: " + scannerName +
                ", FPS: " + count.ToString() +
                ", Type: " + CurrentProfileTypeLabel;

            labelCurrentProfileTypeValue.Text = CurrentProfileTypeLabel;
            labelStreamStatusValue.Text = LastViewerStatus;
            count = 0;
        }

        private string GetProfileTypeLabel(RF62X.PROFILE_DATA_TYPES dataType)
        {
            switch (dataType)
            {
                case RF62X.PROFILE_DATA_TYPES.PIXELS:
                    return "RAW (PIXELS)";
                case RF62X.PROFILE_DATA_TYPES.PIXELS_INTRP:
                    return "RAW (PIXELS_INTRP)";
                case RF62X.PROFILE_DATA_TYPES.PROFILE:
                    return "METRIC (PROFILE)";
                case RF62X.PROFILE_DATA_TYPES.PROFILE_INTRP:
                    return "METRIC (PROFILE_INTRP)";
                case RF62X.PROFILE_DATA_TYPES.PROFILE_POLYNOMIAL:
                    return "METRIC (PROFILE_POLYNOMIAL)";
                default:
                    return dataType.ToString();
            }
        }

        private void DrawMetricProfile(RF62X.Profile2D currentProfile, DataPointCollection data)
        {
            if (currentProfile.points == null || currentProfile.points.Count == 0)
                return;

            double minX = double.MaxValue;
            double maxX = double.MinValue;
            double minZ = double.MaxValue;
            double maxZ = double.MinValue;

            for (int i = 0; i < currentProfile.points.Count; i++)
            {
                double x = currentProfile.points[i].X;
                double z = currentProfile.points[i].Z;

                data.AddXY(x, z);

                if (x < minX) minX = x;
                if (x > maxX) maxX = x;
                if (z < minZ) minZ = z;
                if (z > maxZ) maxZ = z;
            }

            ConfigureAxes(minX, maxX, minZ, maxZ, "X", "Z");
        }

        private void DrawPixelsProfile(RF62X.Profile2D currentProfile, DataPointCollection data)
        {
            List<double> pixels = GetPixelValues(currentProfile);
            if (pixels.Count == 0)
                return;

            double minPixel = double.MaxValue;
            double maxPixel = double.MinValue;

            for (int i = 0; i < pixels.Count; i++)
            {
                double pixelValue = pixels[i];
                data.AddXY(i, pixelValue);

                if (pixelValue < minPixel) minPixel = pixelValue;
                if (pixelValue > maxPixel) maxPixel = pixelValue;
            }

            ConfigureAxes(0, pixels.Count - 1, minPixel, maxPixel, "Pixel index", "Pixel value");
        }

        private void DrawFallbackProfile(RF62X.Profile2D currentProfile, DataPointCollection data)
        {
            if (currentProfile.points != null && currentProfile.points.Count > 0)
            {
                DrawMetricProfile(currentProfile, data);
                return;
            }

            if (GetPixelValues(currentProfile).Count > 0)
            {
                DrawPixelsProfile(currentProfile, data);
            }
        }

        private List<double> GetPixelValues(RF62X.Profile2D currentProfile)
        {
            var pixels = ReadPixelsFromMember(currentProfile, "pixels");
            if (pixels.Count > 0)
                return pixels;

            pixels = ReadPixelsFromMethod(currentProfile, "get_pixels");
            if (pixels.Count > 0)
                return pixels;

            return ReadPixelsFromMethod(currentProfile, "getPixelsArray");
        }

        private List<double> ReadPixelsFromMember(RF62X.Profile2D currentProfile, string memberName)
        {
            if (currentProfile == null)
                return new List<double>();

            try
            {
                PropertyInfo property = currentProfile.GetType().GetProperty(memberName, BindingFlags.Instance | BindingFlags.Public);
                if (property == null)
                    return new List<double>();

                return ConvertPixelsToDoubles(property.GetValue(currentProfile, null) as IEnumerable);
            }
            catch (Exception ex)
            {
                Program.LogException("Form1.ReadPixelsFromMember", ex);
                return new List<double>();
            }
        }

        private List<double> ReadPixelsFromMethod(RF62X.Profile2D currentProfile, string methodName)
        {
            if (currentProfile == null)
                return new List<double>();

            try
            {
                MethodInfo method = currentProfile.GetType().GetMethod(methodName, BindingFlags.Instance | BindingFlags.Public, null, Type.EmptyTypes, null);
                if (method == null)
                    return new List<double>();

                return ConvertPixelsToDoubles(method.Invoke(currentProfile, null) as IEnumerable);
            }
            catch (Exception ex)
            {
                Program.LogException("Form1.ReadPixelsFromMethod", ex);
                return new List<double>();
            }
        }

        private List<double> ConvertPixelsToDoubles(IEnumerable source)
        {
            List<double> pixels = new List<double>();
            if (source == null)
                return pixels;

            foreach (object value in source)
            {
                if (value == null)
                    continue;

                pixels.Add(Convert.ToDouble(value));
            }

            return pixels;
        }

        private void ConfigureAxes(double minX, double maxX, double minY, double maxY, string xTitle, string yTitle)
        {
            if (double.IsInfinity(minX) || double.IsInfinity(maxX) || double.IsInfinity(minY) || double.IsInfinity(maxY))
                return;

            if (minX == maxX)
            {
                minX -= 1;
                maxX += 1;
            }

            if (minY == maxY)
            {
                minY -= 1;
                maxY += 1;
            }

            double xMargin = Math.Max((maxX - minX) * 0.05, 1);
            double yMargin = Math.Max((maxY - minY) * 0.05, 1);

            chart1.ChartAreas[0].AxisX.Minimum = minX - xMargin;
            chart1.ChartAreas[0].AxisX.Maximum = maxX + xMargin;
            chart1.ChartAreas[0].AxisY.Minimum = minY - yMargin;
            chart1.ChartAreas[0].AxisY.Maximum = maxY + yMargin;
            chart1.ChartAreas[0].AxisX.Title = xTitle;
            chart1.ChartAreas[0].AxisY.Title = yTitle;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string selected = this.comboBox1.GetItemText(this.comboBox1.SelectedItem);
            var param = Scanners[currentScanner].GetParam(selected);

            if (param != null)
            {
                labelName.Text = ": " + param.name;
                labelType.Text = ": " + param.type;

                switch (param.type)
                {
                    case "unkn_t":
                        {
                            labelName.Text = ": ...";
                            labelType.Text = ": ...";
                            break;
                        }
                    case "uint32_t":
                        {
                            RF62X.Parameter<uint> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + _param.GetValue();
                            }
                            break;
                        }
                    case "uint64_t":
                        {
                            RF62X.Parameter<ulong> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + _param.GetValue();
                            }
                            break;
                        }
                    case "int32_t":
                        {
                            RF62X.Parameter<int> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + _param.GetValue();
                            }
                            break;
                        }
                    case "int64_t":
                        {
                            RF62X.Parameter<long> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + _param.GetValue();
                            }
                            break;
                        }
                    case "float_t":
                        {
                            RF62X.Parameter<float> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + _param.GetValue();
                            }
                            break;
                        }
                    case "double_t":
                        {
                            RF62X.Parameter<double> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + _param.GetValue();
                            }
                            break;
                        }
                    case "u32_arr_t":
                        {
                            RF62X.Parameter<List<uint>> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + string.Join(",", _param.GetValue());
                            }
                            break;
                        }
                    case "u64_arr_t":
                        {
                            RF62X.Parameter<List<ulong>> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + string.Join(",", _param.GetValue());
                            }
                            break;
                        }
                    case "i32_arr_t":
                        {
                            RF62X.Parameter<List<int>> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + string.Join(",", _param.GetValue());
                            }
                            break;
                        }
                    case "i64_arr_t":
                        {
                            RF62X.Parameter<List<long>> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + string.Join(",", _param.GetValue());
                            }
                            break;
                        }
                    case "flt_array_t":
                        {
                            RF62X.Parameter<List<float>> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + string.Join(",", _param.GetValue());
                            }
                            break;
                        }
                    case "dbl_array_t":
                        {
                            RF62X.Parameter<List<double>> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + string.Join(",", _param.GetValue());
                            }
                            break;
                        }
                    case "string_t":
                        {
                            RF62X.Parameter<string> _param = param;
                            if (param != null)
                            {
                                labelValue.Text = ": " + _param.GetValue();
                            }
                            break;
                        }
                    default:
                        {
                            break;
                        }

                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            t.Stop();
            t2.Stop();
            stop = true;

            if (TmpThread != null && TmpThread.IsAlive)
                TmpThread.Join(500);

            if (Scanners != null)
            {
                foreach (var scanner in Scanners)
                    scanner.Disconnect();
            }
        }
    }
}
