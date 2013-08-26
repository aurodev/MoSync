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
 * @file NumberPicker.cpp
 * @author Emma Tresanszki
 *
 * Class for number picker.
 * Available on iOS, WindowsPhone and Android.
 */

#include "NumberPicker.h"
#include "NumberPickerListener.h"

namespace NativeUI
{

	/**
	 * Constructor.
	 */
	NumberPicker::NumberPicker() :
		Widget(MAW_NUMBER_PICKER)
	{
	}

	/**
	 * Destructor.
	 */
	NumberPicker::~NumberPicker()
	{
	    mNumberPickerListeners.clear();
	}

	/**
	 * Set the current value for the number picker.
	 * If the value is less than MAW_NUMBER_PICKER_MIN_VALUE property value,
	 * the current value is set to min.
	 * If the value is greater than MAW_NUMBER_PICKER_MAX_VALUE value,
	 * the current value is set to max.
	 * @param value The value that we want to set.
	 * @return Any of the following result codes:
	 * - #MAW_RES_OK if the property could be set.
	 * - #MAW_RES_INVALID_PROPERTY_VALUE if the property value was invalid.
	 * - #MAW_RES_ERROR otherwise.
	 */
	int NumberPicker::setValue(const int value)
	{
		return this->setPropertyInt(MAW_NUMBER_PICKER_VALUE, value);
	}

	/**
	 * Get the current value for the number picker.
	 * @return An int that specifies the picker value.
	 */
	int NumberPicker::getValue()
	{
		return this->getPropertyInt(MAW_NUMBER_PICKER_VALUE);
	}

	/**
	 * Set the minimum value of the picker.
	 * @param min An int that specifies the minimum value.
	 * @return Any of the following result codes:
	 * - #MAW_RES_OK if the property could be set.
	 * - #MAW_RES_INVALID_PROPERTY_VALUE if the property value was invalid.
	 * - #MAW_RES_ERROR otherwise.
	 */
	int NumberPicker::setMinValue(const int min)
	{
		return this->setPropertyInt(MAW_NUMBER_PICKER_MIN_VALUE, min);
	}

	/**
	 * Get the minimum value of the picker.
	 * @return An int that specifies the minimum value.
	 */
	int NumberPicker::getMinValue()
	{
		return this->getPropertyInt(MAW_NUMBER_PICKER_MIN_VALUE);
	}

	/**
	 * Set the maximum value of the picker.
	 * @param max An int that specifies the maximum value.
	 * @return Any of the following result codes:
	 * - #MAW_RES_OK if the property could be set.
	 * - #MAW_RES_INVALID_PROPERTY_VALUE if the property value was invalid.
	 * - #MAW_RES_ERROR otherwise.
	 */
	int NumberPicker::setMaxValue(const int max)
	{
		return this->setPropertyInt(MAW_NUMBER_PICKER_MAX_VALUE, max);
	}

	/**
	 * Get the maximum value of the picker.
	 * @return An int that specifies the maximum value.
	 */
	int NumberPicker::getMaxValue()
	{
		return this->getPropertyInt(MAW_NUMBER_PICKER_MAX_VALUE);
	}

    /**
     * Add an number picker event listener.
     * @param listener The listener that will receive number picker events.
     */
    void NumberPicker::addNumberPickerListener(NumberPickerListener* listener)
    {
        addListenerToVector(mNumberPickerListeners, listener);
    }

    /**
     * Remove the number picker listener.
     * @param listener The listener that receives number picker events.
     */
    void NumberPicker::removeNumberPickerListener(NumberPickerListener* listener)
    {
        removeListenerFromVector(mNumberPickerListeners, listener);
    }

    /**
     * This method is called when there is an event for this widget.
     * It passes on the event to all widget's listeners.
     * @param widgetEventData The data for the widget event.
     */
    void NumberPicker::handleWidgetEvent(MAWidgetEventData* widgetEventData)
    {
        Widget::handleWidgetEvent(widgetEventData);

        if (MAW_EVENT_NUMBER_PICKER_VALUE_CHANGED == widgetEventData->eventType)
        {
            int numberPickerValue = widgetEventData->numberPickerValue;
            for (int i = 0; i < mNumberPickerListeners.size(); i++)
            {
                mNumberPickerListeners[i]->numberPickerValueChanged(
                    this,
                    numberPickerValue);
            }
        }
    }

} // namespace NativeUI
