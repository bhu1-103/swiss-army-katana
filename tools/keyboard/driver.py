import sys
import time
import os

# Confirmed device paths [cite: 15, 115]
DEVICE_PATHS = ["/dev/hidraw8", "/dev/hidraw7"]

def send_packet(f, data_bytes):
    """Pads the payload to 64 bytes and writes to the raw device."""
    data_list = list(data_bytes)
    padded_data = bytes(data_list + [0] * (64 - len(data_list)))
    f.write(padded_data)

def main():
    if len(sys.argv) < 2:
        print("Usage: sudo python driver.py \"HEX_STRING\"")
        sys.exit(1)

    raw_input = sys.argv[1]
    clean_hex = raw_input.replace(" ", "").replace(":", "").replace(",", "").replace("0x", "")

    try:
        user_payload = bytes.fromhex(clean_hex)
    except ValueError:
        print(f"Error: Invalid hex string.")
        sys.exit(1)

    # Validate that we have at least 4 bytes to find the Key ID [cite: 1, 9]
    if len(user_payload) < 4:
        print("Error: Hex string too short to identify Key ID.")
        sys.exit(1)

    # DYNAMIC KEY EXTRACTION
    # Byte 4 (index 3) is the physical Key ID [cite: 1, 9, 102]
    key_id = user_payload[3]
    
    # Construct the dynamic wrapper 
    # We use 0x00 for the 5th byte in the wrapper as seen in the 81 packets 
    # While your single-key packets use 0x01 for the "data" mode [cite: 9, 115]
    wrapper_packet = [0x06, 0x14, 0x03, key_id, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00]

    # Find device
    target_dev = next((d for d in DEVICE_PATHS if os.path.exists(d)), None)
    if not target_dev:
        print("Error: Device not found.")
        sys.exit(1)

    try:
        with open(target_dev, "wb") as f:
            # Step A: INIT specific to THIS key [cite: 1]
            send_packet(f, wrapper_packet)
            time.sleep(0.5) # 50ms is safer than 1s for responsiveness

            # Step B: Write your custom color payload [cite: 9, 115]
            send_packet(f, user_payload)
            time.sleep(0.1)

            # Step C: FINALIZE specific to THIS key 
            send_packet(f, wrapper_packet)
            
        print(f"Success: Targeted Key ID 0x{key_id:02x}")
        
    except Exception as e:
        print(f"Failed: {e}")

if __name__ == "__main__":
    main()
