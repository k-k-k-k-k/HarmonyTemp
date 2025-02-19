/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef SOFTBUS_CONN_BLE_SNAPSHOT_H
#define SOFTBUS_CONN_BLE_SNAPSHOT_H

#include <stdint.h>

#include "softbus_common.h"
#include "softbus_conn_ble_connection.h"
#include "softbus_conn_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    ListNode node;
    uint32_t connectionId;
    ConnSideType side;
    char addr[BT_MAC_LEN];
    enum ConnBleConnectionState state;
    uint32_t mtu;
    int32_t connectionRc;
} ConnBleConnectionSnapshot;

ConnBleConnectionSnapshot *ConnBleCreateConnectionSnapshot(const ConnBleConnection *connection);
void ConnBleDestroyConnectionSnapshot(ConnBleConnectionSnapshot *snapshot);
int32_t BleHiDumper(int fd);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
