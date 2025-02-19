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

#ifndef BLUETOOTH_STANDARD_BLUETOOTH_BLE_CENTRAL_MANAGER_CALLBACK_STUB_H
#define BLUETOOTH_STANDARD_BLUETOOTH_BLE_CENTRAL_MANAGER_CALLBACK_STUB_H

#include "i_bluetooth_ble_central_manager_callback.h"
#include "i_bluetooth_host.h"
#include "iremote_stub.h"
#include "map"

namespace OHOS {
namespace Bluetooth {
class BluetoothBleCentralManagerCallBackStub : public IRemoteStub<IBluetoothBleCentralManagerCallback> {
public:
    BluetoothBleCentralManagerCallBackStub();
    ~BluetoothBleCentralManagerCallBackStub() override;

    int OnRemoteRequest(
        uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;

private:
    static ErrCode OnScanCallbackInner(
        BluetoothBleCentralManagerCallBackStub *stub, MessageParcel &data, MessageParcel &reply);
    static ErrCode OnBleBatchScanResultsEventInner(
        BluetoothBleCentralManagerCallBackStub *stub, MessageParcel &data, MessageParcel &reply);
    static ErrCode OnStartOrStopScanEventInner(
        BluetoothBleCentralManagerCallBackStub *stub, MessageParcel &data, MessageParcel &reply);
    static ErrCode OnNotifyMsgReportFromLpDeviceInner(
        BluetoothBleCentralManagerCallBackStub *stub, MessageParcel &data, MessageParcel &reply);

    static const std::map<uint32_t,
        std::function<ErrCode(BluetoothBleCentralManagerCallBackStub *, MessageParcel &, MessageParcel &)>>
        memberFuncMap_;
    DISALLOW_COPY_AND_MOVE(BluetoothBleCentralManagerCallBackStub);
};
}  // namespace Bluetooth
}  // namespace OHOS
#endif  // BLUETOOTH_STANDARD_BLUETOOTH_BLE_CENTRAL_MANAGER_CALLBACK_STUB_H