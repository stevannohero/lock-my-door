##README

## INSTALL PYSERIAL WITH : pip install pyserial
## INSTALL FIREBASE WITH : pip install pyrebase

import serial
import time
import pyrebase
import datetime

# print now.year, now.month, now.day, now.hour, now.minute, now.second

config = {
    "apiKey" : "AIzaSyBjB_e8GmxbTDXXSEaaSWR1zI5O4bcOVXg",
    "authDomain" : "pbd-arduino-3b858.firebaseapp.com",
    "databaseURL" : "https://pbd-arduino-3b858.firebaseio.com",
    "storageBucket" : "pbd-arduino-3b858.appspot.com",
    "serviceAccount" : "serviceAccount.json"
  }


firebase = pyrebase.initialize_app(config)
db = firebase.database()
now = datetime.datetime.now()

#try without arduino
# logs = str(now.year) + "/" + str(now.month) + "/" + str(now.day) + "|" + str(now.hour) + ":" + str(now.minute) + " - hello world"
# db.child("logs").push(logs)

#try with arduino
mSerial = serial.Serial('/dev/ttyUSB1', 9600)
while 1:
    try:
         #baca dari serial
         inp = mSerial.readline()
         if inp != "":
            logs = str(now.year) + "/" + str(now.month) + "/" + str(now.day) + "|" + str(now.hour) + ":" + str(now.minute) + " - " + str(inp)[2:-5]
            #post ke firebase
            print(logs) 
            db.child("logs").push(logs)
        

         #sleep dikit 
         time.sleep(1)
    except mSerial.SerialTimeoutException:
        print('timeout - no data')
        #sleep sikit    
        time.sleep(1)
         


