Weather 95+20 2.0
Author: PeCeT_full
Website: http://www.pecetfull.pl
Copyright (c) by PeCeT_full 2015-2026. Weather 95+20 is published under The MIT License. For more information, please refer to Licence.txt included with the application.

If there are any problems or doubts, please contact me.

-------------------
Program description
-------------------

Weather 95+20 is a weather forecast program designed for both vintage and modern PC workstations that uses WeatherAPI.com API to retrieve weather details from a location requested by the user. It was written in C++ and uses wxWidgets GUI library. This program was created in order to celebrate the 20th Anniversary of Windows 95!

Minimal hardware and system requirements: 133 MHz or faster processor; 16 MB of available RAM; 3 MB of free hard disk space available where the program exists; Windows 95 or newer operating system; active Internet connection.

-----------------------------
Getting to work in Windows 95
-----------------------------

In order to make the software work properly on your Windows 95 computer, you must have Microsoft Internet Explorer 5.0 or 5.5 and Windows Sockets 2 (Winsock 2) installed there. The Internet Explorer installers of those particular versions update some essential system files so that the main program window can be faultlessly presented on the screen and Winsock 2 is generally required by the network libraries included with the program.

--------------------
Handling the program
--------------------

The program greets you with its main window where you are ready to type any desired location. If the location or some counterpart of it is successfully found in the WeatherAPI.com's database along with its data, one should get all the important details about the weather, such as: temperature, condition, pressure, wind speed and so on, that can be saved as a plain text file or also Clipboard contents for reference in the future.

Note: In Windows 9x operating systems, you may experience problems with copying and pasting details saved in Clipboard – this is because the function saves them in the format that's compatible only with programs that have pure Unicode support. The only workaround is to save them as an ANSI file.

---------------
Program options
---------------

Weather 95+20 allows you to adjust the following settings: 

* Measuring units – both metric and imperial are supported. This option changes the units of temperature (Celsius or Fahrenheit degrees), pressure (mb or in), precipitation (mm or in), distance (km or mi) and wind speed (kph or mph) depending on the selected option.

* Time format – you can set the clock to be of 12-hour format (AM/PM) or 24-hour.

* Date format – twelve date patterns are available there to choose from.

* Target file encoding – depending on the selected option, your files will be saved in ANSI or Unicode (UTF-8) format. Keep in mind that some old software may not read UTF-8 files properly.

* Language – you can switch current interface language to a desirable one.

Make sure that you save new settings before exiting the application if you do not want to lose them.

------------
Known issues
------------

WeatherAPI.com has issues with finding some towns after entering their valid name with diacritical marks, e.g. Tarancón in Spain. In such a case, you should try the name without diacritical marks – for Tarancón, it will be "Tarancon".
