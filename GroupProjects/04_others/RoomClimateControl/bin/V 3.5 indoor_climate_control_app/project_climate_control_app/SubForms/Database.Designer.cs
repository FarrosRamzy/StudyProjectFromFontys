
namespace project_climate_control_app.SubForms
{
    partial class Database
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dtCloudData = new System.Windows.Forms.DataGridView();
            this.gbControlPanel = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.btnDownload = new System.Windows.Forms.Button();
            this.btnGenerate = new System.Windows.Forms.Button();
            this.dtpStartTime = new System.Windows.Forms.DateTimePicker();
            this.dtpEndTime = new System.Windows.Forms.DateTimePicker();
            this.dtpEndDate = new System.Windows.Forms.DateTimePicker();
            this.dtpStartDate = new System.Windows.Forms.DateTimePicker();
            this.btnShowPanel = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dtCloudData)).BeginInit();
            this.gbControlPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // dtCloudData
            // 
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.White;
            this.dtCloudData.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle2;
            this.dtCloudData.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dtCloudData.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.DisplayedCells;
            this.dtCloudData.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dtCloudData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dtCloudData.GridColor = System.Drawing.SystemColors.Control;
            this.dtCloudData.Location = new System.Drawing.Point(0, 0);
            this.dtCloudData.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dtCloudData.Name = "dtCloudData";
            this.dtCloudData.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.AutoSizeToDisplayedHeaders;
            this.dtCloudData.Size = new System.Drawing.Size(885, 288);
            this.dtCloudData.TabIndex = 0;
            // 
            // gbControlPanel
            // 
            this.gbControlPanel.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.gbControlPanel.Controls.Add(this.label3);
            this.gbControlPanel.Controls.Add(this.label2);
            this.gbControlPanel.Controls.Add(this.label1);
            this.gbControlPanel.Controls.Add(this.label9);
            this.gbControlPanel.Controls.Add(this.btnDownload);
            this.gbControlPanel.Controls.Add(this.btnGenerate);
            this.gbControlPanel.Controls.Add(this.dtpStartTime);
            this.gbControlPanel.Controls.Add(this.dtpEndTime);
            this.gbControlPanel.Controls.Add(this.dtpEndDate);
            this.gbControlPanel.Controls.Add(this.dtpStartDate);
            this.gbControlPanel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.gbControlPanel.Location = new System.Drawing.Point(344, 288);
            this.gbControlPanel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbControlPanel.Name = "gbControlPanel";
            this.gbControlPanel.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbControlPanel.Size = new System.Drawing.Size(541, 220);
            this.gbControlPanel.TabIndex = 2;
            this.gbControlPanel.TabStop = false;
            this.gbControlPanel.Text = "Data Control Panel";
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label3.Font = new System.Drawing.Font("Roboto Slab", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(20, 142);
            this.label3.Margin = new System.Windows.Forms.Padding(0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(113, 25);
            this.label3.TabIndex = 72;
            this.label3.Text = "End Time";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label2.Font = new System.Drawing.Font("Roboto Slab", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(21, 110);
            this.label2.Margin = new System.Windows.Forms.Padding(0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(113, 25);
            this.label2.TabIndex = 71;
            this.label2.Text = "Start Time";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label1.Font = new System.Drawing.Font("Roboto Slab", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(21, 55);
            this.label1.Margin = new System.Windows.Forms.Padding(0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(113, 25);
            this.label1.TabIndex = 70;
            this.label1.Text = "End Date";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label9
            // 
            this.label9.BackColor = System.Drawing.Color.Transparent;
            this.label9.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label9.Font = new System.Drawing.Font("Roboto Slab", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(20, 23);
            this.label9.Margin = new System.Windows.Forms.Padding(0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(113, 25);
            this.label9.TabIndex = 69;
            this.label9.Text = "Start Date";
            this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // btnDownload
            // 
            this.btnDownload.FlatAppearance.BorderSize = 2;
            this.btnDownload.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDownload.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDownload.Location = new System.Drawing.Point(412, 110);
            this.btnDownload.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(115, 57);
            this.btnDownload.TabIndex = 25;
            this.btnDownload.Text = "Download";
            this.btnDownload.UseVisualStyleBackColor = true;
            this.btnDownload.Click += new System.EventHandler(this.btnDownload_Click);
            // 
            // btnGenerate
            // 
            this.btnGenerate.FlatAppearance.BorderSize = 2;
            this.btnGenerate.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnGenerate.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnGenerate.Location = new System.Drawing.Point(289, 110);
            this.btnGenerate.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnGenerate.Name = "btnGenerate";
            this.btnGenerate.Size = new System.Drawing.Size(115, 57);
            this.btnGenerate.TabIndex = 24;
            this.btnGenerate.Text = "Generate";
            this.btnGenerate.UseVisualStyleBackColor = true;
            this.btnGenerate.Click += new System.EventHandler(this.btnGenerate_Click);
            // 
            // dtpStartTime
            // 
            this.dtpStartTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.dtpStartTime.Location = new System.Drawing.Point(139, 110);
            this.dtpStartTime.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dtpStartTime.Name = "dtpStartTime";
            this.dtpStartTime.ShowUpDown = true;
            this.dtpStartTime.Size = new System.Drawing.Size(124, 22);
            this.dtpStartTime.TabIndex = 3;
            // 
            // dtpEndTime
            // 
            this.dtpEndTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.dtpEndTime.Location = new System.Drawing.Point(139, 142);
            this.dtpEndTime.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dtpEndTime.Name = "dtpEndTime";
            this.dtpEndTime.ShowUpDown = true;
            this.dtpEndTime.Size = new System.Drawing.Size(124, 22);
            this.dtpEndTime.TabIndex = 2;
            // 
            // dtpEndDate
            // 
            this.dtpEndDate.Location = new System.Drawing.Point(139, 55);
            this.dtpEndDate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dtpEndDate.Name = "dtpEndDate";
            this.dtpEndDate.Size = new System.Drawing.Size(264, 22);
            this.dtpEndDate.TabIndex = 1;
            // 
            // dtpStartDate
            // 
            this.dtpStartDate.Location = new System.Drawing.Point(137, 23);
            this.dtpStartDate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dtpStartDate.Name = "dtpStartDate";
            this.dtpStartDate.Size = new System.Drawing.Size(265, 22);
            this.dtpStartDate.TabIndex = 0;
            this.dtpStartDate.ValueChanged += new System.EventHandler(this.dtpStartDate_ValueChanged);
            // 
            // btnShowPanel
            // 
            this.btnShowPanel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnShowPanel.FlatAppearance.BorderSize = 2;
            this.btnShowPanel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnShowPanel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnShowPanel.Location = new System.Drawing.Point(93, 373);
            this.btnShowPanel.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnShowPanel.Name = "btnShowPanel";
            this.btnShowPanel.Size = new System.Drawing.Size(147, 49);
            this.btnShowPanel.TabIndex = 23;
            this.btnShowPanel.Text = "Open Control";
            this.btnShowPanel.UseVisualStyleBackColor = true;
            this.btnShowPanel.Click += new System.EventHandler(this.btnShowPanel_Click);
            // 
            // Database
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(885, 508);
            this.Controls.Add(this.btnShowPanel);
            this.Controls.Add(this.gbControlPanel);
            this.Controls.Add(this.dtCloudData);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MinimumSize = new System.Drawing.Size(901, 473);
            this.Name = "Database";
            this.Text = "Database";
            this.Load += new System.EventHandler(this.Database_Load);
            this.VisibleChanged += new System.EventHandler(this.Database_VisibleChanged);
            ((System.ComponentModel.ISupportInitialize)(this.dtCloudData)).EndInit();
            this.gbControlPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dtCloudData;
        private System.Windows.Forms.GroupBox gbControlPanel;
        private System.Windows.Forms.Button btnShowPanel;
        private System.Windows.Forms.DateTimePicker dtpStartDate;
        private System.Windows.Forms.DateTimePicker dtpEndDate;
        private System.Windows.Forms.DateTimePicker dtpStartTime;
        private System.Windows.Forms.DateTimePicker dtpEndTime;
        private System.Windows.Forms.Button btnDownload;
        private System.Windows.Forms.Button btnGenerate;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
    }
}