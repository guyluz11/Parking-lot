# parking-lot

This Arduino script is built in C that responsible for a parking lot mechanism with 2 gates (entrance and exit).

The code makes the gate rise up whan a car is detected in the infra-red proximity sensor,
and close the gate after few seconds if there isn't any car in front of the sensor.
The Arduino keeps count of how many cars are in the parking lot and displays the available parking spots.
Originally we planned to add an entrance condition, RFID card reader that would only allow people with specific cards to enter,
but due to lack of time and pins on our Arduino board we decided to skip this idea, although we can tweak everything so this works if we want to.

This folder includes the Arduino C code, the schematics diagram and a video of our built project.

![Parking-lot video](https://user-images.githubusercontent.com/9304740/65291180-de9ecf00-db5a-11e9-94f3-bb9249de782d.gif)
