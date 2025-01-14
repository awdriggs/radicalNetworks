import serial

try:
    # Replace '/dev/ttyUSB0' with your device's port
    ser = serial.Serial('/dev/tty.usbserial-0001', 115200, timeout=1)  # Add timeout for safety
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit()

try:
    while True:
        try:
            line = ser.readline().decode('utf-8').strip()
            if "Paxcounter" in line:
                print(line)  # Log or process Paxcounter data here
        except UnicodeDecodeError:
            # Handle any decoding errors
            continue
except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()

