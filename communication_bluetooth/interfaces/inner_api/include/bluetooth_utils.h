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

#ifndef BLUETOOTH_UTILS_H
#define BLUETOOTH_UTILS_H

#include <cstdint>
#include <string>

#include "bluetooth_errorcode.h"
#include "iremote_broker.h"
#include "refbase.h"

class IRemoteObject;
namespace OHOS {
namespace Bluetooth {
static constexpr int GET_PROXY_SLEEP_SEC = 1; // 1s
std::string GetEncryptAddr(std::string addr);
#define GET_ENCRYPT_ADDR(device) (GetEncryptAddr((device).GetDeviceAddr()).c_str())
#define GET_ENCRYPT_RAW_ADDR(rawAddr) (GetEncryptAddr((rawAddr).GetAddress()).c_str())
#define GET_ENCRYPT_GATT_ADDR(device) (GetEncryptAddr((device).addr_.GetAddress()).c_str())
std::string GetBtStateName(int state);
std::string GetBtTransportName(int transport);
std::string GetProfileConnStateName(int state);
std::string GetErrorCode(int32_t errCode);
std::string GenerateRandomMacAddress();
std::string GetUpdateOutputStackActionName(int action);
bool CheckConnectionStrategyInvalid(int32_t strategy);
bool CheckAccessAuthorizationInvalid(int32_t accessAuthorization);
}  // namespace Bluetooth
}  // namespace OHOS

#endif