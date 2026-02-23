from machine import Pin, PWM, deepsleep, RTC
import time

WORK_MIN = 25
BREAK_MIN = 5

WORK_MS = WORK_MIN * 60 * 1000
BREAK_MS = BREAK_MIN * 60 * 1000

rtc = RTC()

buzzer = PWM(Pin(0))
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

state = rtc.memory()

if state == b"WORK_DONE":
    work_done_signal()
    rtc.memory(b"BREAK_DONE")
    deepsleep(BREAK_MS)

elif state == b"BREAK_DONE":
    break_done_signal()
    rtc.memory(b"WORK_DONE")
    deepsleep(WORK_MS)

else:
    rtc.memory(b"WORK_DONE")
    deepsleep(WORK_MS)
