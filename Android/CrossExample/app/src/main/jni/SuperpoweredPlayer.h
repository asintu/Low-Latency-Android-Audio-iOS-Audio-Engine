//
// Created by Bruno on 18.12.16.
//

#ifndef SUPERPOWEREDANDROIDEXPORT_SUPERPOWEREDPLAYER_H
#define SUPERPOWEREDANDROIDEXPORT_SUPERPOWEREDPLAYER_H

#include "SuperpoweredPlayer.h"
#include <AndroidIO/SuperpoweredAndroidAudioIO.h>
#include <SuperpoweredAdvancedAudioPlayer.h>
#include <math.h>

#define HEADROOM_DECIBEL 3.0f
static const float headroom = powf(10.0f, -HEADROOM_DECIBEL * 0.025f);
static const int startLoop = 353;
static const int endLoop = 45000;
static const int fadingTailMs = 4000;
static const float initialVolume = 1.0f;

class SuperpoweredPlayer {
public:
	SuperpoweredPlayer(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength);
	void openPlayer2(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength);
	void openPlayer3(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength);
	void openPlayer4(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength);
	void openPlayer5(unsigned int sampleRate, unsigned int bufferSize, const char *path, int fileOffset, int fileLength);
	void openAudioSystem(unsigned int sampleRate, unsigned int bufferSize);
	~SuperpoweredPlayer();
	bool process(short int *output, unsigned int numberOfSamples);
	bool process2(short int *output, unsigned int numberOfSamples);
	bool process3(short int *output, unsigned int numberOfSamples);
	bool process4(short int *output, unsigned int numberOfSamples);
	bool process5(short int *output, unsigned int numberOfSamples);
	void playPause(bool play);
	void playPause2(bool play);
	void playPause3(bool play);
	void playPause4(bool play);
	void playPause5(bool play);
	void setTempo(double value);
	void setTempo2(double value);
	void setTempo3(double value);
	void setTempo4(double value);
	void setTempo5(double value);
	void setMasterTempo(double value);
	void setVolume(float value);
	void setVolume2(float value);
	void setVolume3(float value);
	void setVolume4(float value);
	void setVolume5(float value);
	float getVolume();
	float getVolume2();
	float getVolume3();
	float getVolume4();
	float getVolume5();
	double getBpm();
	double getBpm2();
	double getBpm3();
	double getBpm4();
	double getBpm5();
	float calculateVolume(SuperpoweredAdvancedAudioPlayer *player, float volumeReference);

private:
	SuperpoweredAdvancedAudioPlayer *player;
	SuperpoweredAdvancedAudioPlayer *player2;
	SuperpoweredAdvancedAudioPlayer *player3;
	SuperpoweredAdvancedAudioPlayer *player4;
	SuperpoweredAdvancedAudioPlayer *player5;
	float *stereoBuffer;
	float *stereoBuffer2;
	float *stereoBuffer3;
	float *stereoBuffer4;
	float *stereoBuffer5;
	SuperpoweredAndroidAudioIO *audioSystem;
	SuperpoweredAndroidAudioIO *audioSystem2;
	SuperpoweredAndroidAudioIO *audioSystem3;
	SuperpoweredAndroidAudioIO *audioSystem4;
	SuperpoweredAndroidAudioIO *audioSystem5;
	float volume, volume2, volume3, volume4, volume5;
	bool started, started2, started3, started4, started5;
	float masterTempo;

};

#endif //SUPERPOWEREDANDROIDEXPORT_SUPERPOWEREDPLAYER_H
