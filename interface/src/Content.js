import React, { useState, useEffect } from 'react';
import axios from 'axios';
import { Routes, Route } from 'react-router-dom';
import Home from './Home';
import Device from './Device';
import Controller from './Controller';
import Devices from './Devices';


const Content = ({}) => {
    return (
        <Routes>
            <Route exact path='/' Component={Home}></Route>
            <Route path='/devices/:device_id' Component={Device}></Route>
            <Route path='/controllers/:controller_id' Component={Controller}></Route>
            <Route exact path='/devices' Component={Devices}></Route>
        </Routes>
    );
}

export default Content;