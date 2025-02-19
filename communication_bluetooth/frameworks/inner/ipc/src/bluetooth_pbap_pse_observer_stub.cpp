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
#ifndef LOG_TAG
#define LOG_TAG "bt_ipc_pbap_pse_observer_stub"
#endif

#include "bluetooth_errorcode.h"
#include "bluetooth_log.h"
#include "bluetooth_pbap_pse_observer_stub.h"

namespace OHOS {
namespace Bluetooth {
BluetoothPbapPseObserverStub::BluetoothPbapPseObserverStub()
{
    HILOGI("start.");
    memberFuncMap_[static_cast<uint32_t>(
        BluetoothPbapPseObserverInterfaceCode::PBAP_PSE_ON_CONNECTION_STATE_CHANGE)] =
        BluetoothPbapPseObserverStub::OnConnectionStateChangedInner;
}

BluetoothPbapPseObserverStub::~BluetoothPbapPseObserverStub()
{
    HILOGI("start.");
    memberFuncMap_.clear();
}

int32_t BluetoothPbapPseObserverStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    HILOGD("PbapPseObserverStub::OnRemoteRequest, cmd = %{public}d, flags= %{public}d", code, option.GetFlags());
    if (BluetoothPbapPseObserverStub::GetDescriptor() != data.ReadInterfaceToken()) {
        HILOGI("local descriptor is not equal to remote");
        return ERR_INVALID_STATE;
    }

    auto itFunc = memberFuncMap_.find(code);
    if (itFunc != memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            return memberFunc(this, data, reply);
        }
    }
    HILOGW("OnRemoteRequest, default case, need check.");
    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t BluetoothPbapPseObserverStub::OnConnectionStateChangedInner(
    BluetoothPbapPseObserverStub *stub, MessageParcel &data, MessageParcel &reply)
{
    HILOGD("Enter.");
    std::shared_ptr<BluetoothRawAddress> device(data.ReadParcelable<BluetoothRawAddress>());
    CHECK_AND_RETURN_LOG_RET((device != nullptr), BT_ERR_INTERNAL_ERROR, "Read device error");
    int32_t state = data.ReadInt32();
    int32_t cause = data.ReadInt32();

    stub->OnConnectionStateChanged(*device, state, cause);
    return BT_NO_ERROR;
}
}  // namespace Bluetooth
}  // namespace OHOS
