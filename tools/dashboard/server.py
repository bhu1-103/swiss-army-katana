import psutil
import asyncio
from fastapi import FastAPI
from fastapi.responses import StreamingResponse, HTMLResponse
import uvicorn
import json
import subprocess
from gpu import get_gpu_stats

app = FastAPI()

def get_process_usage(keyword):
    """
    Returns CPU% and Memory% of processes matching keyword.
    If multiple match, sum them.
    """
    total_cpu = 0.0
    total_mem = 0.0
    for p in psutil.process_iter(['name', 'cpu_percent', 'memory_percent', 'cmdline']):
        try:
            name = p.info['name'] or ""
            cmd = " ".join(p.info['cmdline'] or [])

            if keyword.lower() in name.lower() or keyword.lower() in cmd.lower():
                total_cpu += p.info['cpu_percent']
                total_mem += p.info['memory_percent']
        except:
            pass
    return {"cpu": total_cpu, "mem": total_mem}


async def event_stream():
    while True:
        # CPU
        cpu_total = psutil.cpu_percent()
        cpu_per_core = psutil.cpu_percent(percpu=True)
        cpu_temps = psutil.sensors_temperatures().get("coretemp", [])

        temps = [t.current for t in cpu_temps] if cpu_temps else []

        # RAM / DISK
        ram = psutil.virtual_memory().percent
        disk = psutil.disk_usage('/').percent

        # GPU
        gpu = get_gpu_stats()

        # Processes
        jellyfin = get_process_usage("jellyfin")
        firefox = get_process_usage("firefox")
        n8n = get_process_usage("n8n")

        payload = {
            "cpu": cpu_total,
            "cpu_cores": cpu_per_core,
            "cpu_temps": temps,
            "ram": ram,
            "disk": disk,
            "gpu": gpu["util"],
            "gpu_temp": gpu["temp"],
            "jellyfin": jellyfin,
            "firefox": firefox,
            "n8n": n8n
        }

        yield f"data: {json.dumps(payload)}\n\n"
        await asyncio.sleep(1)


@app.get("/events")
async def events():
    return StreamingResponse(event_stream(), media_type="text/event-stream")


@app.get("/", response_class=HTMLResponse)
async def root():
    return HTMLResponse(open("index.html").read())


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
