<a href="https://youtu.be/RtVD5ZXKVWI">
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/youtube.jpg" /> 
</a></br>
  
Today we will make an automatic air humidifier with Arduino!
</br></br>

► Components</br></br>
The following parts were used in this project:</br>
ESP8266</br>
E-paper</br>
</br>
#Arduino #Arduinoproject #Covid-19 #Counter</br>
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/Circuit%20diagram.jpg" />


Note
1. When uploading the code, please do not connect to the RST of E-paper, otherwise the NodeMCU1.0 will always be in the reset state and the code will not be uploaded successfully. After uploading the code successfully, please connect RST to D4 and wait for the E-paper to refresh and display.
2. If you want to re-power on the electronic paper ink screen to refresh, please disconnect the jumper that connects the RST of the electronic ink screen to the RST of NodeMCU1.0, and then connect the jumper after power on.
3. Please keep the internet speed smooth, the COVID-19 value may need to be refreshed several times to appear, please be patient.

Steps 1: Download the development board and library
1.	Open File-Preferences, enter http://arduino.esp8266.com/stable/package_esp8266com_index.json in the input box of additional Boards Manger URLs, and click "OK".
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/01.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/02.jpg" />
2.	Install the development board: Open Tools-Board-Board Manager. Enter ESP8266 in the search box of Board Manager and install it.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/03.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/04.jpg" />
3.	Install the Library file: Open "Tools"-"Library Manager" in the Arduino development software, then search for “ GxEPD ” ,” Adafruit GFX Library ” , and then install them.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/05.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/06.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/07.jpg" />
Steps 2: Modify the code
1.	Modify the network name and WIFI password in the code.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/08.jpg" />
2.	Modify api_key in the code.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/09.jpg" />
3.	Go to https://www.worldometers.info/coronavirus/#countries and select the country you want to get COVID-19.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/091.jpg" />
4.	Go to https://thingspeak.com/ to create a new ThingHTTP.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/10.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/11.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/12.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/13.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/14.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/15.jpg" />
Steps 3: Compile and upload
1.	Choose the development board as NodeMCU 1.0（ESP-12E Module), this is to choose the right.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/16.jpg" />
2.	select the port, you can burn the code in the development board.
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/17.jpg" />
<img src="https://dkardu.oss-cn-hongkong.aliyuncs.com/covidcounter/18.jpg" />
