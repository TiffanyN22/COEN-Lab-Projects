%% MRI Video
% by Tiffany Nguyen
% This project creates a video to visualize the brain from a top, back,
% and side view using MRI slices in NIfTI files

% Read NIfTI files
V1 = niftiread('/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Week 6/MRI/T1GD.nii.gz');
V2 = niftiread('/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Week 6/MRI/T2.nii.gz');
V3 = niftiread('/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Week 6/MRI/FLAIR.nii.gz');

% Create a VideoWriter object
outputVideoPath = '/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/Week 6/matlab_output_video';
outputVideo = VideoWriter(outputVideoPath, 'MPEG-4'); % stores in mp4 file
outputVideo.FrameRate = 12;
open(outputVideo);

% Loop through slices in the NIfTI volume and write frames to the video
% Top View (move through z axis while viewing xy plane)
for sliceIndex = 1:size(V1, 3)
    % Extract the current slice
    currentSlice = V1(:,:, sliceIndex);

    % Normalize intensity values if needed
    currentSlice = mat2gray(currentSlice);

    % Display the image (optional)
    % imshow(currentSlice, []);

    % Combine slices into an RGB image for better visualization
    RGB_top(:,:,1) = mat2gray(V1(:,:, sliceIndex));
    RGB_top(:,:,2) = mat2gray(V2(:,:, sliceIndex));
    RGB_top(:,:,3) = mat2gray(V3(:,:, sliceIndex));

    % Display the colored image in a figure
    imshow(RGB_top, []);
    pause(0.05);

    % Write the current frame to the video
    writeVideo(outputVideo, im2frame(RGB_top));
end

% Back View (move through y axis while viewing xz plane)
for sliceIndex = 1:size(V1, 2)
    % Combine slices into an RGB image for better visualization
    RGB_back(:,:,1) = mat2gray(V1(:, sliceIndex, :));
    RGB_back(:,:,2) = mat2gray(V2(:, sliceIndex,: ));
    RGB_back(:,:,3) = mat2gray(V3(:, sliceIndex,: ));

    % pad the left of the image with black to write to same video 
    % (becuase image is 240x155 instead of 240x240)
    zero_matrix = zeros(240,240-155);
    RGB_back_padded(:,:,1) = [RGB_back(:,:,1) zero_matrix];
    RGB_back_padded(:,:,2) = [RGB_back(:,:,2) zero_matrix];
    RGB_back_padded(:,:,3) = [RGB_back(:,:,3) zero_matrix];

    % Display the image in a figure
    imshow(squeeze(RGB_back), []); %show in original dimensions
    % imshow(RGB_back_padded, []);
    pause(0.05);

    % Write the current frame to the video
    writeVideo(outputVideo, im2frame(RGB_back_padded));
end

% Side View (move through x axis while viewing yz plane)
for sliceIndex = 1:size(V1, 1)
    % Combine slices into an RGB image for better visualization
    RGB_side(:,:,1) = mat2gray(V1(sliceIndex, :, :));
    RGB_side(:,:,2) = mat2gray(V2(sliceIndex, :, :));
    RGB_side(:,:,3) = mat2gray(V3(sliceIndex, :, :));

    % pad the left of the image with black to write to same video 
    % (becuase image is 240x155 instead of 240x240)
    zero_matrix = zeros(240,240-155);
    RGB_side_padded(:,:,1) = [RGB_side(:,:,1) zero_matrix];
    RGB_side_padded(:,:,2) = [RGB_side(:,:,2) zero_matrix];
    RGB_side_padded(:,:,3) = [RGB_side(:,:,3) zero_matrix];

    % Display the image in a figure
    imshow(squeeze(RGB_side), []);
    pause(0.05);

    % Write the current frame to the video
    writeVideo(outputVideo, im2frame(RGB_side_padded));
end
 
% Close the video writer
close(outputVideo);

disp('Video creation complete.');