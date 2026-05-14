
namespace project_climate_control_app.SubForms
{
    partial class Home
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
            this.components = new System.ComponentModel.Container();
            this.lblTime = new System.Windows.Forms.Label();
            this.lblDate = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lblTemp = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lblHumid = new System.Windows.Forms.Label();
            this.lblCloud = new System.Windows.Forms.Label();
            this.load_timer = new System.Windows.Forms.Timer(this.components);
            this.lblCityName = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pbCloud = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbCloud)).BeginInit();
            this.SuspendLayout();
            // 
            // lblTime
            // 
            this.lblTime.AutoSize = true;
            this.lblTime.Font = new System.Drawing.Font("Roboto Slab", 33F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTime.Location = new System.Drawing.Point(22, 23);
            this.lblTime.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(216, 59);
            this.lblTime.TabIndex = 0;
            this.lblTime.Text = "00:00 PM";
            this.lblTime.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblDate
            // 
            this.lblDate.Font = new System.Drawing.Font("Roboto Slab", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblDate.Location = new System.Drawing.Point(22, 75);
            this.lblDate.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblDate.Name = "lblDate";
            this.lblDate.Size = new System.Drawing.Size(202, 21);
            this.lblDate.TabIndex = 1;
            this.lblDate.Text = "Sunday, December 07, 2021";
            this.lblDate.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label1.Font = new System.Drawing.Font("Roboto Slab", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(513, 88);
            this.label1.Margin = new System.Windows.Forms.Padding(0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 30);
            this.label1.TabIndex = 8;
            this.label1.Text = "℃";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblTemp
            // 
            this.lblTemp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lblTemp.BackColor = System.Drawing.Color.Transparent;
            this.lblTemp.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblTemp.Font = new System.Drawing.Font("Roboto Slab", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTemp.Location = new System.Drawing.Point(442, 98);
            this.lblTemp.Margin = new System.Windows.Forms.Padding(0);
            this.lblTemp.Name = "lblTemp";
            this.lblTemp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblTemp.Size = new System.Drawing.Size(80, 40);
            this.lblTemp.TabIndex = 9;
            this.lblTemp.Text = "0.00";
            this.lblTemp.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label2.Font = new System.Drawing.Font("Roboto Slab", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(613, 88);
            this.label2.Margin = new System.Windows.Forms.Padding(0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(31, 30);
            this.label2.TabIndex = 10;
            this.label2.Text = "%";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblHumid
            // 
            this.lblHumid.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lblHumid.BackColor = System.Drawing.Color.Transparent;
            this.lblHumid.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblHumid.Font = new System.Drawing.Font("Roboto Slab", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblHumid.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblHumid.Location = new System.Drawing.Point(541, 98);
            this.lblHumid.Margin = new System.Windows.Forms.Padding(0);
            this.lblHumid.Name = "lblHumid";
            this.lblHumid.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblHumid.Size = new System.Drawing.Size(80, 40);
            this.lblHumid.TabIndex = 11;
            this.lblHumid.Text = "0.00";
            this.lblHumid.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblCloud
            // 
            this.lblCloud.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lblCloud.BackColor = System.Drawing.Color.Transparent;
            this.lblCloud.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblCloud.Font = new System.Drawing.Font("Roboto Slab", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCloud.Location = new System.Drawing.Point(446, 57);
            this.lblCloud.Margin = new System.Windows.Forms.Padding(0);
            this.lblCloud.Name = "lblCloud";
            this.lblCloud.Size = new System.Drawing.Size(196, 30);
            this.lblCloud.TabIndex = 13;
            this.lblCloud.Text = "Clear";
            this.lblCloud.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // load_timer
            // 
            this.load_timer.Interval = 1000;
            this.load_timer.Tick += new System.EventHandler(this.load_timer_Tick);
            // 
            // lblCityName
            // 
            this.lblCityName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lblCityName.BackColor = System.Drawing.Color.Transparent;
            this.lblCityName.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblCityName.Font = new System.Drawing.Font("Roboto Slab", 22.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCityName.Location = new System.Drawing.Point(361, 12);
            this.lblCityName.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblCityName.Name = "lblCityName";
            this.lblCityName.Size = new System.Drawing.Size(202, 40);
            this.lblCityName.TabIndex = 14;
            this.lblCityName.Text = "cityName";
            this.lblCityName.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.pictureBox1.Image = global::project_climate_control_app.Properties.Resources.AiriosLogo_resized;
            this.pictureBox1.Location = new System.Drawing.Point(345, 169);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(297, 173);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 15;
            this.pictureBox1.TabStop = false;
            // 
            // pbCloud
            // 
            this.pbCloud.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.pbCloud.BackColor = System.Drawing.SystemColors.Control;
            this.pbCloud.Location = new System.Drawing.Point(359, 57);
            this.pbCloud.Margin = new System.Windows.Forms.Padding(2);
            this.pbCloud.Name = "pbCloud";
            this.pbCloud.Size = new System.Drawing.Size(81, 81);
            this.pbCloud.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbCloud.TabIndex = 2;
            this.pbCloud.TabStop = false;
            // 
            // Home
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(664, 354);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.lblCityName);
            this.Controls.Add(this.lblCloud);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lblHumid);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblTemp);
            this.Controls.Add(this.pbCloud);
            this.Controls.Add(this.lblDate);
            this.Controls.Add(this.lblTime);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MinimumSize = new System.Drawing.Size(680, 393);
            this.Name = "Home";
            this.Text = "Home";
            this.Load += new System.EventHandler(this.Home_Load);
            this.VisibleChanged += new System.EventHandler(this.Home_VisibleChanged);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pbCloud)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.Label lblDate;
        private System.Windows.Forms.PictureBox pbCloud;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblTemp;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblHumid;
        private System.Windows.Forms.Label lblCloud;
        private System.Windows.Forms.Timer load_timer;
        private System.Windows.Forms.Label lblCityName;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}