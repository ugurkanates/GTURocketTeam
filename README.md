# GTURocketTeam
Software used on Gebze Technical University Official First Low Altitude Rocket(4921 ft rocket- 1500+ meter) 

All avionic software created for Arduino Pro/Pro Mini module.Backup flight computer is Arduino Uno R3
Processor is ATmega328P 3.3V 8Mhz
Telemetry is 3DR 915 Mhz
For video we used FPV Module with 5.8 GHZ Camera. FPV camera can be watched via TFT screen or any EasyCap stick would work 
with PC and view can be seen programs such as VLC or your own program just uses any WebcamView as screen part.

We have used Kalman Filter for lowering sensor noisy data (mainly for acceleration sensor). It was getting data quite noisy before the hand. While there are many types of Kalman filter we opted for 1 parameter dependent rather basic approach. But this helped us to test better (faster is right word maybe) also help ease of Arduino usage.

All software belongs community of Aerospace and anyone who likes rockets and such. You can modify,manipulate,add contributions to code and notify me error/bug fixes and such. 

If you want to support us please contact us.
Thanks and be safe flying always !

GTU ROCKET TEAM - 2018

This Repo includes

- Libraries(dependencies) for sensors and other electronic parts. Most of them are taken directly with little to no modifications.
If there is any modifications it should be in readme text file of that sensor folder. Also includes why it was needed to include this
sensor / library. Most of them are written in C++.

- Main Flight Software that controls parachutes and flight in general. Created for Arduino , written in its language. ino file.

- Telemetry control (checks serial usb ports) (.sh script) and telemtry data for GPS tracking( Python 2.7)

If there are any thing you dont understand,any bugs,errors or contributions you want to add please let me know anywhere possible.
![alt text](https://raw.githubusercontent.com/ugurkanates/GTURocketTeam/master/IMG_1126.jpg)
![alt text](https://raw.githubusercontent.com/ugurkanates/GTURocketTeam/master/rocketfinaloutput.png)


ugurkanates97@gmail.com
uates@gtu.edu.tr
linkedin : uğurkan ateş
www.gtuhuk.com
