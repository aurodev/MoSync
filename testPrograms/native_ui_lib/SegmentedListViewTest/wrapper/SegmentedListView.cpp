/*
Copyright (C) 2012 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file SegmentedListView.cpp
 * @author Bogdan Iusco
 *
 * @brief A SegmentedListView widget is used to present an indexed/grouped list
 * of items.
 * Available on iOS platform.
 */

#include "SegmentedListView.h"
#include "SegmentedListViewSection.h"

namespace NativeUI
{
	/**
	 * Constructor.
	 */
	SegmentedListView::SegmentedListView() :
		Widget(MAW_SEGMENTED_LIST_VIEW)
	{

	}

	/**
	 * Destructor.
	 */
	SegmentedListView::~SegmentedListView()
	{

	}

	/**
	 * Reload list view data.
	 * Call this method after each modification done to list view data.
	 * Platform: iOS.
	 */
	void SegmentedListView::reloadData()
	{
		this->setProperty(MAW_SEGMENTED_LIST_VIEW_RELOAD_DATA, "");
	}

	/**
	 * Add a section to this list.
	 * @param section The section that will be added.
	 * The ownership of the section object is passed to this method.
	 */
	void SegmentedListView::addSection(SegmentedListViewSection* section)
	{
		this->addChild(section);
	}

	/**
	 * Add a widget as a child of this widget.
	 * @param widget The widget that will be added.
	 * The ownership of the widget is passed to this function.
	 * When the parent widget will be destroyed, all child widgets
	 * will be deleted.
	 * @return Any of the following result codes:
	 * - #MAW_RES_OK if the child could be added to the parent.
	 * - #MAW_RES_INVALID_HANDLE if any of the handles were invalid.
	 * - #MAW_RES_ERROR if it could not be added for some other reason.
	 */
	int SegmentedListView::addChild(Widget* widget)
	{
		return Widget::addChild(widget);
	}

	/**
	 * Insert a widget as a child of this widget, at a given position.
	 * @param widget The widget to be added.
	 * The ownership of the widget is passed to this function.
	 * When the parent widget will be destroyed, all child widgets
	 * will be deleted.
	 * @param index The position on which to add the child.
	 * @return Any of the following result codes:
	 * - #MAW_RES_OK if the child could be added to the parent.
	 * - #MAW_RES_INVALID_HANDLE if any of the handles were invalid.
	 * - #MAW_RES_INVALID_INDEX if the index was out of bounds.
	 * - #MAW_RES_ERROR if it could not be added for some other reason.
	 */
	int SegmentedListView::insertChild(Widget* widget, const int index)
	{
		return Widget::insertChild(widget, index);
	}

	/**
	 * Remove a child widget from its parent (but does not destroy it).
	 * Removing a currently visible top-level widget causes the MoSync view
	 * to become visible.
	 * When the parent widget will be destroyed, the child widget will not
	 * be deleted.
	 * @param widget The widget to be removed.
	 * @return Any of the following result codes:
	 * - #MAW_RES_OK if the child could be removed from the parent.
	 * - #MAW_RES_INVALID_HANDLE if the handle was invalid.
	 * - #MAW_RES_ERROR otherwise.
	 */
	int SegmentedListView::removeChild(Widget* widget)
	{
		return Widget::removeChild(widget);
	}
}
