using System;
using NAudio.Wave;
using System.IO;

namespace MusicPlayerUI
{
    /// <summary>
    /// AudioManager - Handles real audio playback using NAudio
    /// </summary>
    public class AudioManager : IDisposable
    {
        private IWavePlayer wavePlayer;
        private AudioFileReader audioFileReader;
        private string currentAudioFile;
        private bool isDisposed = false;

        public event EventHandler PlaybackStopped;
        public event EventHandler PlaybackStarted;

        public AudioManager()
        {
            wavePlayer = new WaveOutEvent();
            wavePlayer.PlaybackStopped += WavePlayer_PlaybackStopped;
        }

        /// <summary>
        /// Play an audio file
        /// </summary>
        public bool Play(string filePath)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(filePath) || !File.Exists(filePath))
                {
                    Console.WriteLine($"❌ Audio file not found: {filePath}");
                    return false;
                }

                // Dispose previous reader if exists
                audioFileReader?.Dispose();

                // Create new reader
                audioFileReader = new AudioFileReader(filePath);
                wavePlayer.Init(audioFileReader);
                wavePlayer.Play();

                currentAudioFile = filePath;
                Console.WriteLine($"▶️ Playing: {Path.GetFileName(filePath)}");
                PlaybackStarted?.Invoke(this, EventArgs.Empty);
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"❌ Error playing audio: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Pause playback
        /// </summary>
        public void Pause()
        {
            if (wavePlayer?.PlaybackState == PlaybackState.Playing)
            {
                wavePlayer.Pause();
                Console.WriteLine("⏸️ Paused");
            }
        }

        /// <summary>
        /// Resume playback
        /// </summary>
        public void Resume()
        {
            if (wavePlayer?.PlaybackState == PlaybackState.Paused)
            {
                wavePlayer.Play();
                Console.WriteLine("▶️ Resumed");
            }
        }

        /// <summary>
        /// Stop playback completely
        /// </summary>
        public void Stop()
        {
            if (wavePlayer?.PlaybackState != PlaybackState.Stopped)
            {
                wavePlayer?.Stop();
                Console.WriteLine("⏹️ Stopped");
            }
        }

        /// <summary>
        /// Get current playback state
        /// </summary>
        public PlaybackState GetPlaybackState()
        {
            return wavePlayer?.PlaybackState ?? PlaybackState.Stopped;
        }

        /// <summary>
        /// Get total duration of current track
        /// </summary>
        public TimeSpan GetTotalTime()
        {
            return audioFileReader?.TotalTime ?? TimeSpan.Zero;
        }

        /// <summary>
        /// Get current playback position
        /// </summary>
        public TimeSpan GetCurrentTime()
        {
            return audioFileReader?.CurrentTime ?? TimeSpan.Zero;
        }

        /// <summary>
        /// Set volume (0.0 to 1.0)
        /// </summary>
        public void SetVolume(float volume)
        {
            if (audioFileReader != null)
            {
                volume = Math.Max(0f, Math.Min(1f, volume));
                audioFileReader.Volume = volume;
            }
        }

        /// <summary>
        /// Get current volume
        /// </summary>
        public float GetVolume()
        {
            return audioFileReader?.Volume ?? 0.5f;
        }

        /// <summary>
        /// Check if currently playing
        /// </summary>
        public bool IsPlaying()
        {
            return wavePlayer?.PlaybackState == PlaybackState.Playing;
        }

        /// <summary>
        /// Get supported audio formats
        /// </summary>
        public static string[] GetSupportedFormats()
        {
            return new[] { ".mp3", ".wav", ".m4a", ".flac", ".wma" };
        }

        private void WavePlayer_PlaybackStopped(object sender, StoppedEventArgs e)
        {
            Console.WriteLine("⏹️ Playback stopped");
            PlaybackStopped?.Invoke(this, EventArgs.Empty);
        }

        public void Dispose()
        {
            if (!isDisposed)
            {
                Stop();
                audioFileReader?.Dispose();
                wavePlayer?.Dispose();
                isDisposed = true;
            }
        }
    }
}
