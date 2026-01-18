# a few hacks i used to get custom models on imx500 running

## code thinks i am not running it on a raspberry pi 

nvim /home/bhu5/models/4-yolov8/.venv/lib/python3.13/site-packages/modlib/devices/ai_camera/rpk_packager.python3
`
        #if platform.system() != "Linux" or platform.machine() != "aarch64":
        #    raise EnvironmentError("This RPKPackager is intended to run on a Raspberry Pi.")
`

## opencv installation was not happening in raspberry pi due to low storage

- but there was enough storage space.
- checked ram, opencv source package was 96 mb, too much for 512 mb raspberry pi zero 2 w.
- comment out opencv from pyproject.toml as this just uses basic opencv stuff that doesn't change much and is not critical.

`    #"opencv-python>=4.10.0.84,<=4.12.0.88",`


## sony's library needed a newer version of opencv

- bypass it entirely in the 
