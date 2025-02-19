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
#ifndef LOG_TAG
#define LOG_TAG "bt_napi_avrcp_tg_observer"
#endif

#include <uv.h>
#include "bluetooth_utils.h"
#include "napi_bluetooth_avrcp_tg_observer.h"
#include "napi_bluetooth_event.h"
#include "napi_event_subscribe_module.h"

namespace OHOS {
namespace Bluetooth {
NapiAvrcpTargetObserver::NapiAvrcpTargetObserver()
    : eventSubscribe_(STR_BT_AVRCP_TG_CONNECTION_STATE_CHANGE, BT_MODULE_NAME)
{}

void NapiAvrcpTargetObserver::OnConnectionStateChanged(const BluetoothRemoteDevice &device, int state, int cause)
{
    HILOGD("enter, remote device address: %{public}s, state: %{public}d, cause: %{public}d",
        GET_ENCRYPT_ADDR(device), state, cause);
    auto nativeObject = std::make_shared<NapiNativeStateChangeParam>(device.GetDeviceAddr(), state, cause);
    eventSubscribe_.PublishEvent(STR_BT_AVRCP_TG_CONNECTION_STATE_CHANGE, nativeObject);
}

} // namespace Bluetooth
} // namespace OHOS