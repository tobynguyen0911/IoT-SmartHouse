import React, { useState, useEffect } from 'react';
import {useParams} from "react-router-dom";
import Device from './Device';
import axios from 'axios';
import DeviceCard from './DeviceCard';
import { drivers_list } from './Home';

const device_const = [
  {
    "device_id": "uuid",
    "local_id": 111,
    "driver_id": 1
  }
]


const Controller = ({ }) => {
  const {controller_id} = useParams();
  const [devices, setDevices] = useState([]);

  useEffect(() => {
    const fetchDevices = async () => {
      try {
        const response = await axios.get(`/controllers/${controller_id}/devices`);
        setDevices(response.data);
      } catch (error) {
        console.error(`Error fetching devices for controller ${controller_id}:`, error);
      }
    };
    
    fetchDevices();
  }, []);

  return (
    <div>
      <div className="self-stretch py-3 justify-center items-center gap-2 inline-flex">
        <div className="w-8 h-8 bg-black bg-opacity-5 rounded-2xl justify-center items-center flex">
          <div className="w-8 self-stretch text-center text-black text-xl font-normal font-['Roboto'] leading-loose">🏠</div>
        </div>
        <div className="grow shrink basis-0 flex-col justify-start items-start inline-flex">
          <div className="self-stretch text-black text-sm font-normal font-['Roboto'] leading-tight">Living Room</div>
          <div className="self-stretch text-black text-opacity-50 text-xs font-normal font-['Roboto'] leading-none">Connected</div>
        </div>
      </div>
      <div className="self-stretch h-52 px-3 flex-col justify-center items-center gap-2 flex" name="DevicesDiv">
        <div className="self-stretch justify-start items-start gap-2 inline-flex">
          {devices.map(device => (
            <DeviceCard key="device.device_id" device={device} drivers={drivers_list}/>
            ))}
        </div>
      </div>
    </div>
  );
};
/*
    <div className="controller rounded-xl border-4 border-black">
      <h2 className="text-secondary-400">{controller.id}</h2>
      <button onClick={fetchDevices} className='text-secondary-400'>Fetch Devices</button>
      {devices.map(device => (
        <Device key={device.id} device={device} driver_id={device.driver_id} />
      ))}
    </div>

*/

export default Controller;
