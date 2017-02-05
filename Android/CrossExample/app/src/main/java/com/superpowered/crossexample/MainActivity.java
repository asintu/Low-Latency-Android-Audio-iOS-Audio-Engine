package com.superpowered.crossexample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.Menu;
import android.view.MenuItem;
import android.content.res.AssetFileDescriptor;
import java.io.IOException;
import java.text.DecimalFormat;

import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Button;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    boolean playingAll = false;
    boolean playing = false;
    boolean playing2 = false;
    boolean playing3 = false;
    boolean playing4 = false;
    boolean playing5 = false;
    float initialVolume;
    DecimalFormat dfTempo = new DecimalFormat("#");
    DecimalFormat dfVolume = new DecimalFormat("#.##");
    TextView volumeValue;
    TextView tempoValue;
    TextView volumeValue2;
    TextView tempoValue2;
    TextView tempoValue3;
    TextView volumeValue3;
    TextView tempoValue4;
    TextView volumeValue4;
    TextView tempoValue5;
    TextView volumeValue5;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Get the device's sample rate and buffer size to enable low-latency Android audio output, if available.
        String samplerateString = null, buffersizeString = null;
        if (samplerateString == null) samplerateString = "44100";
        if (buffersizeString == null) buffersizeString = "512";

        // Files under res/raw are not zipped, just copied into the APK. Get the offset and length to know where our files are located.
        AssetFileDescriptor fd = getResources().openRawResourceFd(R.raw.part1a0largissimo115);
        AssetFileDescriptor fd2 = getResources().openRawResourceFd(R.raw.part1alargo115);
        AssetFileDescriptor fd3 = getResources().openRawResourceFd(R.raw.part1bandante120);
        AssetFileDescriptor fd4 = getResources().openRawResourceFd(R.raw.part1callegro125);
        AssetFileDescriptor fd5 = getResources().openRawResourceFd(R.raw.part1dvivace130);
        int fileOffset = (int)fd.getStartOffset();
        int fileLength = (int)fd.getLength();
        int file2Offset = (int)fd2.getStartOffset();
        int file2Length = (int)fd2.getLength();
        int file3Offset = (int)fd3.getStartOffset();
        int file3Length = (int)fd3.getLength();
        int file4Offset = (int)fd4.getStartOffset();
        int file4Length = (int)fd4.getLength();
        int file5Offset = (int)fd5.getStartOffset();
        int file5Length = (int)fd5.getLength();
        try {
            fd.getParcelFileDescriptor().close();
            fd2.getParcelFileDescriptor().close();
            fd3.getParcelFileDescriptor().close();
            fd4.getParcelFileDescriptor().close();
            fd5.getParcelFileDescriptor().close();
        } catch (IOException e) {
            android.util.Log.d("", "Close error.");
        }

        // Arguments: path to the APK file, offset and length of the two resource files, sample rate, audio buffer size.
        SuperpoweredPlayer(Integer.parseInt(samplerateString), Integer.parseInt(buffersizeString), getPackageResourcePath(), fileOffset, fileLength);
        openPlayer2(Integer.parseInt(samplerateString), Integer.parseInt(buffersizeString), getPackageResourcePath(), file2Offset, file2Length);
        openPlayer3(Integer.parseInt(samplerateString), Integer.parseInt(buffersizeString), getPackageResourcePath(), file3Offset, file3Length);
        openPlayer4(Integer.parseInt(samplerateString), Integer.parseInt(buffersizeString), getPackageResourcePath(), file4Offset, file4Length);
        openPlayer5(Integer.parseInt(samplerateString), Integer.parseInt(buffersizeString), getPackageResourcePath(), file5Offset, file5Length);
        openAudioSystem(Integer.parseInt(samplerateString), Integer.parseInt(buffersizeString));
        initialVolume = getVolume();


        final SeekBar tempoBar = (SeekBar)findViewById(R.id.player1TempoBar);
        tempoBar.setProgress(50);
        tempoBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser) {
                    setTempo((double)progress);
                    tempoValue.setText(dfTempo.format(getBpm()));
                }

            }

            public void onStartTrackingTouch(SeekBar seekBar) {}
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        final SeekBar volumeSeekBar = (SeekBar)findViewById(R.id.player1VolumeBar);
        volumeSeekBar.setProgress(100);
        volumeSeekBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int proress, boolean b) {
                float newVolume = (proress * initialVolume / 100f);
                setVolume(newVolume);
                volumeValue.setText(dfVolume.format(newVolume));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        tempoValue = (TextView)findViewById(R.id.tempoValue);
        tempoValue.setText(buffersizeString.valueOf(115));

        volumeValue = (TextView)findViewById(R.id.volumeValue);
        volumeValue.setText(dfVolume.format(getVolume()));


        final SeekBar tempoBar2 = (SeekBar)findViewById(R.id.tempoBar2);
        tempoBar2.setProgress(50);
        tempoBar2.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser) {
                    setTempo2((double)(progress));
                    tempoValue2.setText(dfTempo.format(getBpm2()));
                }
            }

            public void onStartTrackingTouch(SeekBar seekBar) {}
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        final SeekBar volumeBar2 = (SeekBar)findViewById(R.id.volumeBar2);
        volumeBar2.setProgress(100);
        volumeBar2.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int proress, boolean b) {
                float newVolume = (proress * initialVolume / 100f);
                setVolume2(newVolume);
                volumeValue2.setText(dfVolume.format(newVolume));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        tempoValue2 = (TextView)findViewById(R.id.tempoValue2);
        tempoValue2.setText(buffersizeString.valueOf(115));

        volumeValue2 = (TextView)findViewById(R.id.volumeValue2);
        volumeValue2.setText(dfVolume.format(getVolume2()));

        // Player 3

        final SeekBar tempoBar3 = (SeekBar)findViewById(R.id.tempoBar3);
        tempoBar3.setProgress(50);
        tempoBar3.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser) {
                    setTempo3((double)progress);
                    tempoValue3.setText(dfTempo.format(getBpm3()));
                }
            }

            public void onStartTrackingTouch(SeekBar seekBar) {}
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        final SeekBar volumeBar3 = (SeekBar)findViewById(R.id.volumeBar3);
        volumeBar3.setProgress(100);
        volumeBar3.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int proress, boolean b) {
                float newVolume = (proress * initialVolume / 100f);
                setVolume3(newVolume);
                volumeValue3.setText(dfVolume.format(newVolume));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        tempoValue3 = (TextView)findViewById(R.id.tempoValue3);
        tempoValue3.setText(buffersizeString.valueOf(120));

        volumeValue3 = (TextView)findViewById(R.id.volumeValue3);
        volumeValue3.setText(dfVolume.format(getVolume3()));


        // Player 4

        final SeekBar tempoBar4 = (SeekBar)findViewById(R.id.tempoBar4);
        tempoBar4.setProgress(50);
        tempoBar4.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser) {
                    setTempo4((double)(progress));
                    tempoValue4.setText(dfTempo.format(getBpm4()));
                }
            }

            public void onStartTrackingTouch(SeekBar seekBar) {}
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        final SeekBar volumeBar4 = (SeekBar)findViewById(R.id.volumeBar4);
        volumeBar4.setProgress(100);
        volumeBar4.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int proress, boolean b) {
                float newVolume = (proress * initialVolume / 100f);
                setVolume4(newVolume);
                volumeValue4.setText(dfVolume.format(newVolume));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        tempoValue4 = (TextView)findViewById(R.id.tempoValue4);
        tempoValue4.setText(buffersizeString.valueOf(125));

        volumeValue4 = (TextView)findViewById(R.id.volumeValue4);
        volumeValue4.setText(dfVolume.format(getVolume4()));

        // Player 5

        final SeekBar tempoBar5 = (SeekBar)findViewById(R.id.tempoBar5);
        tempoBar5.setProgress(50);
        tempoBar5.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser) {
                    setTempo5((double)(progress));
                    tempoValue5.setText(dfTempo.format(getBpm5()));
                }
            }

            public void onStartTrackingTouch(SeekBar seekBar) {}
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        final SeekBar volumeBar5 = (SeekBar)findViewById(R.id.volumeBar5);
        volumeBar5.setProgress(100);
        volumeBar5.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int proress, boolean b) {
                float newVolume = (proress * initialVolume / 100f);
                setVolume5(newVolume);
                volumeValue5.setText(dfVolume.format(newVolume));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        tempoValue5 = (TextView)findViewById(R.id.tempoValue5);
        tempoValue5.setText(buffersizeString.valueOf(130));

        volumeValue5 = (TextView)findViewById(R.id.volumeValue5);
        volumeValue5.setText(dfVolume.format(getVolume5()));

        final EditText masterBpm = (EditText) findViewById(R.id.masterBpm);
        masterBpm.setText("120");

        final Button setMasterBpm = (Button) findViewById(R.id.setMasterBpm);
        setMasterBpm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                double intValue = Double.parseDouble(masterBpm.getText().toString());
                double tempo = intValue;
                int percentValue = (int)((tempo / 240) * 100);
                setMasterTempo(tempo);
                tempoBar.setProgress(percentValue);
                tempoValue.setText(dfTempo.format(getBpm()));
                tempoBar2.setProgress(percentValue );
                tempoValue2.setText(dfTempo.format(getBpm2()));
                tempoBar3.setProgress(percentValue);
                tempoValue3.setText(dfTempo.format(getBpm3()));
                tempoBar4.setProgress(percentValue);
                tempoValue4.setText(dfTempo.format(getBpm4()));
                tempoBar5.setProgress(percentValue);
                tempoValue5.setText(dfTempo.format(getBpm5()));
            }
        });

        double tempo = 120;
        int percentValue = (int)((tempo / 240) * 100);
        setMasterTempo(tempo);
        tempoBar.setProgress(percentValue);
        tempoValue.setText("120");
        tempoBar2.setProgress(percentValue );
        tempoValue2.setText("120");
        tempoBar3.setProgress(percentValue);
        tempoValue3.setText("120");
        tempoBar4.setProgress(percentValue);
        tempoValue4.setText("120");
        tempoBar5.setProgress(percentValue);
        tempoValue5.setText("120");

    }

    public void SuperpoweredExample_PlayPauseAll(View button) {
        playingAll = !playingAll;
        Button ball = (Button) findViewById(R.id.playPauseAll);
        if (ball != null) ball.setText(playingAll? "Pause": "Play");

        playing = !playing;
        playPause(playing);
        Button b = (Button) findViewById(R.id.player1PlayPauseButton);
        if (b != null) b.setText(playing ? "Pause" : "Play");

        playing2 = !playing2;
        playPause2(playing2);
        Button b2 = (Button) findViewById(R.id.playButton2);
        if (b2 != null) b2.setText(playing2 ? "Pause" : "Play");

        playing3 = !playing3;
        playPause3(playing3);
        Button b3 = (Button) findViewById(R.id.playButton3);
        if (b3 != null) b3.setText(playing3 ? "Pause" : "Play");

        playing4 = !playing4;
        playPause4(playing4);
        Button b4 = (Button) findViewById(R.id.playButton4);
        if (b4 != null) b4.setText(playing4 ? "Pause" : "Play");

        playing5 = !playing5;
        playPause5(playing5);
        Button b5 = (Button) findViewById(R.id.playButton5);
        if (b5 != null) b5.setText(playing5 ? "Pause" : "Play");
    }

    public void SuperpoweredExample_PlayPause(View button) {  // Play/pause.
        playing = !playing;
        playPause(playing);
        Button b = (Button) findViewById(R.id.player1PlayPauseButton);
        if (b != null) b.setText(playing ? "Pause" : "Play");
    }

    public void SuperpoweredExample_PlayPause2(View button) {  // Play/pause.
        playing2 = !playing2;
        playPause2(playing2);
        Button b = (Button) findViewById(R.id.playButton2);
        if (b != null) b.setText(playing2 ? "Pause" : "Play");
    }

    public void SuperpoweredExample_PlayPause3(View button) {  // Play/pause.
        playing3 = !playing3;
        playPause3(playing3);
        Button b = (Button) findViewById(R.id.playButton3);
        if (b != null) b.setText(playing3 ? "Pause" : "Play");
    }

    public void SuperpoweredExample_PlayPause4(View button) {  // Play/pause.
        playing4 = !playing4;
        playPause4(playing4);
        Button b = (Button) findViewById(R.id.playButton4);
        if (b != null) b.setText(playing4 ? "Pause" : "Play");
    }

    public void SuperpoweredExample_PlayPause5(View button) {  // Play/pause.
        playing5 = !playing5;
        playPause5(playing5);
        Button b = (Button) findViewById(R.id.playButton5);
        if (b != null) b.setText(playing5 ? "Pause" : "Play");
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private native void SuperpoweredPlayer(int samplerate, int buffersize, String apkPath, int fileAoffset, int fileAlength);
    private native void openAudioSystem(int samplerate, int buffersize);
    private native void openPlayer2(int samplerate, int buffersize, String apkPath, int fileOffset, int fileLength);
    private native void openPlayer3(int samplerate, int buffersize, String apkPath, int fileOffset, int fileLength);
    private native void openPlayer4(int samplerate, int buffersize, String apkPath, int fileOffset, int fileLength);
    private native void openPlayer5(int samplerate, int buffersize, String apkPath, int fileOffset, int fileLength);
    private native void playPause(boolean play);
    private native void playPause2(boolean play);
    private native void playPause3(boolean play);
    private native void playPause4(boolean play);
    private native void playPause5(boolean play);
    private native void setTempo(double value);
    private native void setTempo2(double value);
    private native void setTempo3(double value);
    private native void setTempo4(double value);
    private native void setTempo5(double value);
    private native void setMasterTempo(double value);
    private native void setVolume(float value);
    private native void setVolume2(float value);
    private native void setVolume3(float value);
    private native void setVolume4(float value);
    private native void setVolume5(float value);
    private native float getVolume();
    private native float getVolume2();
    private native float getVolume3();
    private native float getVolume4();
    private native float getVolume5();
    private native double getBpm();
    private native double getBpm2();
    private native double getBpm3();
    private native double getBpm4();
    private native double getBpm5();

    static {
        System.loadLibrary("SuperpoweredPlayer");
    }
}
