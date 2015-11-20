# Weather 95+20 #

Weather 95+20 is a weather forecast program designed for both vintage and modern PC workstations that uses Yahoo Weather API to retrieve weather details from a location requested by the user. It was written in C++ and uses wxWidgets GUI library. This program was created in order to celebrate the 20th Anniversary of Windows 95!

This product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org/).

### Getting to work in Windows 95 ###

In order to make the software work properly on your Windows 95 computer, you must have Microsoft Internet Explorer 5.0 or 5.5 and Windows Sockets 2 (Winsock 2) installed there. The Internet Explorer installers of those particular versions update some essential system files so that the main program window can be faultlessly presented on the screen and Winsock 2 is generally required by the network libraries included with the program.

### Handling the program ###

The program greets you with its main window where you are ready to type any desired location. If the location or some counterpart of it is successfully found in the Yahoo! Weather's database along with its data, one should get all the important details about the weather, such as: temperature, condition, pressure, wind speed and so on, that can be saved as a plain text file or also Clipboard contents for reference in the future.

Note: In Windows 9x operating systems, you may experience problems with copying and pasting details saved in Clipboard – this is because the function saves them in the format that's compatible only with programs that have pure Unicode support. The only workaround is to save them as an ANSI file.

### Program options ###

Weather 95+20 allows you to adjust the following settings: 

* Temperature unit – both Celsius and Fahrenheit are supported. This option also changes the units of distance (km or mi), pressure (mb or in) and wind speed (kph or mph) depending on the selected option.

* Time format – you can set the clock to be of 12-hour format (AM/PM) or 24-hour.

* Date format – twelve date patterns are available there to choose from.

* Target file encoding – depending on the selected option, your files will be saved in ANSI or Unicode (UTF-8) format. Keep in mind that some old software may not read UTF-8 files properly.

* Language – you can switch current interface language to a desirable one.

Make sure that you save new settings before exiting the application if you do not want to lose them.

### Recommended programming setup ###

Source and target OS: Windows

IDE: Code::Blocks Release 13.12 rev 9501 (2013/12/25 19:25:45) gcc 4.7.1 Windows/unicode - 32 bit

wxWidgets version: 2.8.12 (SHARED=0 MONOLITHIC=1 UNICODE=1 MSLU=1)

Additional info: The post-build script for Release contains the line that launches UPX (if it exists) in order to compress the executable file. Please change UPX directory to your desired one or simply remove the line if you do not have the program, otherwise the files from the "common" directory may not be successfully copied after compiling.

### Program licence ###

Weather 95+20 is published under The MIT License. Please refer to the LICENSE.txt file of this repository for more information regarding it.

This program also includes libraries and source codes that are necessary to successfully compile and launch the software. The licensing information regarding those are located in the Licenses directory.