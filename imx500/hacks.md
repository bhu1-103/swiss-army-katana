# a few hacks i used to get custom models on imx500 running

## Jan-18-2026

### code thinks i am not running it on a raspberry pi 

```nvim /home/bhu5/models/4-yolov8/.venv/lib/python3.13/site-packages/modlib/devices/ai_camera/rpk_packager.python3```

```      #if platform.system() != "Linux" or platform.machine() != "aarch64":```

```       #    raise EnvironmentError("This RPKPackager is intended to run on a Raspberry Pi.")```

### opencv installation was not happening in raspberry pi due to low storage

- but there was enough storage space.
- checked ram, opencv source package was 96 mb, too much for 512 mb raspberry pi zero 2 w.
- change temp directory location to somewhere in the sd card insetad of ram or swap space as it is limited there

```       export TMPDIR=~/tmp_build```

### sony's library needed a newer version of opencv

- bypass it entirely in the pyproject.toml file after cloning the repo
- comment out opencv from pyproject.toml as this just uses basic opencv stuff that doesn't change much and is not critical.

```       #"opencv-python>=4.10.0.84,<=4.12.0.88",```

## Jan-18-2026

### inference speeds

- the raspberry pi ai camera usually gets a latency of 66 ms per frame, that is ~16 fps
- trying anything beyond 16 fps will not work as it was hardcoded (kinda) to work at a max of 16 fps
- if using a low end sbc like pi zero 2 w, try to keep it low resolution or just draw bounding boxes without displaying the camera view

## Jan-29-2026

### running imagenet models with picamera2's [classification demo](github.com/raspberrypi/picamera2/blob/main/examples/imx500/imx500_classification_demo.py) code

- this code will refuse to run with [this custom model](models/custom-imagenet/train.py) because it is designed to identify only 2 classes, **Cat** and **Dog**
- the original classification demo code is designed to identify nearly 1000 classes and show 3 classes with the highest confidence in the 
- therefore, we will have to modify the original demo code, `line 52`
```
from
    **top_indices = np.argpartition(-np_output, 3)[:3]  # Get top 3 indices with the highest scores**
to
    **top_indices = np.argsort(-np_output)[:3]  # Get top 3 indices with the highest scores**
```
- there is one more problem, the code still expects 1000 labels
- comment out `line 30`

```        assert len(LABELS) in [1000, 1001], "Labels file should contain 1000 or 1001 labels."```
- with this, the custom model should run properly
