import React, { useState, useEffect } from 'react';
import axios from 'axios';
import DeviceCard from './DeviceCard';
import Controller from './Controller';
import ControllerCard from './ControllerCard';

const controller_const = [
    {
      "Devices": [
        {
          "device_id": "uuid1",
          "local_id": 1,
          "driver_id": 1
        }
      ],
      "id": "123"
    },
    {
      "Devices": [
        {
          "device_id": "uuid2",
          "local_id": 2,
          "driver_id": 1
        }
      ],
      "id": "234"
    }
  ]
  
const drivers_list = [
  { "driver_id": 1, "name" : "LED" },
  { "driver_id": 3, "name" : "RainDetector" },
  { "driver_id": 4, "name" : "Fan" },
  { "driver_id": 5, "name" : "Window" },
  { "driver_id": 6, "name" : "PIRSensor" },
  { "driver_id": 7, "name" : "Buzzer" },
  { "driver_id": 8, "name" : "WaterSensor" },
  { "driver_id": 9, "name" : "SoilHumiditySensor" },
  { "driver_id": 10, "name" : "DHT11" },
  { "driver_id": 11, "name" : "MQ135" },
  { "driver_id": 12, "name" : "Smoke" },
  { "driver_id": 13, "name" : "PhotoSensor" },
  { "driver_id": 14, "name" : "SteamSensor" },
  { "driver_id": 15, "name" : "WaterPump" },
  { "driver_id": 16, "name" : "LCD" }
]

//const c = [{"_id": {"$oid": "6621fd2fc1ffa2398218795f"}, "local_id": 1, "devices": [{"local_id": 0, "driver_id": 4, "state": [{"name": "on", "type": "bool", "value": false}], "controller_id": 1, "device_id": "e37a36f8ffaf4808b2425365a75b79aa", "_id": {"$oid": "6621fd2fc1ffa23982187957"}}, {"local_id": 1, "driver_id": 1, "state": [{"name": "on", "type": "bool", "value": false}], "controller_id": 1, "device_id": "319839c9de754de9bb25936a49347e06", "_id": {"$oid": "6621fd2fc1ffa23982187958"}}, {"local_id": 2, "driver_id": 13, "state": [{"name": "value", "type": "int", "value": 0}], "controller_id": 1, "device_id": "df684cb62ee643e29875af58c9ff7ba3", "_id": {"$oid": "6621fd2fc1ffa23982187959"}}, {"local_id": 3, "driver_id": 14, "state": [{"name": "value", "type": "int", "value": 0}], "controller_id": 1, "device_id": "0d1fdcf56fa0430bb5e0318f2211f7ac", "_id": {"$oid": "6621fd2fc1ffa2398218795a"}}, {"local_id": 4, "driver_id": 8, "state": [{"name": "value", "type": "int", "value": 0}], "controller_id": 1, "device_id": "8e3a1c88d26f43e696dd535b0f4ff38b", "_id": {"$oid": "6621fd2fc1ffa2398218795b"}}, {"local_id": 5, "driver_id": 9, "state": [{"name": "value", "type": "int", "value": 0}], "controller_id": 1, "device_id": "89f1c92cbfbe4556a4e0f4a7cf9267d5", "_id": {"$oid": "6621fd2fc1ffa2398218795c"}}, {"local_id": 6, "driver_id": 15, "state": [{"name": "on", "type": "bool", "value": false}], "controller_id": 1, "device_id": "0392f9bb15a147cd9894b817a44a145e", "_id": {"$oid": "6621fd2fc1ffa2398218795d"}}, {"local_id": 7, "driver_id": 10, "state": [{"name": "temp", "type": "int", "value": 0}, {"name": "humidity", "type": "int", "value": 0}], "controller_id": 1, "device_id": "87ab947c83c149b6ac42391ee360e0cc", "_id": {"$oid": "6621fd2fc1ffa2398218795e"}}]}, {"_id": {"$oid": "6621fe22c1ffa2398218796b"}, "local_id": 3, "devices": [{"local_id": 0, "driver_id": 12, "state": [{"name": "smoke", "type": "int", "value": 0}], "controller_id": 3, "device_id": "b3352dcf20cd4452bd605afa39783ac6", "_id": {"$oid": "6621fe22c1ffa23982187968"}}, {"local_id": 1, "driver_id": 1, "state": [{"name": "on", "type": "bool", "value": false}], "controller_id": 3, "device_id": "54d17728a63345aebb9ce2b45a4beea7", "_id": {"$oid": "6621fe22c1ffa23982187969"}}, {"local_id": 2, "driver_id": 1, "state": [{"name": "on", "type": "bool", "value": false}], "controller_id": 3, "device_id": "1eac0da11bca43998dedf9c8cf302d03", "_id": {"$oid": "6621fe22c1ffa2398218796a"}}]}];


const Home = ({}) => {
    const [controllers, setControllers] = useState([]);
  
    useEffect(() => {
      const fetchControllers = async () => {
        try {
          const response = await axios.get('/api/controllers');
          setControllers(response.data);
        } catch (error) {
          console.error('Error fetching controllers:', error);
        }
      };
  
      fetchControllers();

      const interval= setInterval(fetchControllers, 250);

      return () => {
        clearInterval(interval)
      }
    }, []);
  
    return(
        <div className="grow shrink">
          <div className="px-3 pt-4 justify-start items-center gap-4 inline-flex">
            <div className="grow shrink basis-0 flex-col justify-start items-start inline-flex">
              <div className="self-stretch text-black text-lg font-medium font-['Roboto'] leading-normal">My Devices</div>
              <div className="self-stretch text-black text-opacity-50 text-xs font-normal font-['Roboto'] leading-none">Manage all your IoT devices</div>
            </div>
          </div>
          <div className="grow shrink self-stretch px-3 flex-col justify-center items-center gap-2 flex" name="DevicesDiv">
            <div className="grow shrink justify-start items-start gap-2 inline-flex flex-row flex-wrap">
              {controllers.map(controller => (
                controller.devices.map(device => (
                <DeviceCard key="device.device_id" device={device} drivers={drivers_list}/>
                ))
              ))}
            </div>
          </div>
          <div className="grow shrink h-28 px-3 flex-col justify-center items-center flex" name="ControllerDiv">
            {controllers.map(controller => (
              <ControllerCard key={controller.controller_id} controller={controller} />
            ))}
          </div>
        </div>
    );
}

export default Home;
export {drivers_list};
