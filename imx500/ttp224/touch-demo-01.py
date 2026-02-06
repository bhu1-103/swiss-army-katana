from gpiozero import Button
from signal import pause
import time

PAD_ORDER = [23, 22, 27, 17]
SWIPE_WINDOW = 0.5
MIN_PADS_IN_SWIPE = 3
history = []
pads = []

def check_for_swipe():
    global history
    now = time.time()

    history = [(t,i) for (t,i) in history if now - t < SWIPE_WINDOW]
    indices = [i for (_,i) in history]

    if len(indices) < MIN_PADS_IN_SWIPE:
        return

    cleaned = []
    for i in indices:
        if not cleaned or cleaned[-1] != i:
            cleaned.append(i)

    if cleaned == sorted(cleaned):
        print(">>RIGHT>>")
        history.clear()

    if cleaned == sorted(cleaned, reverse=True):
        print(">>LEFT>>")
        history.clear()

def make_handlers(index):
    def pressed():
        print(f"PAD {index+1} PRESSED")
        history.append((time.time(),index))
        check_for_swipe()

    def released():
        print(f"PAD {index+1} RELEASED")

    return pressed, released


for i, pin in enumerate(PAD_ORDER):
    btn = Button(
        pin,
        pull_up=False,
        bounce_time=0.03
    )

    on_press, on_release = make_handlers(i)
    btn.when_pressed = on_press
    btn.when_released = on_release

    pads.append(btn)

print("いっクソ")

pause()
