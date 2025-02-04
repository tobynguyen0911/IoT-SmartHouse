import axios from "axios";
import { useEffect, useState } from "react";
import DeviceCard from "./DeviceCard";
import { drivers_list } from "./Home";


const Devices = ({}) => {
    const [devices, setDevices] = useState([]);
    useEffect(() => {
        const fetchDevices = async () => {
            try{
                var response = await axios.get("/api/devices");
                setDevices(response.data);
            } catch {
                console.log("Error fetching devices");
            }
        }

        fetchDevices();
    }
    ,[]);
    return (
        <div className="self-stretch items-center gap-2 inline-flex">
            {devices.map(device => 
                <DeviceCard key="device.device_id" device={device} drivers={drivers_list}></DeviceCard>
            )}
        </div>
    );
}

export default Devices;