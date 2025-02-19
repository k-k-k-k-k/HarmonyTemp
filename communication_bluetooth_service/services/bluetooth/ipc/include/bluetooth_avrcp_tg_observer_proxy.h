/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#ifndef OHOS_BLUETOOTH_STANDARD_AVRCP_TG_OBSERVER_PROXY_H
#define OHOS_BLUETOOTH_STANDARD_AVRCP_TG_OBSERVER_PROXY_H

#include "iremote_proxy.h"
#include "i_bluetooth_avrcp_tg_observer.h"

namespace OHOS {
namespace Bluetooth {
class BluetoothAvrcpTgObserverProxy : public IRemoteProxy<IBluetoothAvrcpTgObserver> {
public:
    explicit BluetoothAvrcpTgObserverProxy(const sptr<IRemoteObject> &impl)
        : IRemoteProxy<IBluetoothAvrcpTgObserver>(impl) {}
    ~BluetoothAvrcpTgObserverProxy() {}

    void OnConnectionStateChanged(const BluetoothRawAddress &device, int32_t state, int32_t cause) override;

private:
    static inline BrokerDelegator<BluetoothAvrcpTgObserverProxy> delegator_;
};
}  // namespace Bluetooth
}  // namespace OHOS
#endif  // OHOS_BLUETOOTH_STANDARD_AVRCP_TG_OBSERVER_PROXY_H