# capstone-arduino-code
Code for an ESP8266 to receive valve states from the capstone backend

To try this code, attach an ESP8266 to your computer, open the Arduino IDE with the ESP8266 add-in (search Google for that part),
and upload this code.

Successful output looks like this:

```
attempting to connect to YourWifiName
.......
connected to wifi!
BEGINNING OF MAIN LOOP
connecting to the api at: 0z02zemtz2.execute-api.us-east-2.amazonaws.com
Printing the status of valve: 67 - Off
Printing the status of valve: 70 - On
Printing the status of valve: 66 - On
Printing the status of valve: 68 - Off
Printing the status of valve: 69 - Off
Printing the status of valve: 65 - On

```
