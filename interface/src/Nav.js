import React, { useState, useEffect } from 'react';

const Nav = ({}) => {
    return(
      <div className="grid-span-1 place-content-center flex items-center justify-center">
        <a href="/" className="grow basis-0 p-1 flex-col justify-start items-center inline-flex">
          <div className="w-7 h-7 text-center text-black text-xl font-normal font-['Roboto'] leading-7">🏠</div>
          <div className="self-stretch h-3.5 text-center text-black text-xs font-normal font-['Roboto'] leading-none">Home</div>
        </a>
        <a href="/devices" className="grow basis-0 p-1 flex-col justify-start items-center inline-flex">
          <div className="w-7 h-7 text-center text-black text-xl font-normal font-['Roboto'] leading-7">📟</div>
          <div className="self-stretch h-3.5 text-center text-black text-xs font-normal font-['Roboto'] leading-none">Devices</div>
        </a>
      </div>
    );
}

export default Nav;