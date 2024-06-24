% Heart Rate Calculation
% By Tiffany Nguyen
% Description: The purpose of this project is to process the audio data in a 
% heartbeat wav file and calculate heart rate based on the identified peaks.

% Load the audio file
heartSoundFile = '/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Week 5/heart_sound.wav';
[data, Fs] = audioread(heartSoundFile);

%Plot the wayform
figure;
t=(0:length(data)-1)/Fs; %get time from sampling rate
plot(t, data);
xlabel('Time(s)');
ylabel('Amplitude');
title('Heart Sound');

% Plot the waveform with frequency (to estimate distance between peaks)
figure;
plot(data);
xlabel('Frequency');
ylabel('Amplitude');
title('Heart Sound');

% Get the amplitude using absolute value and plot
figure
data_abs = abs(data);
plot(t, data_abs);
xlabel('Time (s)');
ylabel('Amplitude');
title('Heart Sound Amplitude');

%Filter out noise from the amplitude (>.5 is 1, <.5 is 0)
data_abs(data_abs > 0.5) = 1;
data_abs(data_abs <= 0.5) = 0;

figure;
plot(t, data_abs);
xlabel('Time (s)');
ylabel('Amplitude');
title('Filtered Data');

%Find peaks
[peaks, loc] = findpeaks(data_abs, 'MinPeakDistance',1000);
disp(loc);

%Label peaks on original graph
disp('peaks');
figure;
plot(t, data, '-', t(loc), data(loc), 'o');
xlabel('Time (s)');
ylabel('Amplitude');
title('Heatbeat Peaks');

%Calculate heart rate in bpm
time_between_beats = loc(3) - loc(1);
time_between_beats_sec = time_between_beats / Fs;
beats_per_minute = time_between_beats_sec * 60;
disp("Beats Per Minute:" + beats_per_minute);