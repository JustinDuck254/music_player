#!/usr/bin/env pwsh
# ============================================================================
# Music Player - Master Build Script
# Builds both C++ DLL backend and C# WinForms frontend
# ============================================================================

param(
    [Parameter(Mandatory=$false)]
    [ValidateSet("cpp", "csharp", "both", "clean", "run")]
    [string]$Target = "both"
)

$ErrorActionPreference = "Stop"

# Setup .NET PATH
$DotNetPath = "C:\Users\phulo\AppData\Local\Microsoft\dotnet\"
if (Test-Path $DotNetPath) {
    $env:Path = $DotNetPath + ";" + $env:Path
}

# Colors
$Green = "`e[32m"
$Yellow = "`e[33m"
$Red = "`e[31m"
$Cyan = "`e[36m"
$Reset = "`e[0m"

function Write-Status {
    param([string]$Message, [string]$Color = $Green)
    Write-Host $Color$Message$Reset
}

function Write-Error-Message {
    param([string]$Message)
    Write-Host $Red"❌ ERROR: $Message"$Reset
}

function Write-Title {
    param([string]$Title)
    Write-Host "`n$Cyan╔════════════════════════════════════════════════════════════╗$Reset"
    Write-Host "$Cyan║ $Title$Reset"
    Write-Host "$Cyan╚════════════════════════════════════════════════════════════╝$Reset`n"
}

# Get project root
$ProjectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$CppBackend = Join-Path $ProjectRoot "cpp_backend"
$CSharpFrontend = Join-Path $ProjectRoot "csharp_frontend"
$BuildDir = Join-Path $ProjectRoot "build"

