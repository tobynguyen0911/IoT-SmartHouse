import axios from 'axios';

const post_event = async (device, func_name, params) => {
    var response = null;
    console.log(params);
    try {
        response = await axios.post("/api/devices/" + device.device_id + "/events", {device_id: device.device_id, controller_id: device.controller_id, name: func_name, params: params});
    } catch {
        console.log("Error posting event");
    }
    return response;
}

const post_name = async (device, name) => {
    var response = null;
    try {
        response = await axios.post("/api/devices/" + device.device_id, {device_id: device.device_id, name: name});
    } catch {
        console.log("Error posting event");
    }
    return response;
}


export {post_event, post_name};