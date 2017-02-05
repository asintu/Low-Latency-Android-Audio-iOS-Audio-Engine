#include <jni.h>
#include <stdio.h>
#include "SuperpoweredPlayer.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>
#include <SuperpoweredSimple.h>
#include <SuperpoweredCPU.h>
#include <pthread.h>
#include <android/log.h>

static void playerEventCallback(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void * __unused value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *player = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        player->setBpm(115.0f);
        player->setFirstBeatMs(0);
        player->setPosition(player->firstBeatMs, false, false);
    };
}

static void playerEventCallback2(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void * __unused value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *player = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        player->setBpm(115.0f);
        player->setFirstBeatMs(0);
        player->setPosition(player->firstBeatMs, false, false);
    };
}

static void playerEventCallback3(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void * __unused value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *player = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        player->setBpm(120.0f);
        player->setFirstBeatMs(0);
        player->setPosition(player->firstBeatMs, false, false);
    };
}

static void playerEventCallback4(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void * __unused value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *player = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        player->setBpm(125.0f);
        player->setFirstBeatMs(0);
        player->setPosition(player->firstBeatMs, false, false);
    };
}

static void playerEventCallback5(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void * __unused value) {
    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess) {
        SuperpoweredAdvancedAudioPlayer *player = *((SuperpoweredAdvancedAudioPlayer **)clientData);
        player->setBpm(130.0f);
        player->setFirstBeatMs(0);
        player->setPosition(player->firstBeatMs, false, false);
    };
}

bool SuperpoweredPlayer::process(short int *output, unsigned int numberOfSamples) {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Current MS %f", player->positionMs);
    bool silence =  !player->process(stereoBuffer, false, numberOfSamples, calculateVolume(player, volume), masterTempo);

    bool silence2 = !player2->process(stereoBuffer, !silence, numberOfSamples, calculateVolume(player2, volume2), masterTempo);
    bool silence3 =  !player3->process(stereoBuffer, !silence2 || !silence, numberOfSamples, calculateVolume(player3, volume3), masterTempo);
    bool silence4 = !player4->process(stereoBuffer, !silence3 || !silence2 || !silence, numberOfSamples, calculateVolume(player4, volume4), masterTempo);

    bool silence5 = !player5->process(stereoBuffer, !silence4 || !silence3 || !silence2 || !silence, numberOfSamples, calculateVolume(player5, volume5), masterTempo);

    if (!silence || !silence2 || !silence3 || !silence4 || !silence5) SuperpoweredFloatToShortInt(stereoBuffer, output, numberOfSamples);

    return (!silence || !silence2 || !silence3 || !silence4 || !silence5);
}

bool SuperpoweredPlayer::process2(short int *output, unsigned int numberOfSamples) {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Current MS %f", masterTempo);
    bool processResult =  player2->process(stereoBuffer2, false, numberOfSamples, calculateVolume(player2, volume2), masterTempo);
    SuperpoweredFloatToShortInt(stereoBuffer2, output, numberOfSamples);
    return processResult;
}

bool SuperpoweredPlayer::process3(short int *output, unsigned int numberOfSamples) {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Current MS %f", player->positionMs);
    bool processResult =  player3->process(stereoBuffer3, false, numberOfSamples, calculateVolume(player3, volume3), masterTempo);
    SuperpoweredFloatToShortInt(stereoBuffer3, output, numberOfSamples);
    return processResult;
}

bool SuperpoweredPlayer::process4(short int *output, unsigned int numberOfSamples) {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Current MS %f", player->positionMs);
    bool processResult =  player4->process(stereoBuffer4, false, numberOfSamples, calculateVolume(player4, volume4), masterTempo);
    SuperpoweredFloatToShortInt(stereoBuffer4, output, numberOfSamples);
    return processResult;
}

