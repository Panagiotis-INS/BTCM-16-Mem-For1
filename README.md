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

**Disks:**
| Disk | Size | Description |
|------|------|-------------|
| PhysicalDrive0 | 60 GB | OS disk |
| PhysicalDrive1 | 5 GB | Forensic evidence disk — NTFS image (`ntfs-img-kw-1.dd`) written raw, **read-only** |

**Notes:**
- The 5GB disk has the `ntfs-img-kw-1.dd` image written directly to it via PowerShell raw stream and is set write-protected via `diskpart` (`attributes disk set readonly`). This ensures a consistent, repeatable hash for every deployment.
- FTK Imager is not installed via an installer — it is extracted directly to `C:\Tools\FTKImager` and run as a portable application.
- CodeMeter Runtime is required as a dependency for certain forensic tools and is installed silently.

---

### WVVM — Victim / Evidence Machine (Windows Server 2019)
User `LocalAdmin` / `Password123!` (admin, RDP enabled). **Hidden from students.**

**Software:** None — bare Windows Server 2019 installation.

---

## Notes
- The `community.windows` Ansible collection is required for the `win_unzip` module.
- The `chocolatey.chocolatey` collection (v1.5.1) is required for Chocolatey-based installs.
