%% ECG Signal
% by Tiffany Nguyen
% The purpose of this lab is to process ECG signal from a text file 
% and use that data to estimate a patient's heart rate.

% Open File
ECG_signal_path = '/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Week 7/ecg_signal.txt';
ECG_signal_file_id = fopen(ECG_signal_path, 'r');
if ECG_signal_file_id < 0, error('ERROR: Cannot open file'); end %input validation

% Read numbers into array
ECG_signal = textscan(ECG_signal_file_id, "%d");
ECG_signal = transpose(ECG_signal{:});
fclose(ECG_signal_file_id);

% Plot all Data
sampling_frequency = 250; %Hz
figure;
t=(0:length(ECG_signal)-1)/sampling_frequency; %get time from sampling rate
plot(t,ECG_signal);
xlabel('Time(s)');
ylabel('Amplitude');
title('ECG Signal');

% Plot the first 5 seconds of data
figure;
plot(t,ECG_signal);
xlim([0,5]);
ylim([0,250]);
xlabel('Time(s)');
ylabel('Amplitude');
title('ECG Signal - Closeup');

% Plot the Data based on Frequency
figure;
plot(ECG_signal);
xlim([0,1000]);
ylim([0,250]);
xlabel('Frequency');
ylabel('Amplitude');
title('ECG Signal - Closeup Frequency');

% Identify the QRS complexes (peaks) in the ECG signal
ECG_signal = double(ECG_signal);
[peaks, loc] = findpeaks(ECG_signal, 'MinPeakDistance',200, 'MinPeakHeight', 100);
% disp(loc);

% Label peaks on original graph
figure;
plot(t, ECG_signal, '-', t(loc), ECG_signal(loc), 'o');
xlabel('Time (s)');
ylabel('Amplitude');
title('Heatbeat Peaks');

% Time Interval between consecutive peaks
time_interval = zeros((length(loc) - 1),1);
for i = 1:(length(loc) - 1)
    cur_time_interval = loc(i+1) - loc(i); % distance between peaks
    cur_time_interval_sec = cur_time_interval / sampling_frequency; % convert to seconds
    time_interval(i) = cur_time_interval_sec; % update time_interval array
end
% disp(transpose(time_interval));

% Compute the standard deviation of the time interval
standard_deviation = std(time_interval);
fprintf("Standard Deviation: %f\n", standard_deviation);

% Compuete average heartrate
average_time = mean(time_interval);
avg_rate_bps = 1/average_time;
avg_rate_bpm = avg_rate_bps * 60;
fprintf("Avg heart rate: %.2f bpm\n", avg_rate_bpm);

% Compuete min heartrate
max_time = max(time_interval); % sec/beat
min_rate_bps = 1/max_time; % beats/sec
min_rate_bpm = min_rate_bps * 60; % beats/min
fprintf("Min heart rate: %.2f bpm\n", min_rate_bpm);

% Compuete max heartrate
min_time = min(time_interval);
max_rate_bps = 1/min_time;
max_rate_bpm = max_rate_bps * 60;
fprintf("Max heart rate: %.2f bpm\n", max_rate_bpm);
