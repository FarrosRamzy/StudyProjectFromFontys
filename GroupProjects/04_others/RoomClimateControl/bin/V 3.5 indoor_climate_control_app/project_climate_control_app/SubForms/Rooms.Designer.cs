
namespace project_climate_control_app.SubForms
{
    partial class Rooms
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
            this.cbSelectRoom = new System.Windows.Forms.ComboBox();
            this.btnChangeRoomName = new System.Windows.Forms.Button();
            this.tbRoomName = new System.Windows.Forms.TextBox();
            this.lblFanSpeed = new System.Windows.Forms.Label();
            this.trbFanManual = new System.Windows.Forms.TrackBar();
            this.label9 = new System.Windows.Forms.Label();
            this.lblSetTemp = new System.Windows.Forms.Label();
            this.btnDecreaseTemp = new System.Windows.Forms.Button();
            this.btnIncreaseTemp = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.lblTVOCval = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lblCO2val = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblHumidVal = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lblTempVal = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.room_timer = new System.Windows.Forms.Timer(this.components);
            this.lblAuto = new System.Windows.Forms.Label();
            this.lblManual = new System.Windows.Forms.Label();
            this.data_timer = new System.Windows.Forms.Timer(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.lblCoVal = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.trbFanManual)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // cbSelectRoom
            // 
            this.cbSelectRoom.CausesValidation = false;
            this.cbSelectRoom.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbSelectRoom.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cbSelectRoom.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbSelectRoom.FormattingEnabled = true;
            this.cbSelectRoom.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.cbSelectRoom.Items.AddRange(new object[] {
            "Base Room",
            "Livingroom",
            "Kitchen",
            "Diningroom",
            "Bathroom",
            "Bedroom",
            "ef:cb:34:dd:44:55"});
            this.cbSelectRoom.Location = new System.Drawing.Point(12, 7);
            this.cbSelectRoom.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.cbSelectRoom.Name = "cbSelectRoom";
            this.cbSelectRoom.Size = new System.Drawing.Size(319, 46);
            this.cbSelectRoom.TabIndex = 0;
            this.cbSelectRoom.SelectedIndexChanged += new System.EventHandler(this.cbSelectRoom_SelectedIndexChanged);
            // 
            // btnChangeRoomName
            // 
            this.btnChangeRoomName.FlatAppearance.BorderSize = 2;
            this.btnChangeRoomName.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnChangeRoomName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnChangeRoomName.Location = new System.Drawing.Point(345, 7);
            this.btnChangeRoomName.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnChangeRoomName.Name = "btnChangeRoomName";
            this.btnChangeRoomName.Size = new System.Drawing.Size(103, 49);
            this.btnChangeRoomName.TabIndex = 22;
            this.btnChangeRoomName.Text = "Rename";
            this.btnChangeRoomName.UseVisualStyleBackColor = true;
            this.btnChangeRoomName.Click += new System.EventHandler(this.btnChangeRoomName_Click);
            // 
            // tbRoomName
            // 
            this.tbRoomName.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.tbRoomName.Font = new System.Drawing.Font("Microsoft Sans Serif", 22.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbRoomName.Location = new System.Drawing.Point(489, 7);
            this.tbRoomName.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tbRoomName.Name = "tbRoomName";
            this.tbRoomName.Size = new System.Drawing.Size(368, 42);
            this.tbRoomName.TabIndex = 21;
            // 
            // lblFanSpeed
            // 
            this.lblFanSpeed.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblFanSpeed.BackColor = System.Drawing.Color.Transparent;
            this.lblFanSpeed.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblFanSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 33F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblFanSpeed.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblFanSpeed.Location = new System.Drawing.Point(68, 252);
            this.lblFanSpeed.Margin = new System.Windows.Forms.Padding(0);
            this.lblFanSpeed.Name = "lblFanSpeed";
            this.lblFanSpeed.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblFanSpeed.Size = new System.Drawing.Size(216, 75);
            this.lblFanSpeed.TabIndex = 25;
            this.lblFanSpeed.Text = "0 %";
            this.lblFanSpeed.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // trbFanManual
            // 
            this.trbFanManual.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.trbFanManual.AutoSize = false;
            this.trbFanManual.CausesValidation = false;
            this.trbFanManual.LargeChange = 25;
            this.trbFanManual.Location = new System.Drawing.Point(17, 342);
            this.trbFanManual.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trbFanManual.Maximum = 100;
            this.trbFanManual.Name = "trbFanManual";
            this.trbFanManual.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.trbFanManual.Size = new System.Drawing.Size(289, 57);
            this.trbFanManual.SmallChange = 25;
            this.trbFanManual.TabIndex = 25;
            this.trbFanManual.TickFrequency = 25;
            this.trbFanManual.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.trbFanManual.Scroll += new System.EventHandler(this.trbFanManual_Scroll);
            // 
            // label9
            // 
            this.label9.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label9.BackColor = System.Drawing.Color.Transparent;
            this.label9.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(628, 111);
            this.label9.Margin = new System.Windows.Forms.Padding(0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(245, 37);
            this.label9.TabIndex = 68;
            this.label9.Text = "Set Temperature";
            this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lblSetTemp
            // 
            this.lblSetTemp.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblSetTemp.BackColor = System.Drawing.Color.Transparent;
            this.lblSetTemp.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblSetTemp.Font = new System.Drawing.Font("Microsoft Sans Serif", 33F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblSetTemp.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblSetTemp.Location = new System.Drawing.Point(609, 153);
            this.lblSetTemp.Margin = new System.Windows.Forms.Padding(0);
            this.lblSetTemp.Name = "lblSetTemp";
            this.lblSetTemp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblSetTemp.Size = new System.Drawing.Size(188, 75);
            this.lblSetTemp.TabIndex = 53;
            this.lblSetTemp.Text = "16";
            this.lblSetTemp.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // btnDecreaseTemp
            // 
            this.btnDecreaseTemp.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnDecreaseTemp.FlatAppearance.BorderSize = 2;
            this.btnDecreaseTemp.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDecreaseTemp.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDecreaseTemp.Location = new System.Drawing.Point(815, 188);
            this.btnDecreaseTemp.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnDecreaseTemp.Name = "btnDecreaseTemp";
            this.btnDecreaseTemp.Size = new System.Drawing.Size(59, 31);
            this.btnDecreaseTemp.TabIndex = 67;
            this.btnDecreaseTemp.Text = "-";
            this.btnDecreaseTemp.UseVisualStyleBackColor = true;
            this.btnDecreaseTemp.Click += new System.EventHandler(this.btnDecreaseTemp_Click);
            // 
            // btnIncreaseTemp
            // 
            this.btnIncreaseTemp.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnIncreaseTemp.FlatAppearance.BorderSize = 2;
            this.btnIncreaseTemp.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnIncreaseTemp.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnIncreaseTemp.Location = new System.Drawing.Point(815, 156);
            this.btnIncreaseTemp.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnIncreaseTemp.Name = "btnIncreaseTemp";
            this.btnIncreaseTemp.Size = new System.Drawing.Size(59, 31);
            this.btnIncreaseTemp.TabIndex = 54;
            this.btnIncreaseTemp.Text = "+";
            this.btnIncreaseTemp.UseVisualStyleBackColor = true;
            this.btnIncreaseTemp.Click += new System.EventHandler(this.btnIncreaseTemp_Click);
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(500, 247);
            this.label2.Margin = new System.Windows.Forms.Padding(0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(81, 37);
            this.label2.TabIndex = 61;
            this.label2.Text = "ppm";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblTVOCval
            // 
            this.lblTVOCval.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblTVOCval.BackColor = System.Drawing.Color.Transparent;
            this.lblTVOCval.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblTVOCval.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTVOCval.Location = new System.Drawing.Point(383, 241);
            this.lblTVOCval.Margin = new System.Windows.Forms.Padding(0);
            this.lblTVOCval.Name = "lblTVOCval";
            this.lblTVOCval.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblTVOCval.Size = new System.Drawing.Size(117, 49);
            this.lblTVOCval.TabIndex = 62;
            this.lblTVOCval.Text = "0.00";
            this.lblTVOCval.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(500, 201);
            this.label4.Margin = new System.Windows.Forms.Padding(0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(81, 37);
            this.label4.TabIndex = 59;
            this.label4.Text = "ppm";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblCO2val
            // 
            this.lblCO2val.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblCO2val.BackColor = System.Drawing.Color.Transparent;
            this.lblCO2val.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblCO2val.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCO2val.Location = new System.Drawing.Point(383, 201);
            this.lblCO2val.Margin = new System.Windows.Forms.Padding(0);
            this.lblCO2val.Name = "lblCO2val";
            this.lblCO2val.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblCO2val.Size = new System.Drawing.Size(117, 49);
            this.lblCO2val.TabIndex = 60;
            this.lblCO2val.Text = "0.00";
            this.lblCO2val.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label5
            // 
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(500, 164);
            this.label5.Margin = new System.Windows.Forms.Padding(0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 37);
            this.label5.TabIndex = 57;
            this.label5.Text = "%";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblHumidVal
            // 
            this.lblHumidVal.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblHumidVal.BackColor = System.Drawing.Color.Transparent;
            this.lblHumidVal.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblHumidVal.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblHumidVal.Location = new System.Drawing.Point(383, 162);
            this.lblHumidVal.Margin = new System.Windows.Forms.Padding(0);
            this.lblHumidVal.Name = "lblHumidVal";
            this.lblHumidVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblHumidVal.Size = new System.Drawing.Size(117, 49);
            this.lblHumidVal.TabIndex = 58;
            this.lblHumidVal.Text = "0.00";
            this.lblHumidVal.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(500, 125);
            this.label1.Margin = new System.Windows.Forms.Padding(0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 37);
            this.label1.TabIndex = 55;
            this.label1.Text = "℃";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblTempVal
            // 
            this.lblTempVal.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblTempVal.BackColor = System.Drawing.Color.Transparent;
            this.lblTempVal.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblTempVal.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTempVal.Location = new System.Drawing.Point(383, 122);
            this.lblTempVal.Margin = new System.Windows.Forms.Padding(0);
            this.lblTempVal.Name = "lblTempVal";
            this.lblTempVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblTempVal.Size = new System.Drawing.Size(117, 49);
            this.lblTempVal.TabIndex = 56;
            this.lblTempVal.Text = "0.00";
            this.lblTempVal.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.pictureBox1.Image = global::project_climate_control_app.Properties.Resources.fan;
            this.pictureBox1.Location = new System.Drawing.Point(115, 144);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(113, 105);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 69;
            this.pictureBox1.TabStop = false;
            // 
            // room_timer
            // 
            this.room_timer.Interval = 1000;
            this.room_timer.Tick += new System.EventHandler(this.room_timer_Tick);
            // 
            // lblAuto
            // 
            this.lblAuto.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblAuto.BackColor = System.Drawing.Color.Transparent;
            this.lblAuto.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblAuto.Location = new System.Drawing.Point(23, 172);
            this.lblAuto.Name = "lblAuto";
            this.lblAuto.Size = new System.Drawing.Size(75, 23);
            this.lblAuto.TabIndex = 70;
            this.lblAuto.Text = "Auto";
            this.lblAuto.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblManual
            // 
            this.lblManual.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lblManual.BackColor = System.Drawing.Color.Transparent;
            this.lblManual.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblManual.Location = new System.Drawing.Point(20, 205);
            this.lblManual.Name = "lblManual";
            this.lblManual.Size = new System.Drawing.Size(78, 23);
            this.lblManual.TabIndex = 71;
            this.lblManual.Text = "Manual";
            this.lblManual.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // data_timer
            // 
            this.data_timer.Interval = 10000;
            this.data_timer.Tick += new System.EventHandler(this.data_timer_Tick);
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(329, 247);
            this.label3.Margin = new System.Windows.Forms.Padding(0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 37);
            this.label3.TabIndex = 72;
            this.label3.Text = "CO2";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label6
            // 
            this.label6.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(329, 207);
            this.label6.Margin = new System.Windows.Forms.Padding(0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(90, 37);
            this.label6.TabIndex = 73;
            this.label6.Text = "VOC";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label7
            // 
            this.label7.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label7.BackColor = System.Drawing.Color.Transparent;
            this.label7.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(329, 168);
            this.label7.Margin = new System.Windows.Forms.Padding(0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(90, 37);
            this.label7.TabIndex = 74;
            this.label7.Text = "HUM";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label8
            // 
            this.label8.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label8.BackColor = System.Drawing.Color.Transparent;
            this.label8.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(329, 128);
            this.label8.Margin = new System.Windows.Forms.Padding(0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(90, 37);
            this.label8.TabIndex = 75;
            this.label8.Text = "TMP";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label10
            // 
            this.label10.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label10.BackColor = System.Drawing.Color.Transparent;
            this.label10.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(330, 290);
            this.label10.Margin = new System.Windows.Forms.Padding(0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(90, 37);
            this.label10.TabIndex = 78;
            this.label10.Text = "CO";
            this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label11
            // 
            this.label11.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label11.BackColor = System.Drawing.Color.Transparent;
            this.label11.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(501, 290);
            this.label11.Margin = new System.Windows.Forms.Padding(0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(81, 37);
            this.label11.TabIndex = 76;
            this.label11.Text = "ppm";
            this.label11.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblCoVal
            // 
            this.lblCoVal.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.lblCoVal.BackColor = System.Drawing.Color.Transparent;
            this.lblCoVal.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lblCoVal.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCoVal.Location = new System.Drawing.Point(384, 284);
            this.lblCoVal.Margin = new System.Windows.Forms.Padding(0);
            this.lblCoVal.Name = "lblCoVal";
            this.lblCoVal.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.lblCoVal.Size = new System.Drawing.Size(117, 49);
            this.lblCoVal.TabIndex = 77;
            this.lblCoVal.Text = "0.00";
            this.lblCoVal.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // Rooms
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(885, 436);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.lblCoVal);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lblManual);
            this.Controls.Add(this.lblAuto);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.lblSetTemp);
            this.Controls.Add(this.btnDecreaseTemp);
            this.Controls.Add(this.btnIncreaseTemp);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lblTVOCval);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lblCO2val);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.lblHumidVal);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblTempVal);
            this.Controls.Add(this.trbFanManual);
            this.Controls.Add(this.lblFanSpeed);
            this.Controls.Add(this.btnChangeRoomName);
            this.Controls.Add(this.tbRoomName);
            this.Controls.Add(this.cbSelectRoom);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MinimumSize = new System.Drawing.Size(901, 473);
            this.Name = "Rooms";
            this.Text = "Rooms";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Rooms_FormClosed);
            this.Load += new System.EventHandler(this.Rooms_Load);
            this.VisibleChanged += new System.EventHandler(this.Rooms_VisibleChanged);
            ((System.ComponentModel.ISupportInitialize)(this.trbFanManual)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbSelectRoom;
        private System.Windows.Forms.Button btnChangeRoomName;
        private System.Windows.Forms.TextBox tbRoomName;
        private System.Windows.Forms.Label lblFanSpeed;
        private System.Windows.Forms.TrackBar trbFanManual;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label lblSetTemp;
        private System.Windows.Forms.Button btnDecreaseTemp;
        private System.Windows.Forms.Button btnIncreaseTemp;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblTVOCval;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lblCO2val;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblHumidVal;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblTempVal;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Timer room_timer;
        private System.Windows.Forms.Label lblAuto;
        private System.Windows.Forms.Label lblManual;
        private System.Windows.Forms.Timer data_timer;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label lblCoVal;
    }
}