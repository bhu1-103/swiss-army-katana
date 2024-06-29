# swiss-army-katana
Explore a curated set of versatile tools designed to enhance everyday tasks. Each tool in this collection, like a hidden gem in a Swiss Army Katana, is crafted for efficiency and practicality, ready to assist in a variety of situations.

Like forging your own katana, each tool here sharpens your coding skills with precision.

## [np (new-project)](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/template-handler) 
- Productivity max. Copy-pastes templates and makefiles from a local hidden folder. Currently works for c++.
- usage -> ` np [programming-language] [library] [file_name] `
- [x] C++ raylib
- [x] C++ opengl
- [ ] More customization options
- [ ] More programming languages

## [timer.sh](https://github.com/bhu1-103/swiss-army-katana/tree/main/tools/timer.sh) 
- A simple timer program that automatically switches to the desired workspace and constantly notifies. Good for people who get lost in thought.
- usage -> ` timer [number of seconds] [interval] [workspace to switch to] `
- [x] Workspace switch after time
- [x] Constant annoying notifications
- [ ] Integrate with [polybar](https://github.com/polybar/polybar) or [rofi](https://github.com/davatorium/rofi) for non console access
- [ ] Replace with a better algorithm and remove sleep

## [automatic brightness](https://github.com/bhu1-103/swiss-army-katana/tools/auto-brightness)
- Want to get automatic screen brightness on your laptop? 
- Check if you have [iio-sensors-proxy](https://gitlab.freedesktop.org/hadess/iio-sensor-proxy/) installed. If not, download it from your distro provider or from [here](https://gitlab.freedesktop.org/hadess/iio-sensor-proxy/)
- usage -> run `monitor-sensor > light_values.txt` and `./apply-light.sh`
- [x] Auto brightness
- [x] Logarithmic brightness adjustment. Might not work good everywhere due to differences in hardware.
- [ ] Make it run in all systems by retrieving system information
- [ ] ~~Improve update frequency to make it smoother~~
- [ ] Decrease update frequency and make it more efficient. Fix extensive resource usage
- [ ] **Implement smooth dimming**

## [auto-rotate in laptop](https://github.com/bhu1-103/swiss-army-katana/tools/auto-rotate)
- Pretty good except for the infinite `for` loop 🤢
- usage -> run `./autorotate.sh` and keep the other files, [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/invert-screen.sh), [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/normal-screen.sh), [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/invert-screen-v.sh) and also [this](https://github.com/bhu1-103/swiss-army-katana/blob/main/tools/auto-rotate/normal-screen-v.sh)
- [x] Functional and reliable auto-rotate
- [ ] Fix extensive resource usage
- [ ] Get rid of the stupid loop and try making it a cronjob
- [ ] **Make an accelerometer and gyroscope visualiser**
