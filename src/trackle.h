//
//  Trackle.h
//
//  Created by Flavio Ferrandi on 14/09/17.
//  Copyright © 2017 Flavio Ferrandi. All rights reserved.
//

#ifndef Trackle_h
#define Trackle_h

#include "defines.h"
#include <stdio.h>
#include <string>

using namespace std;

#ifdef __cplusplus

class Trackle
{

private:
        void addDiagnostic(int key, int32_t value);
        bool sendPublish(const char *eventName, const char *data, int ttl, Event_Type eventType, Event_Flags eventFlag, string msg_id);
        bool registerEvent(const char *eventName, Subscription_Scope_Type eventScope, const char *deviceID);
        bool addSubscription(const char *eventName, EventHandler handler, void *handlerData, Subscription_Scope_Type scope, const char *deviceID, void *reserved);
        bool addGet(const char *varKey, void *userVar, Data_TypeDef userVarType);
        bool addGet(const char *varKey, void (*fn)(const char *), Data_TypeDef userVarType);

public:
        Trackle();
        ~Trackle();

        void setEnabled(bool status);
        bool isEnabled();

        bool get(const char *varKey, bool &var);
        bool get(const char *varKey, int &var);
        bool get(const char *varKey, unsigned int &var);
        bool get(const char *varKey, unsigned long &var);
        bool get(const char *varKey, long &var);
        bool get(const char *varKey, double &var);
        bool get(const char *varKey, float &var);
        bool get(const char *varKey, string &var);
        bool get(const char *varKey, char *var);
        bool get(const char *varKey, void *var, Data_TypeDef type);

        bool get(const char *varKey, user_variable_bool_cb_t *fn);
        bool get(const char *varKey, user_variable_int_cb_t *fn);
        bool get(const char *varKey, user_variable_double_cb_t *fn);
        bool get(const char *varKey, user_variable_char_cb_t *fn);
        bool get(const char *varKey, void (*fn)(const char *), Data_TypeDef type);

        bool post(const char *funcKey, user_function_int_char_t *func, Function_PermissionDef permission = ALL_USERS);

        bool publish(const char *eventName, const char *data, int ttl = DEFAULT_TTL, Event_Type eventType = PUBLIC, Event_Flags eventFlag = EMPTY_FLAGS, string msg_id = "");
        bool publish(string eventName, const char *data, int ttl = DEFAULT_TTL, Event_Type eventType = PUBLIC, Event_Flags eventFlag = EMPTY_FLAGS, string msg_id = "");
        bool publish(const char *eventName, const char *data, Event_Type eventType, Event_Flags eventFlag = EMPTY_FLAGS, string msg_id = "");
        bool publish(string eventName, const char *data, Event_Type eventType, Event_Flags eventFlag = EMPTY_FLAGS, string msg_id = "");
        bool publish(const char *eventName);
        bool publish(string eventName);

        bool publishProperties(const char *data);
        bool publishProperties(string data);

        bool subscribe(const char *eventName, EventHandler handler);
        bool subscribe(const char *eventName, EventHandler handler, Subscription_Scope_Type scope);
        bool subscribe(const char *eventName, EventHandler handler, const char *deviceID);
        bool subscribe(const char *eventName, EventHandler handler, Subscription_Scope_Type scope, const char *deviceId);
        void unsubscribe();

        void setMillis(millisCallback *millis);
        void setDeviceId(const uint8_t deviceId[DEVICE_ID_LENGTH]);
        void setKeys(const uint8_t server[PUBLIC_KEY_LENGTH], const uint8_t client[PRIVATE_KEY_LENGTH]);

        void setSendCallback(sendCallback *send);
        void setReceiveCallback(receiveCallback *receive);
        void setConnectCallback(connectCallback *connect);
        void setDisconnectCallback(disconnectCallback *disconnect);
        void setCompletedPublishCallback(publishCompletionCallback *publish);
        void setSendPublishCallback(publishSendCallback *publish);
        void setPrepareForFirmwareUpdateCallback(prepareFirmwareUpdateCallback *prepare);
        void setSaveFirmwareChunkCallback(firmwareChunkCallback *save);
        void setFinishFirmwareUpdateCallback(finishFirmwareUpdateCallback *finish);
        void setFirmwareUrlUpdateCallback(firmwareUrlUpdateCallback *firmwareUrl);
        void setPincodeCallback(pincodeCallback *pincode);
        void setConnectionStatusCallback(connectionStatusCallback *connectionStatus);
        void setUpdatePropertyCallback(updatePropertyCallback *updateProperty);
        void setClaimCode(const char *claimCode);
        void setPingInterval(uint32_t pingInterval);

        void setSaveSessionCallback(saveSessionCallback *save);
        void setRestoreSessionCallback(restoreSessionCallback *restore);

        void setSignalCallback(signalCallback *signal);
        void setSystemTimeCallback(timeCallback *signal);
        void setRandomCallback(randomNumberCallback *random);
        void setSystemRebootCallback(rebootCallback *reboot);

        void setLogCallback(logCallback *log);
        void setLogLevel(Log_Level level);
        const char *getLogLevelName(int level);

        void disableUpdates();
        void enableUpdates();
        bool updatesEnabled();
        bool updatesPending();
        bool updatesForced();

        int connect();
        void connectionCompleted();
        bool connected();
        Connection_Status_Type getConnectionStatus();
        void disconnect();
        void loop();

        void setPublishHealthCheckInterval(uint32_t interval);
        void publishHealthCheck();

        void setFirmwareVersion(int firmwareversion);
        void setProductId(int productid);

        void setUsedMemoryCallback(usedMemoryCallback *usedmemory);
        void diagnosticPower(Power key, double value);
        void diagnosticSystem(System key, double value);
        void diagnosticNetwork(Network key, double value);

        void test(string param);
};

// Random number generator callback
uint32_t HAL_RNG_GetRandomNumber(void);

#endif

#endif /* Trackle_h */
