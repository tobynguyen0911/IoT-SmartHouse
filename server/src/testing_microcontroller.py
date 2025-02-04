import requests
import argparse
import json
import sys

parser = argparse.ArgumentParser(
    prog='Simulate a microntroller'
)

parser.add_argument('-s', '--start', action='store_true', help='Controller whether or not the microcontroller simulation uploads at the beginning like it is turning on')
parser.add_argument('-v', '--value', action='store_true', help='Controller whether or not the microcontroller simulation uploads at the beginning like it is turning on')

device_struct = {
    "driver_id": 1,
    "local_id": 1,
    "state": [
        {
            "name": "on",
            "type": "bool",
            "value": True}
    ]
}

controller_struct = {
    "devices": [
        device_struct
    ],
    "local_id": 1
}

def main():
    args = parser.parse_args()
    host = "maxschaefer.me"
    
    r = requests.post(f"http://{host}/api/controllers", json=controller_struct)
    print(r)
    print(r.content)
    loaded = json.loads(r.content)
    loaded["devices"][0]["state"][0]["value"] = args.value

    r = requests.post(f"http://{host}/api/devices/{loaded['devices'][0]['device_id']}", json=loaded['devices'][0])
    print(r)
    print(r.content)
    

if __name__ == "__main__":
    main()