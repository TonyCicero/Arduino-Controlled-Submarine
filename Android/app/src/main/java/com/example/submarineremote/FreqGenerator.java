package com.example.submarineremote;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;

public class FreqGenerator{
    int sr = 44100;
    public void playTone(double freq){
        int buffsize = AudioTrack.getMinBufferSize(sr,
                AudioFormat.CHANNEL_OUT_MONO,
                AudioFormat.ENCODING_PCM_16BIT);
        //start audio stream
        AudioTrack audioTrack = new AudioTrack(
                AudioManager.STREAM_MUSIC, sr,
                AudioFormat.CHANNEL_OUT_MONO,
                AudioFormat.ENCODING_PCM_16BIT, buffsize,
                AudioTrack.MODE_STREAM);
        short samples[] = new short[buffsize];
        int amp = 10000; //amplitude
        double twopi = 8. * Math.atan(1.);
        double fr = freq; //frequency
        double ph = 0.0;
        audioTrack.play();
        for (int i = 0; i < buffsize; i++) { // gen square wave
            samples[i] = (short) (amp * Math.sin(ph));
            ph += twopi * fr / sr;
        }
        audioTrack.write(samples, 0, buffsize); // write buffer to audio track
    }
}
