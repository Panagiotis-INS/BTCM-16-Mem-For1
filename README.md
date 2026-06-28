# BTCMP-16 — Digital Forensics Lab Environment
applied to BTCMP-16- Memory Forensics Evidence Gathering
## Overview

This lab environment is built around **Digital Forensics** scenarios.

---

## Topology

| Host | Role | Network | CIDR | IP |
|------|------|---------|------|----|
| wavm | Analyst Workstation (Windows Server 2019) | access-switch | 10.10.10.0/24 | 10.10.10.3 |
| wvvm | Victim/Evidence Machine (Windows Server 2019) | access-switch | 10.10.10.0/24 | 10.10.10.4 |
| lvvm | Linux Analyst Workstation (Xubuntu Noble) | access-switch | 10.10.10.0/24 | 10.10.10.5 |
| router | Network Router (Debian 12) | access-switch | 10.10.10.0/24 | 10.10.10.1 |

---

## Machines

### WAVM — Analyst Workstation (Windows Server 2019)
User `LocalAdmin` / `Password123!` (admin, RDP enabled).

**Software:**
- DumpIt (memory acquisition; extracted to `C:\Tools\DumpIt`, Desktop shortcut on public Desktop)
- Sysinternals Strings (extracted to `C:\Tools\Strings`)
- SMB share `\\wavm\investigation` → `C:\Investigation` (Everyone read/write, share + NTFS)

---

### WVVM — Victim / Evidence Machine (Windows Server 2019)
User `LocalAdmin` / `Password123!` (admin, RDP enabled).

**Software:**
- `std_service.exe` copied to `C:\ProgramData\StdService\` and registered under `HKLM\...\CurrentVersion\Run` so it launches on every user logon (keeps the target string resident in memory for acquisition).
- DumpIt (memory acquisition; extracted to `C:\Tools\DumpIt`, Desktop shortcut on public Desktop).
- Sysinternals Strings (extracted to `C:\Tools\Strings`).
- SMB share `\\wvvm\investigation` → `C:\Investigation` (Everyone read/write, share + NTFS).

---

### LVVM — Linux Analyst Workstation (Xubuntu Noble)
User `Maria` / `Password123!` (SSH + sudo enabled).

**Software:**
- `git`, `gcc`
- `std_service` — Linux equivalent of `std_service.exe`. Compiled from `std_service_linux.c` to `/usr/local/bin/std_service`; daemonizes, parks the flag string in an `mlock`-pinned page, and idles in a loop. Auto-launches on every login via `/etc/profile.d/std_service.sh` (SSH and console) and `/etc/xdg/autostart/std_service.desktop` (graphical sessions).
- AVML (Linux memory acquisition, from Microsoft) — installed to `/opt/avml/avml` with a symlink at `/usr/local/bin/avml`. Single static binary, no kernel module; produces LiME-format dumps. Run as `sudo avml /path/to/memory.lime`.

---

## Notes
- The `community.windows` Ansible collection is required for the `win_unzip` module.
- The `ansible-role-user-access` role (cyberrangecz, v1.0.0) is used to provision the Linux user on `lvvm`.
