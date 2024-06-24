%% Detect Altered MRI Image
% by Tiffany Nguyen
% Read all files within the folder
folder_path = '/Users/tiffanynguyen/Downloads/tagged/SCU/BIOE 45/Lab/week 9/JPG';
mri_images_dir = dir([folder_path '/*.jpg']);

deafult_img_name = 'a.jpg'; %first image is default
default_img = imread([folder_path '/' deafult_img_name]); % read default image
diff_img = "";
diff_count = 0;

for i=1:length(mri_images_dir) %iterate through images in folder
    % read current image
    filename=[folder_path '/' mri_images_dir(i).name];
    cur_img = imread(filename);

    % compare current image with default
    difference = default_img - cur_img;
    diff_sum = sum(difference, "all");
    if diff_sum ~= 0 % image is different from default
        diff_img = mri_images_dir(i).name;
        diff_count = diff_count + 1;
    end
end

% there should only be one different image, so default image is wrong is more than one
if diff_count ~= 1 
    disp(deafult_img_name + " is different")
else
    disp(diff_img + " is different")
end