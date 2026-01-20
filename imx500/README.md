# IMX500 test

## Jan-16-2026

- [x] setup imx500 with rpi zero 2 w with right camera cable
- [x] tested various models and achieved stable 30 fps
- [x] models upload and work without issues
- [ ] convert a model to imx500 format
- [ ] make a basic model and export it to imx500

## Jan-17-2026

- [x] convert basic imagenet classification model to imx500
- [ ] convert any other model

## Jan-18-2026

- [x] convert yolo models to imx500
- [x] setup environment and [hacks](./hacks.md#jan-18-2026) correctly
- [x] basic yolo11-n, pose detection, segmentation, classification models inference working, barely
- [ ] setup pyproject.toml file to easily replicate the environment

## Jan-19-2026

- [x] pose detection ([demo code here](./pose-detection/json-viewer.py)) working -> 20 fps -> 7-8 people -> runs without problems
- [x] able to record and replay pose detection videos using json dump
- [ ] implement it in transparent oled display

## Jan-20-2026

- [x] classic yolo11-n model running
- [x] found some more [hacks](./hacks.md#Jan-20-2026)
