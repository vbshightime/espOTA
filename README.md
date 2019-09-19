
# ESP8266 OTA updates 
OTA updates to remotely update the ESP8266 firmware. First of all to initiate the update. First of all ofcourse we need a file to be updated :smile: . You should follow this procedure to export the binary of your arduino sketch.
- Go to **Sketch** -> **Export Compiled Binary**
- Once the compiling finishes then again go to **Sketch** -> **Show Sketch Folder**
- In the sketch folder you can see the compiled binary. This compiled binary is the key of ota updates :flushed:
- Now put this compiled binary on the host bucket the host can be Azure, AWS or any other cloud hosting services  

## How it works
- The file is bin file is first downloaded and is stored in SPIFF memory of ESP8266
- Then we check the size of the file received from server and file stored in SPIFF
- Then the update starts 
- After the Update ends The device will reset after 4 seconds
- Hurray....:+1: can you see your new sketch running?


