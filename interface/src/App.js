import React, { useState, useEffect } from 'react';
import axios from 'axios';
import Controller from './Controller';
import DeviceCard from './DeviceCard';
import Nav from './Nav'
import Content from './Content';



function App() {

  return (
    <div className="App">      
      <div className="grid-rows-8 min-h-screen">
        <div className="grid-span-7 w-full flex-col">
          <div className="bg-white shadow flex-col justify-start items-start flex">
            <div className="w-96 h-6 relative bg-white" />
            <div className="self-stretch pl-4 pr-2 py-3 justify-start items-center gap-2 inline-flex">
              <div className="grow shrink basis-0 text-black text-xl font-medium font-['Roboto'] leading-normal">IoT Smart Home Controller</div>
            </div>
          </div>
          <Content></Content>
        </div>
          
        <Nav />
      </div>
    </div>
  );
}

/*
      <div className="w-96 h-96 px-9 pt-10 pb-20 bg-white flex-col justify-start items-center inline-flex">
          <div className="self-stretch h-16 bg-white shadow flex-col justify-start items-start flex">
            <div className="w-96 h-6 relative bg-white" />
            <div className="self-stretch pl-4 pr-2 py-3 justify-start items-center gap-2 inline-flex">
              <div className="grow shrink basis-0 text-black text-xl font-medium font-['Roboto'] leading-normal">IoT Smart Home Controller</div>

*/

export default App;
