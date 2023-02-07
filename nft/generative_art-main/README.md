This script is a program that generates a large number of images by combining IMG files randomly selected for each layer.


## Samples of completed image files
https://github.com/moyattodataman/generative_art/tree/main/output_sample

## Resource files per layer
https://github.com/moyattodataman/generative_art/tree/main/components

## Procedure

### 1. Clone the repository

```
git clone https://github.com/moyattodataman/generative_art.git
```

### 2. Prepare resource files

1. Create resource files for each layer.
2. Files to the directory of each layer.
3. If layers not enough, create additional directories. If layers are in excess, delete the directories.

```
Directory "1"; bottom layer
directory "2"; second layer from the bottom
directory "3": third layer from the bottom
same as below
```

### 3. Start the program.
The completed file is generated in the "output" directory.

```
python generative_art/generate.py
```

