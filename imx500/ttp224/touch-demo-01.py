from gpiozero import Button
from signal import pause

# BCM order from Left -> Right
PAD_ORDER = [23, 22, 27, 17]

pads = []

def make_handlers(index):
    def pressed():
        print(f"PAD {index+1} PRESSED")

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
