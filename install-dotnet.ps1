#!/usr/bin/env pwsh
# ============================================================================
# .NET SDK Installation Script
# Automatically installs .NET 6.0 SDK for Music Player project
# ============================================================================

param(
    [Parameter(Mandatory=$false)]
    [ValidateSet("winget", "download", "choco")]
    [string]$Method = "winget",
    [Parameter(Mandatory=$false)]
    [ValidateSet("6.0", "8.0", "9.0")]
    [string]$DotNetVersion = "8.0"
)

$ErrorActionPreference = "Continue"

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

function Write-Title {
    param([string]$Title)
    Write-Host "`n$Cyan╔════════════════════════════════════════════════════════════╗$Reset"
    Write-Host "$Cyan║ $Title$Reset"
    Write-Host "$Cyan╚════════════════════════════════════════════════════════════╝$Reset`n"
}

# Check if .NET is already installed
Write-Title ".NET SDK Installation Helper"

Write-Host "Checking if .NET is already installed...$Reset`n"
try {
    $dotnetVersion = dotnet --version
    Write-Status "✅ .NET $dotnetVersion is already installed!`n"
    exit 0
}
catch {
    Write-Host "$Red✗ .NET not found$Reset`n"
}

# Installation methods
function Install-DotNet-Winget {
    Write-Title "Installing .NET $DotNetVersion SDK via WinGet"
    
    Write-Host "Checking if winget is available...$Reset`n"
    try {
        $wingetVersion = winget --version
        Write-Status "✓ WinGet found: $wingetVersion`n"
    }
    catch {
        Write-Host "$Red✗ WinGet not found. Please install Windows Package Manager first.`n$Reset"
        Write-Host "Download from: https://www.microsoft.com/p/app-installer/9nblggh4nns1`n"
        return $false
    }

    # Convert version to package ID
    $packageId = "Microsoft.DotNet.SDK.$DotNetVersion"
    Write-Host "Installing $packageId...$Reset`n"
    winget install $packageId --accept-package-agreements --accept-source-agreements
    
    if ($LASTEXITCODE -eq 0) {
        Write-Status "✅ Installation successful!`n"
        return $true
    } else {
        Write-Host "$Red✗ Installation failed$Reset`n"
        return $false
    }
}

function Install-DotNet-Download {
    Write-Title "Downloading .NET $DotNetVersion SDK Installer"
    
    $downloadUrl = "https://dotnet.microsoft.com/download/dotnet/$DotNetVersion"
    Write-Host "Opening download page in browser...$Reset`n"
    Write-Host "URL: $Cyan$downloadUrl$Reset`n"
    
    Start-Process $downloadUrl
    
    Write-Host "$Yellow" + "=" * 60 + "$Reset"
    Write-Host "Manual Installation Steps:"
    Write-Host "$Yellow" + "=" * 60 + "$Reset`n"
    Write-Host "1. Download the SDK installer for your system (Windows x64)"
    Write-Host "2. Run the installer"
    Write-Host "3. Follow the installation wizard"
    Write-Host "4. When done, restart PowerShell"
    Write-Host "5. Verify with: dotnet --version`n"
    
    Write-Host "$Cyan" + "=" * 60 + "$Reset"
    Write-Host "Waiting for installer to complete..."
    Write-Host "Press Enter when done... $Reset"
    Read-Host
    
    # Verify installation
    try {
        $dotnetVersion = dotnet --version
        Write-Status "✅ Installation successful! .NET $dotnetVersion is now installed`n"
        return $true
    }
    catch {
        Write-Host "$Red✗ .NET still not found. Please restart PowerShell and try again$Reset`n"
        return $false
    }
}

function Install-DotNet-Choco {
    Write-Title "Installing .NET 6.0 SDK via Chocolatey"
    
    Write-Host "Checking if Chocolatey is available...$Reset`n"
    try {
        $chocoVersion = choco --version
        Write-Status "✓ Chocolatey found: $chocoVersion`n"
    }
    catch {
        Write-Host "$Red✗ Chocolatey not found.`n$Reset"
        Write-Host "Install from: https://chocolatey.org/install`n"
        return $false
    }

    Write-Host "Installing .NET 6.0 SDK...$Reset`n"
    choco install dotnet-sdk -y
    
    if ($LASTEXITCODE -eq 0) {
        Write-Status "✅ Installation successful!`n"
        return $true
    } else {
        Write-Host "$Red✗ Installation failed$Reset`n"
        return $false
    }
}

# Execute installation
$success = $false

switch ($Method) {
    "winget" {
        $success = Install-DotNet-Winget
        if (-not $success) {
            Write-Host "`n$Yellow" + "=" * 60 + "$Reset"
            Write-Host "Falling back to manual download..."
            Write-Host "$Yellow" + "=" * 60 + "$Reset`n"
            $success = Install-DotNet-Download
        }
    }
    "download" {
        $success = Install-DotNet-Download
    }
    "choco" {
        $success = Install-DotNet-Choco
    }
}

# Final message
if ($success) {
    Write-Status "`n✅ INSTALLATION COMPLETE!`n"
    Write-Host "You can now:"
    Write-Host "  1. Close this terminal"
    Write-Host "  2. Open a new PowerShell window"
    Write-Host "  3. Build the Music Player: .\build.ps1 -Target both`n"
} else {
    Write-Host "$Red`n✗ Installation could not be completed.`n$Reset"
    Write-Host "Please manually install .NET 6.0 SDK from:"
    Write-Host "https://dotnet.microsoft.com/download/dotnet/6.0`n"
}
