using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace project_climate_control_app.SubForms
{
    public partial class Rooms : Form
    {
        private VentilationBox ventilationBox;
        private DataLogger logger;
        private Server local;

        private string ipAddress;
        private int portNr;

        private bool roomNameChanged;
        private bool serverConnected;
        
        public static RoomClimateData DataCloud;

        public Rooms()
        {
            InitializeComponent();
            DataCloud = new RoomClimateData();
            ventilationBox = new VentilationBox();
            logger = new DataLogger();
            DataCloud.addDefaultRoom();
            UpdateRooms();
        }

        private void Rooms_Load(object sender, EventArgs e)
        {
            changeTheme();
            this.roomNameChanged = false;
            this.serverConnected = false;
            tbRoomName.Visible = false;
            cbSelectRoom.SelectedIndex = 0;

            room_timer.Start();
            data_timer.Start();
        }

        private void Rooms_VisibleChanged(object sender, EventArgs e)
        {
            changeTheme();
        }

        private void changeTheme()
        {
            cbSelectRoom.BackColor = FormThemeColor.Secondary;
            cbSelectRoom.ForeColor = Color.White;
            foreach (Control buttons in this.Controls)
            {
                if (buttons.GetType() == typeof(Button))
                {
                    Button button = (Button)buttons;
                    button.BackColor = FormThemeColor.Primary;
                    button.ForeColor = Color.White;
                    button.FlatAppearance.BorderColor = FormThemeColor.Secondary;
                }
            }
            tbRoomName.BackColor = Color.White;
        }

        private void btnChangeRoomName_Click(object sender, EventArgs e)
        {
            UpdateRoomName();
        }

        private void trbFanManual_Scroll(object sender, EventArgs e)
        {
            lblManual.Show();
            lblAuto.Hide();
            int fanSpeed = trbFanManual.Value;
            if (fanSpeed > 85)
            {
                trbFanManual.Value = 100;
                DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].SetManualFanSpeedSpeed(100);
            }
            else if (fanSpeed <= 85 && fanSpeed > 65)
            {
                trbFanManual.Value = 75;
                DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].SetManualFanSpeedSpeed(75);
            }
            else if (fanSpeed <= 65 && fanSpeed > 45)
            {
                trbFanManual.Value = 50;
                DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].SetManualFanSpeedSpeed(50);
            }
            else if (fanSpeed <= 45 && fanSpeed > 15)
            {
                trbFanManual.Value = 25;
                DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].SetManualFanSpeedSpeed(25);
            }
            else
            {
                trbFanManual.Value = 0;
                DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].SetManualFanSpeedSpeed(0);
            }

            lblFanSpeed.Text = $"{trbFanManual.Value} %";
        }

        private void btnIncreaseTemp_Click(object sender, EventArgs e)
        {
            UpdateTemperature(1);
        }

        private void btnDecreaseTemp_Click(object sender, EventArgs e)
        {
            UpdateTemperature(-1);
        }

        private void cbSelectRoom_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateLabelValues();
        }

        private void room_timer_Tick(object sender, EventArgs e)
        {
            if (this.serverConnected == false)
            {
                updateServer();
            }
            else
            {
                try
                {
                    UpdateLabelValues();
                }
                catch (Exception)
                {

                }
            }
        }

        private void data_timer_Tick(object sender, EventArgs e)
        {
            if (this.serverConnected == true)
            {
                foreach (Room room in DataCloud.listOfRooms)
                {
                    logger.uploadData(room.GetInfo());
                }
            }
        }

        private void Rooms_FormClosed(object sender, FormClosedEventArgs e)
        {
            room_timer.Stop();
            data_timer.Stop();
        }

        private void UpdateRooms()
        {
            cbSelectRoom.Items.Clear();
            foreach (Room room in DataCloud.listOfRooms)
            {
                cbSelectRoom.Items.Add(room.roomName);
            }
        }

        private void UpdateRoomName()
        {
            int index = 0;
            if (this.roomNameChanged == false)
            {
                tbRoomName.Visible = true;
                tbRoomName.BackColor = Color.Black;
                tbRoomName.ForeColor = Color.White;
                btnChangeRoomName.Text = "OK";
                this.roomNameChanged = true;
            }
            else
            {
                if (tbRoomName.Text == "")
                {
                    MessageBox.Show("Please Add the new name!");
                }
                else
                {
                    index = cbSelectRoom.SelectedIndex;
                    DataCloud.listOfRooms[index].SetName(tbRoomName.Text);
                    UpdateRooms();
                }
                tbRoomName.Visible = false;
                tbRoomName.Text = "";
                btnChangeRoomName.Text = "Rename";
                this.roomNameChanged = false;
            }
        }

        private void UpdateTemperature(int change)
        {
            float newTemp = DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].preferedTemperature + change;
            DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].UpdatePreferedTemperature(newTemp);
            UpdatePreferedTemperatureLabel();
        }

        private void UpdatePreferedTemperatureLabel()
        {
            lblSetTemp.Text = Convert.ToString(DataCloud.listOfRooms[cbSelectRoom.SelectedIndex].preferedTemperature);
        }

        private void updateServer()
        {
            Thread server;
            ipAddress = "192.168.137.1";
            portNr = 8888;

            local = new Server(ipAddress, portNr);
            server = new Thread(delegate () { local = new Server(ipAddress, portNr); });
            if (local.GetServerInfo == false)
            {
                this.serverConnected = false;
            }
            else
            {
                this.serverConnected = true;
            }

            if (this.serverConnected == false)
            {
                this.serverConnected = true;
                //lblRoomConnection.Text = "Online";
                server.Start();
            }
        }

        private void UpdateLabelValues()
        {
            lblAuto.Show();
            lblManual.Hide();
            Room room = DataCloud.listOfRooms[cbSelectRoom.SelectedIndex];
            UpdateLabelTemperature(room);
            UpdateLabelHumidity(room);
            UpdateLabelVOC(room);
            UpdateLabelCO2(room);
            UpdateLabelCO(room);
            UpdateFanSpeedLabel(room);
            UpdatePreferedTemperatureLabel();
        }

        private void UpdateLabelTemperature(Room room)
        {
            lblTempVal.Text = Convert.ToString(room.GetTemperature());
        }

        private void UpdateLabelHumidity(Room room)
        {
            lblHumidVal.Text = Convert.ToString(room.GetHumidity());
        }

        private void UpdateLabelVOC(Room room)
        {
            lblTVOCval.Text = Convert.ToString(room.GetVoc());
        }

        private void UpdateLabelCO2(Room room)
        {
            lblCO2val.Text = Convert.ToString(room.GetCo2());
        }

        private void UpdateLabelCO(Room room)
        {
            lblCoVal.Text = Convert.ToString(room.GetCo());
        }

        private void UpdateFanSpeedLabel(Room room)
        {
            if (room.manualOverrideFanSpeed == 0)
            {
                lblFanSpeed.Text = $"{Convert.ToString(ventilationBox.CalculateFanSpeed(room))} %";
                trbFanManual.Value = 0;
            }
            else
            {
                lblFanSpeed.Text = $"{Convert.ToString(ventilationBox.SetManualFanSpeed(room, room.manualOverrideFanSpeed))} %";
                trbFanManual.Value = room.manualOverrideFanSpeed;
            }
        }
    }
}
