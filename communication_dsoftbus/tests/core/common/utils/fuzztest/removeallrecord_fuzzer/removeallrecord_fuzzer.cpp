/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "removeallrecord_fuzzer.h"

#include <unistd.h>

#include "sqlite3_utils.h"

namespace OHOS {
    bool DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
    {
        if (data == nullptr || size == 0) {
            return true;
        }

        uint8_t *numData = const_cast<uint8_t *>(data);
        uint8_t index = *numData % 2;
        TableNameID tableNameID = static_cast<TableNameID>(index);
        DbContext *ctx = nullptr;
        RemoveAllRecord(ctx, tableNameID);

        return true;
    }
} // namespace OHOS

/* Fuzzer entry point */
extern "C" int32_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}
