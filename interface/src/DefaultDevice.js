import React, { useState, useEffect } from 'react';
import {useParams} from "react-router-dom";
import { TERipple, TEInput } from 'tw-elements-react';
import * as Devices from './DeviceComponents';
import axios from 'axios';


const drivers_list = [
  {
    "driver_id": 1,
    "name" : "LED",
    "actions" : [{name: "set", params: [{name: "on", type: "bool"}]}]
  }
]

const handle_click = () => {

};

const default_value = (type) => {
  if (type == "bool") {
    return true;
  } else if (type == "string") {
    return "";
  }
}


/*const driver_map = {
  "LED": LED
}*/

const d = {"device_id": "1", "driver_id": 1, "state": [{name: "on", type: "bool", value: true}]}


const DefaultDevice = ({ }) => {
  const {device_id} = useParams();
  //const [driver, setDriver] = useState([]);
  const [device, setDevice] = useState({});
  const [param_data, setParams] = useState([]);
  var driver = {};
  //setDevice(devices.find(e => e.device_id === device_id));

  const fetchDevice = async () => {
    //try {
      //const response = await axios.get('/api/devices/' + device_id);
      setDevice(d);
      driver = (drivers_list.find(element => element.driver_id === d.driver_id));

      if(Object.keys(param_data).length === 0) {
        var params = driver.actions;
        params.forEach(element => {
          element.params.forEach(param =>
            param.value = default_value(default_value)
          );
        });
        setParams(params);
      }
      //console.log(Devices[driver.name]({device: d}));
      //console.log(response);
      //setDevice(response);
    //} catch (error) {
      //console.error('Error fetching controllers:', error);
    //}
  };

  useEffect(() => {
    fetchDevice();
  }, []);

  //setInterval(fetchDevice, 1000);

  driver = (drivers_list.find(element => element.driver_id === device.driver_id));

  const handle_submit = () => {

  };  

  console.log(param_data)
  
  //console.log(Component != null && Object.hasOwn(device, 'driver_id'))
  //console.log(out);
  return ( 
      <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
        <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
            {Object.keys(device).length === 0 ? "Loading" : drivers_list.find(element => element.driver_id === device.driver_id).name}
        </h5>
        <div className="mb-4 text-base text-neutral-600 dark:text-neutral-200">
          Driver: {device.driver_id}
          <br></br>
          State: {device.state != null ? device.state.map(state => (
            <p>{state.name} : {state.value.toString()}</p>
          )) : <div></div>}
        </div>
        {param_data != null ? param_data.map(action => (
          <div>
          <TERipple>
            <button type="button" onClick={() => handle_submit(action)}
            className="inline-block rounded bg-primary px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out hover:bg-primary-600 hover:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.3),0_4px_18px_0_rgba(59,113,202,0.2)] focus:bg-primary-600 focus:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.3),0_4px_18px_0_rgba(59,113,202,0.2)] focus:outline-none focus:ring-0 active:bg-primary-700 active:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.3),0_4px_18px_0_rgba(59,113,202,0.2)] dark:shadow-[0_4px_9px_-4px_rgba(59,113,202,0.5)] dark:hover:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.2),0_4px_18px_0_rgba(59,113,202,0.1)] dark:focus:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.2),0_4px_18px_0_rgba(59,113,202,0.1)] dark:active:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.2),0_4px_18px_0_rgba(59,113,202,0.1)]">
              {action.name}
            </button>
          </TERipple>
          {action.params.map(param => (
            <div>
              {param.type == "bool" ? 
                <TERipple>
                  <button type="button" onClick={() => {
                    console.log(param.value);
                    setParams(prev_value => 
                      prev_value.map(
                        a => a.name === action.name ? a.params.map(
                          {...a, 
                            params: p => p.name === param.name ? {...p, value: param.value ? false : true} : p }
                        ) : a
                      )
                    );
                  }}
                  className="inline-block rounded bg-primary px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out hover:bg-primary-600 hover:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.3),0_4px_18px_0_rgba(59,113,202,0.2)] focus:bg-primary-600 focus:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.3),0_4px_18px_0_rgba(59,113,202,0.2)] focus:outline-none focus:ring-0 active:bg-primary-700 active:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.3),0_4px_18px_0_rgba(59,113,202,0.2)] dark:shadow-[0_4px_9px_-4px_rgba(59,113,202,0.5)] dark:hover:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.2),0_4px_18px_0_rgba(59,113,202,0.1)] dark:focus:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.2),0_4px_18px_0_rgba(59,113,202,0.1)] dark:active:shadow-[0_8px_9px_-4px_rgba(59,113,202,0.2),0_4px_18px_0_rgba(59,113,202,0.1)]">
                    {param.value ? "On" : "Off"}
                  </button>
                </TERipple> : param.type == "string" ?
                <TEInput
                  type="text"
                  id="exampleFormControlInput1"
                  label="Example label"
                >

                </TEInput>
            
                : <p>Error</p>}
          </div>
          ))}
          </div>

        )) : <div></div>}
        
      </div>
   );
};

export default DefaultDevice;
