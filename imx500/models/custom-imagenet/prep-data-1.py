from roboflow import Roboflow
rf = Roboflow(api_key="add_your_api_key_here")
project = rf.workspace("practica-f6pew").project("dog-cat-g72z3")
version = project.version(3)
dataset = version.download("yolov11")
