╔══════════════════════════════════════════════════════════════════╗
║           ⚠️  .NET SDK NOT FOUND - HERE'S THE FIX ⚠️            ║
╚══════════════════════════════════════════════════════════════════╝

# Problem
```
The .NET SDK cannot be located:
'dotnet' is not recognized as an internal or external command
```

# Root Cause
Your system does **not have .NET SDK** installed. The C# WinForms 
frontend requires .NET 6.0 SDK to build and run.

---

# Solution (Choose ONE)

## ✅ OPTION 1: Automatic Installation (RECOMMENDED)

**Run this in PowerShell:**
```powershell
cd C:\Users\phulo\Documents\Code\Projects\music_player
.\install-dotnet.ps1
```

This script will:
- Check if WinGet is available
- Install .NET 6.0 SDK automatically
- Verify the installation
- Tell you when to restart PowerShell

---

## ✅ OPTION 2: Manual Download

**1. Visit:** https://dotnet.microsoft.com/download/dotnet/6.0

**2. Click "Download .NET SDK 6.0.x" (Windows x64)**
   - Select "Installer" format
   - Choose Windows 64-bit

**3. Run the downloaded .exe file**

**4. Follow the installation wizard**

**5. Restart your computer** (or at least PowerShell)

---

## ✅ OPTION 3: Using Chocolatey

**If you already have Chocolatey installed:**
```powershell
# Run as Administrator
choco install dotnet-sdk -y
```

---

# After Installation

**IMPORTANT:** Close PowerShell and **open a NEW window**

Then verify:
```powershell
dotnet --version
```

Should output something like: `6.0.x` or higher

---

# Then Build & Run

```powershell
# Navigate to project
cd C:\Users\phulo\Documents\Code\Projects\music_player

# Build both C++ and C#
.\build.ps1 -Target both

# Run the app
.\build.ps1 -Target run
```

---

# More Help

**Read:** `docs/INSTALL_DOTNET.md` (detailed guide with screenshots)

---

# Common Issues

### Issue: Still "dotnet not found" after install
**Fix:** Close PowerShell COMPLETELY and open a NEW window

### Issue: "Access Denied" error
**Fix:** Right-click PowerShell → Run as Administrator

### Issue: WinGet not available
**Fix:** Download manually from the link above

---

# What Gets Installed

- **.NET 6.0 SDK** (~500 MB)
  - C# compiler
  - Build tools
  - Runtime libraries
  
Total: ~700 MB

---

**Ready? Run:** `.\install-dotnet.ps1`

Last Updated: November 9, 2025
