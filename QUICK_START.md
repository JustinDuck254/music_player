# 🎵 Music Player - Quick Launch Guide

## 🚀 Cách chạy ứng dụng:

### ✅ Cách 1: Double-click (DỄ NHẤT)
1. Mở File Explorer
2. Vào folder: `c:\Users\phulo\Documents\Code\Projects\music_player\`
3. **Double-click** `RUN.bat`
4. Chờ build xong, ứng dụng sẽ chạy tự động 🎉

---

### ✅ Cách 2: PowerShell (nhanh)
```powershell
cd c:\Users\phulo\Documents\Code\Projects\music_player
.\quick-run.ps1
```

---

### ✅ Cách 3: PowerShell (full control)
```powershell
cd c:\Users\phulo\Documents\Code\Projects\music_player

# Chỉ build
.\build.ps1 -Target both

# Chỉ chạy
.\build.ps1 -Target run

# Clean build artifacts
.\build.ps1 -Target clean
```

---

## 📋 Tệp tin quan trọng:

| Tệp | Mục đích |
|-----|---------|
| `RUN.bat` | **👈 Double-click để chạy** |
| `quick-run.ps1` | Script tự động hóa |
| `build.ps1` | Master build script |
| `install-dotnet.ps1` | Cài đặt .NET 8.0 |

---

## ⚙️ Các lệnh build:

```powershell
# Build C++ + C# + Run
.\build.ps1 -Target both

# Chỉ build C++
.\build.ps1 -Target cpp

# Chỉ build C#
.\build.ps1 -Target csharp

# Chỉ chạy (không build)
.\build.ps1 -Target run

# Clean all
.\build.ps1 -Target clean
```

---

## 🛠️ Xử sự cố:

**Q: Ứng dụng không chạy?**
- A: Kiểm tra .NET: `dotnet --version` (phải là 8.0.x)
- A: Kiểm tra g++: `g++ --version`

**Q: Build lỗi?**
- A: Clean trước: `.\build.ps1 -Target clean`
- A: Build lại: `.\build.ps1 -Target both`

**Q: .NET chưa cài?**
- A: Chạy: `.\install-dotnet.ps1 -DotNetVersion 8.0`

---

**Thêm info**: Xem `README.md` hoặc `docs/INSTALL_DOTNET.md`
