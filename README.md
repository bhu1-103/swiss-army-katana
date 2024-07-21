# swiss-army-katanaa

Tools and programs I write at free time that helps me in day to day tasks and increases productivity.

- legacy opengl 3d cube (journey)
![3d cube](/assets/3d-cube.gif)

- how computers make circles (click [here](/tools/automation/circle.sh) if you want to see how I made this gif) ([old version](/assets/circle.gif))
![circle](/assets/circle-updated.gif)

- fps template
![3d world](/assets/3d-world.gif)

- customized firefox
![setup-firefox.png](/assets/firefox-homepage.png)

- doom remake (gave up, excuse the low resolution, still a beginner using ffmpeg)
![doom remake](/assets/doom_demo.gif)

- Check out my dots [here](https://github.com/bhu1-103/swiss-army-katana/tree/main/dotfiles)


## [voice assistant](https://github.com/bhu1-103/swiss-army-katana/tree/main/assistant/assistant.sh)
- The shell script uses [vosk transcriber](https://alphacephei.com/vosk/) to convert speech to text.
- It then parses the first word and depending on the action, performs the action.
- Integrate with your WM/DE for best performance.
- [x] Resource efficient. [model used](https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip)
- [x] Open desktop applications like firefox.
- [x] Work alongside xdotool (keyboard and mouse emulation) and other tools for infinite freedom.
- [ ] Sudo password stored inside the shell script itself, making it vulnerable to threat actors.
- [ ] Integrate it into polybar/waybar or make a custom dmenu/rofi menu to call it anytime.
- [ ] Start converting to text as soon as silence is detected.
- dependencies: vosk-transcriber (pip install vosk-transcriber), you can replace alacritty, ffmpeg, dunstify, etc tools with any you like.

## [doom-like 3d world using 2d graphics](https://github.com/bhu1-103/swiss-army-katana/tree/main/opengl/doom-limited)
- Thanks to [ray casting](https://en.wikipedia.org/wiki/Ray_casting), we can make a semi-3d world by just using a 2d graphics.
- First we make a top down world as in older rpgs and dungeon crawlers and then we use some math to convert it into 3d.
- [Fish eye effect](https://en.wikipedia.org/wiki/Fisheye_lens) can be fixed.
- [x] 3d world.
- [x] Roam around in the map freely.
- [ ] Add collisions.
- [ ] Map maker.
- [ ] Add enemies.

## [TIC-80](https://github.com/bhu1-103/swiss-army-katana/tree/main/tic-80)
### [Movement and sprite wrapping](https://github.com/bhu1-103/swiss-army-katana/blob/main/tic-80/sprite-wrap.tic)
- [x] Basic program to move meatboy around and implementing sprite wrapping.
- [x] Jump physics that actually feel good.
- [ ] Map implementation

## [graph plotter](https://github.com/bhu1-103/swiss-army-katana/blob/main/opengl/lattice-gradient/lattice_opengl.cpp)
- One of my first opengl projects.
- Gradient made using for loop. Just increment R,G,B values. Cycle the values between 0 to 255 for better effect.
- [x] Plot points and lines.
- [x] Plot custom functions (curves).
- [ ] Scroll across the map and zoom functionality.
- [ ] Add a post compilation method in editor similar to desmos.


## [np (new-project)](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/template-handler) 
- Productivity max. Copy-pastes templates and makefiles from a local hidden folder. Currently works for c++.
- usage -> ` np [language] [library] [file_name] `.
- [x] C++ raylib.
- [x] C++ opengl.
- [ ] More customization options.
- [ ] More languages.

## [timer.sh](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/timer.sh) 
- A simple timer program that automatically switches to the desired workspace and constantly notifies. Good for people who get lost in thought.
- usage -> ` timer [number of seconds] [workspace to switch to] [interval] `.
- [x] Workspace switch after time.
- [x] Constant annoying notifications.
- [ ] Integrate with [polybar](https://github.com/polybar/polybar) or [rofi](https://github.com/davatorium/rofi) for non console access.
- [ ] Replace with a better algorithm and remove sleep.

## [automatic brightness](https://github.com/bhu1-103/swiss-army-katana/tools/auto-brightness)
- Want to get automatic screen brightness on your laptop?
- Check if you have [iio-sensors-proxy](https://gitlab.freedesktop.org/hadess/iio-sensor-proxy/) installed. If not, download it from your distro provider or from [here](https://gitlab.freedesktop.org/hadess/iio-sensor-proxy/).
- usage -> run `monitor-sensor > light_values.txt` and `./apply-light.sh`.
- [x] Auto brightness.
- [x] Logarithmic brightness adjustment. Might not work good everywhere due to differences in hardware.
- [ ] Make it run in all systems by retrieving system information.
- [ ] ~~Improve update frequency to make it smoother~~.
- [ ] Decrease update frequency and make it more efficient. Fix extensive resource usage.
- [ ] **Implement smooth dimming**.

## [auto-rotate in laptop](https://github.com/bhu1-103/swiss-army-katana/tools/auto-rotate)
- Pretty good except for the infinite `for` loop...
- usage -> run `./autorotate.sh` and keep the other files, [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/invert-screen.sh), [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/normal-screen.sh), [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/invert-screen-v.sh) and also [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/normal-screen-v.sh) in the same directory.
- [x] Functional and reliable auto-rotate.
- [ ] Fix extensive resource usage.
- [ ] Get rid of the stupid loop and try making it a cronjob.
- [ ] **Make an accelerometer and gyroscope visualiser**.

## [automation scripts](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/automation)
### [auto-mousemove](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/automation)
- Remind me in 1 day.
