// Device cards show a preview and when clicked take us to the device page

import React, { useState } from 'react';
import { post_name } from './DeviceJSCode/utils';
import { TEInput } from "tw-elements-react";

const DeviceName = ({device, drivers}) => {
    const device_name = device.name ? device.name : drivers.find(e => e.driver_id === device.driver_id).name;

    const [input, setInput] = useState(device_name);
    return(
      <div className="text-lg rounded-md border border-black border-opacity-10 items-center">
        <div className='text-lg'>{device_name}</div>
        <TEInput
            type="text"
            id="exampleFormControlInputText"
            label="Text input"
            value={input}
            onInput={e => setInput(e.target.value)}
            onSubmit={post_name(device, input)}
        ></TEInput>
      </div>
    );
}


export default DeviceName;