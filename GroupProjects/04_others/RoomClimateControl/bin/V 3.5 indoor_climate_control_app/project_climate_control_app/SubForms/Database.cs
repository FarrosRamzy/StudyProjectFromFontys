using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Management;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MongoDB.Bson;

namespace project_climate_control_app.SubForms
{
    public partial class Database : Form
    {
        private DataLogger logger;
        bool showControl = false;
        public Database()
        {
            InitializeComponent();
            logger = new DataLogger();
            gbControlPanel.Visible = false;
        }

        private void Database_Load(object sender, EventArgs e)
        {
            changeTheme();
        }

        private void Database_VisibleChanged(object sender, EventArgs e)
        {
            changeTheme();
        }

        private void changeTheme()
        {
            foreach (Control buttons in this.Controls)
            {
                if (buttons.GetType() == typeof(Button))
                {
                    Button button = (Button)buttons;
                    button.BackColor = FormThemeColor.Primary;
                    button.ForeColor = Color.White;
                    button.FlatAppearance.BorderColor = FormThemeColor.Secondary;
                }
                foreach (Control internalButtons in gbControlPanel.Controls)
                {
                    if (internalButtons.GetType() == typeof(Button))
                    {
                        Button button = (Button)internalButtons;
                        button.BackColor = FormThemeColor.Primary;
                        button.ForeColor = Color.White;
                        button.FlatAppearance.BorderColor = FormThemeColor.Secondary;
                    }
                }
            }
            /*lblCityName.BackColor = Color.White;
            lblTime.ForeColor = FormThemeColor.Primary;
            lblDate.ForeColor = FormThemeColor.Secondary;
            pbCloud.BackColor = Color.White;*/
        }

        private void btnShowPanel_Click(object sender, EventArgs e)
        {
            if (showControl == false)
            {
                btnShowPanel.Text = "Hide Control";
                gbControlPanel.Visible = true;
                showControl = true;
            }
            else
            {
                btnShowPanel.Text = "Show Control";
                gbControlPanel.Visible = false;
                showControl = false;
            }
        }

        private void dtpStartDate_ValueChanged(object sender, EventArgs e)
        {
            dtpEndDate.Value = dtpStartDate.Value;
        }

        private void btnGenerate_Click(object sender, EventArgs e)
        {
            string startDate = dtpStartDate.Value.ToString("dd/MM/yyyy");
            string startTime = dtpStartTime.Value.ToString("HH:mm:ss");
            string endDate = dtpEndDate.Value.ToString("dd/MM/yyyy");
            string endTime = dtpEndTime.Value.ToString("HH:mm:ss");

            if (logger.downloadData(startDate, endDate, startTime, endTime).Count() == 0) 
            {
                MessageBox.Show($"Data Collection between {startDate}, {startTime} and {endDate}, {endTime} are empty.");
            }
            else
            {
                DataTable dt = new DataTable();

                dt.Columns.Add("Date");
                dt.Columns.Add("Time");
                dt.Columns.Add("Room");
                dt.Columns.Add("Temperature (℃)");
                dt.Columns.Add("Humidity (%)");
                dt.Columns.Add("CO2 (ppm)");
                dt.Columns.Add("TVOC (ppm)");

                foreach (BsonDocument collection in logger.downloadData(startDate, endDate, startTime, endTime))
                {
                    if (collection == 0 || collection == null)
                    {
                        MessageBox.Show("Data in this selected Time Frame is unavailable.");
                    }
                    dt.Rows.Add(collection["Date"], collection["Time"], collection["Room"], collection["Temperature"], collection["Humidity"], collection["CO2"], collection["TVOC"]);
                }
                dtCloudData.DataSource = dt;
            }
        }

        private void btnDownload_Click(object sender, EventArgs e)
        {
            if (dtCloudData.DataSource != null)
            {
                Microsoft.Office.Interop.Excel._Application app = new Microsoft.Office.Interop.Excel.Application();
                Microsoft.Office.Interop.Excel._Workbook workBook = app.Workbooks.Add(Type.Missing);
                Microsoft.Office.Interop.Excel._Worksheet workSheet = null;
                app.Visible = true;
                workSheet = workBook.Sheets["Sheet1"];
                workSheet = workBook.ActiveSheet;
                workSheet.Name = $"Downloaded_Room_Data";
                // storing header part in Excel  
                for (int i = 1; i < dtCloudData.Columns.Count + 1; i++)
                {
                    workSheet.Cells[1, i] = dtCloudData.Columns[i - 1].HeaderText;
                }
                // storing Each row and column value to excel sheet  
                for (int i = 0; i < dtCloudData.Rows.Count - 1; i++)
                {
                    for (int j = 0; j < dtCloudData.Columns.Count; j++)
                    {
                        workSheet.Cells[i + 2, j + 1] = dtCloudData.Rows[i].Cells[j].Value.ToString();
                    }
                }
            }
            else
            {
                MessageBox.Show("No Data can be downloaded.");
            }
        }
    }
}
