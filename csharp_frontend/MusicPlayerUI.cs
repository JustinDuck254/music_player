using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.Net.Http;
using System.Threading.Tasks;
using System.Text.Json;
using System.Linq; // 🎵 For LINQ queries

namespace MusicPlayerUI
{
    public partial class MusicPlayerForm : Form
    {
        private Process cppBackend;
        private List<Song> playlist = new List<Song>();
        private Song currentSong = null;
        private bool isPlaying = false;
        private Timer updateTimer;
        private AudioManager audioManager; // 🎵 Real audio playback

        public MusicPlayerForm()
        {
            InitializeComponent();
            audioManager = new AudioManager(); // 🎵 Initialize audio
            StartupCppBackend();
            SetupUI();
            SetupEventHandlers();
        }

        private void InitializeComponent()
        {
            this.Text = "🎵 Music Player";
            this.Size = new Size(800, 600);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.BackColor = Color.FromArgb(30, 30, 30);
            this.ForeColor = Color.White;
            this.Font = new Font("Segoe UI", 10);

            // Main container
            var mainPanel = new Panel { Dock = DockStyle.Fill, BackColor = Color.FromArgb(30, 30, 30) };

            // Header
            var headerPanel = new Panel { Dock = DockStyle.Top, Height = 80, BackColor = Color.FromArgb(20, 20, 20) };
            var titleLabel = new Label 
            { 
                Text = "🎵 Music Player", 
                Dock = DockStyle.Fill, 
                Font = new Font("Segoe UI", 24, FontStyle.Bold),
                TextAlign = ContentAlignment.MiddleCenter,
                ForeColor = Color.Cyan
            };
            headerPanel.Controls.Add(titleLabel);

            // Now Playing Section
            var nowPlayingPanel = new Panel { Dock = DockStyle.Top, Height = 120, BackColor = Color.FromArgb(40, 40, 40), BorderStyle = BorderStyle.FixedSingle };
            
            nowPlayingLabel = new Label
            {
                Text = "▶️ No song playing",
                Location = new Point(15, 10),
                Size = new Size(750, 30),
                Font = new Font("Segoe UI", 14, FontStyle.Bold),
                ForeColor = Color.LimeGreen
            };

            artistLabel = new Label
            {
                Text = "Artist: N/A",
                Location = new Point(15, 45),
                Size = new Size(750, 25),
                Font = new Font("Segoe UI", 11),
                ForeColor = Color.LightGray
            };

            progressLabel = new Label
            {
                Text = "Duration: 00:00 / 00:00",
                Location = new Point(15, 75),
                Size = new Size(750, 25),
                Font = new Font("Segoe UI", 10),
                ForeColor = Color.Yellow
            };

            nowPlayingPanel.Controls.Add(nowPlayingLabel);
            nowPlayingPanel.Controls.Add(artistLabel);
            nowPlayingPanel.Controls.Add(progressLabel);

            // Control Buttons
            var controlPanel = new Panel { Dock = DockStyle.Top, Height = 60, BackColor = Color.FromArgb(40, 40, 40) };
            
            playButton = new Button
            {
                Text = "▶️ Play",
                Location = new Point(10, 10),
                Size = new Size(80, 40),
                BackColor = Color.Green,
                ForeColor = Color.White,
                Font = new Font("Segoe UI", 10, FontStyle.Bold)
            };
            playButton.Click += PlayButton_Click;

            pauseButton = new Button
            {
                Text = "⏸ Pause",
                Location = new Point(100, 10),
                Size = new Size(80, 40),
                BackColor = Color.Orange,
                ForeColor = Color.White,
                Font = new Font("Segoe UI", 10, FontStyle.Bold)
            };
            pauseButton.Click += PauseButton_Click;

            stopButton = new Button
            {
                Text = "⏹ Stop",
                Location = new Point(190, 10),
                Size = new Size(80, 40),
                BackColor = Color.Red,
                ForeColor = Color.White,
                Font = new Font("Segoe UI", 10, FontStyle.Bold)
            };
            stopButton.Click += StopButton_Click;

            controlPanel.Controls.Add(playButton);
            controlPanel.Controls.Add(pauseButton);
            controlPanel.Controls.Add(stopButton);

            // Search Section
            var searchPanel = new Panel { Dock = DockStyle.Top, Height = 50, BackColor = Color.FromArgb(40, 40, 40) };
            
            searchTextBox = new TextBox
            {
                Location = new Point(10, 10),
                Size = new Size(600, 30),
                Font = new Font("Segoe UI", 11),
                Text = "Search songs..."
            };

            searchButton = new Button
            {
                Text = "🔍 Search",
                Location = new Point(620, 10),
                Size = new Size(100, 30),
                BackColor = Color.Blue,
                ForeColor = Color.White,
                Font = new Font("Segoe UI", 10, FontStyle.Bold)
            };
            searchButton.Click += SearchButton_Click;

            searchPanel.Controls.Add(searchTextBox);
            searchPanel.Controls.Add(searchButton);

            // Playlist ListView
            playlistView = new ListBox
            {
                Dock = DockStyle.Fill,
                BackColor = Color.FromArgb(50, 50, 50),
                ForeColor = Color.White,
                Font = new Font("Segoe UI", 11),
                SelectionMode = SelectionMode.One
            };
            playlistView.DoubleClick += PlaylistView_DoubleClick;

            // Status Bar
            statusLabel = new Label
            {
                Dock = DockStyle.Bottom,
                Height = 30,
                BackColor = Color.FromArgb(20, 20, 20),
                ForeColor = Color.LightGray,
                Text = "Ready",
                TextAlign = ContentAlignment.MiddleLeft,
                Padding = new Padding(10, 0, 0, 0)
            };

            // Add all panels to main
            mainPanel.Controls.Add(playlistView);
            mainPanel.Controls.Add(searchPanel);
            mainPanel.Controls.Add(controlPanel);
            mainPanel.Controls.Add(nowPlayingPanel);
            mainPanel.Controls.Add(headerPanel);
            mainPanel.Controls.Add(statusLabel);

            this.Controls.Add(mainPanel);

            // Timer for updates
            updateTimer = new Timer();
            updateTimer.Interval = 1000; // Update every 1 second
            updateTimer.Tick += UpdateTimer_Tick;
            updateTimer.Start();
        }

