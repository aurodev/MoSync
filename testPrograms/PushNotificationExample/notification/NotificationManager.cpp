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
 * @file NotificationManager.h
 * @author Bogdan Iusco
 *
 * \brief  The NotificationManager manages local notification events and
 * dispatches them to the target notifications.
 */

// Default buffer size for buffers.
#define BUFFER_SIZE 256

#include "NotificationManager.h"
#include "LocalNotification.h"
#include "PushNotification.h"
#include "PushNotificationListener.h"

namespace Notification
{

    /**
     * Initialize the singleton variable to NULL.
     */
    NotificationManager* NotificationManager::sInstance = NULL;

    /**
     * Constructor is protected since this is a singleton.
     * (subclasses can still create instances).
     */
    NotificationManager::NotificationManager()
    {
        // Add me as a custom event listener.
        MAUtil::Environment::getEnvironment().addCustomEventListener(this);
    }

    /**
     * Destructor.
     */
    NotificationManager::~NotificationManager()
    {
        // Remove me as a custom event listener.
        MAUtil::Environment::getEnvironment().removeCustomEventListener(this);
    }

    /**
     * Return the single instance of this class.
     */
    NotificationManager* NotificationManager::getInstance()
    {
        if (NULL == NotificationManager::sInstance)
        {
            NotificationManager::sInstance = new NotificationManager();
        }

        return sInstance;
    }

    /**
     * Destroy the single instance of this class.
     * Call this method only when the application will exit.
     */
    void NotificationManager::destroyInstance()
    {
        delete NotificationManager::sInstance;
    }

    /**
     * Implementation of CustomEventListener interface.
     * This method will get called whenever there is a
     * event generated by the system.
     * @param event The new received event.
     */
    void NotificationManager::customEvent(const MAEvent& event)
    {
        printf("didReceiveEvent");
        // Check if this is a notification event.
        if (EVENT_TYPE_LOCAL_NOTIFICATION == event.type)
        {
            // Check if the local notification exists in the map.
            if (mLocalNotificationMap.end() != mLocalNotificationMap.find(
                event.localNotificationHandle))
            {
                // Get the local notification object that wraps the handle.
                LocalNotification* localNotification =
                    mLocalNotificationMap[event.localNotificationHandle];

                // Call the local notification's event handling method.
                localNotification->handleLocalNotificationEvent(event);
            }
        }
        else if (EVENT_TYPE_PUSH_NOTIFICATION == event.type)
        {
            MAHandle pushNotificationHandle = event.pushNotificationHandle;

            // Get push notification data
            MAPushNotificationData data;
            char messageAlert[BUFFER_SIZE];
            char sound[BUFFER_SIZE];
            data.alertMessage = messageAlert;
            data.alertMessageSize = BUFFER_SIZE;
            data.soundFileName = sound;
            data.soundFileNameSize = BUFFER_SIZE;
            maNotificationPushGetData(pushNotificationHandle, &data);

            // Create the push notification object.
            PushNotification* pushNotificationObj = new PushNotification();
            if (data.type & MA_NOTIFICATION_PUSH_TYPE_ALERT)
            {
                pushNotificationObj->setAlertMessage(messageAlert);
            }
            if (data.type & MA_NOTIFICATION_PUSH_TYPE_SOUND)
            {
                pushNotificationObj->setSoundFileName(sound);
            }
            if (data.type & MA_NOTIFICATION_PUSH_TYPE_BADGE)
            {
                pushNotificationObj->setIconBadge(data.badgeIcon);
            }

            // Notify listeners.
            for (int i = 0; i < mPushNotificationListeners.size(); i++)
            {
                PushNotificationListener* listener =
                    mPushNotificationListeners[i];
                listener->didReceivePushNotification(*pushNotificationObj);
            }

            delete pushNotificationObj;
        }
        else if (EVENT_TYPE_PUSH_NOTIFICATION_REGISTRATION == event.type)
        {
            char buffer[1024];
            printf("put token at %d", buffer);
            int result = maNotificationPushGetRegistration(
                buffer,
                1024);
            MAUtil::String message = buffer;
            if (MA_NOTIFICATION_RES_OK == result)
            {
                // Notify listeners.
                for (int i = 0; i < mPushNotificationListeners.size(); i++)
                {
                    PushNotificationListener* listener =
                            mPushNotificationListeners[i];
                    listener->didApplicationRegistered(message);
                }
            } else
            {
                // Notify listeners.
                for (int i = 0; i < mPushNotificationListeners.size(); i++)
                {
                    PushNotificationListener* listener =
                            mPushNotificationListeners[i];
                    listener->didFaildToRegister(result, message);
                }
            }
        }
    }

