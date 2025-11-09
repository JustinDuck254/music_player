╔══════════════════════════════════════════════════════════════════╗
║             ⚙️  .NET SDK INSTALLATION GUIDE ⚙️                   ║
║        For Music Player Project (Windows 64-bit)                 ║
║             Now Using .NET 8.0 LTS (Updated!)                   ║
╚══════════════════════════════════════════════════════════════════╝

# ⚠️ IMPORTANT: .NET 8.0 LTS Update

**We are now using .NET 8.0 LTS** instead of the deprecated .NET 6.0!

| Version | Status | Support Until | Recommendation |
|---------|--------|---|---|
| **.NET 8.0 LTS** | ✅ **CURRENT** | November 2026 | **👈 USE THIS** |
| .NET 6.0 | ❌ End of Life | November 2024 | Deprecated ❌ |
| .NET 9.0 | ✨ Latest | May 2025 | Too new, shorter support |

**Why the upgrade to .NET 8.0?**
- ✅ Long-term support (3 years - until Nov 2026)
- ✅ Stable and production-ready
- ✅ Latest LTS version with active updates
- ✅ Better performance optimizations
- ❌ .NET 6.0 reached end-of-life in November 2024

---

# Why Do You Need .NET SDK?

The C# WinForms frontend requires .NET SDK to:
- Build the C# application
- Run the UI
- Provide runtime libraries

---

## ⚡ FASTEST METHOD (WinGet - Recommended)

**1. Open PowerShell as Administrator**
```powershell
# Right-click PowerShell → Run as Administrator
```

**2. Run installation script for .NET 8.0**
```powershell
cd C:\Users\phulo\Documents\Code\Projects\music_player
.\install-dotnet.ps1 -Method winget -DotNetVersion 8.0
```

**3. Wait for installation (~5-10 minutes)**

**4. Restart PowerShell** (close and open new window)

**5. Verify**
```powershell
dotnet --version
# Should show: 8.0.x or higher
```

---

## 📥 METHOD 2: Manual Download (if WinGet fails)

**1. Visit:** https://dotnet.microsoft.com/download/dotnet/8.0

**2. Download the Windows x64 Installer**
   - Look for ".NET SDK 8.0.x" (not Runtime)
   - Download the installer (.exe file)

**3. Run installer**
   - Double-click the downloaded .exe
   - Click "Install"
   - Wait for completion

**4. Restart PowerShell**
   - Close current PowerShell window
   - Open NEW PowerShell window

**5. Verify**
```powershell
dotnet --version
```

---

## 🍫 METHOD 3: Chocolatey (if you have it)

**1. Open PowerShell as Administrator**

**2. Install .NET 8.0**
```powershell
choco install dotnet-sdk -y --version=8.0
```

**3. Restart PowerShell**

**4. Verify**
```powershell
dotnet --version
```

---

## 🤖 AUTOMATIC INSTALLATION SCRIPT

**Simply run for .NET 8.0 (Recommended):**
```powershell
.\install-dotnet.ps1 -DotNetVersion 8.0
```

**Or specify a different version:**
```powershell
# For .NET 6.0 (if needed for compatibility)
.\install-dotnet.ps1 -DotNetVersion 6.0

# For .NET 9.0 (latest, use with caution)
.\install-dotnet.ps1 -DotNetVersion 9.0
```

---

## ✅ AFTER INSTALLATION

**1. Verify .NET 8.0 is installed**
```powershell
dotnet --version
```

**Output should be:**
```
8.0.x or higher
```

**2. Build the Music Player**
```powershell
.\build.ps1 -Target both
```

**3. Run the app**
```powershell
.\build.ps1 -Target run
```

---

## ⚠️ TROUBLESHOOTING

### Problem: "dotnet not found" after installation

**Solution:**
1. Close PowerShell completely
2. Open a NEW PowerShell window
3. Try again: `dotnet --version`
4. If still fails, restart your computer

### Problem: "Access Denied" error during installation

**Solution:**
1. Right-click PowerShell
2. Select "Run as Administrator"
3. Run installation script again
4. Click "Yes" if prompted by UAC

### Problem: WinGet not available on Windows 10

**Solution:**
1. Download installer manually (Method 2)
2. Or use Chocolatey (Method 3)
3. Or upgrade to Windows 11
4. Or install WinGet from Microsoft Store

### Problem: Installation fails with network error

**Solution:**
1. Check your internet connection
2. Temporarily disable antivirus/firewall
3. Try again
4. If still fails, download manually from https://dotnet.microsoft.com/download/dotnet/8.0

### Problem: Wrong .NET version installed

**Solution - Check what's installed:**
```powershell
dotnet --info
# Shows all installed SDKs and runtimes
```

**If wrong version is installed:**
```powershell
# Remove old version
winget uninstall Microsoft.DotNet.SDK.6.0

# Install correct version
.\install-dotnet.ps1 -DotNetVersion 8.0
```

---

## 📊 WHAT GETS INSTALLED

| Component | Size | Purpose |
|-----------|------|---------|
| .NET 8.0 SDK | ~500 MB | Build & compile |
| Runtime | ~150 MB | Execute apps |
| ASP.NET Core | ~100 MB | Web development (included) |
| Tools | ~50 MB | Compiler, debugger |
| **Total** | **~800 MB** | Everything needed |

---

## 🎯 QUICK START AFTER .NET INSTALL

```powershell
# 1. Navigate to project
cd C:\Users\phulo\Documents\Code\Projects\music_player

# 2. Verify .NET 8.0 is installed
dotnet --version

# 3. Build both C++ and C#
.\build.ps1 -Target both

# 4. Run the app
.\build.ps1 -Target run

# 5. Enjoy! 🎵
```

---

## 📝 COMMAND REFERENCE

| Command | Purpose |
|---------|---------|
| `dotnet --version` | Check installed version |
| `dotnet --info` | Detailed system info |
| `dotnet new winforms` | Create new WinForms project |
| `dotnet build` | Build project |
| `dotnet run` | Run application |
| `dotnet publish` | Create release build |

---

## 🔗 USEFUL LINKS

- **Official .NET 8.0 Download:** https://dotnet.microsoft.com/download/dotnet/8.0
- **WinGet Package (Windows 11):** https://www.microsoft.com/p/app-installer/9nblggh4nns1
- **.NET Documentation:** https://docs.microsoft.com/dotnet/
- **Chocolatey .NET SDK:** https://chocolatey.org/packages/dotnet-sdk

---

## 💡 NEXT STEPS

After .NET 8.0 is installed:

1. **Verify Installation:** `dotnet --version`
2. **Build Project:** `.\build.ps1 -Target both`
3. **Run Application:** `.\build.ps1 -Target run`
4. **Enjoy your Music Player! 🎵**

---

**Questions? Check the troubleshooting section above!**

Last Updated: November 9, 2025
Version: Updated for .NET 8.0 LTS
