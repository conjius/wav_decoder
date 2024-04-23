```
                              _                    _           
__      ____ ___   __      __| | ___  ___ ___   __| | ___ _ __
\ \ /\ / / _` \ \ / /____ / _` |/ _ \/ __/ _ \ / _` |/ _ \ '__|
 \ V  V / (_| |\ V /_____| (_| |  __/ (_| (_) | (_| |  __/ |   
  \_/\_/ \__,_| \_/       \__,_|\___|\___\___/ \__,_|\___|_|   

```
A C++20 .wav file decoder.

.wav file format specification taken from:

https://ccrma.stanford.edu/courses/422-winter-2014/projects/WaveFormat/

### Setup
#### Installation Requirements
1. `brew install cli11@2.4.1 spdlog@1.13.0`
2. Make sure you have a CMake version installed whose version is at least the version 
   stated in 
   `CMakeLists.txt`

### Usage
```wav_decoder -i ./resources/CantinaBand3.wav -fx volume=0.5```