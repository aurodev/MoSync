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

//******************************************************************************
// MinUI test program
//******************************************************************************

#include <conprint.h>
#include <MinUI/MinUI.h>
#include <MAUtil/Moblet.h>

#include "MAHeaders.h"

using namespace MinUI;

#define GREEN 0x40FF40
#define BRIGHT_RED 0xFF8080
#define SKY_BLUE 0x8080FF

//******************************************************************************
// Simple Layout-Label View
//******************************************************************************
#if 0
class MyView : public View {
public:
	MyView() : mLayout(NULL, 2) {
		View::mRootWidget = &mLayout;
		mLayout.add(new Label(&mLayout, "Hello", GREEN), 0);
		mLayout.add(new Label(&mLayout, "World", GREEN), 1);
		mLayout.add(new Label(&mLayout, "2", GREEN), 1);
		mLayout.add(new Label(&mLayout, "0", GREEN), 0);
		mLayout.add(new Label(&mLayout, "3", GREEN), 1);
		mLayout.add(new Label(&mLayout, "4", GREEN), 1);
		Extent s = maGetScrSize();
		MAPoint2d scrSize = { EXTENT_X(s), EXTENT_Y(s) };
		mLayout.setSize(scrSize);
	}
	virtual ~MyView() {}

	//View
	void keyPressEvent(int keyCode) {
		if(keyCode == MAK_0)
			maExit(0);
	}
	void keyReleaseEvent(int keyCode) {
	}
private:
	GridLayout mLayout;
};
#endif
//******************************************************************************
// View with everything
//******************************************************************************

class CompleteView : public View, public HyperlinkListener {
public:
	CompleteView() : mList(1) {
		View::mRootWidget = &mList;
		mList.setBackground(true);

		GridLayout* layout = new GridLayout(2);

		layout->add(new Image(R_IMAGE_1), 0);
		layout->add(new Image(R_IMAGE_2), 0);
		layout->add(new Label("Hello World!", GREEN), 1);	//should wind up on the top left?
		layout->add(new StringLabel("String", GREEN), 1);
		layout->add(new Textbox(10, 20, GREEN, GREEN), 1);

		mList.add(layout, 0, -1, true);
		Textbox* t = new Textbox(10, 200, GREEN, WHITE/*BRIGHT_RED*/);
		mList.add(t, 0, -1, true);
		t->setQwerty();
		t->activate();
		mList.add(new MultilineLabel("Line 1\nLine 10\nYet another line\n ", GREEN), 0);
		mList.add(new Label("Next label", WHITE), 0);
		mList.add(new HyperlinkLabel(this, "To close the program, \1click here\1.\n Now for a \1line-\nbroken\1 link.", GREEN, SKY_BLUE), 0);
	}
	virtual ~CompleteView() {}

	//View
	void keyPressEvent(int keyCode) {
		if(keyCode == MAK_0)
			maExit(0);
		if(keyCode == MAK_FIRE)
			mList.draw();
	}
	void keyReleaseEvent(int keyCode) {
	}

	//HyperlinkListener
	void click(int linkIndex) {
		printf("click %i\n", linkIndex);
	}
private:
	GridLayout mList;
};

//******************************************************************************
// Moblet
//******************************************************************************

class MyMoblet : public MAUtil::Moblet {
public:
	MyMoblet() {
		mView.show();
	}
private:
	CompleteView mView;
};

extern "C" int MAMain() {
	MAUtil::Moblet::run(new MyMoblet());
	return 0;
};
