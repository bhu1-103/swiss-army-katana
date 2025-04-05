from pynput.keyboard import Key, Controller
import time

keyboard = Controller()

def wopen():
	keyboard.press(Key.cmd)
	keyboard.press('1')
	keyboard.release(Key.cmd)
	keyboard.release('1')
	time.sleep(0.2)

def wreload():
	keyboard.press(Key.ctrl)
	keyboard.press('r')
	keyboard.release(Key.ctrl)
	keyboard.release('r')
	time.sleep(0.5)

def wclose():
	open()
	keyboard.press(Key.ctrl)
	keyboard.press('w')
	keyboard.release('w')
	keyboard.release(Key.ctrl)

def wtab():
	keyboard.press(Key.tab)
	time.sleep(0.1)
	keyboard.release(Key.tab)

def wtype():
	wtab()
	wtab()
	keyboard.type("Guest")
	wtab()
	keyboard.type("Guest@123")
	keyboard.press(Key.enter)
	keyboard.release(Key.enter)

wopen()
time.sleep(0.5)
wreload()
time.sleep(0.5)
wtype()
time.sleep(0.5)
wopen()

with keyboard.pressed(Key.ctrl):
	with keyboard.pressed(Key.cmd):
		keyboard.press(Key.right)
		keyboard.release(Key.right)

time.sleep(10)

while True:
	wopen()
	wreload()
	time.sleep(0.5)
	wtype()
	time.sleep(0.5)
	wopen()
	time.sleep(0.1)
	wopen()	
	time.sleep(0.1)
	wopen()
	notification.notify(title="Windows Defender",message="Checking for updates",app_icon="C:/Users/ARC Lab/Downloads/defico.ico")
	time.sleep(1800)
