# PSX_GRAPHICS
Welcome to this ambitious project of mine where I try to understand and implement some of the [PsyQ library](https://psx.arthus.net/sdk/Psy-Q/) functions and concepts to make cool looking 3D effects. These are the current examples i've made that run using [PCSX-REDUX](https://github.com/grumpycoders/pcsx-redux) :
## Table of Contents
* [Current Examples](#current-examples)
    * [Triangle](#triangle)
    * [Pyramid](#pyramid)
    * [Brick Cube](#brick-cube)
    * [Ship Selection Demo](#ship-selection-demo)
* [Getting Started](#getting-started)
    * [Prerequisites](#prerequisites)
    * [Setting up the Development Environment](#setting-up-the-development-environment)
        * [1. PsyQ SDK](#1-psyq-sdk)
        * [2. ARMIPS](#2-armips)
        * [3. mkpsxiso](#3-mkpsxiso)
    * [Building and Running Examples](#building-and-running-examples)
# Current Examples 
## Triangle 
This is a simple rotating triangle made using a Struct called **POLY_G3** , you can check the documentation in this link for more info about the [**POLY_G3**](https://psx.arthus.net/sdk/Psy-Q/DOCS/LibRef47.pdf) Struct.

<img src="https://github.com/user-attachments/assets/5e232bae-8f9b-477f-a271-185f2008df7f" alt="Pyramid" style="display: block; margin: auto;">

## Pyramid 
In this example, I had to make the 4 triangle faces with the **POLY_G3** Struct , I will try to make the base of the triangle look good because it's glitching but for the mean time there is no base.

<img src="https://github.com/user-attachments/assets/f10d896f-996a-4501-83c2-7b579b6a2735" alt="Pyramid" style="display: block; margin: auto;">

## Brick Cube 
It's a rotating cube but with a texture from a **.tim** file (bricks.tim in the ASSETS folder) using UV coordinates to map the texture onto the cube. This example implemented a tutorial by the [**Pikuma Course**](https://pikuma.com/courses/ps1-programming-mips-assembly-language) go check it out it's a wonderful course for beginners.

<img src="https://github.com/user-attachments/assets/f65f2b7a-1f29-4aa8-a49e-4d3dd7945f1c" alt="Bricks Cube" style="display: block; margin: auto;">

## Ship Selection Demo 
In this demo, I implemented ship selection using linked lists to link each ship to the next/previous one. These ships are extracted from the leaked **Wipeout** source code. 

<img src="https://github.com/user-attachments/assets/79c1d0fc-551a-49ef-bfcc-e7e7b1c4364c" alt="Ship Selection Demo" style="display: block; margin: auto;">

# Getting Started

This section guides you through setting up your environment to build and run the PSX_GRAPHICS examples.

## Prerequisites

Before you begin, ensure you have the following installed:

* **Python:** Required for the `bin2exe.py` script included in this repository. Most systems come with Python pre-installed.
* **PCSX-REDUX Emulator:** [Download PCSX-REDUX](https://distrib.app/pub/org/pcsx-redux/project/dev-win-x64) for your operating system. This emulator is highly recommended for its accuracy and debugging features for PS1 homebrew development.
* **PS1 BIOS:** You will need a PS1 BIOS file (e.g., `SCPH1001.BIN`, `SCPH5500.BIN`, `SCPH7502.BIN`). Place this file in the `bios/` directory of your PCSX-REDUX installation.

## Setting up the Development Environment

### 1. PsyQ SDK

The PsyQ SDK is the official development kit used for PlayStation 1 homebrew. It provides the necessary compilers, linkers, libraries, and tools.

* **Download:** You can find the PsyQ SDK from various archives; a common source is [psx.arthus.net/sdk/Psy-Q/](https://psx.arthus.net/sdk/Psy-Q/). Look for a `PsyQ_4.7.zip` or similar archive.
* **Extraction:** Extract the contents of the PsyQ SDK archive to a convenient location on your system. A common practice is to extract it to `C:\psyq` on Windows. For the rest of this guide, we'll assume it's extracted to `C:\psyq` (Windows).
* **Environment Variables (Windows):**
    * Add the `bin` directory of your PsyQ installation to your system's `PATH` environment variable. For example, if you extracted to `C:\psyq`, add `C:\psyq\bin`.
    * Create a new system environment variable called `PSYQ_SDK` and set its value to the root directory of your PsyQ installation (e.g., `C:\psyq`).
### 2. ARMIPS
**ARMIPS** is a powerful and widely used assembler for various MIPS-based platforms, including the PlayStation 1. It's essential for compiling `.s` (assembly) source files.

* **Download:** You can find ARMIPS releases on its GitHub page: [https://github.com/Kingcom/armips/releases](https://github.com/Kingcom/armips/releases). Download the appropriate binary for your operating system.
* **Installation:**
    * **Windows:** Place the `armips.exe` file in a directory that's included in your system's `PATH` (e.g., `C:\Windows\System32`, or a custom `Tools` directory that you've added to `PATH`).
### 3. mkpsxiso

`mkpsxiso` is a command-line tool used to create PlayStation 1 disc images (ISO/BIN/CUE files) from your compiled executables and assets. This is essential for emulators to load your games.

* **Download:** You can find `mkpsxiso` at its GitHub repository: [https://github.com/Lameguy64/mkpsxiso/releases](https://github.com/Lameguy64/mkpsxiso). Download the appropriate binary for your system.
* **Installation:**
    * **Windows:** Place the `mkpsxiso.exe` file in a directory that is included in your system's `PATH` (e.g., `C:\Windows\System32`, or a custom `Tools` directory that you've added to `PATH`).
## Building and Running Examples
Once your development environment is set up, you can build and run the examples in this repository.

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/abdessalamzarrouk/PSX_GRAPHICS.git
    cd PSX_GRAPHICS
    ```

2.  **Compile the Example:**
    The PsyQ SDK includes a `make` utility compatible with its toolchain. Most PS1 projects use a `Makefile` to automate the build process.
    * For C examples (like Triangle, Pyramid, Brick Cube):
        ```bash
        make buildc SRC=your_example
        ```
        (e.g., `make buildc SRC=triangle`)
    * For Assembly examples (like `asm_hellogpu`):
        ```bash
        make build SRC=asm_hellogpu
        ```
    These commands will compile your source files and produce a `.BIN` executable file (e.g., `asm_image.bin`, `asm_hellogpu.bin`).

3.  **Convert `.BIN` to `.EXE` (for assembly examples):**
    Use the `bin2exe.py` script provided in this repository. Assuming it's in your project's root or a well-known `tools` directory:
    ```bash
    python ../bin2exe.py asm_hellogpu.bin asm_hellogpu.exe
    ```
    You can use also `make` command in the project root directory:
    ```
    make build SRC=asm_hellogpu
    make exe SRC=asm_hellogpu
    ```
    This will create `asm_hellogpu.exe`.

4.  **Run in PCSX-REDUX:**
    Open the PCSX-REDUX emulator.
    * Go to `File` -> `Open Executable...` (or similar).
    * Navigate to your example's directory and select the newly created `.EXE` file (e.g., `triangle.exe`).

    Your PS1 example should now be running in the emulator!
