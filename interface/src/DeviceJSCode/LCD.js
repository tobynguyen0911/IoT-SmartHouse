import React, { useState } from 'react';
import { post_event } from './utils';
import { TEInput } from "tw-elements-react";

const LCD = ({ device }) => {
    const [input, setInput] = useState("text");

    return (
      <div className="block rounded-lg bg-white p-6 shadow-[0_2px_15px_-3px_rgba(0,0,0,0.07),0_10px_20px_-2px_rgba(0,0,0,0.04)] dark:bg-neutral-700">
        <h5 className="mb-2 text-xl font-medium leading-tight text-neutral-800 dark:text-neutral-50">
            LCD
        </h5>
        <p className="mb-4 text-base text-neutral-600 dark:text-neutral-200">
          Driver: {device.driver_id}
          <br></br>
          State: {device.state.find(element => element.name==="text").value}
        </p>
        <TEInput
            type="text"
            id="exampleFormControlInputText"
            label="Text input"
            value={input}
            onInput={e => setInput(e.target.value)}
            onSubmit={post_event(device, "set", input)}
        ></TEInput>
      </div>
    );
};

export default LCD;