import React, { useState } from 'react';
import { TERipple } from 'tw-elements-react';
import { post_event } from './utils';

const Smoke = ({ device }) => {

    console.log(device);

    return (
        <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
            <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
                Smoke Sensor
            </h5>
            {(
                <p className="mb-2 text-base text-neutral-600 dark:text-neutral-200">
                    Smoke: {device.state.find(element => element.name==="smoke").value ? `${device.state.find(element => element.name==="smoke").value}` : "0"}
                </p>
            )}
        </div>
    );
};

export default Smoke;
