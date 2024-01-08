# NTPU Fall 2023 DSP Homework #4

* Source code is hosted at https://github.com/twolights/ntpu-dsp-homework4

# Prerequisites

## For Performing Resampling

1. CMake 3.27+ or make
2. gcc with C99 standard support

## For Plotting Impulse Response

1. Python 3.8+ (only tested on 3.8.17 though)
2. NumPy
3. matplotlib
4. virtualenv
5. pip

# How to Run

## Perform Resampling

### With make

1. Build the project
    ```bash
    # make
    ```
   
2. Run the program
   ```bash
   # make test
   ```

### With CMake

1. Build the project
    ```bash
    # cmake -S . -B cmake-build-debug
    # cmake --build ./cmake-build-debug
    ```
   
2. Run the program
   ```bash 
   # ./cmake-build-debug/HW4 ./input/input.wav ./output/output.wav
   ```


### Low-Pass Filter Coefficients

* After running the program, the coefficients will be saved in `./output/lpf.csv`

## Plotting Impulse Response

1. Create a virtual environment with
    ```bash
    # cd plot
    # virtualenv `which python3` env
    ```
   
2. Install dependencies with
    ```bash
    # pip install -r requirements.txt
    ```
   
3. Run main.py
    ```bash
    # python main.py
    ```

4. The image will be saved to `./output/ir-and-magnitude.png`
