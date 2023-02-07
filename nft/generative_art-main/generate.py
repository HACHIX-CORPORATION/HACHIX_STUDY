import random
import os
from PIL import Image

# Set components directory and output directory
components_directory_path = 'components'
output_directory_path = 'output'

# Get layers list in components directory
layers = os.listdir(components_directory_path)
layers.sort()

# Calculate max patterns 
max_patterns = 1
for layer in layers:
    layer_path = os.path.join(components_directory_path, layer)
    max_patterns = max_patterns * len(os.listdir(layer_path))

# Set how many files to create
count = input(f'How many files created? Max {max_patterns}\n')
count = int(count)

# If larger than max_patterns, re-enter
while count > max_patterns:
    count = input(f'Set a value less than Max {max_patterns}\n')
    count = int(count)

# Generate images
id_length = len(str(count - 1))
img_patterns = []
n = 0
while n < count:
    
    # Set 1st layer
    layer_path = os.path.join(components_directory_path, layers[0])
    files = os.listdir(layer_path)
    random_file = random.choice(files)
    file_path = os.path.join(layer_path, random_file)
    img = Image.open(file_path)
    img_pattern = random_file.split('.')[0]

    # Set 2nd and above layers
    for layer in layers[1:]:
        layer_path = os.path.join(components_directory_path, layer)
        files = os.listdir(layer_path)
        random_file = random.choice(files)
        file_path = os.path.join(layer_path, random_file)
        add_img = Image.open(file_path)
        img.paste(add_img, add_img)
        img_pattern = img_pattern + random_file.split('.')[0]

    # Check duplicate
    if img_pattern in img_patterns:
        continue;
    # Generate image
    else:
        img_patterns.append(img_pattern)
        id = str(n).zfill(id_length)
        img_file_name = id + '_' + img_pattern + '.png'
        img.save(os.path.join(output_directory_path, img_file_name))
        n += 1
        print(f'File{id} has been generated.')

print("Complete!")