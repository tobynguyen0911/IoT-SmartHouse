// Device cards show a preview and when clicked take us to the device page

import React, { useState } from 'react';


const DeviceCard = ({device, drivers}) => {
    const device_name = device.name ? device.name : drivers.find(e => e.driver_id === device.driver_id).name;
    return(
      <div className="w-36 rounded-md border border-black border-opacity-10 flex-col justify-start items-center inline-flex">
        <a href={"/devices/".concat(device.device_id)}>
            <div className="self-stretch h-14 p-2 flex-col justify-start items-start gap-1 flex">
                <div className="self-stretch text-black text-base font-medium font-['Roboto'] leading-normal">{device_name}</div>
            </div>
        </a>
        
      </div>
    );
}


export default DeviceCard;