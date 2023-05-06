namespace PoloClubApp
{
    partial class PoloClubAppForm
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
            this.lbOverview = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnViewAllWearables = new System.Windows.Forms.Button();
            this.btnViewAllDevices = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tbPlayerNameForFile = new System.Windows.Forms.TextBox();
            this.btnGeneratePlayerTextReport = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnShowAssignedDevices = new System.Windows.Forms.Button();
            this.btnReturn = new System.Windows.Forms.Button();
            this.btnAssign = new System.Windows.Forms.Button();
            this.lblDevice = new System.Windows.Forms.Label();
            this.cbDevice = new System.Windows.Forms.ComboBox();
            this.lblPlayerName = new System.Windows.Forms.Label();
            this.tbPlayerName = new System.Windows.Forms.TextBox();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbOverview
            // 
            this.lbOverview.Dock = System.Windows.Forms.DockStyle.Top;
            this.lbOverview.FormattingEnabled = true;
            this.lbOverview.Location = new System.Drawing.Point(0, 0);
            this.lbOverview.Name = "lbOverview";
            this.lbOverview.Size = new System.Drawing.Size(598, 212);
            this.lbOverview.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Green;
            this.groupBox1.Controls.Add(this.btnViewAllWearables);
            this.groupBox1.Controls.Add(this.btnViewAllDevices);
            this.groupBox1.Location = new System.Drawing.Point(12, 229);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(247, 58);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Overview";
            // 
            // btnViewAllWearables
            // 
            this.btnViewAllWearables.Location = new System.Drawing.Point(124, 19);
            this.btnViewAllWearables.Name = "btnViewAllWearables";
            this.btnViewAllWearables.Size = new System.Drawing.Size(112, 23);
            this.btnViewAllWearables.TabIndex = 1;
            this.btnViewAllWearables.Text = "View All Wearables";
            this.btnViewAllWearables.UseVisualStyleBackColor = true;
            this.btnViewAllWearables.Click += new System.EventHandler(this.btnViewAllWearables_Click);
            // 
            // btnViewAllDevices
            // 
            this.btnViewAllDevices.BackColor = System.Drawing.SystemColors.Control;
            this.btnViewAllDevices.Location = new System.Drawing.Point(6, 19);
            this.btnViewAllDevices.Name = "btnViewAllDevices";
            this.btnViewAllDevices.Size = new System.Drawing.Size(112, 23);
            this.btnViewAllDevices.TabIndex = 0;
            this.btnViewAllDevices.Text = "View All Devices";
            this.btnViewAllDevices.UseVisualStyleBackColor = false;
            this.btnViewAllDevices.Click += new System.EventHandler(this.btnViewAllDevices_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Red;
            this.groupBox2.Controls.Add(this.tbPlayerNameForFile);
            this.groupBox2.Controls.Add(this.btnGeneratePlayerTextReport);
            this.groupBox2.Location = new System.Drawing.Point(12, 293);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(247, 65);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Report";
            // 
            // tbPlayerNameForFile
            // 
            this.tbPlayerNameForFile.Location = new System.Drawing.Point(141, 10);
            this.tbPlayerNameForFile.Name = "tbPlayerNameForFile";
            this.tbPlayerNameForFile.Size = new System.Drawing.Size(100, 20);
            this.tbPlayerNameForFile.TabIndex = 2;
            // 
            // btnGeneratePlayerTextReport
            // 
            this.btnGeneratePlayerTextReport.Location = new System.Drawing.Point(6, 36);
            this.btnGeneratePlayerTextReport.Name = "btnGeneratePlayerTextReport";
            this.btnGeneratePlayerTextReport.Size = new System.Drawing.Size(238, 23);
            this.btnGeneratePlayerTextReport.TabIndex = 0;
            this.btnGeneratePlayerTextReport.Text = "Generate report per player";
            this.btnGeneratePlayerTextReport.UseVisualStyleBackColor = true;
            this.btnGeneratePlayerTextReport.Click += new System.EventHandler(this.btnGeneratePlayerTextReport_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.DodgerBlue;
            this.groupBox3.Controls.Add(this.btnShowAssignedDevices);
            this.groupBox3.Controls.Add(this.btnReturn);
            this.groupBox3.Controls.Add(this.btnAssign);
            this.groupBox3.Controls.Add(this.lblDevice);
            this.groupBox3.Controls.Add(this.cbDevice);
            this.groupBox3.Controls.Add(this.lblPlayerName);
            this.groupBox3.Controls.Add(this.tbPlayerName);
            this.groupBox3.Location = new System.Drawing.Point(275, 229);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(313, 129);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Assign / Return";
            // 
            // btnShowAssignedDevices
            // 
            this.btnShowAssignedDevices.Location = new System.Drawing.Point(6, 93);
            this.btnShowAssignedDevices.Name = "btnShowAssignedDevices";
            this.btnShowAssignedDevices.Size = new System.Drawing.Size(133, 23);
            this.btnShowAssignedDevices.TabIndex = 6;
            this.btnShowAssignedDevices.Text = "Show Assigned Devices";
            this.btnShowAssignedDevices.UseVisualStyleBackColor = true;
            this.btnShowAssignedDevices.Click += new System.EventHandler(this.btnShowAssignedDevices_Click);
            // 
            // btnReturn
            // 
            this.btnReturn.Location = new System.Drawing.Point(172, 64);
            this.btnReturn.Name = "btnReturn";
            this.btnReturn.Size = new System.Drawing.Size(132, 23);
            this.btnReturn.TabIndex = 5;
            this.btnReturn.Text = "Return Device";
            this.btnReturn.UseVisualStyleBackColor = true;
            this.btnReturn.Click += new System.EventHandler(this.btnReturn_Click);
            // 
            // btnAssign
            // 
            this.btnAssign.Location = new System.Drawing.Point(6, 64);
            this.btnAssign.Name = "btnAssign";
            this.btnAssign.Size = new System.Drawing.Size(132, 23);
            this.btnAssign.TabIndex = 4;
            this.btnAssign.Text = "Assign Device";
            this.btnAssign.UseVisualStyleBackColor = true;
            this.btnAssign.Click += new System.EventHandler(this.btnAssign_Click);
            // 
            // lblDevice
            // 
            this.lblDevice.AutoSize = true;
            this.lblDevice.Location = new System.Drawing.Point(169, 22);
            this.lblDevice.Name = "lblDevice";
            this.lblDevice.Size = new System.Drawing.Size(53, 13);
            this.lblDevice.TabIndex = 3;
            this.lblDevice.Text = "Device Id";
            // 
            // cbDevice
            // 
            this.cbDevice.FormattingEnabled = true;
            this.cbDevice.Location = new System.Drawing.Point(172, 37);
            this.cbDevice.Name = "cbDevice";
            this.cbDevice.Size = new System.Drawing.Size(132, 21);
            this.cbDevice.TabIndex = 1;
            // 
            // lblPlayerName
            // 
            this.lblPlayerName.AutoSize = true;
            this.lblPlayerName.Location = new System.Drawing.Point(6, 22);
            this.lblPlayerName.Name = "lblPlayerName";
            this.lblPlayerName.Size = new System.Drawing.Size(67, 13);
            this.lblPlayerName.TabIndex = 1;
            this.lblPlayerName.Text = "Player Name";
            // 
            // tbPlayerName
            // 
            this.tbPlayerName.Location = new System.Drawing.Point(6, 38);
            this.tbPlayerName.Name = "tbPlayerName";
            this.tbPlayerName.Size = new System.Drawing.Size(132, 20);
            this.tbPlayerName.TabIndex = 0;
            // 
            // PoloClubAppForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(598, 377);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.lbOverview);
            this.Name = "PoloClubAppForm";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox lbOverview;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnViewAllDevices;
        private System.Windows.Forms.Button btnViewAllWearables;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnGeneratePlayerTextReport;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label lblPlayerName;
        private System.Windows.Forms.TextBox tbPlayerName;
        private System.Windows.Forms.Label lblDevice;
        private System.Windows.Forms.ComboBox cbDevice;
        private System.Windows.Forms.Button btnShowAssignedDevices;
        private System.Windows.Forms.Button btnReturn;
        private System.Windows.Forms.Button btnAssign;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.TextBox tbPlayerNameForFile;
    }
}

