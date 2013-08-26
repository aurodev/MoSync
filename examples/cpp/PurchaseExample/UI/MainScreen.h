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
 * Class that creates a screen.
 * The screen consists of two main parts:
 *  - "Buy" section with a buy button and a list of available items for sale.
 *  - "History" section with a list of purchased items.
 *  For each purchased item there is a Receipt button.
 *  When the Receipt button is pressed a dialog/new screen shows the receipt details.
 *  @author Emma Tresanszki
 */

#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_

#include <maapi.h>

#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>
#include <Purchase/PurchaseManager.h>
#include "../Logic/ApplicationController.h"

using namespace NativeUI;
using namespace IAP;

/** Colors used for UI widgets. */
enum Colors{
	/** The background color for the main layout. */
	MAIN_LAYOUT_COLOR = 0x9BCD9B ,
	/** The color for the info labels. */
	INFO_LABELS_COLOR = 0x2200EE ,
	/** The color used for the products. */
	ITEMS_COLOR = 0x006400 ,
	/** The color used for the receipt fields. */
	RECEIPT_FIELD_COLOR = 0x98fb98,
	/** The color used for information. */
	INFO_BACKGROUND_COLOR = 0xEE0000,
	/** The color used for spacers. */
	BREAKLINE_COLOR  = 0x0000EE
};

/**
 * Class that creates a screen.
 * The screen consists of two main parts:
 *  - "Buy" section with a buy button and a list of available items for sale.
 *  - "History" section with a list of purchased items (along with the quantity).
 *  ( The owned items are retrieved from database repository.)
 *  For each purchased item there is a Receipt available.
 *  When one of the purchase items is selected, a dialog/new screen shows
 *  it's receipt details.
 */
class MainScreen:
	public Screen,
	ButtonListener,
	CheckBoxListener
{

public:
	/**
	 * Constructor.
	 */
	MainScreen(ApplicationController* appControler);

	/**
	 * Destructor.
	 */
	virtual ~MainScreen();

	Button* getBuyButton(){ return mBuyButton;}
	ListView* getPurchasedItemList(){ return mPurchasedItemsList;}

	/**
	 * Get the index for the selected product to buy.
	 * @return The product ID.
	 */
	MAUtil::String getSelectedAvailableProduct();

	/**
	 * Fill the items in the receipt dialog with values.
	 */
	void fillReceiptDialog(MAUtil::String appID, MAUtil::String productID,
			int transactionDate, MAUtil::String transactionId,
			MAUtil::String BID, double price, MAUtil::String title);

	/**
	 * Dismiss receipt dialog when Ok button is pressed.
	 */
	void dismissReceiptDialog();

	/**
	 * Main screen is notified that a purchase was completed.
	 * Use this method to append to productId of the purchased
	 * item to the history section.
	 * @param productId the product Id.
	 */
	void productPurchased(MAUtil::String productId);

	/**
	 * Main screen is notified that a purchase was restored.
	 * @param productId The product Id.
	 */
	void productRestored(MAUtil::String productId);

	/**
	 * Main screen is notified that a purchase was refunded.
	 * @param productId The product Id.
	 */
	void productRefunded(MAUtil::String productId);

	/**
	 * Main screen is notified of a purchase error.
	 * @param errorMessage.
	 */
	void productError(MAUtil::String errorMessage);

    /**
     * This method is called if the touch-up event was inside the
     * bounds of the button.
     * Platform: iOS, Android, Windows Phone.
     * @param button The button object that generated the event.
     */
    virtual void buttonClicked(Widget* button);

    /**
     * This method is called when the state of the check box was changed
     * by the user.
     * @param checkBox The check box object that generated the event.
     * @param state True if the check box is checked, false otherwise.
     */
    virtual void checkBoxStateChanged(
        CheckBox* checkBox,
        bool state);
private:

    /**
     * Create the list of available products.
     */
    void createProductIdList();

	/**
	 * Creates and adds main layout to the screen.
	 */
	void createMainLayout();

	/**
	 * Create the dialog that will display receipt fields, on rows.
	 */
	void createReceiptDialog();
private:

	/**
	 * The productIds of the available items, exactly as they are
	 * going to be send to the server in the purchase request.
	 */
	MAUtil::Vector<MAUtil::String> mProductIdList;
	/**
	 * The product names of the available items, user readable.
	 */
	MAUtil::Vector<MAUtil::String> mProductNamesList;
	/**
	 * Main layout.
	 */
	VerticalLayout* mMainLayout;
	/**
	 * Items previously purchased, loaded from the repository.
	 */
	VerticalLayout* mDatabaseItems;
	Button* mBuyButton;
	ListView* mAvailableItemsList;
	int mProductToBuy;
	ListView* mPurchasedItemsList;
	// Check boxes for picking the item to buy.
	MAUtil::Vector<CheckBox*> mItemsCheckBoxes;

	// The dialog that displays the receipt fields.
	Dialog* mReceiptDialog;
	// Receipt fields. columns for each field.
	Label* mReceiptProductId;
	Label* mReceiptAppId;
	Label* mReceiptTransactionDate;
	Label* mReceiptTransactionId;
	Label* mReceiptBid;
	Label* mReceiptPrice;
	Label* mReceiptTitle;
	Button* mReceiptOkButton;
	Button* mRestoreProducts;
	/**
	 * Application controller.
	 */
	ApplicationController* mApplicationController;
};

#endif /* MAINSCREEN_H_ */
