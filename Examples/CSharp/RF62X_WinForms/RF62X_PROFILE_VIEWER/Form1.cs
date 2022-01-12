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
            TmpThread = new Thread(ReadData);
           
            t = new System.Windows.Forms.Timer();
            t2 = new System.Windows.Forms.Timer();

            t.Tick += T_Tick1;
            t2.Tick += T_Tick2;
            t.Interval = 30;
            t2.Interval = 1000;
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
            Scanners = RF62X.RF627smart.Search();

            for (int i = 0; i < Scanners.Count; i++)
            {
                Scanners[i].Connect();
                Scanners[i].ReadParams();
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
                    if (TmpThread.IsAlive)
                    {
                        currentScanner = i;
                        currentScannerChanged = true;
                    }
                    else
                    {
                        TmpThread.Start();

                        currentScanner = i;
                        currentScannerChanged = true;

                        t.Start();
                        t2.Start();

                    }
                                       
                }
            }        

        }
        public int count { get; set; }
        private void ReadData()
        {
            while(true)
            {
                // Receive profile
                RF62X.Profile2D _profile = Scanners[currentScanner].GetProfile();
                if (_profile != null)
                {
                    profile = _profile;
                    count++;
                }

                if (profile != null && currentScannerChanged)
                {
                    if (profile.pixels != null)
                        profile.pixels.Clear();
                    if (profile.points != null)
                        profile.points.Clear();
                    currentScannerChanged = false;
                }

                if (stop)
                    break;

            }
        }

        private void T_Tick1(object sender, EventArgs e)
        {
            if(profile != null && profile.header != null)
            {
                chart1.Series[0].Points.Clear();

                var data = chart1.Series[0].Points;
                data.SuspendUpdates();

                for (int i = 0; i < profile.points.Count; i++)
                    data.Add(profile.points[i].Z, profile.points[i].X);

                data.ResumeUpdates();
            }
        }
        private void T_Tick2(object sender, EventArgs e)
        {
            // Receive profile
            chart1.Titles[0].Text = "Name: " + listScanners.Items[currentScanner].Text + ", FPS: " + count.ToString();
            count = 0;
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
        }
    }
}
