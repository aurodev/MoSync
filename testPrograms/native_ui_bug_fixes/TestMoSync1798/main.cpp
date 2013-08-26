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

#include <ma.h>
#include <mavsprintf.h>
#include <MAUtil/Moblet.h>
#include <NativeUI/Widgets.h>
#include <NativeUI/WidgetUtil.h>

#include "AppStackScreen.h"

using namespace MAUtil;
using namespace NativeUI;

/**
 * Moblet to be used as a template for a Native UI application.
 */
class NativeUIMoblet : public Moblet
{
public:
	/**
	 * The constructor creates the user interface.
	 */
	NativeUIMoblet()
	{
		this->createUI();
	}

	/**
	 * Destructor.
	 */
	virtual ~NativeUIMoblet()
	{
		delete mAppStackScreen;
	}

	/**
	 * Create the user interface.
	 */
	void createUI()
	{
		mAppStackScreen = new AppStackScreen();
	}

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			// Call close to exit the application.
			close();
		}
	}

	/**
	* This method is called when there is an touch-down event for
	* a button.
	* Only for iphone platform.
	* @param button The button object that generated the event.
	*/
	virtual void buttonPressed(Widget* button)
	{
	};

	/**
	* This method is called when there is an touch-up event for
	* a button.
	* Only for iphone platform.
	* @param button The button object that generated the event.
	*/
	virtual void buttonReleased(Widget* button)
	{
	};

	/**
	* This method is called if the touch-up event was inside the
	* bounds of the button.
	* @param button The button object that generated the event.
	*/
	virtual void buttonClicked(Widget* button)
	{
	}

private:
	/**
	 * App's stack screen.
	 */
	AppStackScreen* mAppStackScreen;
};

/**
 * Main function that is called when the program starts.
 */
extern "C" int MAMain()
{
	Moblet::run(new NativeUIMoblet());
	return 0;
}
