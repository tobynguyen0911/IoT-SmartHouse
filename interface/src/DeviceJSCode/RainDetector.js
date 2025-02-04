import React, { useState } from 'react';
import { TERipple } from 'tw-elements-react';
import { post_event } from './utils';

const RainDetector = ({ device }) => {
    const [isRaining, setIsRaining] = useState(false);

    console.log(device);

    const handleRainDetection = () => {
        // Simulate rain detection event
        setIsRaining(true);
        // Here you can also post the event to your backend if needed
        // post_event(device, "rain_detected", { value: true });
    };

    const handleReset = () => {
        // Reset rain detection state
        setIsRaining(false);
    };

    return (
        <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
            <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
                Rain Detector
            </h5>
            {isRaining ? (
                <p className="mb-4 text-base text-blue-600 dark:text-blue-400">
                    It is raining outside. Please bring an umbrella.
                </p>
            ) : (
                <p className="mb-4 text-base text-neutral-600 dark:text-neutral-200">
                    No Rain Detected
                </p>
            )}
            <TERipple>
                <button
                    type="button"
                    onClick={handleRainDetection}
                    className={`inline-block rounded ${
                        isRaining ? 'bg-blue-500' : 'bg-gray-400'
                    } px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out focus:outline-none focus:ring-0`}
                >
                    {isRaining ? 'It\'s Raining' : 'Check'}
                </button>
            </TERipple>
            {isRaining && (
                <TERipple>
                    <button
                        type="button"
                        onClick={handleReset}
                        className="mt-2 inline-block rounded bg-gray-400 px-6 pb-2 pt-2.5 text-xs font-medium uppercase leading-normal text-white shadow-[0_4px_9px_-4px_#3b71ca] transition duration-150 ease-in-out hover:bg-gray-500 focus:bg-gray-500 focus:outline-none focus:ring-0"
                    >
                        Reset
                    </button>
                </TERipple>
            )}
        </div>
    );
};

export default RainDetector;
