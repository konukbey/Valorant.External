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

public partial class OverlayForm : Form
{
    private Timer autoUpdateTimer;

    public OverlayForm()
    {
        InitializeComponent();
        InitializeAutoUpdateTimer();
    }

    private void InitializeAutoUpdateTimer()
    {
        autoUpdateTimer = new Timer();
        autoUpdateTimer.Interval = 5000; // 5 seconds
        autoUpdateTimer.Tick += AutoUpdateTimer_Tick;
        autoUpdateTimer.Start();
    }

    private void AutoUpdateTimer_Tick(object sender, EventArgs e)
    {
        // Do something on each tick of the timer
        // For example, update data from a server
    }

    private void OverlayForm_Load(object sender, EventArgs e)
    {
        // Perform additional initialization here
        // For example, set the form's size and position
        this.Size = new Size(400, 300);
        this.Location = new Point(Screen.PrimaryScreen.WorkingArea.Width - this.Width,
                                   Screen.PrimaryScreen.WorkingArea.Height - this.Height);
    }

    private void OverlayForm_Paint(object sender, PaintEventArgs e)
    {
        // Draw custom graphics or text on the form's surface here
        // For example, draw a border and some text
        e.Graphics.DrawRectangle(Pens.Red, 0, 0, this.Width - 1, this.Height - 1);
        e.Graphics.DrawString("Hello, World!", new Font("Arial", 12), Brushes.Black, 10, 10);
    }
}

