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

#include "disc_coap_capability.h"

#include "anonymizer.h"
#include "disc_log.h"
#include "disc_nstackx_adapter.h"
#include "softbus_error_code.h"

int32_t DiscCoapAssembleCapData(uint32_t capability, const char *capabilityData, uint32_t dataLen, char *outData,
    uint32_t outLen)
{
    (void)capability;
    (void)capabilityData;
    (void)dataLen;
    (void)outData;
    (void)outLen;
    return SOFTBUS_FUNC_NOT_SUPPORT;
}

int32_t DiscCoapFillServiceData(const PublishOption *option, char *outData, uint32_t outDataLen, uint32_t allCap)
{
    (void)option;
    (void)outData;
    (void)outDataLen;
    (void)allCap;
    return SOFTBUS_OK;
}

int32_t DiscFillBtype(uint32_t capability, uint32_t allCap, NSTACKX_DiscoverySettings *discSet)
{
    (void)allCap;
    DISC_CHECK_AND_RETURN_RET_LOGW(discSet != NULL, SOFTBUS_INVALID_PARAM, DISC_COAP, "discSet is NULL");
    switch (capability) {
        case 1 << DDMP_CAPABILITY_BITMAP:
#ifdef DSOFTBUS_FEATURE_DISC_LNN_COAP
            discSet->businessType = (uint8_t)NSTACKX_BUSINESS_TYPE_AUTONET;
            break;
#else
            return SOFTBUS_INVALID_PARAM;
#endif /* DSOFTBUS_FEATURE_DISC_LNN_COAP */
        case 1 << SHARE_CAPABILITY_BITMAP:
#ifdef DSOFTBUS_FEATURE_DISC_SHARE_COAP
            discSet->businessType = (uint8_t)NSTACKX_BUSINESS_TYPE_STRATEGY;
            break;
#else
            return SOFTBUS_INVALID_PARAM;
#endif /* DSOFTBUS_FEATURE_DISC_SHARE_COAP */
        default:
#ifdef DSOFTBUS_FEATURE_DISC_COAP
            DISC_LOGW(DISC_COAP, "use the default bType, capability=%{public}u", capability);
            discSet->businessType = (uint8_t)NSTACKX_BUSINESS_TYPE_NULL;
            break;
#else
            return SOFTBUS_INVALID_PARAM;
#endif /* DSOFTBUS_FEATURE_DISC_COAP */
    }
    return SOFTBUS_OK;
}

int32_t DiscCoapProcessDeviceInfo(const NSTACKX_DeviceInfo *nstackxInfo, DeviceInfo *devInfo,
    const DiscInnerCallback *discCb, SoftBusMutex *discCbLock)
{
    DISC_CHECK_AND_RETURN_RET_LOGE(nstackxInfo != NULL, SOFTBUS_INVALID_PARAM, DISC_COAP, "nstackx devInfo is NULL");
    DISC_CHECK_AND_RETURN_RET_LOGE(devInfo != NULL, SOFTBUS_INVALID_PARAM, DISC_COAP, "devInfo is NULL");

    InnerDeviceInfoAddtions additions = {
        .medium = COAP,
    };
    char *anonymizedName = NULL;
    char *anonymizedId = NULL;
    char *anonymizedIp = NULL;
    Anonymize(devInfo->devName, &anonymizedName);
    Anonymize(devInfo->devId, &anonymizedId);
    Anonymize(devInfo->addr[0].info.ip.ip, &anonymizedIp);
    if (nstackxInfo->discoveryType == NSTACKX_DISCOVERY_TYPE_ACTIVE ||
        nstackxInfo->mode == PUBLISH_MODE_PROACTIVE) {
        DISC_LOGI(DISC_COAP, "DiscFound: devName=%{public}s, netIf=%{public}s, capa=%{public}u, port=%{public}hu, "
            "devId=%{public}s, devType=%{public}03x, ip=%{public}s, accountHash=%{public}02X%{public}02X",
            AnonymizeWrapper(anonymizedName), nstackxInfo->networkName, devInfo->capabilityBitmap[0],
            devInfo->addr[0].info.ip.port, AnonymizeWrapper(anonymizedId), devInfo->devType,
            AnonymizeWrapper(anonymizedIp), devInfo->accountHash[0], devInfo->accountHash[1]);
        AnonymizeFree(anonymizedName);
        AnonymizeFree(anonymizedId);
        AnonymizeFree(anonymizedIp);
        DISC_CHECK_AND_RETURN_RET_LOGE(SoftBusMutexLock(discCbLock) == SOFTBUS_OK, SOFTBUS_LOCK_ERR,
            DISC_COAP, "lock failed");
        if (discCb == NULL || discCb->OnDeviceFound == NULL) {
            DISC_LOGW(DISC_COAP, "discCb is NULL");
            (void)SoftBusMutexUnlock(discCbLock);
            return SOFTBUS_INVALID_PARAM;
        }
        discCb->OnDeviceFound(devInfo, &additions);
        (void)SoftBusMutexUnlock(discCbLock);
        return SOFTBUS_OK;
    }

    uint8_t bType = nstackxInfo->businessType;
    DISC_LOGI(DISC_COAP, "DiscRecv: broadcast devName=%{public}s, devId=%{public}s, ip=%{public}s, bType=%{public}u",
        AnonymizeWrapper(anonymizedName), AnonymizeWrapper(anonymizedId), AnonymizeWrapper(anonymizedIp), bType);
    AnonymizeFree(anonymizedName);
    AnonymizeFree(anonymizedId);
    AnonymizeFree(anonymizedIp);
    if (bType != NSTACKX_BUSINESS_TYPE_NULL && DiscCoapSendRsp(devInfo, bType) != SOFTBUS_OK) {
        DISC_LOGE(DISC_COAP, "send response failed");
        return SOFTBUS_DISCOVER_COAP_SEND_RSP_FAIL;
    }
    return SOFTBUS_OK;
}

void DiscCoapReportNotification(const NSTACKX_NotificationConfig *notification)
{
    (void)notification;
}
