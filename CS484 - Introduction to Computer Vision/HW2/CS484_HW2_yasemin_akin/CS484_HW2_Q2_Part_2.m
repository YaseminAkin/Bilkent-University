addpath('/Users/yaseminakin/Documents/MATLAB');

image_dir = '/Users/yaseminakin/Desktop/CS484 - Introduction to Computer Vision/HW2/part2';         
label_dir = '/Users/yaseminakin/Desktop/CS484 - Introduction to Computer Vision/HW2/label_matrices_mat';      
feature_output_dir = '/Users/yaseminakin/Desktop/CS484 - Introduction to Computer Vision/HW2/feature_matrices';      
visualization_output_dir = '/Users/yaseminakin/Desktop/CS484 - Introduction to Computer Vision/HW2/gabor_visualizations'; 

if ~exist(feature_output_dir, 'dir')
    mkdir(feature_output_dir);
end
if ~exist(visualization_output_dir, 'dir')
    mkdir(visualization_output_dir);
end

image_files = dir(fullfile(image_dir, '*.jpg')); 

num_scales = 4;
num_orientations = 4;
minWaveLength = 3;
mult = 2;
sigmaOnf = 0.65;      
dThetaOnSigma = 1.5;  

for i = 1:length(image_files)
    image_name = image_files(i).name;
    base_name = image_name(1:strfind(image_name, '.') - 1);  

    image_path = fullfile(image_dir, image_name);
    img = imread(image_path);
    if size(img, 3) == 3
        img_gray = rgb2gray(img);
    else
        img_gray = img;
    end
    img_gray = im2double(img_gray);

    label_file = fullfile(label_dir, [base_name, '_labels.mat']);
    if exist(label_file, 'file')
        data = load(label_file);
        labels = data.labels;
    else
        fprintf('Label file %s not found. Skipping image.\n', label_file);
        continue;
    end

    try
        EO = gaborconvolve(img_gray, num_scales, num_orientations, ...
                           minWaveLength, mult, sigmaOnf, dThetaOnSigma);
    catch ME
        fprintf('Error processing image %s: %s\n', image_name, ME.message);
        continue;
    end

    num_filters = num_scales * num_orientations;
    [rows, cols] = size(img_gray);
    responses = zeros(rows, cols, num_filters);
    idx = 1;
    for scale = 1:num_scales
        for orientation = 1:num_orientations
            real_part = real(EO{scale, orientation});
            imag_part = imag(EO{scale, orientation});
            magnitude = sqrt(real_part.^2 + imag_part.^2);
            responses(:, :, idx) = magnitude;
            idx = idx + 1;
        end
    end

    num_superpixels = max(labels(:)) + 1;  
    feature_matrix = zeros(num_superpixels, num_filters);
    for j = 1:num_filters
        response = responses(:, :, j);
        for k = 0:num_superpixels - 1
            mask = labels == k;
            if any(mask(:))
                feature_matrix(k + 1, j) = mean(response(mask));
            else
                feature_matrix(k + 1, j) = 0;
            end
        end
    end

    feature_output_file = fullfile(feature_output_dir, [base_name, '_features.mat']);
    save(feature_output_file, 'feature_matrix');
    fprintf('Saved feature matrix to %s\n', feature_output_file);

    figure('Name', ['Gabor Features for ', image_name], 'NumberTitle', 'off');
    idx = 1;
    for scale = 1:num_scales
        for orientation = 1:num_orientations
            subplot(num_scales, num_orientations, idx);
            imshow(responses(:, :, idx), []);
            title(sprintf('Scale %d, Orientation %d', scale, orientation));
            idx = idx + 1;
        end
    end
    set(gcf, 'Position', get(0, 'Screensize'));  
    sgtitle(['Gabor Filter Responses for ', image_name], 'FontSize', 16);

    visualization_output_file = fullfile(visualization_output_dir, [base_name, '_gabor_features.png']);
    saveas(gcf, visualization_output_file);
    fprintf('Saved Gabor feature visualization to %s\n', visualization_output_file);

    close(gcf);
end