#!/usr/bin/env pwsh
<#
.SYNOPSIS
    Create test WAV audio files for Music Player testing
    
.DESCRIPTION
    Generates simple sine wave WAV files that can be played by the Music Player
    Files are saved to: %USERPROFILE%\Music\MusicPlayer\
#>

$ErrorActionPreference = "Stop"

Write-Host "`n╔════════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║  🎵 Test Audio File Generator for Music Player  🎵        ║" -ForegroundColor Cyan
Write-Host "╚════════════════════════════════════════════════════════════╝`n" -ForegroundColor Cyan

$musicFolder = Join-Path $env:USERPROFILE "Music\MusicPlayer"

# Create folder if doesn't exist
if (-not (Test-Path $musicFolder)) {
    New-Item -ItemType Directory -Path $musicFolder -Force | Out-Null
    Write-Host "✅ Created folder: $musicFolder`n" -ForegroundColor Green
}

# Function to create a simple WAV file
function Create-TestWavFile {
    param(
        [string]$FileName,
        [string]$DisplayName,
        [int]$DurationSeconds = 5,
        [int]$Frequency = 440  # A4 note
    )

    Write-Host "🎵 Generating: $DisplayName" -ForegroundColor Yellow

    $FilePath = Join-Path $musicFolder $FileName

    # WAV parameters
    $SampleRate = 44100
    $BitsPerSample = 16
    $Channels = 2
    $NumSamples = $SampleRate * $DurationSeconds

    # Create WAV header
    $BytesPerSecond = $SampleRate * $Channels * ($BitsPerSample / 8)
    $BytesPerSample = $Channels * ($BitsPerSample / 8)

    # WAV file structure
    [byte[]]$WavHeader = @()
    
    # "RIFF" chunk descriptor
    $WavHeader += [System.Text.Encoding]::ASCII.GetBytes("RIFF")
    $fileSize = 36 + ($NumSamples * $BytesPerSample)
    $WavHeader += [BitConverter]::GetBytes($fileSize)
    $WavHeader += [System.Text.Encoding]::ASCII.GetBytes("WAVE")
    
    # "fmt " sub-chunk
    $WavHeader += [System.Text.Encoding]::ASCII.GetBytes("fmt ")
    $WavHeader += [BitConverter]::GetBytes([uint32]16)  # Subchunk1Size
    $WavHeader += [BitConverter]::GetBytes([uint16]1)   # AudioFormat (PCM)
    $WavHeader += [BitConverter]::GetBytes([uint16]$Channels)
    $WavHeader += [BitConverter]::GetBytes([uint32]$SampleRate)
    $WavHeader += [BitConverter]::GetBytes([uint32]$BytesPerSecond)
    $WavHeader += [BitConverter]::GetBytes([uint16]$BytesPerSample)
    $WavHeader += [BitConverter]::GetBytes([uint16]$BitsPerSample)
    
    # "data" sub-chunk
    $WavHeader += [System.Text.Encoding]::ASCII.GetBytes("data")
    $WavHeader += [BitConverter]::GetBytes([uint32]($NumSamples * $BytesPerSample))

    # Generate audio data (simple sine wave)
    [byte[]]$AudioData = @()
    $amplitude = 30000  # Moderate volume
    
    for ($i = 0; $i -lt $NumSamples; $i++) {
        $t = [double]$i / $SampleRate
        
        # Create a simple tone that fades in/out
        $fadeIn = if ($i -lt $SampleRate * 0.1) { $i / ($SampleRate * 0.1) } else { 1.0 }
        $fadeOut = if ($i -gt $NumSamples - $SampleRate * 0.1) { ($NumSamples - $i) / ($SampleRate * 0.1) } else { 1.0 }
        $envelope = $fadeIn * $fadeOut
        
        $sample = [int]($amplitude * [Math]::Sin(2 * [Math]::PI * $Frequency * $t) * $envelope)
        $sample = [Math]::Max(-32768, [Math]::Min(32767, $sample))
        
        # Write sample twice for stereo
        $bytes = [BitConverter]::GetBytes([int16]$sample)
        $AudioData += $bytes
        $AudioData += $bytes
    }

    # Combine header and audio data
    $WavFile = $WavHeader + $AudioData

    # Write to file
    [System.IO.File]::WriteAllBytes($FilePath, $WavFile)
    
    $FileSizeMB = [math]::Round(($FilePath | Get-Item).Length / 1MB, 2)
    Write-Host "   ✅ Created: $FileName ($FileSizeMB MB)`n" -ForegroundColor Green
}

# Create test files with different frequencies
Write-Host "Creating test audio files...`n" -ForegroundColor Cyan

Create-TestWavFile -FileName "Test-Tone-A4.wav" -DisplayName "Test Tone (A4 - 440Hz)" -DurationSeconds 5 -Frequency 440
Create-TestWavFile -FileName "Test-Tone-C4.wav" -DisplayName "Test Tone (C4 - 261Hz)" -DurationSeconds 5 -Frequency 261
Create-TestWavFile -FileName "Test-Tone-G4.wav" -DisplayName "Test Tone (G4 - 392Hz)" -DurationSeconds 5 -Frequency 392

# Summary
Write-Host "════════════════════════════════════════════════════════════" -ForegroundColor Cyan
Write-Host "✅ All test files created successfully!" -ForegroundColor Green
Write-Host "📁 Location: $musicFolder" -ForegroundColor Green
Write-Host "`nYou can now:" -ForegroundColor Yellow
Write-Host "  1. Run the Music Player"
Write-Host "  2. Click 'Refresh' to load songs"
Write-Host "  3. Select a song and click 'Play' to hear the test tone`n" -ForegroundColor Yellow
