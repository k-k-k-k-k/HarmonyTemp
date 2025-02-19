/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef NAPI_BLUETOOTH_BLE_CENTRAL_MANAGER_H
#define NAPI_BLUETOOTH_BLE_CENTRAL_MANAGER_H

#include "bluetooth_ble_central_manager.h"
#include "napi_async_callback.h"
#include "napi_bluetooth_ble_utils.h"
#include "napi_event_subscribe_module.h"

namespace OHOS {
namespace Bluetooth {
class NapiBluetoothBleCentralManagerCallback : public BleCentralManagerCallback {
public:
    NapiBluetoothBleCentralManagerCallback(bool isLatestNapiBleScannerObj);
    ~NapiBluetoothBleCentralManagerCallback() override = default;

    static NapiBluetoothBleCentralManagerCallback &GetInstance(void);

    void OnScanCallback(const BleScanResult &result) override;
    void OnFoundOrLostCallback(const BleScanResult &result, uint8_t callbackType) override;
    void OnBleBatchScanResultsEvent(const std::vector<BleScanResult> &results) override;
    void OnStartOrStopScanEvent(int resultCode, bool isStartScan) override;
    void OnNotifyMsgReportFromLpDevice(const UUID &uuid, int msgType, const std::vector<uint8_t> &value) override {};

    void ConvertScanReportType(ScanReportType &scanReportType, uint8_t callbackType);
    NapiEventSubscribeModule eventSubscribe_;
    NapiAsyncWorkMap asyncWorkMap_ {};
    bool isLatestNapiBleScannerObj_ = false;

private:
    void UvQueueWorkOnScanCallback(uv_work_t *work, std::shared_ptr<BleScanResult> &result);
    void UvQueueWorkOnBleBatchScanResultsEvent(uv_work_t *work, const std::vector<BleScanResult> &results);
};
}  // namespace Bluetooth
}  // namespace OHOS
#endif  // NAPI_BLUETOOTH_BLE_CENTRAL_MANAGER_H
