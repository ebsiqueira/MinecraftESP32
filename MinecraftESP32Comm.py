from mcpi.minecraft import Minecraft
import socket
import requests
import time

mc = Minecraft.create()  # Connect Minecraft to localhost
esp32_ip = "XXX.XXX.X.XXX"  # ESP32 IP
esp32_port = 80           # ESP32 Port

def send_to_esp32(command):
    try:
        url = f"http://{esp32_ip}/{command}"
        response = requests.get(url, timeout=5)
        print(f"Sent {command}, response: {response.status_code}")
    except Exception as e:
        print(f"Erro ao conectar ao ESP32: {e}")

def check_rfid():
    try:
        url = f"http://{esp32_ip}/rfid"
        response = requests.get(url, timeout=5)
        return response.text == "1"
    except Exception as e:
        print(f"Error checking RFID: {e}")
        return False

while True:
    # Control the LED with the lever
    block = mc.getBlockWithData(514, 63, -76)  # Lever coordinates
    if block.data == 14:
        send_to_esp32("ON")
    elif block.data == 6:
        send_to_esp32("OFF")
    
    # Control door with RFID
    if check_rfid():
        print('Valid RFID card detected - opening door')
        # Get the current state of the door          
        door_block = mc.getBlockWithData(516, 63, -74)
        print(door_block.id)
        print(door_block.data)
        # Open the door for 3 seconds       
        mc.setBlock(516, 63, -74, 71, 4)  # Open the door
        time.sleep(3)
        mc.setBlock(516, 63, -74, 71, 0)  # Close the door