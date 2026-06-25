# BTCMP-16 — Digital Forensics Lab Environment - Windows
applied to BTCMP-16- Memory Forensics Evidence Gathering
## Overview

This lab environment is built around **Digital Forensics** scenarios.

---

## Topology

| Host | Role | Network | CIDR | IP |
|------|------|---------|------|----|
| wavm | Analyst Workstation (Windows Server 2019) | access-switch | 10.10.10.0/24 | 10.10.10.3 |
| wvvm | Victim/Evidence Machine (Windows Server 2019) | access-switch | 10.10.10.0/24 | 10.10.10.4 |
| router | Network Router (Debian 12) | access-switch | 10.10.10.0/24 | 10.10.10.1 |

---

## Machines

### WAVM — Analyst Workstation (Windows Server 2019)
User `LocalAdmin` / `Password123!` (admin, RDP enabled).

**Software:**
- Git (via Chocolatey)
- Autopsy / Sleuth Kit 4.21.0 (via Chocolatey)
- Strawberry Perl (via Chocolatey)
- CodeMeter Runtime (installed silently from GitHub release)
- FTK Imager (extracted to `C:\Tools\FTKImager`)
- DumpIt (memory acquisition; extracted to `C:\Tools\DumpIt`, Desktop shortcut on public Desktop)

**Notes:**
- FTK Imager is not installed via an installer — it is extracted directly to `C:\Tools\FTKImager` and run as a portable application.
- CodeMeter Runtime is required as a dependency for certain forensic tools and is installed silently.

---

### WVVM — Victim / Evidence Machine (Windows Server 2019)
User `LocalAdmin` / `Password123!` (admin, RDP enabled).

**Software:**
- `std_service.exe` copied to `C:\ProgramData\StdService\` and registered under `HKLM\...\CurrentVersion\Run` so it launches on every user logon (keeps the target string resident in memory for acquisition).

---

## Notes
- The `community.windows` Ansible collection is required for the `win_unzip` module.
- The `chocolatey.chocolatey` collection (v1.5.1) is required for Chocolatey-based installs.