# Create build directory
if (-not (Test-Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}

# ============================================================================
# BUILD C++ DLL
# ============================================================================
function Build-CppDll {
    Write-Title "🔨 Building C++ DLL Backend"

    # Set MinGW path
    $env:Path = "C:\msys64\ucrt64\bin;" + $env:Path

    # Verify g++ is available
    try {
        $gppVersion = g++ --version 2>$null | Select-Object -First 1
        Write-Status "✓ Found: $gppVersion"
    } catch {
        Write-Error-Message "g++ not found! Install MinGW-w64 UCRT64"
        return $false
    }

    # Collect source files
    $Headers = Get-ChildItem -Path "$CppBackend\headers" -Filter "*.hpp" | Select-Object -ExpandProperty FullName
    $Sources = Get-ChildItem -Path "$CppBackend\src" -Filter "*.cpp" | Select-Object -ExpandProperty FullName

    if ($Sources.Count -eq 0) {
        Write-Error-Message "No C++ source files found in $CppBackend\src"
        return $false
    }

    Write-Host "Found $($Sources.Count) source files"
    Write-Host "Building DLL with -shared flag...`n"

    # Build command
    $DllOutput = Join-Path $BuildDir "MusicPlayerDLL.dll"
    $Args = @(
        "-I$($CppBackend)\headers",
        "-std=c++17",
        "-O2",
        "-Wall",
        "-shared",
        $Sources,
        "-o", $DllOutput
    )

    Write-Host "$Yellow$($env:Path.Split(';')[0])\g++ ...`n$Reset"

    # Execute build
    & g++ $Args 2>&1
    $BuildSuccess = $?

    if ($BuildSuccess -and (Test-Path $DllOutput)) {
        $DllSize = (Get-Item $DllOutput).Length / 1KB
        Write-Status "✅ DLL built successfully: $DllOutput ($($DllSize)KB)"
        return $true
    } else {
        Write-Error-Message "Failed to build C++ DLL"
        return $false
    }
}

# ============================================================================
# BUILD C# UI
# ============================================================================
function Build-CSharpUI {
    Write-Title "🎨 Building C# WinForms Frontend"

    # Verify dotnet is available
    try {
        $dotnetVersion = dotnet --version
        Write-Status "✓ Found .NET SDK: $dotnetVersion"
    } catch {
        Write-Error-Message ".NET SDK not found! Install from https://dotnet.microsoft.com/download"
        return $false
    }

    $ProjectFile = Join-Path $CSharpFrontend "MusicPlayerUI.csproj"
    
    if (-not (Test-Path $ProjectFile)) {
        Write-Error-Message "Project file not found: $ProjectFile"
        return $false
    }

    # Copy DLL before building
    $DllSrc = Join-Path $BuildDir "MusicPlayerDLL.dll"
    $DllDest = Join-Path $CSharpFrontend "MusicPlayerDLL.dll"
    if (Test-Path $DllSrc) {
        Copy-Item $DllSrc -Destination $DllDest -Force
        Write-Status "✓ Copied DLL to $DllDest"
    }

    Write-Host "Building C# project...`n"

    # Restore and build
    Push-Location $CSharpFrontend
    dotnet restore 2>&1 | Out-Null
    dotnet build -c Release 2>&1
    $BuildSuccess = $?
    Pop-Location

    if ($BuildSuccess) {
        Write-Status "✅ C# UI built successfully"
        return $true
    } else {
        Write-Error-Message "Failed to build C# UI"
        return $false
    }
}

# ============================================================================
# CLEAN BUILD
# ============================================================================
function Clean-Build {
    Write-Title "🧹 Cleaning Build Artifacts"

    # C++ build artifacts
    Remove-Item -Path "$BuildDir\*.dll" -Force -ErrorAction SilentlyContinue
    Remove-Item -Path "$BuildDir\*.exe" -Force -ErrorAction SilentlyContinue
    Remove-Item -Path "$BuildDir\*.o" -Force -ErrorAction SilentlyContinue

    # C# build artifacts
    Remove-Item -Path "$CSharpFrontend\bin" -Recurse -Force -ErrorAction SilentlyContinue
    Remove-Item -Path "$CSharpFrontend\obj" -Recurse -Force -ErrorAction SilentlyContinue

    Write-Status "✅ Clean complete"
}

# ============================================================================
# RUN APPLICATION
# ============================================================================
function Run-Application {
    Write-Title "▶️  Running Music Player"

    $ExePath = Join-Path $CSharpFrontend "bin\Release\net8.0-windows\MusicPlayerUI.exe"
    
    if (-not (Test-Path $ExePath)) {
        Write-Error-Message "Executable not found: $ExePath"
        Write-Host "Please build first: .\build.ps1 -Target both"
        return $false
    }

    Write-Status "Launching: $ExePath`n"
    & $ExePath
}

# ============================================================================
# MAIN
# ============================================================================
try {
    Write-Host "`n$Cyan╔════════════════════════════════════════════════════════════╗$Reset"
    Write-Host "$Cyan║   🎵 Music Player - Build System 🎵                       ║$Reset"
    Write-Host "$Cyan╚════════════════════════════════════════════════════════════╝$Reset`n"

    $Success = $true

    switch ($Target) {
        "cpp" {
            $Success = Build-CppDll
        }
        "csharp" {
            $Success = Build-CSharpUI
        }
        "both" {
            $Success = Build-CppDll
            if ($Success) {
                $Success = Build-CSharpUI
            }
        }
        "clean" {
            Clean-Build
        }
        "run" {
            Run-Application
        }
    }

    if ($Success -and $Target -ne "clean") {
        Write-Host "`n$Green━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$Reset"
        Write-Status "✅ BUILD COMPLETE!"
        Write-Host "$Green━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$Reset"
        Write-Host "`n$Yellow📍 Next steps:$Reset"
        Write-Host "  1. Run: .\build.ps1 -Target run"
        Write-Host "  2. Or:  dotnet run --project csharp_frontend/MusicPlayerUI.csproj"
    }
}
catch {
    Write-Error-Message $_.Exception.Message
    exit 1
}
