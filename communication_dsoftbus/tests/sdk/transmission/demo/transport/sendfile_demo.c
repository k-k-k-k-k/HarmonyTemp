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

/**
 * @file sendfile_demo.c
 *
 * @brief Provides the sample code for sending a file.
 *
 * @since 1.0
 * @version 1.0
 */

// Device A:

#include <stdio.h>
#include "session.h"
#include "softbus_config_type.h"

const char *g_pkgNameA = "dms"; // Application bundle name of device A
const char *g_sessionNameA = "ohos.distributedschedule.dms.test";  // Session name of device A

// Network ID generated by device B after devices A and B are networked
const char *g_networkidB = "ABCDEF00ABCDEF00ABCDEF00ABCDEF00ABCDEF00ABCDEF00ABCDEF00ABCDEF00";
const char *g_groupid = "TEST_GROUP_ID";  // Group ID
static SessionAttribute g_sessionAttr = {
    .dataType = TYPE_FILE,  // File type
};
const char *g_rootDir = "/data/"; // Root directory for the files on the receiver side
const int32_t FILE_NUM = 4;

// Notify that the session is set up successfully.
static int32_t OnSessionOpened(int32_t sessionId, int32_t result)
{
    printf("session opened,sesison id = %d\r\n", sessionId);
    return 0;
}

// Notify that the session is closed.
static void OnSessionClosed(int32_t sessionId)
{
    printf("session closed, session id = %d\r\n", sessionId);
}

// Session-related callbacks
static ISessionListener g_sessionlistenerA = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
};

static int32_t OnSendFileProcess(int32_t sessionId, uint64_t bytesUpload, uint64_t bytesTotal)
{
    printf("OnSendFileProcess sessionId = %d, bytesUpload = %llu, total = %llu\n",
        sessionId, bytesUpload, bytesTotal);
    return 0;
}

static int32_t OnSendFileFinished(int32_t sessionId, const char *firstFile)
{
    printf("OnSendFileFinished sessionId = %d, first file = %s\n", sessionId, firstFile);
    return 0;
}

static void OnFileTransError(int32_t sessionId)
{
    printf("OnFileTransError sessionId = %d\n", sessionId);
}

// Callbacks related to file sending
static IFileSendListener g_fileSendListener = {
    .OnSendFileProcess = OnSendFileProcess,
    .OnSendFileFinished = OnSendFileFinished,
    .OnFileTransError = OnFileTransError,
};

int32_t main(void)
{
    /* 1. Device A calls SetFileSendListener() to set callbacks for file sending. */
    int32_t ret = SetFileSendListener(g_pkgNameA, g_sessionNameA, &g_fileSendListener);
    printf("set file send listener result = %d\n", ret);

    /*
     * 2. Device A calls CreateSessionServer() to create a session server based on
     * the application bundle name and session name, and registers the callbacks for
     * session opened, session closed, byte received, and message received.
     */
    ret = CreateSessionServer(g_pkgNameA, g_sessionNameA, &g_sessionlistenerA);
    printf("create session server result = %d\n", ret);

    /*
     * 3. Device A calls OpenSession() to open a session based on the local session name,
     * peer session name, peer network ID and session type, and determine the session channel based on the session type.
     * When the session is open, a callback will be invoked to notify devices A and B.
     * A session ID is returned for subsequent file sending.
     */
    int32_t sessionId = OpenSession(g_sessionNameA, g_sessionNameB, g_networkidB, g_groupid, &g_sessionAttr);
    printf("open session result = %d\n", sessionId);

    /* 4. Device A calls SendFile() to send files to device B. */
    const char *sfileList[] = {
        "/data/big.tar",
        "/data/richu.jpg",
        "/data/richu-002.jpg",
        "/data/richu-003.jpg",
    };
    ret = SendFile(sessionId, sfileList, NULL, FILE_NUM);
    printf("send file result = %d\n", ret);

    /* 5. After data transmission is complete, device A calls CloseSession() to close the session
     * and instructs device B to close the session.
     */
    CloseSession(sessionId);
    printf("SOFTBUS_OK");

    /* 6. After the session is closed, devices A and B call RemoveSessionServer() to remove the session server. */
    ret = RemoveSessionServer(g_pkgNameA, g_sessionNameA);
    printf("remove session server result = %d\n", ret);
}

// Device B:

#include <stdio.h>
#include "session.h"

const char *g_pkgNameB = "dmsB"; // Application bundle name of device B
const char *g_sessionNameB = "ohos.distributedschedule.dms.testB";  // Session name of device B
const char *g_rootDirB = "/data"; // File directory of device B

static int32_t OnSessionOpened(int32_t sessionId, int32_t result)
{
    printf("session opened,sesison id = %d\r\n", sessionId);
    return 0;
}

static void OnSessionClosed(int32_t sessionId)
{
    printf("session closed, session id = %d\r\n", sessionId);
}

static ISessionListener g_sessionlistenerB = {
    .OnSessionOpened = OnSessionOpened,
    .OnSessionClosed = OnSessionClosed,
};

static int32_t OnReceiveFileStarted(int32_t sessionId, const char *files, int32_t fileCnt)
{
    printf("File receive start sessionId = %d, first file = %s, fileCnt = %d\n", sessionId, files, fileCnt);
    return 0;
}

static int32_t OnReceiveFileProcess(int32_t sessionId, const char *firstFile, uint64_t bytesUpload, uint64_t bytesTotal)
{
    printf("File receive Process sessionId = %d, first file = %s, bytesUpload = %llu, bytesTotal = %llu\n",
        sessionId, firstFile, bytesUpload, bytesTotal);
    return 0;
}

static void OnReceiveFileFinished(int32_t sessionId, const char *files, int32_t fileCnt)
{
    printf("File receive finished sessionId = %d, first file = %s, fileCnt = %d\n", sessionId, files, fileCnt);
}

static void OnFileTransError(int32_t sessionId)
{
    printf("OnFileTransError sessionId = %d\n", sessionId);
}

// Callbacks related to file receiving
static IFileReceiveListener g_fileRecvListener = {
    .OnReceiveFileStarted = OnReceiveFileStarted,
    .OnReceiveFileProcess = OnReceiveFileProcess,
    .OnReceiveFileFinished = OnReceiveFileFinished,
    .OnFileTransError = OnFileTransError,
};

int32_t main(void)
{
    /* 1. Device B calls SetFileReceiveListener() to set callbacks for file receiving. */
    int32_t ret = SetFileReceiveListener(g_pkgNameB, g_sessionNameB, &g_fileRecvListener, g_rootDirB);
    printf("set file receive listener result = %d\n", ret);

    /*
     * 2. Device B calls CreateSessionServer() to create a session server based on
     * the application bundle name and session name, and registers the callbacks for
     * session opened, session closed, byte received, and message received.
     */
    ret = CreateSessionServer(g_pkgNameB, g_sessionNameB, &g_sessionlistenerB);
    printf("create session server result = %d\n", ret);

    /*
     * 3. Upon receiving the session open notification via OnSessionOpened(), device B waits for device A to send files.
     * When receiving the files, device B returns the file receiving status via
     * OnReceiveFileProcess(), OnReceiveFileStarted(), and OnReceiveFileFinished().
     */
 
    /* 4. When all the files are received, device B closes the session and removes the session service. */
    ret = RemoveSessionServer(g_pkgNameB, g_sessionNameB);
    printf("remove session server result = %d\n", ret);
}
