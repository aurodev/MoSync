/* Copyright (C) 2009 Mobile Sorcery AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

/** 
* \file Engine.h 
* \brief MAUI widget manager, useful for developing custom widgets
* \author Patrick Broman and Niklas Nummelin
*/

#ifndef _SE_MSAB_MAUI_ENGINE_H_
#define _SE_MSAB_MAUI_ENGINE_H_

#include "Widget.h"
#include "Font.h"
#include "Style.h"

#include <MAUtil/Map.h>
#include <MAUtil/Vector.h>
#include <MAUtil/String.h>
#include <MAUtil/Environment.h>

namespace MAUI {

	/** \brief Widget manager.
	  *
	  * This class manages the MAUI widget system. It is mainly of interest when
	  * when developing custom widgets.
	**/

	class Engine : public IdleListener, public FocusListener {
	public:
		/** Sets the widget that is main to the application, constituting the root of the UI tree **/
		void setMain(Widget* main);
		
		virtual ~Engine();

		void idle();
		
		/** Widgets call this function when they require repainting. It will cause 
		  * any dirty widgets to be redrawn in the next iteration of the event loop.
		  **/
		void requestUIUpdate();
		
		// added this because graphics can be invalidated on some devices when the focus is lost...
		void focusLost();
		void focusGained();

		/** Actually performs repainting **/ 
		void repaint();
		
		/** Returns a reference to the single instance of this class, using lazy
		  * initialization.
      	  **/
		static Engine& getSingleton();

		/* is an overlay shown? */
		bool isOverlayShown();

		/* shows the overlay (passed as an argument). Put the top left
		corner at position x and y. */
		void showOverlay(int x, int y, Widget *overlay);
		
		/* hide the currently shown overlay. */
		void hideOverlay();

		// if style already has been set, it just overwrites the element (not deleting the pointer).
		void setDefaultStyle(const String& widgetType, Style* style);
		const Style* getDefaultStyle(const String& widgetType) const;

		void setDisplayConsole(bool dc=true);

	protected:
		Widget *mOverlay;
		Point mOverlayPosition;

		Widget* mMain;

		static Engine* mSingletonPtr;

		bool mCharacterInputActive;

		// possibly change this to hash map.
		MAUtil::Map<String, Style*> mDefaultStyles;

		bool mDisplayConsole;

	private:
		Engine();
	};
}

#endif /*_SE_MSAB_MAUI_ENGINE_H_ */
