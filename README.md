# Algorithms I. - Project

## About

IoT Decoder.

## Compilation

To compile, run `make` from the workdir.

The executable is named `iotdecoder`.

## Usage

``` bash
  $ ./iotdecoder [input] [output] [num_of_intervals]
	 [input]  - input file required
	 [output] - output file required
	 [num_of_intervals] - number of intervals of the histogram
```

Test it with test data, run for example:

``` bash
./target/iotdec iot_sensor_data_1.txt iot_output.txt 12
```
or

``` bash
./target/iotdec iot_sensor_data_2.txt iot_output.txt 12
```

## Documentation

For Doxygen documentation run `firefox doxy/index.html`.
