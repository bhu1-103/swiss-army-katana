# IMX500

Experiments with running custom YOLO and pose detection models directly on the Sony IMX500 intelligent vision sensor.

## To-do

- [x] get yolo working
- [ ] transparent display
- [ ] make it portable, replace powerbank with lipo battery

---

## Notes & Logs

- [Timeline of experiments](timeline.md)
- [Dataset prepration for fine tuning](custom-dataset.md)
- [Hacks and undocumented behavior](hacks.md)

---

## Models & Utilities

### Classic YOLO
- [`models/classic-yolo/classic-yolo.py`](models/classic-yolo/classic-yolo.py)

### Pose Detection
- [`models/pose-detection/json-ify.py`](models/pose-detection/json-ify.py)
