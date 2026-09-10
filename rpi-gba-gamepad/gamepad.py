import time, signal, sys
import RPi.GPIO as GPIO
from evdev import UInput, ecodes as e

R = [38, 32, 37, 35]
C = [33, 18, 36, 15]
K = [['1','2','3','A'],['4','5','6','B'],['7','8','9','C'],['*','0','#','D']]

M = {
    '1':(e.KEY_UP,e.KEY_LEFT),'2':(e.KEY_UP,),'3':(e.KEY_UP,e.KEY_RIGHT),
    '4':(e.KEY_LEFT,),'5':(),'6':(e.KEY_RIGHT,),
    '7':(e.KEY_DOWN,e.KEY_LEFT),'8':(e.KEY_DOWN,),'9':(e.KEY_DOWN,e.KEY_RIGHT),
    'A':(e.KEY_Z,),'B':(e.KEY_X,),'C':(e.KEY_Q,),'D':(e.KEY_E,),
    '*':(e.KEY_ENTER,),'#':(e.KEY_BACKSPACE,),'0':()
}

GPIO.setmode(GPIO.BOARD)
for x in R: GPIO.setup(x, GPIO.OUT, initial=GPIO.HIGH)
for x in C: GPIO.setup(x, GPIO.IN, pull_up_down=GPIO.PUD_UP)

keys = sorted({k for v in M.values() for k in v})
u = UInput({e.EV_KEY: keys}, name='Pi 5 GBA Keypad')

def stop(*_):
    u.close()
    GPIO.cleanup()
    sys.exit()

signal.signal(signal.SIGINT, stop)
signal.signal(signal.SIGTERM, stop)

prev = set()

while 1:
    cur = set()

    for i, r in enumerate(R):
        GPIO.output(r, GPIO.LOW)
        for j, c in enumerate(C):
            if not GPIO.input(c): cur.add(K[i][j])
        GPIO.output(r, GPIO.HIGH)

    now = {k for x in cur for k in M[x]}

    for k in now - prev: u.write(e.EV_KEY, k, 1)
    for k in prev - now: u.write(e.EV_KEY, k, 0)
    if now != prev: u.syn()

    prev = now
    time.sleep(.001)import time, signal, sys
import RPi.GPIO as GPIO
from evdev import UInput, ecodes as e

R = [38, 32, 37, 35]
C = [33, 18, 36, 15]
K = [['1','2','3','A'],['4','5','6','B'],['7','8','9','C'],['*','0','#','D']]

M = {
    '1':(e.KEY_UP,e.KEY_LEFT),'2':(e.KEY_UP,),'3':(e.KEY_UP,e.KEY_RIGHT),
    '4':(e.KEY_LEFT,),'5':(),'6':(e.KEY_RIGHT,),
    '7':(e.KEY_DOWN,e.KEY_LEFT),'8':(e.KEY_DOWN,),'9':(e.KEY_DOWN,e.KEY_RIGHT),
    'A':(e.KEY_Z,),'B':(e.KEY_X,),'C':(e.KEY_Q,),'D':(e.KEY_E,),
    '*':(e.KEY_ENTER,),'#':(e.KEY_BACKSPACE,),'0':()
}

GPIO.setmode(GPIO.BOARD)
for x in R: GPIO.setup(x, GPIO.OUT, initial=GPIO.HIGH)
for x in C: GPIO.setup(x, GPIO.IN, pull_up_down=GPIO.PUD_UP)

keys = sorted({k for v in M.values() for k in v})
u = UInput({e.EV_KEY: keys}, name='Pi 5 GBA Keypad')

def stop(*_):
    u.close()
    GPIO.cleanup()
    sys.exit()

signal.signal(signal.SIGINT, stop)
signal.signal(signal.SIGTERM, stop)

prev = set()

while 1:
    cur = set()

    for i, r in enumerate(R):
        GPIO.output(r, GPIO.LOW)
        for j, c in enumerate(C):
            if not GPIO.input(c): cur.add(K[i][j])
        GPIO.output(r, GPIO.HIGH)

    now = {k for x in cur for k in M[x]}

    for k in now - prev: u.write(e.EV_KEY, k, 1)
    for k in prev - now: u.write(e.EV_KEY, k, 0)
    if now != prev: u.syn()

    prev = now
    time.sleep(.001)