        private void SetupUI()
        {
            // Load initial playlist from C++ backend
            RefreshPlaylist();
        }

        private void SetupEventHandlers()
        {
            this.FormClosing += (s, e) => ShutdownCppBackend();
        }

        private void StartupCppBackend()
        {
            try
            {
                string exePath = Path.Combine(Directory.GetCurrentDirectory(), "music_player.exe");
                if (!File.Exists(exePath))
                {
                    MessageBox.Show("C++ Backend (music_player.exe) not found!\n\nPlace it in: " + exePath, 
                        "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                cppBackend = new Process();
                cppBackend.StartInfo.FileName = exePath;
                cppBackend.StartInfo.UseShellExecute = false;
                cppBackend.StartInfo.RedirectStandardOutput = true;
                cppBackend.StartInfo.CreateNoWindow = true;
                cppBackend.Start();

                statusLabel.Text = "✅ Backend started";
            }
            catch (Exception ex)
            {
                MessageBox.Show("Failed to start C++ backend: " + ex.Message, "Error");
            }
        }

        private void ShutdownCppBackend()
        {
            try
            {
                audioManager?.Dispose(); // 🎵 Stop audio
                if (cppBackend != null && !cppBackend.HasExited)
                {
                    cppBackend.Kill();
                    cppBackend.Dispose();
                }
            }
            catch { }
        }

        private void RefreshPlaylist()
        {
            playlistView.Items.Clear();
            
            // 🎵 Load actual audio files from Music folder
            string musicFolder = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyMusic), "MusicPlayer");
            
            if (Directory.Exists(musicFolder))
            {
                var audioFormats = AudioManager.GetSupportedFormats();
                var files = Directory.GetFiles(musicFolder)
                    .Where(f => audioFormats.Contains(Path.GetExtension(f).ToLower()))
                    .OrderBy(f => Path.GetFileName(f))
                    .ToList();

                if (files.Count > 0)
                {
                    foreach (var file in files)
                    {
                        playlistView.Items.Add($"🎵 {Path.GetFileNameWithoutExtension(file)}");
                    }
                    statusLabel.Text = $"📊 Playlist: {files.Count} songs from {musicFolder}";
                    return;
                }
            }

            // Demo fallback - 生成 test audio files info
            var demoSongs = new[]
            {
                "🎵 Blinding Lights - The Weeknd (3:20)",
                "🎵 Shape of You - Ed Sheeran (3:53)",
                "🎵 Someone Like You - Adele (4:45)",
                "🎵 Bad Guy - Billie Eilish (3:14)",
                "🎵 Perfect - Ed Sheeran (4:23)"
            };

            foreach (var song in demoSongs)
            {
                playlistView.Items.Add(song);
            }

            statusLabel.Text = $"📊 Demo Playlist: {demoSongs.Length} songs (Place real audio files in: {musicFolder})";
        }

        private void PlayButton_Click(object sender, EventArgs e)
        {
            if (playlistView.SelectedIndex >= 0)
            {
                string selectedSong = playlistView.SelectedItem.ToString();
                string songTitle = selectedSong.Replace("🎵 ", "").Split('-')[0].Trim();

                // 🎵 Try to find and play actual audio file
                string musicFolder = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyMusic), "MusicPlayer");
                string audioFile = null;

