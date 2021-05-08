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


namespace RF62X_PROFILE_VIEWER
{
    public partial class Form1 : Form
    {
        // RF627old devices list
        public List<RF62X.RF627old> Scanners { get; set; }
        public RF62X.Profile profile { get; set; }
        public List<RF62X.Params.Description> ParamDescriptionList { get; set; }

        public Thread TmpThread { get; set; }
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

            ParamDescriptionList = RF62X.Params.GetParamsDescriptionList();

            foreach (RF62X.Params.Description param in ParamDescriptionList)
            {
                paramsComboBox.Items.Add(param.Key);
            }

            TmpThread = new Thread(ReadData);
           
            t = new System.Windows.Forms.Timer();
            t2 = new System.Windows.Forms.Timer();

            t.Tick += T_Tick1;
            t2.Tick += T_Tick2;
            t.Interval = 30;
            t2.Interval = 1000;
        }

        private void buttonForSearch_Click(object sender, EventArgs e)
        {
            Scanners = RF62X.RF627old.Search();

            for (int i = 0; i < Scanners.Count; i++)
            {
                Scanners[i].Connect();
                Scanners[i].ReadParams();
                RF62X.Param<string> name = Scanners[i].GetParam(RF62X.Params.User.General.deviceName);
                listScanners.Items.Add(name.GetValue());
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
                RF62X.Profile _profile = Scanners[currentScanner].GetProfile();
                if (_profile.header != null)
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

        private void paramsComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            RF62X.Params.Description selectedParamDescription = ParamDescriptionList.Where(p => p.Key.Equals(paramsComboBox.SelectedItem)).FirstOrDefault();

            if (selectedParamDescription != null)
            {

                labelParamName.Text = "Name:";
                labelParamType.Text = "Type:";
                labelParamAccess.Text = "Access:";
                labelParamIndex.Text = "Index:";
                labelParamOffset.Text = "Offset:";
                labelParamSize.Text = "Size:";
                labelParamUints.Text = "Uints:";

                switch (selectedParamDescription.Type)
                {
                    case "unkn_t":
                        {
                            
                            break;
                        }
                    case "uint32_t":
                        {
                            RF62X.Param<uint> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "uint64_t":
                        {
                            RF62X.Param<ulong> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "int32_t":
                        {
                            RF62X.Param<int> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "int64_t":
                        {
                            RF62X.Param<long> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamName.Text = "Type:" + param.type;
                                labelParamName.Text = "Access:" + param.access;
                                labelParamName.Text = "Index:" + param.index.ToString();
                                labelParamName.Text = "Offset:" + param.offset.ToString();
                                labelParamName.Text = "Size:" + param.size.ToString();
                                labelParamName.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "float_t":
                        {
                            RF62X.Param<float> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "double_t":
                        {
                            RF62X.Param<double> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "u32_arr_t":
                        {
                            RF62X.Param<uint[]> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "u64_arr_t":
                        {
                            RF62X.Param<ulong> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "i32_arr_t":
                        {
                            RF62X.Param<int[]> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "i64_arr_t":
                        {
                            RF62X.Param<long[]> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "flt_array_t":
                        {
                            RF62X.Param<float[]> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "dbl_array_t":
                        {
                            RF62X.Param<double[]> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
                            }
                            break;
                        }
                    case "string_t":
                        {
                            RF62X.Param<string> param = Scanners[currentScanner].GetParam(selectedParamDescription);
                            if (param != null)
                            {
                                labelParamName.Text = "Name:" + param.name;
                                labelParamType.Text = "Type:" + param.type;
                                labelParamAccess.Text = "Access:" + param.access;
                                labelParamIndex.Text = "Index:" + param.index.ToString();
                                labelParamOffset.Text = "Offset:" + param.offset.ToString();
                                labelParamSize.Text = "Size:" + param.size.ToString();
                                labelParamUints.Text = "Uints:" + param.units;
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
    }
}
