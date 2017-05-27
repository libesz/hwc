# Hot Water Circulation with AVR

## The problem
This is a tiny project to control a water pump. In a typical domestic hot water system, there is a common problem that the water gets cold in the pipes if some faucets are too far. So you have to waste a lot of water (and time :) ) until you get the hot water, if is was not used recently.

The base of the solution is to build also a returning pipe between the last faucet and the boiler or hot water tank, where a pump can circulate the returning water, so that keeping the pipes hot.

The big question is that based on what event are you going to circulate the water? After a bit of googling you can find these ideas:
* Timer switch, programmed for the typical hot water use times (morning, evening).
* Thermostat: you somehow measure the returning water's temperature and control the pump when needed.
* Detect water usage: there are solutions which can detect when you use any faucet in the house. So you can trigger the circulation by using the e.g. shower for a second, than wait until the hot water arrive before you really start to use it.

## Solution
I was not impressed by any of the solutions above, even not with any combinations. Fortunately I had the pump and the returning pipe built in, so I can control it how I want.
My solution is based on the detection of motion in the house. I have a basic alarm system in the house with passive IR motion sensors in every rooms. The idea is that before every water usage, the people have to walk to the desired faucet. There might be additional time before you need the hot water, like you use the toilet first, for instance :). This time is most probably enough for the pump to get hot water everywhere.
I inspected my alarm system and found a programmable output on the board which can follow any selection of the motion sensors status, so it can trigger this AVR project, which will control the pump for a predefined time.
Also there is a hold timer, which will not switch on the pump ON again if the water is supposed to be still hot in the pipe.

The code is written in C++ and using my base library [from here](https://github.com/libesz/AvrCppBaseLib).

### HW:
* ATTINY45@1MHz
* Opto couplers for both input from the alarm system and towards the output
* 12V relay to control the pump

## Project documentation:
[Link](http://libesz.digitaltrip.hu/automatic-how-water-circulator/)
