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
 * @file main.cpp
 * @author Bogdan Iusco
 *
 * @brief Application entry point.
 */

#include <MAUtil/Moblet.h>

#include "Controller/Controller.h"

namespace EuropeanCountries
{

	/**
	 * Application moblet.
	 */
	class NativeUIMoblet : public MAUtil::Moblet
	{
	public:
		/**
		 * Constructor.
		 */
		NativeUIMoblet()
		{
			mController = new EuropeanCountries::Controller();
		}

		/**
		 * Called when a key is pressed.
		 */
		void keyPressEvent(int keyCode, int nativeCode)
		{
			if (MAK_BACK == keyCode || MAK_0 == keyCode)
			{
				mController->backButtonPressed();
			}
		}

	private:
		/**
		 * Application controller.
		 */
		Controller* mController;
	};

} // end of EuropeanCountries

/**
 * Main function that is called when the program starts.
 */
extern "C" int MAMain()
{
	MAUtil::Moblet::run(new EuropeanCountries::NativeUIMoblet());
	return 0;
}
