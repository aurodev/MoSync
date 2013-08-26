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
 * @file MyMessageHandler.cpp
 * @author Mikael Kindborg
 *
 * Class that abstracts away some of the details of processing
 * messages from Wormhole (JavaScript).
 */

#include "MyMessageHandler.h"

MyMessageHandler::MyMessageHandler(NativeUI::WebView* webView) :
	mPhoneGapMessageHandler(webView),
	mNativeUIMessageHandler(webView),
	mResourceMessageHandler(webView)
{
}

MyMessageHandler::~MyMessageHandler()
{
	// Add cleanup code as needed.
}

void MyMessageHandler::init(MAHandle beepSound, Wormhole::WebAppMoblet* moblet)
{
	// Send the Device Screen size to JavaScript.
	MAExtent scrSize = maGetScrSize();
	int width = EXTENT_X(scrSize);
	int height = EXTENT_Y(scrSize);
	char buf[512];
	sprintf(
		buf,
		"{mosyncScreenWidth=%d; mosyncScreenHeight=%d;}",
		width,
		height);
	moblet->callJS(buf);

	// Set beep sound resource.
	mPhoneGapMessageHandler.setBeepSound(beepSound);

	// Initialize PhoneGap.
	mPhoneGapMessageHandler.initializePhoneGap();
}

void MyMessageHandler::addMessageFun(
	const char* command,
	MyMessageHandlerFun fun)
{
	mFunMap[command] = fun;
}

void MyMessageHandler::callMessageFun(
	const char* command,
	Wormhole::MessageStream& stream,
	Wormhole::WebAppMoblet* moblet)
{
	MyMessageHandlerFun fun = mFunMap[command];
	(moblet->*fun)(stream);
}

void MyMessageHandler::keyPressEvent(int keyCode, int nativeCode)
{
	// Forward to PhoneGap MessageHandler.
	mPhoneGapMessageHandler.processKeyEvent(keyCode, nativeCode);
}

/**
 * This method handles messages sent from the WebView.
 *
 * Note that the data object will be valid only during
 * the life-time of the call of this method, then it
 * will be deallocated.
 *
 * @param webView The WebView that sent the message.
 * @param urlData Data object that holds message content.
 */
void MyMessageHandler::handleWebViewMessage(
	NativeUI::WebView* webView,
	MAHandle data,
	Wormhole::WebAppMoblet* moblet)
{
	// Check the message protocol.
	Wormhole::MessageProtocol protocol(data);
	if (protocol.isMessageStreamJSON())
	{
		handleMessageStreamJSON(webView, data);
	}
	else if (protocol.isMessageStream())
	{
		handleMessageStream(webView, data, moblet);
	}
}

/**
 * Handles JSON messages. This is used by PhoneGap.
 *
 * @param webView A pointer to the web view posting this message.
 * @param data The raw encoded JSON message array.
 */
void MyMessageHandler::handleMessageStreamJSON(
	NativeUI::WebView* webView,
	MAHandle data)
{
	// Create the message object. This parses the message data.
	// The message object contains one or more messages.
	Wormhole::JSONMessage message(webView, data);

	// Loop through messages.
	while (message.next())
	{
		// This detects the PhoneGap protocol.
		if (message.is("PhoneGap"))
		{
			mPhoneGapMessageHandler.handlePhoneGapMessage(message);
		}
	}
}

/**
 * Handles string stream messages (generally faster than JSON messages).
 * This is used by the JavaScript NativeUI system.
 *
 * You can send your own messages from JavaScript and handle them here.
 *
 * @param webView A pointer to the web view posting this message.
 * @param data The raw encoded stream of string messages.
 */
void MyMessageHandler::handleMessageStream(
	NativeUI::WebView* webView,
	MAHandle data,
	Wormhole::WebAppMoblet* moblet)
{
	// Create a message stream object. This parses the message data.
	// The message object contains one or more strings.
	Wormhole::MessageStream stream(webView, data);

	// Pointer to a string in the message stream.
	const char* p;

	// Process messages while there are strings left in the stream.
	while (p = stream.getNext())
	{
		if (0 == strcmp(p, "NativeUI"))
		{
			//Forward NativeUI messages to the respective message handler
			mNativeUIMessageHandler.handleMessage(stream);
		}
		else if (0 == strcmp(p, "Resource"))
		{
			//Forward Resource messages to the respective message handler
			mResourceMessageHandler.handleMessage(stream);
		}
		else if (0 == strcmp(p, "close"))
		{
			// Close the application (calls method in class Moblet).
			moblet->close();
		}
		else if (0 == strcmp(p, "Custom"))
		{
			// Lookup and call function to handle custom message.
			const char* command = stream.getNext();
			if (NULL != command)
			{
				callMessageFun(
					command,
					stream,
					moblet);
			}
		}
	}
}
