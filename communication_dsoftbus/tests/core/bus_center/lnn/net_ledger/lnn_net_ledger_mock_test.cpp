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

#include <gtest/gtest.h>
#include <securec.h>

#include "bus_center_mock.h"
#include "lnn_data_cloud_sync_deps_mock.h"
#include "lnn_distributed_net_ledger.h"
#include "lnn_distributed_net_ledger_manager.c"
#include "lnn_net_ledger.c"

namespace OHOS {
using namespace testing::ext;
using namespace testing;

class LNNNetLedgerMockTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void LNNNetLedgerMockTest::SetUpTestCase()
{
}

void LNNNetLedgerMockTest::TearDownTestCase()
{
}

void LNNNetLedgerMockTest::SetUp() { }

void LNNNetLedgerMockTest::TearDown()
{
}

/*
 * @tc.name: IsLocalIrkInfoChangeTest001
 * @tc.desc: local irk info change test
 * @tc.type: FUNC
 * @tc.require: IBH09C
 */
HWTEST_F(LNNNetLedgerMockTest, IsLocalIrkInfoChangeTest001, TestSize.Level0)
{
    NodeInfo info;
    (void)memset_s(&info, sizeof(NodeInfo), 0, sizeof(NodeInfo));
    BusCenterMock busCenterMock;
    EXPECT_CALL(busCenterMock, LnnGetLocalByteInfo).WillRepeatedly(Return(SOFTBUS_ERR));
    EXPECT_EQ(IsLocalIrkInfoChange(&info), false);
}

/*
 * @tc.name: IsLocalIrkInfoChangeTest002
 * @tc.desc: local irk info change test
 * @tc.type: FUNC
 * @tc.require: IBH09C
 */
HWTEST_F(LNNNetLedgerMockTest, IsLocalIrkInfoChangeTest002, TestSize.Level0)
{
    NodeInfo info;
    (void)memset_s(&info, sizeof(NodeInfo), 0, sizeof(NodeInfo));
    BusCenterMock busCenterMock;
    EXPECT_CALL(busCenterMock, LnnGetLocalByteInfo).WillOnce(Return(SOFTBUS_OK));
    EXPECT_EQ(IsLocalIrkInfoChange(&info), false);
}

/*
 * @tc.name: IsLocalBroadcastLinKeyChangeTest001
 * @tc.desc: local link key change test
 * @tc.type: FUNC
 * @tc.require: IBH09C
 */
HWTEST_F(LNNNetLedgerMockTest, IsLocalBroadcastLinKeyChangeTest001, TestSize.Level0)
{
    NodeInfo info;
    (void)memset_s(&info, sizeof(NodeInfo), 0, sizeof(NodeInfo));
    BusCenterMock busCenterMock;
    EXPECT_CALL(busCenterMock, LnnGetLocalByteInfo).WillRepeatedly(Return(SOFTBUS_ERR));
    EXPECT_EQ(IsLocalBroadcastLinKeyChange(&info), false);
}

/*
 * @tc.name: IsLocalBroadcastLinKeyChangeTest002
 * @tc.desc: local link key change test
 * @tc.type: FUNC
 * @tc.require: IBH09C
 */
HWTEST_F(LNNNetLedgerMockTest, IsLocalBroadcastLinKeyChangeTest002, TestSize.Level0)
{
    NodeInfo info;
    (void)memset_s(&info, sizeof(NodeInfo), 0, sizeof(NodeInfo));
    BusCenterMock busCenterMock;
    EXPECT_CALL(busCenterMock, LnnGetLocalByteInfo).WillOnce(Return(SOFTBUS_OK))
    .WillRepeatedly(Return(SOFTBUS_ERR));
    EXPECT_EQ(IsLocalBroadcastLinKeyChange(&info), false);
}

/*
 * @tc.name: IsLocalBroadcastLinKeyChangeTest003
 * @tc.desc: local link key change test
 * @tc.type: FUNC
 * @tc.require: IBH09C
 */
HWTEST_F(LNNNetLedgerMockTest, IsLocalBroadcastLinKeyChangeTest003, TestSize.Level0)
{
    NodeInfo info;
    (void)memset_s(&info, sizeof(NodeInfo), 0, sizeof(NodeInfo));
    BusCenterMock busCenterMock;
    EXPECT_CALL(busCenterMock, LnnGetLocalByteInfo).WillRepeatedly(Return(SOFTBUS_OK));
    EXPECT_EQ(IsLocalBroadcastLinKeyChange(&info), false);
}

/*
 * @tc.name: LnnSaveBroadcastLinkKeyTest001
 * @tc.desc: save broadcast link key test
 * @tc.type: FUNC
 * @tc.require: IBH09C
 */
HWTEST_F(LNNNetLedgerMockTest, LnnSaveBroadcastLinkKeyTest001, TestSize.Level0)
{
    EXPECT_EQ(LnnSaveBroadcastLinkKey(nullptr, nullptr), false);

    NiceMock<LnnDataCloudSyncInterfaceMock> syncMock;
    EXPECT_CALL(syncMock, LnnGenerateHexStringHash)
        .WillOnce(Return(SOFTBUS_ENCRYPT_ERR))
        .WillRepeatedly(Return(SOFTBUS_OK));
    char udid[UDID_BUF_LEN] = { 0 };
    BroadcastCipherInfo info;
    (void)memset_s(&info, sizeof(BroadcastCipherInfo), 0, sizeof(BroadcastCipherInfo));
    (void)memcpy_s(info.key, SESSION_KEY_LENGTH, "testkey", strlen("testkey"));
    (void)memcpy_s(info.iv, BROADCAST_IV_LEN, "testiv", strlen("testiv"));
    EXPECT_EQ(LnnSaveBroadcastLinkKey(udid, &info), false);

    EXPECT_CALL(syncMock, LnnRetrieveDeviceInfo).WillOnce(Return(SOFTBUS_INVALID_PARAM));
    EXPECT_EQ(LnnSaveBroadcastLinkKey(udid, &info), true);

    NodeInfo deviceInfo;
    (void)memset_s(&deviceInfo, sizeof(NodeInfo), 0, sizeof(NodeInfo));
    (void)memcpy_s(deviceInfo.cipherInfo.key, SESSION_KEY_LENGTH, "changekey", strlen("changekey"));
    (void)memcpy_s(deviceInfo.cipherInfo.iv, BROADCAST_IV_LEN, "changeiv", strlen("changeiv"));
    EXPECT_CALL(syncMock, LnnRetrieveDeviceInfo).WillOnce(DoAll(SetArgPointee<1>(deviceInfo), Return(SOFTBUS_OK)));
    EXPECT_EQ(LnnSaveBroadcastLinkKey(udid, &info), true);

    (void)memcpy_s(deviceInfo.cipherInfo.key, SESSION_KEY_LENGTH, "testkey", strlen("testkey"));
    (void)memcpy_s(deviceInfo.cipherInfo.iv, BROADCAST_IV_LEN, "changeiv", strlen("changeiv"));
    EXPECT_CALL(syncMock, LnnRetrieveDeviceInfo).WillOnce(DoAll(SetArgPointee<1>(deviceInfo), Return(SOFTBUS_OK)));
    EXPECT_EQ(LnnSaveBroadcastLinkKey(udid, &info), true);

    (void)memcpy_s(&deviceInfo.cipherInfo, sizeof(BroadcastCipherInfo), &info, sizeof(BroadcastCipherInfo));
    EXPECT_CALL(syncMock, LnnRetrieveDeviceInfo).WillOnce(DoAll(SetArgPointee<1>(deviceInfo), Return(SOFTBUS_OK)));
    EXPECT_EQ(LnnSaveBroadcastLinkKey(udid, &info), true);
}
} // namespace OHOS
