/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_BLUETOOTH_STANDARD_RESOURCE_MANAGER_OBSERVER_INTERFACE_H
#define OHOS_BLUETOOTH_STANDARD_RESOURCE_MANAGER_OBSERVER_INTERFACE_H

#include "../parcel/bluetooth_raw_address.h"
#include "iremote_broker.h"
#include "../parcel/bluetooth_sensing_info.h"
#include "bluetooth_service_ipc_interface_code.h"

namespace OHOS {
namespace Bluetooth {
class IBluetoothResourceManagerObserver : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ipc.IBluetoothResourceManagerObserver");

    virtual void OnSensingStateChanged(uint8_t eventId, const BluetoothSensingInfo &info) = 0;
    virtual void OnBluetoothResourceDecision(uint8_t eventId, const BluetoothSensingInfo &info, uint32_t &result) = 0;
};
}  // namespace Bluetooth
}  // namespace OHOS
#endif  // OHOS_BLUETOOTH_STANDARD_RESOURCE_MANAGER_OBSERVER_INTERFACE_H