# a few hacks i used to get custom models on imx500 running

## 

nvim /home/bhu5/models/4-yolov8/.venv/lib/python3.13/site-packages/modlib/devices/ai_camera/rpk_packager.python3
```
        #if platform.system() != "Linux" or platform.machine() != "aarch64":
        #    raise EnvironmentError("This RPKPackager is intended to run on a Raspberry Pi.")
```
