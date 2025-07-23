import time
import board
import digitalio
import wifi
import socketpool
import adafruit_httpserver

SSID = "your-ssid"
PASSWORD = "your-password"

wifi.radio.connect(SSID, PASSWORD)
print("Connected:", wifi.radio.ipv4_address)

led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

pool = socketpool.SocketPool(wifi.radio)
server = adafruit_httpserver.Server(pool, "/static", debug=True)

blink_delay = 0.5

html = """
<!DOCTYPE html>
<html>
<head><title>LED Speed Control</title></head>
<body>
<h1>LED Blinker</h1>
<label for="speed">Delay (ms):</label>
<input type="range" id="speed" min="50" max="2000" value="500" step="50"
       oninput="sendDelay(this.value)">
<p id="value">500 ms</p>
<script>
function sendDelay(val) {
    document.getElementById("value").innerText = val + " ms";
    fetch("/set?delay=" + val);
}
</script>
</body>
</html>
"""

@server.route("/")
def base(request: adafruit_httpserver.Request):
    return adafruit_httpserver.Response(request, body=html, content_type="text/html")

@server.route("/set")
def set_delay(request: adafruit_httpserver.Request):
    global blink_delay
    params = request.query_params
    try:
        delay_ms = int(params.get("delay", "500"))
        blink_delay = max(0.05, delay_ms / 1000)
        print("Delay updated to", blink_delay)
    except Exception as e:
        print("Bad delay:", e)
    return adafruit_httpserver.Response(request, body="OK")

server.start(str(wifi.radio.ipv4_address))
print("Server started")

while True:
    try:
        server.poll()
    except Exception as e:
        print("HTTP error:", e)

    led.value = not led.value
    time.sleep(blink_delay)
