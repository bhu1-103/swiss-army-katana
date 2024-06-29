# swiss-army-katana
Explore a curated set of versatile tools designed to enhance everyday tasks. Each tool in this collection, like a hidden gem in a Swiss Army Katana, is crafted for efficiency and practicality, ready to assist in a variety of situations.

Like forging your own katana, each tool here sharpens your coding skills with precision.

![setup.png](/.images/setup.png)


## [doom-like 3d world using 2d graphics](https://github.com/bhu1-103/swiss-army-katana/tree/main/opengl/doom-limited)
- Thanks to [ray casting](https://en.wikipedia.org/wiki/Ray_casting), we can make a semi-3d world by just using a 2d graphics.
- First we make a top down world as in older rpgs and then we use some math to convert it into 3d.
- [Fish eye effect](https://en.wikipedia.org/wiki/Fisheye_lens) can be fixed.
- [x] 3d world.
- [x] Roam around in the map freely.
- [ ] Add collisions.
- [ ] Map maker.
- [ ] Add enemies.

## [graph plotter](https://github.com/bhu1-103/swiss-army-katana/blob/main/opengl/lattice-gradient/lattice_opengl.cpp)
- One of my first opengl projects.
- Gradient made using for loop. Just increment R,G,B values. Cycle the values between 0 to 255 for better effect.
- [x] Plot points and lines.
- [x] Plot custom functions (curves).
- [ ] Scroll across the map and zoom functionality.
- [ ] Add a post compilation method in editor similar to desmos.


## [np (new-project)](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/template-handler) 
- Productivity max. Copy-pastes templates and makefiles from a local hidden folder. Currently works for c++.
- usage -> ` np [programming-language] [library] [file_name] `.
- [x] C++ raylib.
- [x] C++ opengl.
- [ ] More customization options.
- [ ] More programming languages.

## [timer.sh](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/timer.sh) 
- A simple timer program that automatically switches to the desired workspace and constantly notifies. Good for people who get lost in thought.
- usage -> ` timer [number of seconds] [interval] [workspace to switch to] `.
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
- Pretty good except for the infinite `for` loop 🤢.
- usage -> run `./autorotate.sh` and keep the other files, [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/invert-screen.sh), [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/normal-screen.sh), [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/invert-screen-v.sh) and also [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/normal-screen-v.sh) in the same directory.
- [x] Functional and reliable auto-rotate.
- [ ] Fix extensive resource usage.
- [ ] Get rid of the stupid loop and try making it a cronjob.
- [ ] **Make an accelerometer and gyroscope visualiser**.
