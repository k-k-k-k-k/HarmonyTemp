/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_INNERKITS_TRANS_CLIENT_PROXY_STANDARD_H_
#define INTERFACES_INNERKITS_TRANS_CLIENT_PROXY_STANDARD_H_

#include "if_softbus_client.h"

namespace OHOS {
class TransClientProxy : public IRemoteProxy<ISoftBusClient> {
public:
    explicit TransClientProxy(const sptr<IRemoteObject> &impl)
        : IRemoteProxy<ISoftBusClient>(impl) {}
    virtual ~TransClientProxy() = default;

    int32_t OnChannelOpened(const char *sessionName, const ChannelInfo *channel) override;
    int32_t OnChannelBind(int32_t channelId, int32_t channelType) override;
    int32_t OnChannelOpenFailed(int32_t channelId, int32_t channelType, int32_t errCode) override;
    int32_t OnChannelLinkDown(const char *networkId, int32_t routeType) override;
    int32_t OnChannelClosed(int32_t channelId, int32_t channelType, int32_t messageType) override;
    int32_t OnChannelMsgReceived(int32_t channelId, int32_t channelType, const void *dataInfo,
        uint32_t len, int32_t type) override;
    int32_t OnChannelQosEvent(int32_t channelId, int32_t channelType, int32_t eventId, int32_t tvCount,
        const QosTv *tvList) override;
    int32_t SetChannelInfo(const char *sessionName, int32_t sessionId, int32_t channelId, int32_t channelType) override;
    int32_t OnJoinLNNResult(void *addr, uint32_t addrTypeLen, const char *networkId, int retCode) override;
    int32_t OnJoinMetaNodeResult(void *addr, uint32_t addrTypeLen, void *metaInfo, uint32_t infoLen,
        int retCode) override;
    int32_t OnLeaveLNNResult(const char *networkId, int retCode) override;
    int32_t OnLeaveMetaNodeResult(const char *networkId, int retCode) override;
    int32_t OnNodeOnlineStateChanged(const char *pkgName, bool isOnline, void *info, uint32_t infoTypeLen) override;
    int32_t OnNodeBasicInfoChanged(const char *pkgName, void *info, uint32_t infoTypeLen, int32_t type) override;
    int32_t OnNodeStatusChanged(const char *pkgName, void *info, uint32_t infoTypeLen, int32_t type) override;
    int32_t OnTimeSyncResult(const void *info, uint32_t infoTypeLen, int32_t retCode) override;
    void OnPublishLNNResult(int32_t publishId, int32_t reason) override;
    void OnRefreshLNNResult(int32_t refreshId, int32_t reason) override;
    void OnRefreshDeviceFound(const void *device, uint32_t deviceLen) override;
    int32_t OnClientPermissonChange(const char *pkgName, int32_t state);
    void OnDataLevelChanged(const char *networkId, const DataLevelInfo *dataLevelInfo) override;
    int32_t OnClientTransLimitChange(int32_t channelId, uint8_t tos) override;
    int32_t OnClientChannelOnQos(
        int32_t channelId, int32_t channelType, QoSEvent event, const QosTV *qos, uint32_t count) override;
    int32_t OnCheckCollabRelation(
        const CollabInfo *sourceInfo, const CollabInfo *sinkInfo, int32_t channelId, int32_t channeltype) override;

private:
    static inline BrokerDelegator<TransClientProxy> delegator_;

    int32_t MessageParcelWrite(MessageParcel &data, const char *sessionName, const ChannelInfo *channel);
};
} // namespace OHOS

#endif // !defined(INTERFACES_INNERKITS_TRANS_CLIENT_PROXY_STANDARD_H_)