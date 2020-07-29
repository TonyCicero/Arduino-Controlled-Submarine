package com.example.submarineremote;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    FreqGenerator Freq;
    TextView Freq_txt;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Freq_txt = findViewById(R.id.Freq);
        Freq_txt.setText("Frequency: ---");
        Freq = new FreqGenerator();

    }

    public void Forward(View view) {
        Freq_txt.setText("Frequency: 400hz");
        Freq.playTone(400.0);
    }

    public void Reverse(View view) {
        Freq_txt.setText("Frequency: 500hz");
        Freq.playTone(500.0);
    }

    public void Right(View view) {
        Freq_txt.setText("Frequency: 600hz");
        Freq.playTone(600.0);
    }

    public void Left(View view) {
        Freq_txt.setText("Frequency: 700hz");
        Freq.playTone(700.0);
    }

    public void StopProp(View view) {
        Freq_txt.setText("Frequency: 800hz");
        Freq.playTone(800.0);
    }

    public void Up(View view) {
        Freq_txt.setText("Frequency: 900hz");
        Freq.playTone(900.0);
    }

    public void Down(View view) {
        Freq_txt.setText("Frequency: 1000hz");
        Freq.playTone(1000.0);
    }

    public void StopPump(View view) {
        Freq_txt.setText("Frequency: 1100hz");
        Freq.playTone(1100.0);
    }
}
