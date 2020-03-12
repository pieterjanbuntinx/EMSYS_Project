# H1 Bare Metal Game for the Raspberry Pi B+

This project was made for a course at my university. I made a game for the Broadcomm BCM2835 SoC on the first Raspberry Pi B+. It was developed to use no OS and runs directly from the SD card in the RPI. The game uses a WS2812 LED strip with a configurable length to display everything and a Wii Classic Controller as input. The LED strip is controlled by the hardware PWM controller on the SoC and the controller was read out using I2C. More information can be found in the project report.
