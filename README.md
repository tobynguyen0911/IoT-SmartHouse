# IoT Smart Home

## All code should be tracked in this repository

### Directory Structure

```
proj/
├── server/
│   ├── src
│   ├── data
│   └── tests
├── common/
├── interface/
├── controller/
│   ├── main/
│   └── components/
└── hardware/
```

All subdirectories should adhere to the format above, all code files should go in a folder named 'src'. All tests for code should go in a folder named 'tests'. All data should go in a folder named 'data', etc.

Place in a README.md file in each top level subdirectory to explain how to use/run the files included.

- Write flexible software to handle any configuration of 
- Synchronization of the microcontrollers and web interface with the server accomplished with frequent HTTP requests.
- Server manages the current state of all devices in a MongoDB database.