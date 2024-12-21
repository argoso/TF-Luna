# ESP32 and Benewake TF Luna Lidar

Benewake TF Luna Lidar
https://files.seeedstudio.com/wiki/Grove-TF_Mini_LiDAR/res/SJ-PM-TF-Luna-A03-Product-Manual.pdf

Sample sketches for ESP32 and TF Luna serial mode and i2c mode. In the example I use the same GPIO pins 16 and 17 for both modes. In order for TF Luna to work in i2c mode, you need to connect its 5 pin to GND. For serial mode, you either connect it to 3.3V or you don't connect it at all. If you switch between one mode or another, you have to restart TF Luna's power, otherwise it won't understand that it has to change mode.
