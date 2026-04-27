import time

HID_PATH = "/dev/hidg0"

MODIFIERS = {
    "CTRL":  0x01,
    "SHIFT": 0x02,
    "ALT":   0x04,
    "GUI":   0x08,
}

KEYCODES = {
    **{chr(i+97): (0x00, 0x04+i) for i in range(26)},
    **{chr(i+65): (0x02, 0x04+i) for i in range(26)},

    "1": (0x00, 0x1e), "!": (0x02, 0x1e),
    "2": (0x00, 0x1f), "@": (0x02, 0x1f),
    "3": (0x00, 0x20), "#": (0x02, 0x20),
    "4": (0x00, 0x21), "$": (0x02, 0x21),
    "5": (0x00, 0x22), "%": (0x02, 0x22),
    "6": (0x00, 0x23), "^": (0x02, 0x23),
    "7": (0x00, 0x24), "&": (0x02, 0x24),
    "8": (0x00, 0x25), "*": (0x02, 0x25),
    "9": (0x00, 0x26), "(": (0x02, 0x26),
    "0": (0x00, 0x27), ")": (0x02, 0x27),

    "ENTER": (0x00, 0x28),
    "ESC": (0x00, 0x29),
    "BACKSPACE": (0x00, 0x2a),
    "TAB": (0x00, 0x2b),
    "SPACE": (0x00, 0x2c),

    "UP": (0x00, 0x52),
    "DOWN": (0x00, 0x51),
    "LEFT": (0x00, 0x50),
    "RIGHT": (0x00, 0x4f),
}

_active_keys = set()
_active_mods = 0

def _update_hid():
    report = bytearray(8)
    report[0] = _active_mods
    
    for i, key_code in enumerate(list(_active_keys)[:6]):
        report[2 + i] = key_code
        
    with open(HID_PATH, "wb") as f:
        f.write(report)

def press(*keys):
    global _active_mods
    for k in keys:
        if k in KEYCODES:
            mod, code = KEYCODES[k]
            _active_mods |= mod
            if code: _active_keys.add(code)
    _update_hid()

def release(*keys):
    global _active_mods
    if not keys:
        _active_keys.clear()
        _active_mods = 0
    else:
        for k in keys:
            if k in KEYCODES:
                mod, code = KEYCODES[k]
                _active_mods &= ~mod
                if code in _active_keys:
                    _active_keys.remove(code)
    _update_hid()

def tap(key, delay=0.01):
    press(key)
    time.sleep(delay)
    release(key)
    time.sleep(delay)

