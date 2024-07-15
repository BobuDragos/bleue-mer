import serial
import time

def turn_on_led():
    # Replace 'COM3' with your Arduino's serial port
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    time.sleep(2)  # Wait for the serial connection to initialize
    
    ser.write(b'1')  # Send the command to turn on the LED
    ser.close()

if __name__ == "__main__":
    turn_on_led()

