import React, { useState } from 'react';
import { TERipple } from 'tw-elements-react';
import { post_event } from './utils';

const Window = ({ device }) => {
    const [windowState, setWindowState] = useState('closed');
    const [ultrasonicState, setUltrasonicState] = useState(false);

    console.log(device);

    const handleWindowAction = (action) => {
        // Perform window action (open/close)
        setWindowState(action);
        // Here you can also post the event to your backend if needed
        // post_event(device, "window_action", { action });
    };

    const handleUltrasonicToggle = () => {
        // Toggle ultrasonic sensor state
        setUltrasonicState(!ultrasonicState);
        // Here you can also post the event to your backend if needed
        // post_event(device, "ultrasonic_toggle", { state: !ultrasonicState });
    };

    return (
        <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
            <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
                Window Motor
            </h5>
            <p className="mb-4 text-base text-neutral-600 dark:text-neutral-200">
                Window State: {windowState}
            </p>
            <div className="flex justify-between mb-4">
                <TERipple>
                    <button
                        type="button"
                        onClick={() => handleWindowAction('open')}
                        className="rounded bg-blue-500 px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out focus:outline-none focus:ring-0"
                    >
                        Open
                    </button>
                </TERipple>
                <TERipple>
                    <button
                        type="button"
                        onClick={() => handleWindowAction('closed')}
                        className="rounded bg-red-500 px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out focus:outline-none focus:ring-0"
                    >
                        Close
                    </button>
                </TERipple>
            </div>
            <div className="flex justify-between">
                <p className="mb-2 text-base text-neutral-600 dark:text-neutral-200">Ultrasonic Sensor:</p>
                <TERipple>
                    <button
                        type="button"
                        onClick={handleUltrasonicToggle}
                        className={`rounded ${
                            ultrasonicState ? 'bg-green-500' : 'bg-red-500'
                        } px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out focus:outline-none focus:ring-0`}
                    >
                        {ultrasonicState ? 'On' : 'Off'}
                    </button>
                </TERipple>
            </div>
        </div>
    );
};

export default Window;
