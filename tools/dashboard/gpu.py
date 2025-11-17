import warnings
warnings.filterwarnings("ignore", category=FutureWarning)

import pynvml

try:
    pynvml.nvmlInit()
except:
    pass


def get_gpu_stats():
    try:
        h = pynvml.nvmlDeviceGetHandleByIndex(0)
        util = pynvml.nvmlDeviceGetUtilizationRates(h).gpu
        temp = pynvml.nvmlDeviceGetTemperature(h, pynvml.NVML_TEMPERATURE_GPU)
        mem = pynvml.nvmlDeviceGetMemoryInfo(h)

        return {
            "util": util,
            "mem_used": mem.used,
            "mem_total": mem.total,
            "temp": temp
        }
    except:
        return {"util": 0, "mem_used": 0, "mem_total": 0, "temp": 0}
