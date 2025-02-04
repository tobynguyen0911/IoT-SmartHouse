import React, { useState } from 'react';
import { TERipple } from 'tw-elements-react';
import { post_event } from './utils';

const PIRSensor = ({ device }) => {
    console.log(device);
    const intruderDetected = device.state.find(element => element.name==="pir").value > 2000;

    return (
        <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
            <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
                PIR Sensor
            </h5>
            {intruderDetected ? (
                <p className="mb-4 text-base text-red-600 dark:text-red-400">
                    Possible Intruders
                </p>
            ) : (
                <p className="mb-4 text-base text-neutral-600 dark:text-neutral-200">
                    No Suspicious Movement
                </p>
            )}
            {intruderDetected && (
                <TERipple>
                    <button
                        type="button"
                        className="mt-2 inline-block rounded bg-gray-400 px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out hover:bg-gray-500 focus:bg-gray-500 focus:outline-none focus:ring-0"
                    >
                        Reset
                    </button>
                </TERipple>
            )}
        </div>
    );
};

export default PIRSensor;
