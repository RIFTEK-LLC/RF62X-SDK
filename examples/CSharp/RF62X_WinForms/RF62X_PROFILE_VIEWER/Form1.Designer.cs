namespace RF62X_PROFILE_VIEWER
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title2 = new System.Windows.Forms.DataVisualization.Charting.Title();
            this.buttonForSearch = new System.Windows.Forms.Button();
            this.listScanners = new System.Windows.Forms.ListView();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.paramsComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.labelParamName = new System.Windows.Forms.Label();
            this.labelParamType = new System.Windows.Forms.Label();
            this.labelParamAccess = new System.Windows.Forms.Label();
            this.labelParamIndex = new System.Windows.Forms.Label();
            this.labelParamOffset = new System.Windows.Forms.Label();
            this.labelParamSize = new System.Windows.Forms.Label();
            this.labelParamUints = new System.Windows.Forms.Label();
            this.labelParamMin = new System.Windows.Forms.Label();
            this.labelParamMax = new System.Windows.Forms.Label();
            this.labelParamMaxCount = new System.Windows.Forms.Label();
            this.labelParamDefCount = new System.Windows.Forms.Label();
            this.labelParamStep = new System.Windows.Forms.Label();
            this.labelParamDefValue = new System.Windows.Forms.Label();
            this.labelParamValue = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonForSearch
            // 
            this.buttonForSearch.Location = new System.Drawing.Point(12, 12);
            this.buttonForSearch.Name = "buttonForSearch";
            this.buttonForSearch.Size = new System.Drawing.Size(201, 33);
            this.buttonForSearch.TabIndex = 0;
            this.buttonForSearch.Text = "SEARCH SCANNERS";
            this.buttonForSearch.UseVisualStyleBackColor = true;
            this.buttonForSearch.Click += new System.EventHandler(this.buttonForSearch_Click);
            // 
            // listScanners
            // 
            this.listScanners.HideSelection = false;
            this.listScanners.Location = new System.Drawing.Point(12, 51);
            this.listScanners.Name = "listScanners";
            this.listScanners.Size = new System.Drawing.Size(201, 105);
            this.listScanners.TabIndex = 1;
            this.listScanners.UseCompatibleStateImageBehavior = false;
            this.listScanners.View = System.Windows.Forms.View.List;
            this.listScanners.SelectedIndexChanged += new System.EventHandler(this.listScanners_SelectedIndexChanged);
            // 
            // chart1
            // 
            chartArea2.AxisY.Maximum = 50D;
            chartArea2.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea2);
            legend2.Name = "Legend1";
            this.chart1.Legends.Add(legend2);
            this.chart1.Location = new System.Drawing.Point(219, 12);
            this.chart1.Name = "chart1";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            series2.IsVisibleInLegend = false;
            series2.Legend = "Legend1";
            series2.Name = "Series1";
            series2.YValuesPerPoint = 2;
            this.chart1.Series.Add(series2);
            this.chart1.Size = new System.Drawing.Size(496, 444);
            this.chart1.TabIndex = 2;
            this.chart1.Text = "chart1";
            title2.Name = "Title1";
            title2.Text = "FPS: ";
            this.chart1.Titles.Add(title2);
            // 
            // paramsComboBox
            // 
            this.paramsComboBox.FormattingEnabled = true;
            this.paramsComboBox.Location = new System.Drawing.Point(12, 178);
            this.paramsComboBox.Name = "paramsComboBox";
            this.paramsComboBox.Size = new System.Drawing.Size(201, 21);
            this.paramsComboBox.TabIndex = 3;
            this.paramsComboBox.SelectedIndexChanged += new System.EventHandler(this.paramsComboBox_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 162);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(99, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "parameter selection";
            // 
            // labelParamName
            // 
            this.labelParamName.AutoSize = true;
            this.labelParamName.Location = new System.Drawing.Point(12, 212);
            this.labelParamName.Name = "labelParamName";
            this.labelParamName.Size = new System.Drawing.Size(38, 13);
            this.labelParamName.TabIndex = 5;
            this.labelParamName.Text = "Name:";
            // 
            // labelParamType
            // 
            this.labelParamType.AutoSize = true;
            this.labelParamType.Location = new System.Drawing.Point(12, 225);
            this.labelParamType.Name = "labelParamType";
            this.labelParamType.Size = new System.Drawing.Size(34, 13);
            this.labelParamType.TabIndex = 6;
            this.labelParamType.Text = "Type:";
            // 
            // labelParamAccess
            // 
            this.labelParamAccess.AutoSize = true;
            this.labelParamAccess.Location = new System.Drawing.Point(12, 238);
            this.labelParamAccess.Name = "labelParamAccess";
            this.labelParamAccess.Size = new System.Drawing.Size(45, 13);
            this.labelParamAccess.TabIndex = 7;
            this.labelParamAccess.Text = "Access:";
            // 
            // labelParamIndex
            // 
            this.labelParamIndex.AutoSize = true;
            this.labelParamIndex.Location = new System.Drawing.Point(12, 251);
            this.labelParamIndex.Name = "labelParamIndex";
            this.labelParamIndex.Size = new System.Drawing.Size(36, 13);
            this.labelParamIndex.TabIndex = 8;
            this.labelParamIndex.Text = "Index:";
            // 
            // labelParamOffset
            // 
            this.labelParamOffset.AutoSize = true;
            this.labelParamOffset.Location = new System.Drawing.Point(12, 264);
            this.labelParamOffset.Name = "labelParamOffset";
            this.labelParamOffset.Size = new System.Drawing.Size(38, 13);
            this.labelParamOffset.TabIndex = 9;
            this.labelParamOffset.Text = "Offset:";
            // 
            // labelParamSize
            // 
            this.labelParamSize.AutoSize = true;
            this.labelParamSize.Location = new System.Drawing.Point(12, 277);
            this.labelParamSize.Name = "labelParamSize";
            this.labelParamSize.Size = new System.Drawing.Size(30, 13);
            this.labelParamSize.TabIndex = 10;
            this.labelParamSize.Text = "Size:";
            // 
            // labelParamUints
            // 
            this.labelParamUints.AutoSize = true;
            this.labelParamUints.Location = new System.Drawing.Point(12, 290);
            this.labelParamUints.Name = "labelParamUints";
            this.labelParamUints.Size = new System.Drawing.Size(34, 13);
            this.labelParamUints.TabIndex = 11;
            this.labelParamUints.Text = "Uints:";
            // 
            // labelParamMin
            // 
            this.labelParamMin.AutoSize = true;
            this.labelParamMin.Location = new System.Drawing.Point(12, 311);
            this.labelParamMin.Name = "labelParamMin";
            this.labelParamMin.Size = new System.Drawing.Size(27, 13);
            this.labelParamMin.TabIndex = 12;
            this.labelParamMin.Text = "Min:";
            // 
            // labelParamMax
            // 
            this.labelParamMax.AutoSize = true;
            this.labelParamMax.Location = new System.Drawing.Point(12, 324);
            this.labelParamMax.Name = "labelParamMax";
            this.labelParamMax.Size = new System.Drawing.Size(30, 13);
            this.labelParamMax.TabIndex = 13;
            this.labelParamMax.Text = "Max:";
            // 
            // labelParamMaxCount
            // 
            this.labelParamMaxCount.AutoSize = true;
            this.labelParamMaxCount.Location = new System.Drawing.Point(12, 337);
            this.labelParamMaxCount.Name = "labelParamMaxCount";
            this.labelParamMaxCount.Size = new System.Drawing.Size(58, 13);
            this.labelParamMaxCount.TabIndex = 14;
            this.labelParamMaxCount.Text = "MaxCount:";
            // 
            // labelParamDefCount
            // 
            this.labelParamDefCount.AutoSize = true;
            this.labelParamDefCount.Location = new System.Drawing.Point(12, 350);
            this.labelParamDefCount.Name = "labelParamDefCount";
            this.labelParamDefCount.Size = new System.Drawing.Size(55, 13);
            this.labelParamDefCount.TabIndex = 15;
            this.labelParamDefCount.Text = "DefCount:";
            // 
            // labelParamStep
            // 
            this.labelParamStep.AutoSize = true;
            this.labelParamStep.Location = new System.Drawing.Point(12, 370);
            this.labelParamStep.Name = "labelParamStep";
            this.labelParamStep.Size = new System.Drawing.Size(32, 13);
            this.labelParamStep.TabIndex = 16;
            this.labelParamStep.Text = "Step:";
            // 
            // labelParamDefValue
            // 
            this.labelParamDefValue.AutoSize = true;
            this.labelParamDefValue.Location = new System.Drawing.Point(12, 383);
            this.labelParamDefValue.Name = "labelParamDefValue";
            this.labelParamDefValue.Size = new System.Drawing.Size(54, 13);
            this.labelParamDefValue.TabIndex = 17;
            this.labelParamDefValue.Text = "DefValue:";
            // 
            // labelParamValue
            // 
            this.labelParamValue.AutoSize = true;
            this.labelParamValue.Location = new System.Drawing.Point(12, 396);
            this.labelParamValue.Name = "labelParamValue";
            this.labelParamValue.Size = new System.Drawing.Size(37, 13);
            this.labelParamValue.TabIndex = 17;
            this.labelParamValue.Text = "Value:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(727, 468);
            this.Controls.Add(this.labelParamValue);
            this.Controls.Add(this.labelParamDefValue);
            this.Controls.Add(this.labelParamStep);
            this.Controls.Add(this.labelParamDefCount);
            this.Controls.Add(this.labelParamMaxCount);
            this.Controls.Add(this.labelParamMax);
            this.Controls.Add(this.labelParamMin);
            this.Controls.Add(this.labelParamUints);
            this.Controls.Add(this.labelParamSize);
            this.Controls.Add(this.labelParamOffset);
            this.Controls.Add(this.labelParamIndex);
            this.Controls.Add(this.labelParamAccess);
            this.Controls.Add(this.labelParamType);
            this.Controls.Add(this.labelParamName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.paramsComboBox);
            this.Controls.Add(this.chart1);
            this.Controls.Add(this.listScanners);
            this.Controls.Add(this.buttonForSearch);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonForSearch;
        private System.Windows.Forms.ListView listScanners;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.ComboBox paramsComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelParamName;
        private System.Windows.Forms.Label labelParamType;
        private System.Windows.Forms.Label labelParamAccess;
        private System.Windows.Forms.Label labelParamIndex;
        private System.Windows.Forms.Label labelParamOffset;
        private System.Windows.Forms.Label labelParamSize;
        private System.Windows.Forms.Label labelParamUints;
        private System.Windows.Forms.Label labelParamMin;
        private System.Windows.Forms.Label labelParamMax;
        private System.Windows.Forms.Label labelParamMaxCount;
        private System.Windows.Forms.Label labelParamDefCount;
        private System.Windows.Forms.Label labelParamStep;
        private System.Windows.Forms.Label labelParamDefValue;
        private System.Windows.Forms.Label labelParamValue;
    }
}

