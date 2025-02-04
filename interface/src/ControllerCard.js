import { Link } from 'react-router-dom';
import React, { useState } from 'react';

import Device from './Device';
import axios from 'axios';

const device_const = [
  {
    "device_id": "uuid",
    "local_id": 111,
    "driver_id": 1
  }
]


const ControllerCard = ({ controller }) => {


  return (
    <a href={"/controllers/".concat(controller.controller_id)} className="self-stretch py-3 justify-center items-center gap-4 inline-flex">
      <div className="w-8 h-8 bg-black bg-opacity-5 rounded-2xl justify-center items-center flex">
        <div className="w-8 self-stretch text-center text-black text-xl font-normal font-['Roboto'] leading-loose">🏠</div>
      </div>
      <div className="grow shrink basis-0 flex-col justify-start items-start inline-flex">
        <div className="self-stretch text-black text-sm font-normal font-['Roboto'] leading-tight">Living Room</div>
        <div className="self-stretch text-black text-opacity-50 text-xs font-normal font-['Roboto'] leading-none">Connected</div>
      </div>
      <div className="text-right text-black text-sm font-medium font-['Roboto'] leading-tight">Devices: {controller.devices.length}</div>
    </a>
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

export default ControllerCard;
