# sip_and_puff
A sip and puff device to control your computer

## Problem setting 

When interviewing visitors using our web platform with alternative input devices the sip and puff device showed up several times. A check online showed these devices are selling for at least 250 Euro, but easily do more than a thousand.

To have such a device available to test, but also create a way to let people who depend on such devices to use our site this project we will investigate, design, program and build such a device. The target is to have it available for around 10 Euros.


## Initial setup

The base setup will run on an Arduino Pro Micro (replaced the Arduino Nano with a Arduino Pro Micro as that one has Keyboard support).
A tube will be connected to 4 sensors that can detect sip and puff actions, that can bring the user 8 different actions that the arduino can translate into keyboard actions and send to the computer via USB. Also combinations of sip and puff actions can be combined to add more actions.

As moist should be prevented from entering the sensors Anti-tar cigarette filters should be placed on the inlets. A filter will be ok for about a week of usage and should be replaced after.

To create create a tight connection for the tar-filter mouht pieces I used heat-proof electric-wire insulation tape, cut in half and wrap arround the inlets twice. The tape needed replacedment after a year of usage.

## Base prices

Prices checked on 9 Februari 2023 all including shipping. Mostly using AliExpress

### Fixed prices:
- Arduino Pro Micro (32u4): € 4,98
- HX710b pressure sensor (PSG010R) (4x): € 1,24
- 2m Cable micro usb: € 1,15
- LED (2x): € 0,04

Total fixed costs: 11,17


### Dynamic prices:
- PLA: € 0,05 meter
- 28AWG cable: € 0,22 meter
- Silicon tube (food save): € 1,07 meter
- Anti-tar cigarette filters (100): € 8,50
- heat-proof electric-wire insulation tape (10cm): € 0,02
