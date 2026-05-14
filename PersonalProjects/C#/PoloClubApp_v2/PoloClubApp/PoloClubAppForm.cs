using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PoloClubApp
{
    //////////////////////////////////////////////////////////////////////
    //PoloClubApp
    //
    //Course	    : Programming in C# 2 (PCS2)
    //Assignment	: Assignment 1
    //Date		    : 19-03-2022 (assignment_a)
    //                22-03-2022 (assignment_b)
    //Student	    : Farros Ramzy (3767353)
    //
    //////////////////////////////////////////////////////////////////////
    /// <summary>
    /// A completed version of PoloClubApp.
    /// </summary>

    public partial class PoloClubAppForm : Form
    {

        // Provide your answers here
        private string user;
        private int deviceId;

        private void btnViewAllWearables_Click(object sender, EventArgs e)
        {
            lbOverview.Items.Clear();
            foreach (Device device in myClub.GetAllWearables())
            {
                this.lbOverview.Items.Add(device.GetDetails());
            }
        }

        private void btnAssign_Click(object sender, EventArgs e)
        {
            try
            {
                lbOverview.Items.Clear();
                if (cbDevice.SelectedIndex == -1 || tbPlayerName.Text == "")
                {
                    throw new EmptyAssignInputException(cbDevice.SelectedIndex,tbPlayerName.Text);
                }
                else
                {
                    this.deviceId = Convert.ToInt32(cbDevice.SelectedItem);
                    this.user = tbPlayerName.Text;
                    myClub.AssignDevice(deviceId, user);
                    cbDevice.SelectedIndex = -1;
                }
            }
            catch (PoloClubAppException ex)
            {
                MessageBox.Show(ex.GetDetails());
            }
        }

        private void btnReturn_Click(object sender, EventArgs e)
        {
            try
            {
                lbOverview.Items.Clear();
                if (cbDevice.SelectedIndex == -1)
                {
                    throw new EmptyDeviceReturnInputException();
                }
                else
                {
                    this.deviceId = Convert.ToInt32(cbDevice.SelectedItem);
                    this.user = tbPlayerName.Text;
                    myClub.ReturnDevice(deviceId);
                    cbDevice.SelectedIndex = -1;
                }
            }
            catch (PoloClubAppException ex)
            {
                MessageBox.Show(ex.GetDetails());
            }
        }

        private void btnShowAssignedDevices_Click(object sender, EventArgs e)
        {
            try
            {
                lbOverview.Items.Clear();
                if (tbPlayerName.Text != "")
                {
                    string userName = tbPlayerName.Text;
                    if (myClub.GetAllAssignedDevicesPerPlayer(userName).Count() != 0)
                    {
                        lbOverview.Items.Add($"The devices that assigned to {userName} are:");
                        lbOverview.Items.Add("");
                        foreach (Device device in myClub.GetAllAssignedDevicesPerPlayer(userName))
                        {
                            this.lbOverview.Items.Add(device.GetDetails());
                        }
                    }
                    else
                    {
                        throw new NoAssignedDeviceFoundException(userName);
                    }
                }
                else
                {
                    throw new EmptyNameInputException();
                }
            }
            catch (PoloClubAppException ex)
            {
                MessageBox.Show(ex.GetDetails());
            }
        }


        private void btnGeneratePlayerTextReport_Click(object sender, EventArgs e)
        {
            try
            {
                lbOverview.Items.Clear();
                if (tbPlayerNameForFile.Text != "")
                {
                    string user = tbPlayerNameForFile.Text;
                    if (myClub.GetAllAssignedDevicesPerPlayer(user).Count() != 0)
                    {
                        foreach (String data in myClub.GenerateReportPerPlayer(user))
                        {
                            this.lbOverview.Items.Add(data);
                        }
                    }
                    else
                    {
                        throw new NoUserDataFoundException(user);
                    }
                }
                else
                {
                    throw new EmptyNameInputException();
                }
            }
            catch (PoloClubAppException ex)
            {
                MessageBox.Show(ex.GetDetails());
            }
        }



        // -----The provided code below will not be graded, therefore should not be changed-----

        private Club myClub;
        public PoloClubAppForm()
        {
            InitializeComponent();
            myClub = new Club("Polo Koningen - powered by Farros Ramzy");
            this.Text = myClub.Name;
            this.addSomeTestingStuff();
            this.fillComboBoxDevices();
        }

        private void addSomeTestingStuff()
        {
            myClub.AddDevice(new SmartPhone(101, "iPhone X"));
            myClub.AddDevice(new SmartWatch(202, "Apple Watch Sport", 5, 38));
            myClub.AddDevice(new FitTracker(300, "Fitbit Ionic", 1, "pink"));
            myClub.AddDevice(new SmartWatch(203, "Motorola Moto 360", 9, 40));
            myClub.AddDevice(new SmartPhone(102, "iPhone 9"));
            myClub.AddDevice(new SmartPhone(103, "Galaxy S9"));
            myClub.AddDevice(new FitTracker(301, "Fitbit Alta HR", 8, "blue"));
            myClub.AddDevice(new SmartPhone(104, "Pixels 2"));
            myClub.AddDevice(new SmartWatch(204, "Samsung Gear Sport", 2, 42));
            myClub.AddDevice(new FitTracker(302, "Fitbit Charge 2", 10, "black"));
            myClub.AddDevice(new FitTracker(303, "Misfit Ray", 0, "black"));

        }
        private void fillComboBoxDevices()
        {
            foreach (Device dev in myClub.GetAllDevices())
            {
                cbDevice.Items.Add(dev.Id);
            }
        }

        private void btnViewAllDevices_Click(object sender, EventArgs e)
        {
            this.lbOverview.Items.Clear();
            foreach (Device dev in myClub.GetAllDevices())
            {
                this.lbOverview.Items.Add(dev.GetDetails());
            }

        }
    }
}
