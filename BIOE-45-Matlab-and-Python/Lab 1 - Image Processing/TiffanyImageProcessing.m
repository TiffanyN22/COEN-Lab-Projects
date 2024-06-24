%% Simple Image Processing Project
% by Tiffany Nguyen

%% Read the Image
img = imread('/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Lab3/blood_smear.jpg');
% Display the Image
figure; imshow(img); title('Original Blood Smear');

%% Create a binary mask highlighting RBC regions
% Threshold Values
% Note: filtering out background also filters out the center of some of the
% cells (similar RBG values)
RGBHigh = [240 240 240]; 
RGBLow = [0 0 0];
% Filter out values out of range
binaryMask = all(img(:, :, 1) >= RGBLow(1) & img(:, :, 1) <= RGBHigh(1) & ...
img(:, :, 2) >= RGBLow(2) & img(:, :, 2) <= RGBHigh(2) & ...
img(:, :, 3) >= RGBLow(3) & img(:, :, 3) <= RGBHigh(3), 3);
% Display Mask
figure; imshow(binaryMask); title('Binary Mask');

%% Black out non-RBC regions in the original image.
RBC = img; RBC(~repmat(binaryMask, [1, 1, size(img, 3)])) = 0;
% Displayed RBC regions
figure; imshow(RBC); title('Red Blood Cell Regions');

%% Save the processed image.
imwrite(RBC, '/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Lab3/RBC_Matlab.jpg');

%% Plot histograms of red, green, and blue intensities for RBC cells.
numBins = 25;

% Plot Red Intensities
redIntensities = RBC (:, :, 1); % read all red pixel values (1st channel)
redIntensities = redIntensities(:); % flatten
redIntensities = redIntensities(redIntensities ~= 0); % filter out 0 (mask)
subplot(3, 1, 1); % rgb histograms in 3 rows, red in first row
histogram(redIntensities, numBins); %plot histogram
title('Red Intensities') % label subplot
xlabel('Intensity')
ylabel('Pixel Count')
xlim([0, 255]); % set range from 0-255 so all plots have same x scale

% Plot Green Intensities
greenIntensities = RBC (:, :, 2); % Green is 2nd channel
greenIntensities = greenIntensities(:);
greenIntensities = greenIntensities(greenIntensities ~= 0); 
subplot(3, 1, 2); % second row
histogram(greenIntensities, numBins);
title('Green Intensities')
xlabel('Intensity')
ylabel('Pixel Count')
xlim([0, 255]);

% Plot Blue Intensities
blueIntensities = RBC (:, :, 3); % Blue is 3rd channel
blueIntensities = blueIntensities(:);
blueIntensities = blueIntensities(blueIntensities ~= 0); 
subplot(3, 1, 3); % 3rd row subplot
histogram(blueIntensities, numBins);
title('Blue Intensities')
xlabel('Intensity')
ylabel('Pixel Count')
xlim([0, 255]);



