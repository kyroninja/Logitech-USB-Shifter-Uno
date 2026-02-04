# Logitech Driving Force Shifter USB Adapter

## Prerequisites

* Logitech Driving Force Shifter (Used with G29, G920, and G923 steering wheels)
* Arduino UNO R3 (with atmega 16u2 chip or equivalent)
* USBasp programmer or other ISP programmer
* [Arduino IDE](https://www.arduino.cc/en/software)
* [HoodLoader2 by NicoHood](https://github.com/NicoHood/HoodLoader2)

## Wiring

![Shifter to Arduino wiring](/logitech_shifter_usb/images/wiring2.jpg)
The pinout is the same for the Arduino Uno

## Setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software)
2. Install Hoodloader2
3. Open Logitech_Shifter_G29_USBHID.ino and select "HoodLoader2 16u2" under board. Then use upload via programmer (connect ISP programmer first to 16u2 chip)
4. Open Logitech_Shifter_G29_Main.ino and select "HoodLoader2 Uno" under board. Then use upload programmer (connect ISP to atmega328p chip)
5. Plug the Arduino into the PC

## Testing

### Optional:

If you want to get the values correct for the axes and buttons - use the debug sketch, this needs the Arduino to be in normal (non Hoodloader2)

### Windows:

1. Open Settings
2. Click "Bluetooth and Devices"
3. Click "More Devices and Printer Settings"
4. Look for a device called "HoodLoader 16u2" (This should have like a Gamepad Icon)
6. Right-click the "HoodLoader 16u2" and click on "Properties"
7. Go to the "Test" tab and push the shifter into each gear. If buttons 1, 2, 3, 4, 5, 6 and 7 can all be seen as pressed (not at the same time), everything is working as it should.

If the shift values dont align - you have to adjust the code in the main file thats uploaded to the 328p
