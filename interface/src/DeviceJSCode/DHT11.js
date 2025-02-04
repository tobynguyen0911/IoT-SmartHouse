import React, { useState } from 'react';
import { TERipple } from 'tw-elements-react';
import { post_event } from './utils';

const DHT11 = ({ device }) => {

    console.log(device);

    return (
        <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
            <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
                DHT11 Sensor
            </h5>
            {(
                <p className="mb-2 text-base text-neutral-600 dark:text-neutral-200">
                    Temperature: {device.state.find(element => element.name==="temp").value ? `${device.state.find(element => element.name==="temp").value}°C` : "0"}
                </p>
            )}
            {(
                <p className="mb-2 text-base text-neutral-600 dark:text-neutral-200">
                    Humidity: {device.state.find(element => element.name==="temp").value ? `${device.state.find(element => element.name==="humidity").value}%` : "0"}
                </p>
            )}
        </div>
    );
};

export default DHT11;
