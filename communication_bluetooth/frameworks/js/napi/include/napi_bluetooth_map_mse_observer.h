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

#ifndef NAPI_BLUETOOTH_MAP_MSE_OBSERVER_H_
#define NAPI_BLUETOOTH_MAP_MSE_OBSERVER_H_

#include <shared_mutex>
#include "bluetooth_map_mse.h"
#include "napi_bluetooth_utils.h"
#include "napi_event_subscribe_module.h"

namespace OHOS {
namespace Bluetooth {
const char * const STR_BT_MAP_MSE_CONNECTION_STATE_CHANGE = "connectionStateChange";

class NapiMapMseObserver : public MapMseObserver {
public:
    void OnConnectionStateChanged(const BluetoothRemoteDevice &device, int32_t state, int32_t cause) override;

    NapiMapMseObserver();
    ~NapiMapMseObserver() override = default;

    NapiEventSubscribeModule eventSubscribe_;
};

}  // namespace Bluetooth
}  // namespace OHOS
#endif /* NAPI_BLUETOOTH_MAP_MSE_OBSERVER_H_ */