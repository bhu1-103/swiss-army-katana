from machine import Pin, PWM
import time

WORK_MIN = 25
BREAK_MIN = 5

# convert to seconds
WORK_SEC = WORK_MIN * 60
BREAK_SEC = BREAK_MIN * 60

buzzer = PWM(Pin(1))
buzzer.duty_u16(0)

def beep(freq=2000, duration=0.2):
    buzzer.freq(freq)
    buzzer.duty_u16(20000)
    time.sleep(duration)
    buzzer.duty_u16(0)
    time.sleep(0.1)

def work_done_signal():
    for _ in range(3):
        beep(2500, 0.15)

def break_done_signal():
    beep(1200, 0.6)

while True:
    time.sleep(WORK_SEC)
    work_done_signal()

    time.sleep(BREAK_SEC)
    break_done_signal()
