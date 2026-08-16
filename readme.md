# Vertypad Macro Pad

The **Vertypad** is a custom, high-utility 4x2 matrix mechanical macropad featuring an integrated rotary encoder, and a 0.91-inch OLED status display screen. It is built around the Seeed Studio XIAO RP2040 micro-controller, and powered by QMK (VIA support).

### PCB
![Vertypad PCB Trace Routing](assets/pcb.png)

### Schematics
![Vertypad Matrix Schematic Map](assets/schema.png)

## BOM

| Component Type | Part Description | Quantity | Notes |
| :--- | :--- | :--- | :--- |
| **Microcontroller** | Seeed Studio XIAO RP2040 | 1 | High-speed dual-core ARM Cortex-M0+ |
| **Switches** | MX-Style Mechanical Switches | 7 | Sockets SW1 through SW7 |
| **Rotary Encoder** | EC11 Rotary Encoder with Switch | 1 | Socket SW8 (Volume / Mute control) |
| **Diodes** | 1N4148 Through-Hole Signal Diodes | 8 | Formed COL2ROW layout path isolation |
| **Display Panel** | 0.91-inch I2C Monochromatic OLED | 1 | Pin order: GND - VCC - SCL - SDA (128x32) |
| **Keycaps** | DSA Profile Blank Keycaps | 7 | Uniform shape height mapping |
| **Screws**| M3 x 16mm Screws | 4 | Secures the 3.0mm plate layer |

## Hardware and Schematic Pin Map

The custom circuit traces hook into the Seeed Studio XIAO RP2040 using an efficient 4x2 matrix layout structure that fully incorporates all key matrices and the encoder click line:

### 1. Matrix Interconnects (COL2ROW)
* **Columns (Output):** `COL0` ➔ **GP0**, `COL1` ➔ **GP28**, `COL2` ➔ **GP27**, `COL3` ➔ **GP26**
* **Rows (Input):** `ROW0` ➔ **GP4**, `ROW1` ➔ **GP3**

### 2. Specialized Component Pins
* **EC11 Rotary Encoder:** `RNA (Phase A)` ➔ **GP2**, `RNB (Phase B)` ➔ **GP1**
* **OLED Screen Bus (I2C1):** `SDA` ➔ **GP6**, `SCL` ➔ **GP7**

## macOS Macro Profiles

The integrated keymap configuration has macro controls tailored explicitly for Apple macOS systems:

* **SW1 Location:** `Command + C` ➔ Immediate Copy Execution.
* **SW3 Location:** `Command + V` ➔ Immediate Paste Insertion.
* **SW5 Location:** `Command + Spacebar` ➔ Instantly launches Apple Spotlight Search.
* **SW7 Location:** `Command + Control + Q` ➔ Instantly locks the Mac screen securely.
* **Rotary Dial (SW8):** Precise system hardware Volume Up / Volume Down adjustment steps.
* **Encoder Click Button:** Instant target audio stream muting toggle.
