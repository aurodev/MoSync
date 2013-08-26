/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/**
 * @file Common.h
 * @author Mikael Kindborg
 *
 * Description:
 *
 *  This file contains variables and functions that
 *  are shared between the BluetoothServer project and
 *  the BluetoothClient project.
 *
 *  These projects demonstrate a how to write a Bluetooth
 *  server and client application. You need to build both
 *  projects and deploy to two devices to use this code
 *  example.
 *
 *  When making your own projects that use Bluetooth,
 *  note that you need to enable Bluetooth in
 *  Project/Properties/MoSync Project/Application Permissions.
 *
 * How to use:
 *
 *  You need two Bluetooth capable devices. Make sure that
 *  Bluetooth is turned on and that the devices are paired
 *  before running the server and the client applications.
 *
 *  Build and run the server application:
 *   - Build and run project BluetoothServer.
 *   - Deploy and launch the server application on the first device.
 *   - Note the Bluetooth device address that is displayed,
 *     it is to entered as the value for the variable
 *     sServerAddress in Client.cpp.
 *
 *  Build and run the client application:
 *   - Edit the value of the variable sServerAddress to be
 *     the address of the server in file Client.cpp in
 *     project BluetoothClient. (If you have not entered
 *     this address, a panic message is shown, and the
 *     application closes).
 *   - Build and run the project BluetoothClient.
 *   - Deploy and launch the client on the second device.
 *
 * How to verify that it works:
 *
 *  In the client application, press keys on key pad or touch the screen,
 *  this sends data to the server application. The data should be displayed
 *  on the server screen.
 *
 *  When a key for a printable character is pressed and it is
 *  usually sent one character at a time, but may buffer if the
 *  connection is (very) slow. Non-printable characters will
 *  not be sent.
 *
 *  When touching the screen, the string: "Touch event: <x,y>"
 *  is sent, where <x,y> is the touch coordinate, for example:
 *  "Touch event: 234,318".
 */

#ifndef COMMON_H
#define COMMON_H

/**
 * Size of buffer used for writing (server) and reading (client).
 */
static const int sBufferSize = 64;

/**
 * This is the service UUID string, shared between client and server.
 */
static const char* sServiceUUID = "102030405060708090A0B0C0D0E0F010";

/**
 * Helper function that prints a divider to increase output readability.
 */
static void printDivider()
{
	printf("-----------------------------\n");
}

#endif // COMMON_H
