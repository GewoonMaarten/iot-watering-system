# IOT watering system 
Watering system with moisture sensor and firebase database.

## Firebase <img src="https://firebase.google.com/_static/images/firebase/touchicon-180.png" width="40">
This project uses Firebase from Google to store the data collected from the moisture sensor. The Arduino code only uploads the value from the moisture sensor and whether the pump is on to the database. There is a Nodejs project include which, when uploaded as a cloud function to the Firebase database will add a datetime to the newly added values. 

### The JSON structure
The cloud function will format a datetime based on the machine time. the format is a YYYY-MM-DD HH:mm:ss, e.g.: `2017-04-13 16:59:23`.
The Arduino codes add a boolean based on whether the pump is currently active. And the value the value of the moisture sensor is added.
This all combined gives the following data structure: 
``` JSON
{
  "measurement" : {
    "-KgQiGUIjxPrxezXVW1H" : {
      "dateTime" : "2017-04-13 16:59:23",
      "isWatering" : 0,
      "value" : 2.72
    }
  }
} 
```

## The Hardware
### Parts list:
I bought most of the things on Ali Express so thats where I will provide links for.
* [WEmos D1 mini](https://www.aliexpress.com/item/D1-mini-V2-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/32529101036.html?spm=2114.13010608.0.0.lmmSkm)
* [Power Relay (5v)](https://www.aliexpress.com/item/10PCS-RELAY-5V-SRD-5VDC-SL-C-T73-5V-Power-Relay-NEW/32444246523.html?spm=2114.13010608.0.0.lmmSkm)
* [Small pump](https://www.aliexpress.com/item/1Pcs-DC-12v-D2-Small-Dosing-Pump-2mm-DIY-Peristaltic-Tube-Head-For-Aquarium-Lab-Chemical/32650282709.html?spm=2114.13010608.0.0.lmmSkm)
* [Tube](https://www.aliexpress.com/item/3M-2-4mm-2x4mm-Creamy-White-Black-Red-Yellow-Medical-Food-Grade-Drink-Machine-Flexible-Pipe/32787873264.html?spm=2114.13010608.0.0.lmmSkm)
* [Moisture sensor](https://www.aliexpress.com/item/1Pcs-Soil-Hygrometer-Detection-Module-Soil-Moisture-Sensor/2035877568.html?spm=2114.13010608.0.0.lmmSkm)
* A way to convert 12v to 5v. Is used [this](https://www.aliexpress.com/item/8pcs-10W-Breadboard-Power-Module-DC-6-5V-23V-12V-to-5V-DC-DC-Converter-replace/32326359914.html?spm=2114.13010608.0.0.lmmSkm). But you could use a 5v regulator.
* Diode
* NPN transistor. I used a BC547
* Wire
* 12v powersupply with 5.5 * 2.1mm DC jack

For this project I made a super scientific representation of the hardware: <br />
![hardware](https://github.com/GewoonMaarten/iot-watering-system/blob/master/layout%20schematic.jpg)

The final product: <br />
<img src="https://github.com/GewoonMaarten/iot-watering-system/blob/master/final%20board.jpg" width="200"><img src="https://github.com/GewoonMaarten/iot-watering-system/blob/master/final%20assembly.jpg" width="450">

#### Related
How to plot the sensor data:
[Systems.maartens.website](http://maartens.website/)

License: [MIT](https://github.com/GewoonMaarten/iot-watering-system/blob/master/LICENSE)
