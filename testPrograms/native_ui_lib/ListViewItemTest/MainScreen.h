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
 * @file MainScreen.h
 * @author Bogdan Iusco.
 */

#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_

#include <maapi.h>
#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>

using namespace NativeUI;

/**
 * Class that creates a screen that displays an ListView.
 */
class MainScreen:
	public Screen,
	public ListViewListener,
	public ButtonListener
{

public:
	/**
	 * Constructor.
	 */
		MainScreen();

	/**
	 * Destructor.
	 */
	~MainScreen();

private:
    /**
     * This method is called when a list view item is clicked.
     * @param listView The list view object that generated the event.
     * @param listViewItem The ListViewItem object that was clicked.
     */
    virtual void listViewItemClicked(
        ListView* listView,
        ListViewItem* listViewItem);

    /**
     * This method is called when there is an touch-down event for
     * a button.
     * @param button The button object that generated the event.
     */
    virtual void buttonPressed(Widget* button) {};

    /**
     * This method is called when there is an touch-up event for
     * a button.
     * @param button The button object that generated the event.
     */
    virtual void buttonReleased(Widget* button) {};

    /**
     * This method is called if the touch-up event was inside the
     * bounds of the button.
     * @param button The button object that generated the event.
     */
    virtual void buttonClicked(Widget* button);

	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainLayout();

	/**
	 * Function for testing the "text" property
	 * Sets the text displayed on the item
	 */
	void setItemText(ListViewItem *item, const MAUtil::String &text);

	/**
	 * Function for testing the "background" property
	 */
	void setItemBackground(ListViewItem *item, int color);

	/**
	 * Function for testing the "Icon" property
	 * Sets an icon of the list view item that is placed to the left of the text
	 */
	void setItemIcon(ListViewItem *item, MAHandle image);

	/**
	 * Function for testing the "accessoryType" property.
	 * Sets the type of list item displayed.
	 * Provides the corresponding icon in the right side of the list view.
	 * This is not available for Windows Phone. The "accessoryType" should
	 * have no effect.
	 */
	void setItemAccessoryType(ListViewItem *item, NativeUI::ListViewItemAccessory accessory);

	/**
	 * Function for testing the "fontSize" property
	 * Sets the font size of the text part
	 */
	void setItemFontSize(ListViewItem *item, int size);

	/**
	 * Function for testing the "fontColor" property
	 * Sets the font color of the text
	 */
	void setItemFontColor(ListViewItem *item, int color);

	/**
	 * Function for testing the "fontHandle" property.
	 * The "font" property sets the typeface and style in which the text
	 * should be displayed
	 */
	void setItemFont(ListViewItem *item);

private:
	/**
	 * Main layout.
	 */
	VerticalLayout* mMainLayout;

	ListView* mListView;

	Button* mAddItemButton;
	Button* mRemoveItemButton;

	MAUtil::Vector<Widget*> mVector;
};


#endif /* MAINSCREEN_H_ */
