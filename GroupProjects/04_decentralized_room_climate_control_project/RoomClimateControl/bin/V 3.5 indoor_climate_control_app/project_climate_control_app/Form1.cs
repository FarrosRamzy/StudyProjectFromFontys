using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace project_climate_control_app
{
    public partial class Form1 : Form
    {
        private Button currentButton;
        private Random random;

        private Form activeForm;
        private Form HomeForm;
        private Form RoomsForm;
        private Form WeatherForm;
        private Form DataForm;
        private Form GraphForm;

        private int tempIndex;
        private string cityForWeather;

        public Form1()
        {
            InitializeComponent();
            cityForWeather = WeatherCity.GetDefaultCity;
            random = new Random();
            HomeForm = new SubForms.Home(cityForWeather);
            RoomsForm = new SubForms.Rooms();
            WeatherForm = new SubForms.Weather(cityForWeather);
            DataForm = new SubForms.Database();
            GraphForm = new SubForms.Graph();
            this.Text = string.Empty;
            this.ControlBox = false;
            this.MaximizedBounds = Screen.FromHandle(this.Handle).WorkingArea;
        }

        [DllImport("user32.DLL", EntryPoint = "ReleaseCapture")]
        private extern static void ReleaseCapture();
        [DllImport("user32.DLL", EntryPoint = "SendMessage")]
        private extern static void SendMessage(System.IntPtr hWnd, int wMsg, int wParam, int lParam);

        private void Form1_Load(object sender, EventArgs e)
        {
            OpenChildForm(HomeForm);
        }

        private Color SelectThemeColor()
        {
            int index = random.Next(FormThemeColor.ColorList.Count);
            while (tempIndex == index)
            {
                index = random.Next(FormThemeColor.ColorList.Count);
            }
            tempIndex = index;
            string color = FormThemeColor.ColorList[index];
            return ColorTranslator.FromHtml(color);
        }

        private void ActivatedButton(object btnPressed)
        {
            if (btnPressed != null)
            {
                if (currentButton != (Button)btnPressed)
                {
                    DeactivatedButton();
                    Color color = SelectThemeColor();
                    currentButton = (Button)btnPressed;
                    currentButton.BackColor = color;
                    currentButton.ForeColor = Color.White;
                    currentButton.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 10.8F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                    pnTitle.BackColor = FormThemeColor.changeBrightness(color, -0.2);
                    pnMenu.BackColor = FormThemeColor.changeBrightness(color, -0.2);
                    pnLogo.BackColor = FormThemeColor.changeBrightness(color, -0.3);
                    btnBackToHome.BackColor = pnTitle.BackColor;
                    btnMinimize.ForeColor = Color.White;
                    btnMaximize.ForeColor = Color.White;
                    btnClose.ForeColor = Color.White;
                    FormThemeColor.Primary = color;
                    FormThemeColor.Secondary = FormThemeColor.changeBrightness(color, -0.3);

                    /*lblGroup.ForeColor = Color.White;*/
                    lblTitle.ForeColor = Color.White;
                    lblTitle.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 10.8F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                }
            }
        }

        private void DeactivatedButton()
        {
            foreach (Control unclickedBtn in pnMenu.Controls)
            {
                if (unclickedBtn.GetType() == typeof(Button))
                {
                    unclickedBtn.BackColor = Color.Transparent;
                    unclickedBtn.ForeColor = Color.Black;
                    unclickedBtn.Font = new System.Drawing.Font("Yu Gothic UI Semibold", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                }
            }
        }

        private void MenuClicked(Form supportForm, object btnPressed)
        {
            if (activeForm != null)
            {
                activeForm.Hide();
            }
            ActivatedButton(btnPressed);
            OpenChildForm(supportForm);
        }

        private void OpenChildForm(Form subForm)
        {
            if (subForm is SubForms.Home)
            {
                btnBackToHome.Visible = false;
            }
            else
            {
                btnBackToHome.Visible = true;
            }

            activeForm = subForm;
            subForm.BackColor = Color.White;
            subForm.TopLevel = false;
            subForm.FormBorderStyle = FormBorderStyle.None;
            subForm.Dock = DockStyle.Fill;
            this.pnDesktop.Controls.Add(subForm);
            this.pnDesktop.Tag = subForm;
            subForm.BringToFront();
            subForm.Show();
            lblTitle.Text = subForm.Text;
        }

        private void checkWeatherServerInfo()
        {
            if (WeatherCity.GetServerInfo == false)
            {
                MessageBox.Show("Weather data is offline!");
            }
        }

        private void btnHome_Click(object sender, EventArgs e)
        {
            MenuClicked(HomeForm, sender);
            checkWeatherServerInfo();
        }

        private void btnRooms_Click(object sender, EventArgs e)
        {
            MenuClicked(RoomsForm, sender);
        }

        private void btnWeather_Click(object sender, EventArgs e)
        {
            MenuClicked(WeatherForm, sender);
            checkWeatherServerInfo();
        }

        private void btnDatabase_Click(object sender, EventArgs e)
        {
            MenuClicked(DataForm, sender);
        }

        /*private void btnGraph_Click(object sender, EventArgs e)
        {
            MenuClicked(GraphForm, sender);
        }*/

        private void btnBackToHome_Click(object sender, EventArgs e)
        {
            MenuClicked(HomeForm, sender);
            checkWeatherServerInfo();
            currentButton = null;
        }

        private void pnTitle_MouseDown(object sender, MouseEventArgs e)
        {
            ReleaseCapture();
            SendMessage(this.Handle, 0x112, 0xf012, 0);
        }

        private void btnMinimize_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void btnMaximize_Click(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Normal)
            {
                this.WindowState = FormWindowState.Maximized;
            }
            else
            {
                this.WindowState = FormWindowState.Normal;
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