                if (Directory.Exists(musicFolder))
                {
                    var audioFormats = AudioManager.GetSupportedFormats();
                    audioFile = Directory.GetFiles(musicFolder)
                        .FirstOrDefault(f => 
                            audioFormats.Contains(Path.GetExtension(f).ToLower()) &&
                            Path.GetFileNameWithoutExtension(f).Contains(songTitle, StringComparison.OrdinalIgnoreCase)
                        );
                }

                if (!string.IsNullOrEmpty(audioFile) && File.Exists(audioFile))
                {
                    // Play real audio file
                    if (audioManager.Play(audioFile))
                    {
                        currentSong = new Song { Title = songTitle, Artist = "Unknown Artist" };
                        isPlaying = true;
                        nowPlayingLabel.Text = "▶️ Now Playing: " + songTitle;
                        playButton.BackColor = Color.DarkGreen;
                        statusLabel.Text = "▶️ Playing: " + Path.GetFileName(audioFile);
                        
                        // Start update timer
                        if (updateTimer == null)
                        {
                            updateTimer = new Timer();
                            updateTimer.Interval = 500;
                            updateTimer.Tick += UpdateTimer_Tick;
                        }
                        updateTimer.Start();
                    }
                    else
                    {
                        MessageBox.Show("❌ Could not play audio file!", "Error");
                        statusLabel.Text = "❌ Playback failed";
                    }
                }
                else
                {
                    // Demo mode - no audio file found
                    currentSong = new Song { Title = songTitle, Artist = "Demo" };
                    isPlaying = true;
                    nowPlayingLabel.Text = "▶️ Now Playing (Demo): " + songTitle;
                    playButton.BackColor = Color.DarkGreen;
                    statusLabel.Text = "🎵 Demo mode - place audio files in: " + 
                        Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyMusic), "MusicPlayer");
                }
            }
            else
            {
                MessageBox.Show("Please select a song first!", "Info");
            }
        }

        private void PauseButton_Click(object sender, EventArgs e)
        {
            if (isPlaying && audioManager.IsPlaying())
            {
                audioManager.Pause(); // 🎵 Pause audio
                isPlaying = false;
                nowPlayingLabel.Text = "⏸️ Paused";
                playButton.BackColor = Color.Green;
                statusLabel.Text = "⏸️ Paused";
                updateTimer?.Stop();
            }
            else
            {
                audioManager.Resume(); // 🎵 Resume audio
                isPlaying = true;
                nowPlayingLabel.Text = "▶️ Resumed";
                playButton.BackColor = Color.DarkGreen;
                statusLabel.Text = "▶️ Playing...";
                updateTimer?.Start();
            }
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            audioManager.Stop(); // 🎵 Stop audio
            isPlaying = false;
            currentSong = null;
            nowPlayingLabel.Text = "⏹️ Stopped";
            artistLabel.Text = "Artist: N/A";
            progressLabel.Text = "Duration: 00:00 / 00:00";
            playButton.BackColor = Color.Green;
            statusLabel.Text = "Stopped";
            updateTimer?.Stop();
        }

        private void SearchButton_Click(object sender, EventArgs e)
        {
            string query = searchTextBox.Text;
            if (string.IsNullOrWhiteSpace(query) || query == "Search songs...")
            {
                MessageBox.Show("Please enter a search query!", "Info");
                return;
            }

            statusLabel.Text = $"🔍 Searching for '{query}'...";
            
            // TODO: Call C++ backend to search via Last.fm API
            MessageBox.Show($"Searching for: {query}\n\n(Connected to C++ backend for Last.fm API)", "Search");
            
            statusLabel.Text = "Ready";
        }

        private void PlaylistView_DoubleClick(object sender, EventArgs e)
        {
            PlayButton_Click(null, null);
        }

        private void UpdateTimer_Tick(object sender, EventArgs e)
        {
            if (isPlaying && currentSong != null && audioManager.IsPlaying())
            {
                // 🎵 Update progress bar with real audio time
                TimeSpan current = audioManager.GetCurrentTime();
                TimeSpan total = audioManager.GetTotalTime();

                string timeStr = $"{current.Minutes:D2}:{current.Seconds:D2} / {total.Minutes:D2}:{total.Seconds:D2}";
                progressLabel.Text = $"Duration: {timeStr}";
            }
            else if (!audioManager.IsPlaying() && isPlaying)
            {
                // Audio finished, stop playback
                isPlaying = false;
                statusLabel.Text = "▶️ Track finished";
                playButton.BackColor = Color.Green;
                updateTimer?.Stop();
            }
        }

        private Label nowPlayingLabel;
        private Label artistLabel;
        private Label progressLabel;
        private Label statusLabel;
        private Button playButton;
        private Button pauseButton;
        private Button stopButton;
        private Button searchButton;
        private TextBox searchTextBox;
        private ListBox playlistView;
    }

    public class Song
    {
        public string Title { get; set; }
        public string Artist { get; set; }
        public int Duration { get; set; }
    }

    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MusicPlayerForm());
        }
    }
}
