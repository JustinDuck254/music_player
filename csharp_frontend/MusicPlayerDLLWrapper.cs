using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

namespace MusicPlayerUI
{
    /// <summary>
    /// P/Invoke wrapper for C++ DLL
    /// </summary>
    public static class MusicPlayerDLL
    {
        private const string DLL_NAME = "MusicPlayerDLL.dll";

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct SongData
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
            public string title;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
            public string artist;

            public int duration;
        }

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitBackend();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetPlaylistSize();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int AddSongToPlaylist(string title, string artist, int duration);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int RemoveSongFromPlaylist(int index);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetPlaylistSong(int index, ref SongData outSong);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ClearPlaylist();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetAllSongs(SongData[] outArray, int maxSize);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void PlaySong(int index);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void PauseSong();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ResumeSong();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void StopSong();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetCurrentSongIndex();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetPlaybackState(); // 0=STOPPED, 1=PLAYING, 2=PAUSED

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern float GetProgress();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SearchFromLastFM(string query, SongData[] outArray, int maxResults);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetTopTracks(SongData[] outArray, int maxResults);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SavePlaylist(string filename);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LoadPlaylist(string filename);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShutdownBackend();
    }

    /// <summary>
    /// Helper class to manage backend calls
    /// </summary>
    public class MusicPlayerBackend
    {
        public static List<Song> GetPlaylist()
        {
            var playlist = new List<Song>();
            int size = MusicPlayerDLL.GetPlaylistSize();

            for (int i = 0; i < size; i++)
            {
                var songData = new MusicPlayerDLL.SongData();
                if (MusicPlayerDLL.GetPlaylistSong(i, ref songData) == 0)
                {
                    playlist.Add(new Song
                    {
                        Title = songData.title,
                        Artist = songData.artist,
                        Duration = songData.duration
                    });
                }
            }

            return playlist;
        }

        public static List<Song> SearchLastFM(string query, int maxResults = 20)
        {
            var songs = new List<Song>();
            var resultsArray = new MusicPlayerDLL.SongData[maxResults];

            int count = MusicPlayerDLL.SearchFromLastFM(query, resultsArray, maxResults);

            for (int i = 0; i < count; i++)
            {
                songs.Add(new Song
                {
                    Title = resultsArray[i].title,
                    Artist = resultsArray[i].artist,
                    Duration = resultsArray[i].duration
                });
            }

            return songs;
        }

        public static List<Song> GetTopTracks(int maxResults = 20)
        {
            var songs = new List<Song>();
            var resultsArray = new MusicPlayerDLL.SongData[maxResults];

            int count = MusicPlayerDLL.GetTopTracks(resultsArray, maxResults);

            for (int i = 0; i < count; i++)
            {
                songs.Add(new Song
                {
                    Title = resultsArray[i].title,
                    Artist = resultsArray[i].artist,
                    Duration = resultsArray[i].duration
                });
            }

            return songs;
        }

        public static void PlaySong(int index) => MusicPlayerDLL.PlaySong(index);
        public static void PauseSong() => MusicPlayerDLL.PauseSong();
        public static void ResumeSong() => MusicPlayerDLL.ResumeSong();
        public static void StopSong() => MusicPlayerDLL.StopSong();

        public static int GetCurrentSongIndex() => MusicPlayerDLL.GetCurrentSongIndex();
        public static PlaybackState GetPlaybackState() => (PlaybackState)MusicPlayerDLL.GetPlaybackState();
        public static float GetProgress() => MusicPlayerDLL.GetProgress();

        public static int AddSong(string title, string artist, int duration)
            => MusicPlayerDLL.AddSongToPlaylist(title, artist, duration);

        public static void RemoveSong(int index)
            => MusicPlayerDLL.RemoveSongFromPlaylist(index);

        public static void SavePlaylist(string filename)
            => MusicPlayerDLL.SavePlaylist(filename);

        public static void LoadPlaylist(string filename)
            => MusicPlayerDLL.LoadPlaylist(filename);
    }

    public enum PlaybackState
    {
        STOPPED = 0,
        PLAYING = 1,
        PAUSED = 2
    }
}
