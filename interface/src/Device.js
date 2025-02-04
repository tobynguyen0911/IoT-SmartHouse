import React, { useState, useEffect, Component } from 'react';
import {useParams} from "react-router-dom";
import { TERipple, TEInput } from 'tw-elements-react';
import * as Devices from './DeviceJSCode/DeviceComponents';
import axios from 'axios';
import { drivers_list } from './Home';
import DeviceName from './DeviceName';



const default_value = (type) => {
  if (type == "bool") {
    return true;
  } else if (type == "string") {
    return "";
  }
}

const d = {"device_id": "1", "driver_id": 1, "state": [{name: "on", type: "bool", value: true}]}

const DeviceSelector = ({device, device_type}) => {
  
  const Component = Devices[device_type];

  return (Component ? <Component device={device} /> : null);

}


const Device = ({ }) => {
  const {device_id} = useParams();
  //const [driver, setDriver] = useState([]);
  const [device, setDevice] = useState({});
  //setDevice(devices.find(e => e.device_id === device_id));

  useEffect(() => {
    const fetchDevice = async () => {
      try {
        const response = await axios.get('/api/devices/' + device_id);
        //setDevice(d);
        console.log("refreshed");
        //console.log(Devices[driver.name]({device: d}));
        //console.log(response);
        setDevice(response.data);
      } catch (error) {
        console.error('Error fetching controllers:', error);
      }
    };

    fetchDevice();

    const interval= setInterval(fetchDevice, 250);

    return () => {
      clearInterval(interval)
    }
  }, []);
  
  //console.log(Component != null && Object.hasOwn(device, 'driver_id'))
  //console.log(out);
  return (device.driver_id ?  
    <div>
      <DeviceName device={device} drivers={drivers_list}></DeviceName>
      <DeviceSelector device={device} device_type={drivers_list.find((e) => (e.driver_id === device.driver_id)).name}></DeviceSelector>
    </div> : null);
};

export default Device;
