## Software and tools  

#### Phenobottle_RaspberryPi.py  
Script which controls experiment  
Exports data to csv  
Can export data to database, but database must be set up and connected  
Code which export data to database is commented out  

#### OpticalDensity.py  
Measure optical density and prints value to terminal  
Useful for determination of initial optical density  

#### Fluorescence.py  
Perform one time measuring of fluorescence  
Data are printed to output  
Data can be visualized by using gnuplot tool  

#### Light_test.py  
Perform test of RGB lights on Phenobottle  
Tests all three colors at maximum intensity  

#### Motor_test.py  
Perform test of all motors in sequence: mixing, bubbling, pump  

#### OJIP_curve.sh  
Perform fluorescence measuring and plot graph  
When executed on RPi, which is connect via ssh, X11 forwarding must be enabled (`-X`) to show plot  
Or output format must be change in script to PNG  
Use `Fluorescence.py` and `Fluorescence.plt`  

#### Fluorescence.plt  
Gnuplot script for plotting curve from fluorescence measurement data saved in fluorescence.data file  
Script is used by `OJIP_curve.sh`  

#### Motor_HAT.py  
Library for motor control  

#### PCA9685.py.py  
Additional library for motor control  
