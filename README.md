# Project Algorithms I.

## About

This project decodes IoT sensor data from an inputed file.

## Compilation

Before compiling, clone the repo by running `git clone https://github.com/phatt-23/alg-projekt.git`.
To compile it run `make` from the working directory.

The binary is in the `target` directory and is called `iotdec`.

## Usage

Run `./iotdec --help` to see the usage.

Test it with test data, run
```
`./target/iotdec iot_sensor_data_1.txt iot_output.txt`
```
or
```
`./target/iotdec iot_sensor_data_2.txt iot_output.txt`.
```

## Documentation

For Doxygen documentation run `firefox doxy/index.html`.