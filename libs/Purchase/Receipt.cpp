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
 * @file Receipt.h
 * @author Bogdan Iusco
 * @date 7 May 2012
 *
 * @brief A Receipt wraps the details of a purchase.
 */

#include <MAUtil/util.h>

#include "Receipt.h"

namespace IAP
{

	// Usual size for a buffer.
	const int BUF_SIZE = 256;

	/**
	 * Constructor.
	 * @param productHandle Handle to the its product.
	 */
	Receipt::Receipt(MAHandle productHandle):
		mHandle(productHandle)
	{

	}

	/**
	 * Copy constructor.
	 */
	Receipt::Receipt(const Receipt& receipt):
		mHandle(receipt.mHandle)
	{

	}

	/**
	 * Get the product id of the item that was purchased.
	 * Platform: Android and iOS.
	 */
	MAUtil::String Receipt::getProductID()
	{
		return this->getFieldValue(MA_PURCHASE_RECEIPT_PRODUCT_ID);
	}


	/**
	 * Get the transaction identifier of the item that has been purchased.
	 * Platform: iOS and Android.
	 */
	MAUtil::String Receipt::getTransactionID()
	{
		return this->getFieldValue(MA_PURCHASE_RECEIPT_TRANSACTION_ID);
	}

	/**
	 * Get the transaction date and time of the item that has been purchased.
	 * Platform: Android and iOS.
	 * @return Time in seconds since January 1st, 1970.
	 */
	int Receipt::getTransactionDate()
	{
		char buffer[BUF_SIZE];
		maPurchaseGetField(mHandle,
			MA_PURCHASE_RECEIPT_PURCHASE_DATE,
			buffer,
			BUF_SIZE);
		return MAUtil::stringToInteger(buffer);
	}

	/**
	 * Get a string that the App Store/Google Play uses to uniquely identify
	 * the application that created the payment transaction. If your server
	 * supports multipl applications, you can use this value to differentiate
	 * between them.
	 * Applications that are executing in the sandbox do not yet have an
	 * app-item-id assigned to them,so this key is missing from receipts created
	 * by the sandbox.
	 * Platform: iOS and Android.
	 */
	MAUtil::String Receipt::getAppID()
	{
		return this->getFieldValue(MA_PURCHASE_RECEIPT_APP_ITEM_ID);
	}

	/**
	 * Get the arbitrary number that uniquely identifies a revision of your
	 * application.
	 * This key is missing in receipts created by the sandbox.
	 * Platform: iOS.
	 */
	MAUtil::String Receipt::getVersionExternalID()
	{
		return this->getFieldValue(
			MA_PURCHASE_RECEIPT_VERSION_EXTERNAL_IDENTIFIER);
	}

	/**
	 * Get the bundle identifier for the application.
	 * Platform: iOS.
	 */
	MAUtil::String Receipt::getBID()
	{
		return this->getFieldValue(MA_PURCHASE_RECEIPT_BID);
	}

	/**
	 * Get the version number of the application.
	 * Platform: iOS.
	 */
	MAUtil::String Receipt::getBVRS()
	{
		return this->getFieldValue(MA_PURCHASE_RECEIPT_BVRS);
	}

	/**
	 * The cost of the product in the local currency.
	 */
	double Receipt::getPrice()
	{
		char buffer[BUF_SIZE];
		maPurchaseGetField(mHandle,
			MA_PURCHASE_RECEIPT_PRICE,
			buffer,
			BUF_SIZE);
		return MAUtil::stringToDouble(buffer);
	}

	/**
	 * Get the localized product title.
	 */
	MAUtil::String Receipt::getTitle()
	{
		return this->getFieldValue(MA_PURCHASE_RECEIPT_TITLE);
	}

	/**
	 * Get the localized product description.
	 */
	MAUtil::String Receipt::getDescription()
	{
		return this->getFieldValue(MA_PURCHASE_RECEIPT_DESCRIPTION);
	}

	/**
	 * Get a receipt field value.
	 * Platform: Android and iOS.
	 * @param field One of the MA_PURCHASE_RECEIPT constants.
	 * @return The field value, or a empty string in case of error.
	 */
	MAUtil::String Receipt::getFieldValue(const MAUtil::String field)
	{
		char buffer[BUF_SIZE];
		int result = maPurchaseGetField(mHandle,
			field.c_str(),
			buffer,
			BUF_SIZE);
		if (result < 0)
		{
			return "";
		}
		return buffer;
	}

} // namespace IAP
