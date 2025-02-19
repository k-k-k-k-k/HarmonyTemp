/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef NAPI_BLUETOOTH_ACCESS_OBSERVER_H
#define NAPI_BLUETOOTH_ACCESS_OBSERVER_H

#include "bluetooth_host.h"
#include "napi_async_callback.h"
#include "napi_bluetooth_utils.h"
#include "napi_event_subscribe_module.h"
namespace OHOS {
namespace Bluetooth {
class NapiBluetoothAccessObserver : public BluetoothHostObserver {
public:
    NapiBluetoothAccessObserver();
    ~NapiBluetoothAccessObserver() override = default;

    void OnStateChanged(const int transport, const int status) override;
    void OnDiscoveryStateChanged(int status) override {};
    void OnDiscoveryResult(
        const BluetoothRemoteDevice &device, int rssi, const std::string deviceName, int deviceClass) override {};
    void OnPairRequested(const BluetoothRemoteDevice &device) override {};
    void OnPairConfirmed(const BluetoothRemoteDevice &device, int reqType, int number) override {};
    void OnScanModeChanged(int mode) override {};
    void OnDeviceNameChanged(const std::string &deviceName) override {};
    void OnDeviceAddrChanged(const std::string &address) override {};

private:
    bool DealStateChange(const int transport, const int status, BluetoothState &state);
    void EnableBt();
    void DisableBle();
    void GetBrStateByStatus(const int status, BluetoothState &state, bool &isCallback);
    void GetBleStateByStatus(const int status, BluetoothState &state);

    friend class NapiAccess;
    NapiEventSubscribeModule eventSubscribe_;
};
}  // namespace Bluetooth
}  // namespace OHOS
#endif  // NAPI_BLUETOOTH_ACCESS_OBSERVER_H
