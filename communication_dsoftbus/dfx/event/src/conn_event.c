/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "comm_log.h"
#include "conn_event.h"

#include "softbus_event.h"

void ConnEventInner(int32_t scene, int32_t stage, const char *func, int32_t line, ConnEventExtra *extra)
{
    if (func == NULL || extra == NULL) {
        COMM_LOGE(COMM_DFX, "func or extra is NUll");
        return;
    }
    SoftbusEventForm form = {
        .eventName = CONN_EVENT_NAME,
        .scene = scene,
        .stage = stage,
        .func = func,
        .line = line,
        .connExtra = extra,
    };
    SoftbusEventInner(EVENT_MODULE_CONN, &form);
}

void ConnAlarmInner(int32_t scene, int32_t type, const char *func, int32_t line, ConnAlarmExtra *extra)
{
    if (extra == NULL) {
        return;
    }
    SoftbusEventForm form = {
        .eventName = (type == MANAGE_ALARM_TYPE) ? MANAGE_ALARM_EVENT_NAME : CONTROL_ALARM_EVENT_NAME,
        .scene = scene,
        .stage = SOFTBUS_DEFAULT_STAGE,
        .func = func,
        .line = line,
        .connAlarmExtra = extra,
    };
    SoftbusEventInner(EVENT_MODULE_CONN_ALARM, &form);
}

void ConnAuditInner(int32_t scene, const char *func, int32_t line, ConnAuditExtra *extra)
{
    if (func == NULL || extra == NULL) {
        COMM_LOGE(COMM_DFX, "func or extra is NUll");
        return;
    }
    SoftbusEventForm form = {
        .eventName = CONN_AUDIT_NAME,
        .scene = scene,
        .stage = SOFTBUS_DEFAULT_STAGE,
        .func = func,
        .line = line,
        .connAuditExtra = extra,
    };
    SoftbusAuditInner(EVENT_MODULE_CONN, &form);
}