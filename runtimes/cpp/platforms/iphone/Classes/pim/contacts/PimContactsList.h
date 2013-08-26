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

#import <Foundation/Foundation.h>
#import <AddressBook/AddressBook.h>

#include "helpers/cpp_defs.h"
#include "helpers/cpp_ix_pim.h"
#include "PimContactItem.h"
#include "PimUtil.h"
#import "PimList.h"

@interface PimContactsList:  PimList {
    /**
     * Stores the contact items imported from address book or
     * created by user.
     */
    NSMutableDictionary* mContactsDictionary;

    /**
     * Reference to an object used to interact with the Address Book database.
     */
    ABAddressBookRef mAddressBook;

    /**
     * The current item index in key array(generated by mContactsDictionary).
     */
    int mKeysArrayIndex;
}

/**
 * Init function.
 */
-(id) init;

/**
 * Imports all contact items from Address Book.
 */
-(void) openList;

/**
 * Gets a handle to the next item in list.
 * @return A handle to the next item in list, or 0 if the are no more items,
 *         or one of the MA_PIM_ERR constants in case of error.
 */
-(MAHandle) getNextItem;

/**
 * Gets an pim item for a given handle.
 * @param itemHandle The specified handle.
 * @return The item, or nil if the database does not contain
 *         an item with the given handle.
 */
-(PimItem*) getItem:(MAHandle) itemHandle;

/**
 * Creates an Contact item.
 * @return A handle to the new Contact item.
 */
-(MAHandle) createItem;

/**
 * Closes the list.
 * Adds the new items into Address Book.
 * Saves the modified items into Address Book.
 * Removes all items from the list.
 * @return One of MA_PIM_ERR constants.
 */
-(int) close;

/**
 * Closes a given item.
 * @param itemHandle A handle to a pim item.
 * @return One of the MA_PIM_ERR constants.
 */
-(int) closeItem:(MAHandle) itemHandle;

/**
 * Adds an item in Address Book.
 * @param item The given item.
 * @return One of the MA_PIM_ERR constants.
 */
-(int) saveItemInAddressBook:(PimContactItem*) item;

/**
 * Removes an pim item from this list.
 * @param itemHandle The given item.
 * @return One of the MA_PIM_ERR constants.
 **/
-(int) removeItem:(MAHandle) itemHandle;

@end
