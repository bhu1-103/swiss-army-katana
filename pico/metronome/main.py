from machine import Pin, PWM, lightsleep
import time

buzzer = PWM(Pin(0))
buzzer.duty_u16(0)

BPM = 120
BEATS_PER_BAR = 4

interval_ms = int(60000 / BPM)

def click(freq=1200, dur=40):
    buzzer.freq(freq)
    buzzer.duty_u16(10000)
    time.sleep_ms(dur)
    buzzer.duty_u16(0)

beat = 0

while True:
    start = time.ticks_ms()

    if beat == 0:
        click(1600, 60)
    else:
        click(1200, 30)

    beat = (beat + 1) % BEATS_PER_BAR

    elapsed = time.ticks_diff(time.ticks_ms(), start)
    remaining = interval_ms - elapsed
    if remaining > 0:
        lightsleep(remaining)
