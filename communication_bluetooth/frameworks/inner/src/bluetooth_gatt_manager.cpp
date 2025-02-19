/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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
#ifndef LOG_TAG
#define LOG_TAG "bt_fwk_gatt_manager"
#endif

#include <set>
#include <vector>

#include <functional>
#include "__tree"
#include "array"

#include "bluetooth_def.h"
#include "bluetooth_gatt_client_proxy.h"
#include "bluetooth_gatt_device.h"
#include "bluetooth_gatt_manager.h"
#include "bluetooth_host.h"
#include "bluetooth_host_proxy.h"
#include "bluetooth_log.h"
#include "bluetooth_remote_device.h"
#include "bluetooth_utils.h"
#include "i_bluetooth_host.h"
#include "if_system_ability_manager.h"
#include "iremote_object.h"
#include "iservice_registry.h"
#include "memory"
#include "new"
#include "raw_address.h"
#include "refbase.h"
#include "system_ability_definition.h"
#include "bluetooth_profile_manager.h"

namespace OHOS {
namespace Bluetooth {
struct GattManager::impl {
public:
    impl()
    {
        sptr<BluetoothGattClientProxy> proxy =
            GetRemoteProxy<BluetoothGattClientProxy>(PROFILE_GATT_CLIENT);
        CHECK_AND_RETURN_LOG(proxy != nullptr, "failed: no proxy");
    };
    ~impl() {};
    bool InitGattManagerProxy(void);

    sptr<BluetoothGattClientProxy> clientProxy_;
};

GattManager::GattManager() : pimpl(new GattManager::impl())
{
    sptr<BluetoothGattClientProxy> proxy =
        GetRemoteProxy<BluetoothGattClientProxy>(PROFILE_GATT_CLIENT);
    CHECK_AND_RETURN_LOG(proxy != nullptr, "failed: no proxy");
    pimpl->clientProxy_ = proxy;
}

GattManager::~GattManager()
{}

std::vector<BluetoothRemoteDevice> GattManager::GetDevicesByStates(
    const std::array<int, GATT_CONNECTION_STATE_NUM> &states)
{
    std::vector<BluetoothRemoteDevice> result;
    std::set<int> stateSet;
    if (!IS_BLE_ENABLED()) {
        HILOGE("bluetooth is off.");
        return result;
    }
    sptr<BluetoothGattClientProxy> proxy =
        GetRemoteProxy<BluetoothGattClientProxy>(PROFILE_GATT_CLIENT);
    CHECK_AND_RETURN_LOG_RET(proxy != nullptr, result, "failed: no proxy");

    for (auto &state : states) {
        stateSet.emplace(state);
    }
    if (pimpl->clientProxy_ != nullptr) {
        std::vector<BluetoothGattDevice> devices;
        pimpl->clientProxy_->GetAllDevice(devices);
        for (auto &item : devices) {
            if (stateSet.find(item.connectState_) != stateSet.end()) {
                result.push_back(BluetoothRemoteDevice(item.addr_.GetAddress(),
                    item.transport_ == (GATT_TRANSPORT_TYPE_LE ? BT_TRANSPORT_BLE : BT_TRANSPORT_BREDR)));
            }
        }
    }
    return result;
}

std::vector<BluetoothRemoteDevice> GattManager::GetConnectedDevices()
{
    std::vector<BluetoothRemoteDevice> result;
    if (!IS_BLE_ENABLED()) {
        HILOGE("bluetooth is off.");
        return result;
    }

    sptr<BluetoothGattClientProxy> proxy =
        GetRemoteProxy<BluetoothGattClientProxy>(PROFILE_GATT_CLIENT);
    CHECK_AND_RETURN_LOG_RET(proxy != nullptr, result, "failed: no proxy");

    if (pimpl->clientProxy_ != nullptr) {
        std::vector<BluetoothGattDevice> device;
        pimpl->clientProxy_->GetAllDevice(device);
        for (auto &item : device) {
            if (item.connectState_ == static_cast<int>(BTConnectState::CONNECTED)) {
                result.push_back(BluetoothRemoteDevice(item.addr_.GetAddress(),
                    item.transport_ == (GATT_TRANSPORT_TYPE_LE ? BT_TRANSPORT_BLE : BT_TRANSPORT_BREDR)));
            }
        }
    }
    return result;
}
}  // namespace Bluetooth
}  // namespace OHOS
