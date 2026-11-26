/* Reference:
 * https://github.com/doldecomp/sms/blob/main/libs/THPPlayer/src/THPAudioDecode.c. */
#include "thp_player.h"

#define STACK_SIZE 4096

static OSThread AudioDecodeThread;
static u8 AudioDecodeThreadStack[STACK_SIZE];
static OSMessageQueue FreeAudioBufferQueue;
static OSMessageQueue DecodedAudioBufferQueue;
static OSMessage FreeAudioBufferMessage[THP_AUDIO_BUFFER_COUNT];
static OSMessage DecodedAudioBufferMessage[THP_AUDIO_BUFFER_COUNT];

static BOOL AudioDecodeThreadCreated;

static void *AudioDecoderForOnMemory(void *arg);
static void *AudioDecoder(void *arg);
static void AudioDecode(THPReadBuffer *readBuffer);

BOOL CreateAudioDecodeThread(OSPriority prio, void *arg)
{
    BOOL res;
    if (arg) {
        res = OSCreateThread(&AudioDecodeThread, AudioDecoderForOnMemory, arg,
                             AudioDecodeThreadStack + STACK_SIZE, STACK_SIZE, prio, 1);
        if (res == FALSE)
            return FALSE;
    } else {
        res = OSCreateThread(&AudioDecodeThread, AudioDecoder, NULL,
                             AudioDecodeThreadStack + STACK_SIZE, STACK_SIZE, prio, 1);
        if (res == FALSE)
            return FALSE;
    }

    OSInitMessageQueue(&FreeAudioBufferQueue, FreeAudioBufferMessage,
                       THP_AUDIO_BUFFER_COUNT);
    OSInitMessageQueue(&DecodedAudioBufferQueue, DecodedAudioBufferMessage,
                       THP_AUDIO_BUFFER_COUNT);
    AudioDecodeThreadCreated = TRUE;
    return TRUE;
}

void AudioDecodeThreadStart()
{
    if (AudioDecodeThreadCreated)
        OSResumeThread(&AudioDecodeThread);
}

void AudioDecodeThreadCancel()
{
    if (AudioDecodeThreadCreated) {
        OSCancelThread(&AudioDecodeThread);
        AudioDecodeThreadCreated = FALSE;
    }
}

static void *AudioDecoder(void *arg)
{
    THPReadBuffer *buf;
    while (TRUE) {
        buf = (THPReadBuffer *)PopReadedBuffer();
        AudioDecode(buf);
        PushReadedBuffer2(buf);
    }
}

static void *AudioDecoderForOnMemory(void *arg)
{
    s32 readSize;
    THPReadBuffer readBuffer;
    s32 size;
    s32 frame;
    s32 remaining;

    frame = 0;
    readSize = ActivePlayer.initReadSize;
    readBuffer.ptr = (u8 *)arg;

    while (TRUE) {
        readBuffer.frameNumber = frame;
        AudioDecode(&readBuffer);

        remaining =
            (frame + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;

        if (remaining == ActivePlayer.header.numFrames - 1) {
            if ((ActivePlayer.playFlag & THP_PLAY_LOOP)) {
                readSize = *(s32 *)readBuffer.ptr;
                readBuffer.ptr = ActivePlayer.movieData;
            } else {
                OSSuspendThread(&AudioDecodeThread);
            }
        } else {
            size = *(s32 *)readBuffer.ptr;
            readBuffer.ptr += readSize;
            readSize = size;
        }
        frame++;
    }
}

#pragma dont_inline on
static void AudioDecode(THPReadBuffer *readBuffer)
{
    THPAudioBuffer *audioBuf;
    s32 i;
    u32 *offsets;
    u8 *audioData;

    offsets = (u32 *)(readBuffer->ptr + 8);
    audioData = &readBuffer->ptr[ActivePlayer.compInfo.numComponents * 4] + 8;
    audioBuf = (THPAudioBuffer *)PopFreeAudioBuffer();

    for (i = 0; i < ActivePlayer.compInfo.numComponents; i++) {
        switch (ActivePlayer.compInfo.frameComp[i]) {
        case 1: {
            audioBuf->validSample = THPAudioDecode(audioBuf->buffer, audioData, 0);
            audioBuf->curPtr = audioBuf->buffer;
            audioBuf->frameNumber = readBuffer->frameNumber;
            PushDecodedAudioBuffer(audioBuf);
            break;
        }
        }

        audioData += *offsets;
        offsets++;
    }
}
#pragma dont_inline off

void *PopFreeAudioBuffer()
{
    void *buf;
    OSReceiveMessage(&FreeAudioBufferQueue, &buf, 1);
    return buf;
}

void PushFreeAudioBuffer(void *buf)
{
    OSSendMessage(&FreeAudioBufferQueue, buf, OS_MESSAGE_NOBLOCK);
}

void *PopDecodedAudioBuffer(s32 flags)
{
    void *buf;
    s32 res = OSReceiveMessage(&DecodedAudioBufferQueue, &buf, flags);
    if (res == 1) {
        return buf;
    }
    return NULL;
}

void PushDecodedAudioBuffer(void *buf)
{
    OSSendMessage(&DecodedAudioBufferQueue, buf, 1);
}
