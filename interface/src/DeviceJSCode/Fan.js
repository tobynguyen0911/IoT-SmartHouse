import React, { useState } from 'react';
import { TERipple } from 'tw-elements-react';
import { post_event } from './utils';

const Fan = ({ device }) => {

    const handleFanToggle = () => {
        // Toggle fan state
        post_event(device, "set", ! device.state.find(element => element.name==="on").value);
        // Here you can also post the event to your backend if needed
        // post_event(device, "fan_toggle", { state: !fanState });
    };

    return (
        <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
            <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
                Fan
            </h5>
            <div className="flex justify-between">
                <p className="mb-2 text-base text-neutral-600 dark:text-neutral-200">Fan:</p>
                <TERipple>
                    <button
                        type="button"
                        onClick={handleFanToggle}
                        className={`rounded ${
                            device.state.find(element => element.name==="on").value ? 'bg-green-500' : 'bg-red-500'
                        } px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out focus:outline-none focus:ring-0`}
                    >
                        {device.state.find(element => element.name==="on").value ? 'On' : 'Off'}
                    </button>
                </TERipple>
            </div>
        </div>
    );
};

export default Fan;
