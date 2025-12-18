
namespace project_climate_control_app
{
    partial class Form1
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
            this.pnMenu = new System.Windows.Forms.Panel();
            this.btnGraph = new System.Windows.Forms.Button();
            this.btnDatabase = new System.Windows.Forms.Button();
            this.btnWeather = new System.Windows.Forms.Button();
            this.btnRooms = new System.Windows.Forms.Button();
            this.btnHome = new System.Windows.Forms.Button();
            this.pnLogo = new System.Windows.Forms.Panel();
            this.pbLogo = new System.Windows.Forms.PictureBox();
            this.pnTitle = new System.Windows.Forms.Panel();
            this.btnMaximize = new System.Windows.Forms.Button();
            this.btnMinimize = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnBackToHome = new System.Windows.Forms.Button();
            this.lblTitle = new System.Windows.Forms.Label();
            this.pnDesktop = new System.Windows.Forms.Panel();
            this.pnMenu.SuspendLayout();
            this.pnLogo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbLogo)).BeginInit();
            this.pnTitle.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnMenu
            // 
            this.pnMenu.BackColor = System.Drawing.Color.White;
            this.pnMenu.Controls.Add(this.btnGraph);
            this.pnMenu.Controls.Add(this.btnDatabase);
            this.pnMenu.Controls.Add(this.btnWeather);
            this.pnMenu.Controls.Add(this.btnRooms);
            this.pnMenu.Controls.Add(this.btnHome);
            this.pnMenu.Controls.Add(this.pnLogo);
            this.pnMenu.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnMenu.Location = new System.Drawing.Point(0, 0);
            this.pnMenu.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnMenu.Name = "pnMenu";
            this.pnMenu.Size = new System.Drawing.Size(220, 583);
            this.pnMenu.TabIndex = 0;
            // 
            // btnGraph
            // 
            this.btnGraph.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnGraph.FlatAppearance.BorderSize = 0;
            this.btnGraph.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnGraph.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnGraph.Image = global::project_climate_control_app.Properties.Resources.bar_graph_icon_;
            this.btnGraph.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnGraph.Location = new System.Drawing.Point(0, 416);
            this.btnGraph.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnGraph.Name = "btnGraph";
            this.btnGraph.Padding = new System.Windows.Forms.Padding(12, 0, 0, 0);
            this.btnGraph.Size = new System.Drawing.Size(220, 60);
            this.btnGraph.TabIndex = 5;
            this.btnGraph.Text = "       Graph";
            this.btnGraph.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnGraph.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnGraph.UseVisualStyleBackColor = true;
            this.btnGraph.Visible = false;
            // 
            // btnDatabase
            // 
            this.btnDatabase.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnDatabase.FlatAppearance.BorderSize = 0;
            this.btnDatabase.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDatabase.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDatabase.Image = global::project_climate_control_app.Properties.Resources.folder_icon_;
            this.btnDatabase.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnDatabase.Location = new System.Drawing.Point(0, 356);
            this.btnDatabase.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnDatabase.Name = "btnDatabase";
            this.btnDatabase.Padding = new System.Windows.Forms.Padding(12, 0, 0, 0);
            this.btnDatabase.Size = new System.Drawing.Size(220, 60);
            this.btnDatabase.TabIndex = 4;
            this.btnDatabase.Text = "       Database";
            this.btnDatabase.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnDatabase.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnDatabase.UseVisualStyleBackColor = true;
            this.btnDatabase.Click += new System.EventHandler(this.btnDatabase_Click);
            // 
            // btnWeather
            // 
            this.btnWeather.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnWeather.FlatAppearance.BorderSize = 0;
            this.btnWeather.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnWeather.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnWeather.Image = global::project_climate_control_app.Properties.Resources.caution_sign_icon_;
            this.btnWeather.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnWeather.Location = new System.Drawing.Point(0, 296);
            this.btnWeather.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnWeather.Name = "btnWeather";
            this.btnWeather.Padding = new System.Windows.Forms.Padding(12, 0, 0, 0);
            this.btnWeather.Size = new System.Drawing.Size(220, 60);
            this.btnWeather.TabIndex = 3;
            this.btnWeather.Text = "       Weather";
            this.btnWeather.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnWeather.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnWeather.UseVisualStyleBackColor = true;
            this.btnWeather.Click += new System.EventHandler(this.btnWeather_Click);
            // 
            // btnRooms
            // 
            this.btnRooms.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnRooms.FlatAppearance.BorderSize = 0;
            this.btnRooms.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRooms.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRooms.Image = global::project_climate_control_app.Properties.Resources.sensor_icon_;
            this.btnRooms.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRooms.Location = new System.Drawing.Point(0, 236);
            this.btnRooms.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnRooms.Name = "btnRooms";
            this.btnRooms.Padding = new System.Windows.Forms.Padding(12, 0, 0, 0);
            this.btnRooms.Size = new System.Drawing.Size(220, 60);
            this.btnRooms.TabIndex = 2;
            this.btnRooms.Text = "       Rooms";
            this.btnRooms.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnRooms.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnRooms.UseVisualStyleBackColor = true;
            this.btnRooms.Click += new System.EventHandler(this.btnRooms_Click);
            // 
            // btnHome
            // 
            this.btnHome.BackColor = System.Drawing.Color.White;
            this.btnHome.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnHome.FlatAppearance.BorderSize = 0;
            this.btnHome.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnHome.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnHome.Image = global::project_climate_control_app.Properties.Resources.home_icon_;
            this.btnHome.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnHome.Location = new System.Drawing.Point(0, 176);
            this.btnHome.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnHome.Name = "btnHome";
            this.btnHome.Padding = new System.Windows.Forms.Padding(12, 0, 0, 0);
            this.btnHome.Size = new System.Drawing.Size(220, 60);
            this.btnHome.TabIndex = 1;
            this.btnHome.Text = "       Home";
            this.btnHome.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnHome.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnHome.UseVisualStyleBackColor = false;
            this.btnHome.Click += new System.EventHandler(this.btnHome_Click);
            // 
            // pnLogo
            // 
            this.pnLogo.Controls.Add(this.pbLogo);
            this.pnLogo.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnLogo.Location = new System.Drawing.Point(0, 0);
            this.pnLogo.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnLogo.Name = "pnLogo";
            this.pnLogo.Size = new System.Drawing.Size(220, 176);
            this.pnLogo.TabIndex = 0;
            // 
            // pbLogo
            // 
            this.pbLogo.Image = global::project_climate_control_app.Properties.Resources.AiriosLogoIcon;
            this.pbLogo.Location = new System.Drawing.Point(57, 11);
            this.pbLogo.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pbLogo.Name = "pbLogo";
            this.pbLogo.Size = new System.Drawing.Size(92, 89);
            this.pbLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbLogo.TabIndex = 0;
            this.pbLogo.TabStop = false;
            // 
            // pnTitle
            // 
            this.pnTitle.BackColor = System.Drawing.Color.White;
            this.pnTitle.Controls.Add(this.btnMaximize);
            this.pnTitle.Controls.Add(this.btnMinimize);
            this.pnTitle.Controls.Add(this.btnClose);
            this.pnTitle.Controls.Add(this.btnBackToHome);
            this.pnTitle.Controls.Add(this.lblTitle);
            this.pnTitle.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnTitle.Location = new System.Drawing.Point(220, 0);
            this.pnTitle.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnTitle.Name = "pnTitle";
            this.pnTitle.Size = new System.Drawing.Size(907, 100);
            this.pnTitle.TabIndex = 1;
            this.pnTitle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnTitle_MouseDown);
            // 
            // btnMaximize
            // 
            this.btnMaximize.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnMaximize.FlatAppearance.BorderSize = 0;
            this.btnMaximize.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMaximize.Location = new System.Drawing.Point(852, 2);
            this.btnMaximize.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnMaximize.Name = "btnMaximize";
            this.btnMaximize.Size = new System.Drawing.Size(23, 23);
            this.btnMaximize.TabIndex = 5;
            this.btnMaximize.Text = "O";
            this.btnMaximize.UseVisualStyleBackColor = true;
            this.btnMaximize.Click += new System.EventHandler(this.btnMaximize_Click);
            // 
            // btnMinimize
            // 
            this.btnMinimize.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnMinimize.FlatAppearance.BorderSize = 0;
            this.btnMinimize.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMinimize.Location = new System.Drawing.Point(823, 2);
            this.btnMinimize.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnMinimize.Name = "btnMinimize";
            this.btnMinimize.Size = new System.Drawing.Size(23, 23);
            this.btnMinimize.TabIndex = 4;
            this.btnMinimize.Text = "—";
            this.btnMinimize.UseVisualStyleBackColor = true;
            this.btnMinimize.Click += new System.EventHandler(this.btnMinimize_Click);
            // 
            // btnClose
            // 
            this.btnClose.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnClose.FlatAppearance.BorderSize = 0;
            this.btnClose.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnClose.Location = new System.Drawing.Point(880, 2);
            this.btnClose.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(23, 23);
            this.btnClose.TabIndex = 3;
            this.btnClose.Text = "X";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnBackToHome
            // 
            this.btnBackToHome.BackColor = System.Drawing.Color.Transparent;
            this.btnBackToHome.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnBackToHome.FlatAppearance.BorderSize = 0;
            this.btnBackToHome.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnBackToHome.Image = global::project_climate_control_app.Properties.Resources.double_chevron_icon_;
            this.btnBackToHome.Location = new System.Drawing.Point(0, 0);
            this.btnBackToHome.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnBackToHome.Name = "btnBackToHome";
            this.btnBackToHome.Size = new System.Drawing.Size(108, 100);
            this.btnBackToHome.TabIndex = 2;
            this.btnBackToHome.UseVisualStyleBackColor = false;
            this.btnBackToHome.Click += new System.EventHandler(this.btnBackToHome_Click);
            // 
            // lblTitle
            // 
            this.lblTitle.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblTitle.AutoSize = true;
            this.lblTitle.Font = new System.Drawing.Font("Roboto Black", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTitle.ForeColor = System.Drawing.Color.Black;
            this.lblTitle.Location = new System.Drawing.Point(395, 36);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(63, 24);
            this.lblTitle.TabIndex = 1;
            this.lblTitle.Text = "Home";
            this.lblTitle.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pnDesktop
            // 
            this.pnDesktop.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnDesktop.Location = new System.Drawing.Point(220, 100);
            this.pnDesktop.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnDesktop.MinimumSize = new System.Drawing.Size(907, 484);
            this.pnDesktop.Name = "pnDesktop";
            this.pnDesktop.Size = new System.Drawing.Size(907, 484);
            this.pnDesktop.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1127, 583);
            this.Controls.Add(this.pnDesktop);
            this.Controls.Add(this.pnTitle);
            this.Controls.Add(this.pnMenu);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MinimumSize = new System.Drawing.Size(1141, 619);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.pnMenu.ResumeLayout(false);
            this.pnLogo.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pbLogo)).EndInit();
            this.pnTitle.ResumeLayout(false);
            this.pnTitle.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnMenu;
        private System.Windows.Forms.Button btnGraph;
        private System.Windows.Forms.Button btnDatabase;
        private System.Windows.Forms.Button btnWeather;
        private System.Windows.Forms.Button btnRooms;
        private System.Windows.Forms.Button btnHome;
        private System.Windows.Forms.Panel pnLogo;
        private System.Windows.Forms.Panel pnTitle;
        private System.Windows.Forms.Panel pnDesktop;
        private System.Windows.Forms.Label lblTitle;
        private System.Windows.Forms.Button btnBackToHome;
        private System.Windows.Forms.Button btnMaximize;
        private System.Windows.Forms.Button btnMinimize;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.PictureBox pbLogo;
    }
}

