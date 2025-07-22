import socket
import network

page = open("index.html", "r")
html = page.read()
page.close()

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect("WIFI-SSID","PASSWORD")
sta_if = network.WLAN(network.STA_IF)
print(sta_if.ifconfig()[0])
addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
s = socket.socket()
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(addr)
s.listen(1)
while True:
    cl, addr = s.accept()
    cl_file = cl.makefile('rwb', 0)
    while True:
        line = cl_file.readline()
        if not line or line == b'\r\n':
            break
    response = html 
    
    cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
    cl.send(response)
    cl.close()
