#!/usr/bin/env pwsh
<#
.SYNOPSIS
    Music Player - Quick Build & Run Script
    Tự động build C++ + C# và chạy ứng dụng
    
.EXAMPLE
    .\quick-run.ps1
#>

param(
    [Parameter(Mandatory=$false)]
    [ValidateSet("build", "run", "buildrun")]
    [string]$Mode = "buildrun"
)

$ErrorActionPreference = "Stop"

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

# Setup paths
$ProjectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$DotNetPath = "C:\Users\phulo\AppData\Local\Microsoft\dotnet\"
$MsysPath = "C:\msys64\ucrt64\bin"

# Add to PATH
if (Test-Path $DotNetPath) {
    $env:Path = $DotNetPath + ";" + $env:Path
}
if (Test-Path $MsysPath) {
    $env:Path = $MsysPath + ";" + $env:Path
}

# Verify tools
Write-Title "🔧 Verifying Tools"
try {
    $gppVersion = g++ --version 2>$null | Select-Object -First 1
    Write-Status "✓ g++: $gppVersion"
} catch {
    Write-Host "$Red✗ g++ not found!$Reset"
    exit 1
}

try {
    $dotnetVersion = dotnet --version
    Write-Status "✓ .NET: $dotnetVersion"
} catch {
    Write-Host "$Red✗ .NET SDK not found!$Reset"
    exit 1
}

# Execute build
if ($Mode -eq "build" -or $Mode -eq "buildrun") {
    Write-Title "🏗️  Building..."
    cd $ProjectRoot
    .\build.ps1 -Target both
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "$Red✗ Build failed!$Reset"
        exit 1
    }
}

# Execute run
if ($Mode -eq "run" -or $Mode -eq "buildrun") {
    Write-Title "🎵 Launching Music Player..."
    cd $ProjectRoot
    .\build.ps1 -Target run
}

Write-Host "`n$Green✅ Done!$Reset`n"