    /**
     * Add a local notification to the map that holds notifications.
     * The local notification will receive custom events.
     * @param localNotification The local notification that needs to be
     * registered.
     * The ownership of the local notification is not passed to this method.
     */
    void NotificationManager::addEventListener(
        LocalNotification* localNotification)
    {
        mLocalNotificationMap[localNotification->getHandle()] =
            localNotification;
    }

    /**
     * Remove a local notification from the map that holds notifications.
     * The local notification will not receive custom events.
     * @param banner The local notification that needs to be unregistered.
     */
    void NotificationManager::removeEventListener(
        LocalNotification* localNotification)
    {
        mLocalNotificationMap.erase(localNotification->getHandle());
    }

    /**
     * Schedules a local notification for delivery at its encapsulated
     * date and time.
     * @param localNotification Handle to a local notification object.
     */
    void NotificationManager::registerLocalNotification(
        LocalNotification* localNotification)
    {
        maNotificationLocalRegister(localNotification->getHandle());
    }

    /**
     * Cancels the delivery of the specified scheduled local notification.
     * calling this method also programmatically dismisses the notification
     * if  it is currently displaying an alert.
     * @param localNotification Handle to a local notification object.
     */
    void NotificationManager::unregisterLocalNotification(
        LocalNotification* localNotification)
    {
        maNotificationLocalUnregister(localNotification->getHandle());
    }

    /**
     * Registers the current application for receiving push notifications.
     * @param types A bit mask specifying the types of notifications the
     * application accepts.
     * See PushNotificationType for valid bit-mask values.
     * This param is applied only on iOS platform. Android platform will
     * ignore this value.
     * @param accountID Is the ID of the account authorized to send messages
     * to the application, typically the email address of an account set up
     * by the application's developer.
     * On iOS platform this param is ignored.
     *
     * Example: Notification::getInstance->registerPushNotification(
     *  PUSH_NOTIFICATION_TYPE_BADGE | PUSH_NOTIFICATION_TYPE_ALERT);
     *
     *  @return One of the next result codes:
     *  - MA_NOTIFICATION_RES_OK if no error occurred.
     *  - MA_NOTIFICATION_ALREADY_REGISTERED if the application is already
     *    registered for receiving push notifications.
     */
    int NotificationManager::registerPushNotification(const int types,
        const MAUtil::String& accountID)
    {
        return maNotificationPushRegister(types, accountID.c_str());
    }

    /**
     * Unregister application for push notifications.
     */
    void NotificationManager::unregisterPushNotification()
    {
        maNotificationPushUnregister();
    }

    /**
     * Add listener for push notifications received by this application.
     * @param listener The listener that will receive
     * push notification events.
     * Don't forget to register the application for receiving push
     * notifications by calling registerPushNotification function.
     */
    void NotificationManager::addPushNotificationListener(
        PushNotificationListener* listener)
    {
        for (int i = 0; i < mPushNotificationListeners.size(); i++)
        {
            if (listener == mPushNotificationListeners[i])
            {
                return;
            }
        }

        mPushNotificationListeners.add(listener);
    }

    /**
     * Remove listener for push notifications received by this application.
     * @param listener The listener that receives push notification events.
     */
    void NotificationManager::removePushNotificationListener(
        PushNotificationListener* listener)
    {
        for (int i = 0; i < mPushNotificationListeners.size(); i++)
        {
            if (listener == mPushNotificationListeners[i])
            {
                mPushNotificationListeners.remove(i);
                break;
            }
        }
    }

    /**
     * Set the number currently set as the badge of the application icon.
     * Platform: iOS only.
     * @param iconBadgeNumber The number that will be set as the badge of
     * the application icon.
     * If this value is negative this method will do nothing.
     */
    void NotificationManager::setApplicationIconBadgeNumber(
        const int iconBadgeNumber)
    {
        maNotificationSetIconBadge(iconBadgeNumber);
    }

    /**
     * Get the number currently set as the badge of the application icon.
     * Platform: iOS only.
     * @return The number currently set as the badge of the application icon.
     */
    int NotificationManager::getApplicationIconBadgeNumber()
    {
        return maNotificationGetIconBadge();
    }

} // namespace Notification
