using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Siticone.UI.WinForms;

namespace External
{
    public partial class SplashScreen : Form
    {
        private Thread startupSong;

        public SplashScreen()
        {
            InitializeComponent();
            SiticoneShadowForm siticoneShadowForm = new SiticoneShadowForm();
            siticoneShadowForm.SetShadowForm(this);
            startupSong = new Thread(PlayStartupSound);
        }

        private void SplashScreen_Load(object sender, EventArgs e)
        {
            lblWelcome.Parent = splashProgress;
            lblWelcome.BackColor = Color.Transparent;
            lblWelcome.Location = new Point(26, 3);
            lblWelcome.ForeColor = Color.FromArgb(58, 53, 53);
            startupSong.Start();
        }

        private void SplashScreenTimer_Tick(object sender, EventArgs e)
        {
            if (splashProgress.Value < 101)
            {
                splashProgress.Value++;
            }
            else
            {
                MainForm mainForm = new MainForm();
                SystemSounds.Beep.Play();
                mainForm.Show();
                startupSong.Abort();
                Hide();
                SplashScreenTimer.Stop();
            }
        }

        private void PlayStartupSound()
        {
            // Add code to play startup sound here
        }
    }
}


		// Token: 0x06000022 RID: 34 RVA: 0x00004D98 File Offset: 0x00002F98
		private static void Mario()
		{
			Console.Beep(659, 125);
			Console.Beep(659, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(140);
			Console.Beep(523, 125);
			Console.Beep(659, 125);
			Thread.Sleep(100);
			Console.Beep(784, 125);
			Thread.Sleep(375);
			Console.Beep(392, 125);
			Thread.Sleep(375);
			Console.Beep(523, 125);
			Thread.Sleep(250);
			Console.Beep(392, 125);
			Thread.Sleep(250);
			Console.Beep(330, 125);
			Thread.Sleep(250);
			Console.Beep(440, 125);
			Thread.Sleep(125);
			Console.Beep(494, 125);
			Thread.Sleep(125);
			Console.Beep(466, 125);
			Thread.Sleep(42);
			Console.Beep(440, 125);
			Thread.Sleep(125);
			Console.Beep(392, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(125);
			Console.Beep(784, 125);
			Thread.Sleep(125);
			Console.Beep(880, 125);
			Thread.Sleep(125);
			Console.Beep(698, 125);
			Console.Beep(784, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(125);
			Console.Beep(523, 125);
			Thread.Sleep(125);
			Console.Beep(587, 125);
			Console.Beep(494, 125);
			Thread.Sleep(125);
			Console.Beep(523, 125);
			Thread.Sleep(250);
			Console.Beep(392, 125);
			Thread.Sleep(250);
			Console.Beep(330, 125);
			Thread.Sleep(250);
			Console.Beep(440, 125);
			Thread.Sleep(125);
			Console.Beep(494, 125);
			Thread.Sleep(125);
			Console.Beep(466, 125);
			Thread.Sleep(42);
			Console.Beep(440, 125);
			Thread.Sleep(125);
			Console.Beep(392, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(125);
			Console.Beep(784, 125);
			Thread.Sleep(125);
			Console.Beep(880, 125);
			Thread.Sleep(125);
			Console.Beep(698, 125);
			Console.Beep(784, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(125);
			Console.Beep(523, 125);
			Thread.Sleep(125);
			Console.Beep(587, 125);
			Console.Beep(494, 125);
			Thread.Sleep(375);
			Console.Beep(784, 125);
			Console.Beep(740, 125);
			Console.Beep(698, 125);
			Thread.Sleep(42);
			Console.Beep(622, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(167);
			Console.Beep(415, 125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Thread.Sleep(125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Console.Beep(587, 125);
			Thread.Sleep(250);
			Console.Beep(784, 125);
			Console.Beep(740, 125);
			Console.Beep(698, 125);
			Thread.Sleep(42);
			Console.Beep(622, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(167);
			Console.Beep(698, 125);
			Thread.Sleep(125);
			Console.Beep(698, 125);
			Console.Beep(698, 125);
			Thread.Sleep(625);
			Console.Beep(784, 125);
			Console.Beep(740, 125);
			Console.Beep(698, 125);
			Thread.Sleep(42);
			Console.Beep(622, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(167);
			Console.Beep(415, 125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Thread.Sleep(125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Console.Beep(587, 125);
			Thread.Sleep(250);
			Console.Beep(622, 125);
			Thread.Sleep(250);
			Console.Beep(587, 125);
			Thread.Sleep(250);
			Console.Beep(523, 125);
			Thread.Sleep(1125);
			Console.Beep(784, 125);
			Console.Beep(740, 125);
			Console.Beep(698, 125);
			Thread.Sleep(42);
			Console.Beep(622, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(167);
			Console.Beep(415, 125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Thread.Sleep(125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Console.Beep(587, 125);
			Thread.Sleep(250);
			Console.Beep(784, 125);
			Console.Beep(740, 125);
			Console.Beep(698, 125);
			Thread.Sleep(42);
			Console.Beep(622, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(167);
			Console.Beep(698, 125);
			Thread.Sleep(125);
			Console.Beep(698, 125);
			Console.Beep(698, 125);
			Thread.Sleep(625);
			Console.Beep(784, 125);
			Console.Beep(740, 125);
			Console.Beep(698, 125);
			Thread.Sleep(42);
			Console.Beep(622, 125);
			Thread.Sleep(125);
			Console.Beep(659, 125);
			Thread.Sleep(167);
			Console.Beep(415, 125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Thread.Sleep(125);
			Console.Beep(440, 125);
			Console.Beep(523, 125);
			Console.Beep(587, 125);
			Thread.Sleep(250);
			Console.Beep(622, 125);
			Thread.Sleep(250);
			Console.Beep(587, 125);
			Thread.Sleep(250);
			Console.Beep(523, 125);
		}

		// Token: 0x06000023 RID: 35 RVA: 0x00005598 File Offset: 0x00003798
		private static void StarWars()
		{
			Console.Beep(300, 500);
			Thread.Sleep(50);
			Console.Beep(300, 500);
			Thread.Sleep(50);
			Console.Beep(300, 500);
			Thread.Sleep(50);
			Console.Beep(250, 500);
			Thread.Sleep(50);
			Console.Beep(350, 250);
			Console.Beep(300, 500);
			Thread.Sleep(50);
			Console.Beep(250, 500);
			Thread.Sleep(50);
			Console.Beep(350, 250);
			Console.Beep(300, 500);
			Thread.Sleep(50);
		}

		// Token: 0x0400002A RID: 42
		private Thread = new Thread(new ThreadStart(SplashScreen.Mario));
	}
}
