# IOT watering system 
Watering system with moisture sensor and firebase database.

## Firebase <img src="https://firebase.google.com/_static/images/firebase/touchicon-180.png" width="40">
This project uses Firebase from Google to store the data collected from the moisture sensor. The Arduino code only uploads the value from the moisture sensor and whether the pump is on to the database. There is a Nodejs project include which, when uploaded as a cloud function to the Firebase database will add a datetime to the newly added values. 

### The JSON structure
The cloud function will format a datetime based on the machine time. the format is a DD:MM:YYYY:HH:MM:SS, e.g.: ```"29:2:2017:20:22:25"```.
The Arduino codes add a boolean based on whether the pump is currently active. And the value the value of the moisture sensor is added.
This all commbined gives the following data structure: 
``` JSON
{
  "measurement" : {
    "-KgQiGUIjxPrxezXVW1H" : {
      "dateTime" : "29:2:2017:20:19:26",
      "isWatering" : 0,
      "value" : 2.72
    }
  }
} 
```

## The Hardware
For this project I made a super scientific representation of the hardware: <br />
![test](https://github.com/GewoonMaarten/iot-watering-system/blob/master/layout%20schematic.jpg)