bool SuperpoweredPlayer::process5(short int *output, unsigned int numberOfSamples) {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Current MS %f", player->positionMs);
    bool processResult =  player5->process(stereoBuffer5, false, numberOfSamples, calculateVolume(player5, volume5), masterTempo);
    SuperpoweredFloatToShortInt(stereoBuffer5, output, numberOfSamples);
    return processResult;
}

float SuperpoweredPlayer::calculateVolume(SuperpoweredAdvancedAudioPlayer *player, float volumeReference) {
//    float calculatedVolume = volumeReference;
//    if (player->positionMs > endLoop - fadingTailMs) {
//        calculatedVolume = (float) ((endLoop - player->positionMs) * (volumeReference) / fadingTailMs);
//    }
//    return calculatedVolume;

    return volumeReference;
}

static bool audioProcessing(void *clientdata, short int *audioIO, int numberOfSamples, int __unused samplerate) {
    return ((SuperpoweredPlayer *)clientdata)->process(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessing2(void *clientdata, short int *audioIO, int numberOfSamples, int __unused samplerate) {
    return ((SuperpoweredPlayer *)clientdata)->process2(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessing3(void *clientdata, short int *audioIO, int numberOfSamples, int __unused samplerate) {
    return ((SuperpoweredPlayer *)clientdata)->process3(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessing4(void *clientdata, short int *audioIO, int numberOfSamples, int __unused samplerate) {
    return ((SuperpoweredPlayer *)clientdata)->process4(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessing5(void *clientdata, short int *audioIO, int numberOfSamples, int __unused samplerate) {
    return ((SuperpoweredPlayer *)clientdata)->process5(audioIO, (unsigned int)numberOfSamples);
}

SuperpoweredPlayer::SuperpoweredPlayer(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength) {
    volume = initialVolume;
    masterTempo = 0.0f;
    started = false;
    stereoBuffer = (float *)memalign(16, (bufferSize + 16) * sizeof(float) * 2);
    player = new SuperpoweredAdvancedAudioPlayer(&player, playerEventCallback, sampleRate, 0);
    player->open(path, fileOffset, fileLength);
    player->syncMode = SuperpoweredAdvancedAudioPlayerSyncMode_TempoAndBeat;

}

void SuperpoweredPlayer::openAudioSystem(unsigned int sampleRate, unsigned int bufferSize) {
    SuperpoweredCPU::setSustainedPerformanceMode(true);
    audioSystem = new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessing, this, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2);
}

void SuperpoweredPlayer::openPlayer2(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength) {
    volume2 = initialVolume;
    started2 = false;
    //stereoBuffer2 = (float *)memalign(16, (bufferSize + 16) * sizeof(float) * 2);
    player2 = new SuperpoweredAdvancedAudioPlayer(&player2, playerEventCallback2, sampleRate, 0);
    player2->open(path, fileOffset, fileLength);
    player2->syncMode = SuperpoweredAdvancedAudioPlayerSyncMode_TempoAndBeat;
    //audioSystem2 = new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessing2, this, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2);
}

void SuperpoweredPlayer::openPlayer3(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength) {
    volume3 = initialVolume;
    started3 = false;
    //stereoBuffer3 = (float *)memalign(16, (bufferSize + 16) * sizeof(float) * 2);
    player3 = new SuperpoweredAdvancedAudioPlayer(&player3, playerEventCallback3, sampleRate, 0);
    player3->open(path, fileOffset, fileLength);
    player3->syncMode = SuperpoweredAdvancedAudioPlayerSyncMode_TempoAndBeat;
    //audioSystem3 = new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessing3, this, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2);
}

void SuperpoweredPlayer::openPlayer4(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength) {
    volume4 = initialVolume;
    started4 = false;
    //stereoBuffer4 = (float *)memalign(16, (bufferSize + 16) * sizeof(float) * 2);
    player4 = new SuperpoweredAdvancedAudioPlayer(&player4, playerEventCallback4, sampleRate, 0);
    player4->open(path, fileOffset, fileLength);
    player4->syncMode = SuperpoweredAdvancedAudioPlayerSyncMode_TempoAndBeat;
    //audioSystem4 = new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessing4, this, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2);
}

void SuperpoweredPlayer::openPlayer5(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength) {
    volume5 = initialVolume;
    started5 = false;
    //stereoBuffer5 = (float *)memalign(16, (bufferSize + 16) * sizeof(float) * 2);
    player5 = new SuperpoweredAdvancedAudioPlayer(&player5, playerEventCallback5, sampleRate, 0);
    player5->open(path, fileOffset, fileLength);
    player5->syncMode = SuperpoweredAdvancedAudioPlayerSyncMode_TempoAndBeat;
    //audioSystem5 = new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessing5, this, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2);
}

void SuperpoweredPlayer::playPause(bool play) {
    if (!play) {
        player->pause();
    }
    else {
        //if (started) {
            player->play(true);
        //}
       // else {

       //     player->loop(startLoop, endLoop, false, 255, true);
        //    started = true;
        //}
    }
    //SuperpoweredCPU::setSustainedPerformanceMode(play);
}

void SuperpoweredPlayer::playPause2(bool play) {
    if (!play) {
        player2->pause();
    }
    else {
//        if (started2) {
            player2->play(true);
//        }
//        else {
//            player2->loop(startLoop, endLoop, false, 255, true);
//            started2 = true;
//        }
    }
}

void SuperpoweredPlayer::playPause3(bool play) {
    if (!play) {
        player3->pause();
    }
    else {
//        if (started3) {
            player3->play(true);
//        }
//        else {
//            player3->loop(startLoop, endLoop, false, 255, true);
//            started3 = true;
//        }
    }
    //SuperpoweredCPU::setSustainedPerformanceMode(play);
}

void SuperpoweredPlayer::playPause4(bool play) {
    if (!play) {
        player4->pause();
    }
    else {
//        if (started4) {
            player4->play(true);
//        }
//        else {
//            player4->loop(startLoop, endLoop, false, 255, true);
//            started4 = true;
//        }
    }
    //SuperpoweredCPU::setSustainedPerformanceMode(play);
}

void SuperpoweredPlayer::playPause5(bool play) {
    if (!play) {
        player5->pause();
    }
    else {
//        if (started5) {
            player5->play(true);
//        }
//        else {
//            player5->loop(startLoop, endLoop, false, 255, true);
//            started5 = true;
//        }
    }
    //SuperpoweredCPU::setSustainedPerformanceMode(play);
}


void SuperpoweredPlayer::setTempo(double value) {
    double convertedValue = value / 50.0f;
    player->setTempo(convertedValue, true);
}

void SuperpoweredPlayer::setTempo2(double value) {
    double convertedValue = value / 50.0f;
    player2->setTempo(convertedValue, true);
}

void SuperpoweredPlayer::setTempo3(double value) {
    double convertedValue = value / 50.0f;
    player3->setTempo(convertedValue, true);
}

void SuperpoweredPlayer::setTempo4(double value) {
    double convertedValue = value / 50.0f;
    player4->setTempo(convertedValue, true);
}

void SuperpoweredPlayer::setTempo5(double value) {
    double convertedValue = value / 50.0f;
    player5->setTempo(convertedValue, true);
}

void SuperpoweredPlayer::setMasterTempo(double value) {
    //double convertedValue = value / 120.0f;
    masterTempo = value;
    player->setTempo(value / 115.0f, true);
    player2->setTempo(value / 115.0f, true);
    player3->setTempo(value / 120.0f, true);
    player4->setTempo(value / 125.0f, true);
    player5->setTempo(value / 130.0f, true);
}

void SuperpoweredPlayer::setVolume(float value) {
    volume = value;
}

void SuperpoweredPlayer::setVolume2(float value) {
    volume2 = value;
}

void SuperpoweredPlayer::setVolume3(float value) {
    volume3 = value;
}

void SuperpoweredPlayer::setVolume4(float value) {
    volume4 = value;
}

void SuperpoweredPlayer::setVolume5(float value) {
    volume5 = value;
}

float SuperpoweredPlayer::getVolume() {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Volue %f", volume);
    return volume;
}

float SuperpoweredPlayer::getVolume2() {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Volue %f", volume);
    return volume2;
}

float SuperpoweredPlayer::getVolume3() {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Volue %f", volume);
    return volume3;
}

float SuperpoweredPlayer::getVolume4() {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Volue %f", volume);
    return volume4;
}

float SuperpoweredPlayer::getVolume5() {
    //__android_log_print(ANDROID_LOG_VERBOSE, "SuperpoweredPlayer", "Volue %f", volume);
    return volume5;
}

double SuperpoweredPlayer::getBpm() {
    return player->currentBpm;
}

double SuperpoweredPlayer::getBpm2() {
    return player2->currentBpm;
}

double SuperpoweredPlayer::getBpm3() {
    return player3->currentBpm;
}

double SuperpoweredPlayer::getBpm4() {
    return player4->currentBpm;
}

double SuperpoweredPlayer::getBpm5() {
    return player5->currentBpm;
}

SuperpoweredPlayer::~SuperpoweredPlayer() {
    delete player;
    delete player2;
    delete player3;
    delete player4;
    delete player5;
    free(stereoBuffer);
    free(stereoBuffer2);
    free(stereoBuffer3);
    free(stereoBuffer4);
    free(stereoBuffer5);
}

static SuperpoweredPlayer *player = NULL;

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_SuperpoweredPlayer(JNIEnv *javaEnvironment, jobject __unused obj, jint sampleRate, jint bufferSize, jstring apkPath, jint fileOffset, jint fileLength) {
    const char *path = javaEnvironment->GetStringUTFChars(apkPath, JNI_FALSE);
    player = new SuperpoweredPlayer((unsigned int)sampleRate, ((unsigned int)bufferSize), path, fileOffset, fileLength);
    javaEnvironment->ReleaseStringUTFChars(apkPath, path);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_openPlayer2(JNIEnv *javaEnvironment, jobject __unused obj, jint sampleRate, jint bufferSize, jstring apkPath, jint fileOffset, jint fileLength) {
    const char *path = javaEnvironment->GetStringUTFChars(apkPath, JNI_FALSE);
    player->openPlayer2((unsigned int)sampleRate, ((unsigned int)bufferSize), path, fileOffset, fileLength);
    javaEnvironment->ReleaseStringUTFChars(apkPath, path);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_openAudioSystem(JNIEnv *javaEnvironment, jobject __unused obj, jint sampleRate, jint bufferSize) {
    player->openAudioSystem((unsigned int)sampleRate, ((unsigned int)bufferSize));
}


extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_openPlayer3(JNIEnv *javaEnvironment, jobject __unused obj, jint sampleRate, jint bufferSize, jstring apkPath, jint fileOffset, jint fileLength) {
    const char *path = javaEnvironment->GetStringUTFChars(apkPath, JNI_FALSE);
    player->openPlayer3((unsigned int)sampleRate, ((unsigned int)bufferSize), path, fileOffset, fileLength);
    javaEnvironment->ReleaseStringUTFChars(apkPath, path);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_openPlayer4(JNIEnv *javaEnvironment, jobject __unused obj, jint sampleRate, jint bufferSize, jstring apkPath, jint fileOffset, jint fileLength) {
    const char *path = javaEnvironment->GetStringUTFChars(apkPath, JNI_FALSE);
    player->openPlayer4((unsigned int)sampleRate, ((unsigned int)bufferSize), path, fileOffset, fileLength);
    javaEnvironment->ReleaseStringUTFChars(apkPath, path);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_openPlayer5(JNIEnv *javaEnvironment, jobject __unused obj, jint sampleRate, jint bufferSize, jstring apkPath, jint fileOffset, jint fileLength) {
    const char *path = javaEnvironment->GetStringUTFChars(apkPath, JNI_FALSE);
    player->openPlayer5((unsigned int)sampleRate, ((unsigned int)bufferSize), path, fileOffset, fileLength);
    javaEnvironment->ReleaseStringUTFChars(apkPath, path);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_playPause(JNIEnv * __unused javaEnvironment, jobject __unused obj, jboolean play) {
    player->playPause(play);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_playPause2(JNIEnv * __unused javaEnvironment, jobject __unused obj, jboolean play) {
    player->playPause2(play);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_playPause3(JNIEnv * __unused javaEnvironment, jobject __unused obj, jboolean play) {
    player->playPause3(play);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_playPause4(JNIEnv * __unused javaEnvironment, jobject __unused obj, jboolean play) {
    player->playPause4(play);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_playPause5(JNIEnv * __unused javaEnvironment, jobject __unused obj, jboolean play) {
    player->playPause5(play);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setTempo(JNIEnv * __unused javaEnvironment, jobject __unused obj, jdouble value) {
    player->setTempo(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setTempo2(JNIEnv * __unused javaEnvironment, jobject __unused obj, jdouble value) {
    player->setTempo2(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setTempo3(JNIEnv * __unused javaEnvironment, jobject __unused obj, jdouble value) {
    player->setTempo3(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setTempo4(JNIEnv * __unused javaEnvironment, jobject __unused obj, jdouble value) {
    player->setTempo4(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setTempo5(JNIEnv * __unused javaEnvironment, jobject __unused obj, jdouble value) {
    player->setTempo5(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setMasterTempo(JNIEnv * __unused javaEnvironment, jobject __unused obj, jdouble value) {
    player->setMasterTempo(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setVolume(JNIEnv * __unused javaEnvironment, jobject __unused obj, jfloat value) {
    player->setVolume(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setVolume2(JNIEnv * __unused javaEnvironment, jobject __unused obj, jfloat value) {
    player->setVolume2(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setVolume3(JNIEnv * __unused javaEnvironment, jobject __unused obj, jfloat value) {
    player->setVolume3(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setVolume4(JNIEnv * __unused javaEnvironment, jobject __unused obj, jfloat value) {
    player->setVolume4(value);
}

extern "C" JNIEXPORT void Java_com_superpowered_crossexample_MainActivity_setVolume5(JNIEnv * __unused javaEnvironment, jobject __unused obj, jfloat value) {
    player->setVolume5(value);
}

extern "C" JNIEXPORT jfloat Java_com_superpowered_crossexample_MainActivity_getVolume(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getVolume();
}

extern "C" JNIEXPORT jfloat Java_com_superpowered_crossexample_MainActivity_getVolume2(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getVolume2();
}

extern "C" JNIEXPORT jfloat Java_com_superpowered_crossexample_MainActivity_getVolume3(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getVolume3();
}

extern "C" JNIEXPORT jfloat Java_com_superpowered_crossexample_MainActivity_getVolume4(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getVolume4();
}

extern "C" JNIEXPORT jfloat Java_com_superpowered_crossexample_MainActivity_getVolume5(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getVolume5();
}

extern "C" JNIEXPORT jdouble Java_com_superpowered_crossexample_MainActivity_getBpm(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getBpm();
}

extern "C" JNIEXPORT jdouble Java_com_superpowered_crossexample_MainActivity_getBpm2(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getBpm2();
}

extern "C" JNIEXPORT jdouble Java_com_superpowered_crossexample_MainActivity_getBpm3(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getBpm3();
}

extern "C" JNIEXPORT jdouble Java_com_superpowered_crossexample_MainActivity_getBpm4(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getBpm4();
}

extern "C" JNIEXPORT jdouble Java_com_superpowered_crossexample_MainActivity_getBpm5(JNIEnv * __unused javaEnvironment, jobject __unused obj) {
    return player->getBpm5();
}