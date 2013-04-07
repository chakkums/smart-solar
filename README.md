smart-solar
===========

A remote condition monitoring system for battery charging stations in developing countries such as The Gambia.

Arduino
-------
Contains all code used to control a 2G SM5100B modem, and send and receive data to a remote server.

Java Server
-----------
Multi-threaded server used to receive data from remote system, parse and update SQL database, and send messages containg asset condition back to remote system.

Web Application
---------------
Includes: Javascript charts and tables to show data, PHP login/registration system, user enabling/disabling of assets.

Android
---------------
Application developed using PhoneGap to scan a battery's barcode, and then show data loaded from remote server.

Testing
---------------
Files used for prototyping, and testing certain features of entire system.
