# Platinum QOL Features

***NOTE:*** This repository is deprecated; I highly recommend not making use of it, as it breaks the evolution sequence for unknown reasons.

This repository contains a host of QOL features that can be applied to Pokemon Platinum via C injection. Code written herein is based on the US version of Pokemon Platinum, specifically Rev 1.

This repository is also structured to be extensible as a C injection template with the requisite infrastructure already set up for an aspiring hacker.

## Table of Contents

- [Features](#features)
- [Setup Instructions](#setup-instructions)
  - [Windows](#windows)
  - [Mac OSX](#mac-osx)
  - [Linux](#linux)
- [Build Instructions](#build-instructions)
- [Credits](#credits)

## Features

Each of these features is controlled by a flag defined in [this file](include/config.h). If there is any feature you do not want to include, then modify that file to exclude it.

<details>
<summary>- Summary Screen with IVs, EVs, and Nature Highlighting</summary>
<br>

Press **R** to change to IVs, **L** to change to EVs, and **SELECT** to change to actual stats.

![summary screen preview](previews/summary_screen.gif)
</details>
<details>
<summary>- Unlimited TMs</summary>
<br>

![infinite TMs](previews/infinite_tms.png)
</details>
<details>
<summary>- HM Usage Based on Possession</summary>
<br>

Cut, Rock Smash, Strength, Surf, Rock Climb, and Waterfall are all usable via overworld interaction events.

Fly and Defog will appear on the move selection screen for any Pokemon that can learn them.

![HMs usable without knowing the move](previews/usable_hms.gif)
</details>
<details>
<summary>- Double-tap B to RUN in a Wild Battle</summary>
<br>

![press B to run in a wild battle](previews/b_to_run.gif)
</details>
<details>
<summary>- Faster HP Bar Drain</summary>
<br>

![increased hp bar speed](previews/hp_bar.gif)
</details>

There are also a few bugfixes to vanilla Platinum included in this repo:

- Double-battle bosses now use the correct music
- Fire Fang no longer pierces Wonder Guard regardless of effectiveness
- Trainer Pokemon with different forms now use the correct base stats
- Trainer Pokemon can now have abilities other than slot 1 specified

## Setup Instructions

### Windows

Windows builds are based on WSL. If you do not have WSL set up (or do not know if you do), follow the instructions in [Setting up WSL](#setting-up-wsl) below.

If you already have a WSL environment set up, proceed to [Further Instructions](#further-instructions).

#### Setting up WSL

1. Enable Windows Subsystem for Linux.
    1. Open your command prompt as Administrator.
        1. In the search bar in the Start Menu, search for "cmd".
        2. Right-click on **Command Prompt**.
        3. Click **Run as Administrator**.
    2. Run the following command: `dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all`.
    3. After the process completes, you will be prompted to restart your PC. Type "Y" and press **Enter** to restart.
    4. During the reboot process, enable virtualization in your BIOS.
        - The exact steps here will vary by system and the exact make/model of your PC's motherboard. You can find a general sketch of instructions [here](https://bce.berkeley.edu/enabling-virtualization-in-your-pc-bios.html).
2. Install Ubuntu.
    1. In the search bar in the Start Menu, search for "store" and open **Microsoft Store**.
    2. In the search bar of the window that opens, search for "Ubuntu".
    3. Click the blue **Get** button.
    4. Once installation is complete, launch Ubuntu from its page in the Microsoft Store to finish setup.
        - This will start a setup procedure that may take some time to complete.
    5. Once the setup procedure is complete, choose a username and password for the system.
3. Open WSL.
    1. Open the **Run** window by pressing the **Windows Key** and **R** at the same time.
    2. Type `wsl` into the window and press **Enter**.
4. Update WSL.
    1. In WSL, type `sudo apt update` and press **Enter**.
    2. After the update process completes, type `sudo apt upgrade` and press **Enter**.
        - This process may take a long time.
        - You may be prompted to confirm that WSL should restart automatically during package updates. Select **Yes** and press **Enter**.

#### Further Instructions

1. Download and install devkitPro-pacman.
    - In WSL, run the following commands:
        1. `wget https://apt.devkitpro.org/install-devkitpro-pacman`
        2. `chmod +x ./install-devkitpro-pacman`
        3. `sudo ./install-devkitpro-pacman`
2. Install necessary packages.
    - In WSL, run the following commands:
        1. `sudo apt-get install build-essential git libpng-dev gdebi-core python3 python3-pip cmake automake`
        2. `pip3 install ndspy`
        3. `dkp-pacman -S gba-dev`
3. Restart WSL, then run the following commands.
    1. `export DEVKITPRO=/opt/devkitpro`
    2. `echo "export DEVKITPRO=$DEVKITPRO" >> ~/.bashrc`
    3. `export DEVKITARM=$DEVKITPRO/devkitARM`
    4. `echo "export DEVKITARM=$DEVKITARM" >> ~/.bashrc`
    5. `cd Documents`
    6. `git clone https://github.com/lhearachel/plat-qol.git`
        - This will create a new directory `plat-qol`, which will be short-handed as "the project directory" from hereon.

### Mac OSX

TBD

### Linux

#### Debian-based (e.g. Debian, Ubuntu, Linux Mint)

1. Download and install devkitPro-pacman.
    - Follow the instructions listed [here](https://github.com/devkitPro/pacman/releases).
1. Install necessary packages.
    - In Terminal, run the following commands:
        1. `sudo apt install libpng-dev build-essential cmake python3-pip git automake`
        2. `pip3 install ndspy`
        3. `dkp-pacman -S gba-dev`

#### Arch-based (e.g. Arch Linux, Endeavour)

1. Import keys for devkitPro's repository.
    - Follow the instructions listed [here](https://devkitpro.org/wiki/devkitPro_pacman#Customising_Existing_Pacman_Install).
1. Install necessary packages.
    - In Terminal, run the following commands:
        1. `sudo pacman -S libpng base-devel cmake python-pip git automake gba-dev`
        2. `pip3 install ndspy`

#### Further Instructions (Platform Agnostic)

1. Restart Terminal, then run the following commands.
    1. `export DEVKITPRO=/opt/devkitpro`
    2. `echo "export DEVKITPRO=$DEVKITPRO" >> ~/.bashrc`
    3. `export DEVKITARM=$DEVKITPRO/devkitARM`
    4. `echo "export DEVKITARM=$DEVKITARM" >> ~/.bashrc`
    5. `cd Documents`
    6. `git clone https://github.com/lhearachel/plat-qol.git`
        - This will create a new directory `plat-qol`, which will be short-handed as "the project directory" from hereon.

## Build Instructions

1. Setup your ROM.
    - Your base ROM *must* be a verified dump of **Pokemon Platinum (US)**.
    - Perform any and all edits to scripts, maps, events, etc. to your ROM *before* you install this repository.
    - Make an additional edit to the common scripts for the game:
        1. Open your ROM in DSPRE.
        2. Open the Script Editor and navigate to Script File 409.
        3. Click **Import File**.
        4. Choose the file `extra/Script File 409.scr` included in this project.
        5. Save your ROM.
2. Place your ROM.
    - Place your finalized ROM into the project directory and rename it to `rom.nds`.
3. Navigate to the project directory in Terminal/WSL.
4. Download and build necessary tools.
    - Run `make build_tools -j$(nprocs)`. This process will download the source code for tools needed by the injection routine and compile them for you.
5. Make your ROM.
    - Run `make -j$(nprocs)`.
6. Test your ROM.
    - After the previous `make` process completes, a new file will appear in this folder named `test.nds`. This ROM will contain all injected routines and modifications from this project.
    - The `test.nds` ROM should be judged as the *final* copy of your ROM for any patch-creation routines! Do *not* attempt to modify it!

## Credits

- [**Skeli789** (Complete Fire Red Upgrade Engine)](https://github.com/Skeli789/Complete-Fire-Red-Upgrade)
- [**Mikelan98 and Nomura** (ARM9 Expansion Routines)](https://pokehacking.com/tutorials/ramexpansion/)
- [**AdAstra-LD** (DSPRE)](https://github.com/AdAstra-LD/DS-Pokemon-Rom-Editor)
- [**BluRose** (plat_qol)](https://github.com/BluRosie/plat_qol)
- [**Bubble791** (IV/EV Summary Screen)](https://github.com/Bubble791/Platinum-Hack/tree/English-version)
- [**Rafael Vuijik** (ndstool)](https://github.com/devkitPro/ndstool)
- [**Kingcom** (armips)](https://github.com/Kingcom/armips)
