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
 * @file ThirdScreen.cpp
 * @author emma
 *
 */

#include "ThirdScreen.h"

/**
 * Constructor.
 */
ThirdScreen::ThirdScreen() :
		Screen(),
		mMainLayout(NULL),
		mEditBox(NULL),
		mEventsList(NULL)

{
	createMainLayout();
	mEditBox->addEditBoxListener(this);
}

/**
 * Destructor.
 */
ThirdScreen::~ThirdScreen()
{
	mEditBox->addEditBoxListener(this);
}

/**
 * Creates and adds main layout to the screen.
 */
void ThirdScreen::createMainLayout()
{
	// Create and add the main layout to the screen.
	mMainLayout = new VerticalLayout();
	Screen::setMainWidget(mMainLayout);

	Label* mLabel = new Label("Multiline edit box.Check FINISHED EDITING and BEGIN_EDITING events.");
	mMainLayout->addChild(mLabel);

	mEditBox = new EditBox();
	mEditBox->setInputMode(EDIT_BOX_INPUT_MODE_ANY);
	mEditBox->fillSpaceHorizontally();
	mMainLayout->addChild(mEditBox);

	mEventsList = new ListView();
	mMainLayout->addChild(mEventsList);
	ListViewItem* info = new ListViewItem();
	info->setText("Events list:");
	mEventsList->addChild(info);
}

/**
 * This method is called when the return button was pressed.
 * On iphone platform the virtual keyboard is not hidden after
 * receiving this event.
 * @param editBox The edit box object that generated the event.
 */
void ThirdScreen::editBoxReturn(EditBox* editBox)
{
	if ( mEditBox == editBox )
	{
		ListViewItem* info = new ListViewItem();
		info->setText("EditBox return event" );
		mEventsList->addChild(info);
	}
}

/**
 * This method is called when an edit box gains focus.
 * The virtual keyboard is shown.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void ThirdScreen::editBoxEditingDidBegin(EditBox* editBox)
{
	if ( mEditBox == editBox )
	{
		ListViewItem* info = new ListViewItem();
		info->setText("BEGIN EDITING  event");
		mEventsList->addChild(info);
	}
}

/**
 * This method is called when an edit box loses focus.
 * The virtual keyboard is hidden.
 * Only for iphone platform.
 * @param editBox The edit box object that generated the event.
 */
void ThirdScreen::editBoxEditingDidEnd(EditBox* editBox)
{
	if ( mEditBox == editBox )
	{
		ListViewItem* info = new ListViewItem();
		info->setText("FINISHED EDITING event");
		mEventsList->addChild(info);
	}
}
