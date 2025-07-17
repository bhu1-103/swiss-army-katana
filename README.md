# swiss-army-katana
A collection of personal projects and tools I've developed in my free time.

## Demos

| 3D Ray-Casted World | Synthwave Animation | Circle Algorithm |
| :---: | :---: | :---: |
| ![3d world](/assets/3d-world.gif) | ![synthwave animation](/assets/synthwave-sun.gif) | ![circle](/assets/circle-updated.gif) |

## Featured Projects

### [Sasta-ChatGPT](https://github.com/bhu1-103/swiss-army-katana/tree/main/sasta-chatgpt)
A Retrieval-Augmented Generation (RAG) tool that uses a local LLM (via Ollama) to answer questions about a given knowledge base. It fetches content from sources like Wikipedia, processes it, and uses a sentence-transformer model to find relevant context for the user's query.

### [ASCII Art Converter](https://github.com/bhu1-103/swiss-army-katana/tree/main/ascii-art-converter)
A Python tool that converts images into ASCII art. It uses a simple PyTorch model to map pixel brightness to a corresponding set of ASCII characters.

### [Graphics Programming with OpenGL](https://github.com/bhu1-103/swiss-army-katana/tree/main/opengl)
This directory contains various experiments with OpenGL, including:
- A **Doom-like 3D engine** that uses 2D ray casting to render a 3D perspective.
- A series of **Synthwave-style animations** exploring 3D transformations and camera movement.
- A basic 3D cube and other smaller projects.

### [Console Homebrew (NDS & PSP)](https://github.com/bhu1-103/swiss-army-katana/tree/main/libnds)
A collection of small projects written in C for the Nintendo DS and PlayStation Portable. These experiments involve direct hardware interaction for tasks like reading controller input, rendering basic 2D/3D graphics, and recording audio from the DS microphone.

### [Voice Assistant](https://github.com/bhu1-103/swiss-army-katana/tree/main/assistant)
A simple voice assistant built with a shell script. It uses `ffmpeg` for audio capture and the `vosk-transcriber` library for speech-to-text, allowing it to perform basic commands like opening applications.

## Scripts & Utilities
This repository also contains a variety of smaller scripts and tools to automate tasks, including:
- **[np](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/template-handler):** A script to quickly scaffold new C++ projects from templates.
- **[auto-rotate](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/auto-rotate):** A script for enabling automatic screen rotation on laptops with accelerometers.
- **[timer.sh](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/timer-bspwm.sh):** A simple countdown timer that sends notifications and can switch workspaces.

## [Dotfiles](https://github.com/bhu1-103/swiss-army-katana/tree/main/dotfiles)
My personal configuration files for various tools and window managers like Hyprland, bspwm, and i3.
