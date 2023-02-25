namespace Immortal
{
    public partial class OverlayForm : Form
    {
        private Timer autoUpdate;
        
        public OverlayForm()
        {
            InitializeComponent();
        }
        
        protected override void Dispose(bool disposing)
        {
            if (disposing && components != null)
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            autoUpdate = new Timer(components);
            SuspendLayout();

            autoUpdate.Enabled = true;
            autoUpdate.Interval = 500;
            autoUpdate.Tick += new EventHandler(autoUpdate_Tick);

            ClientSize = new System.Drawing.Size(800, 450);
            DoubleBuffered = true;
            FormBorderStyle = FormBorderStyle.None;
            Icon = Properties.Resources.MyIcon;
            MaximizeBox = false;
            MinimizeBox = false;
            Name = "OverlayForm";
            Opacity = 0.8;
            ShowIcon = false;
            ShowInTaskbar = false;
            StartPosition = FormStartPosition.CenterScreen;
            TopMost = true;
            TransparencyKey = System.Drawing.Color.FromArgb(1, 1, 1);
            WindowState = FormWindowState.Maximized;

            ResumeLayout(false);
        }

        private void autoUpdate_Tick(object sender, EventArgs e)
        {
            // Do something on each tick of the timer
        }

        private void OverlayForm_Load(object sender, EventArgs e)
        {
            // Perform additional initialization here
        }

        private void OverlayForm_Paint(object sender, PaintEventArgs e)
        {
            // Draw custom graphics or text on the form's surface here
        }
    }
}

