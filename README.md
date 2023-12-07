# Multithreaded Merge Sort

This program implements multithreaded merge sort using pthreads. The goal is to efficiently sort an array of integers.

## Overview

The program uses the divide-and-conquer strategy of merge sort, and it employs pthreads to parallelize the sorting process. The array is split into two halves, and each half is sorted in parallel. Afterward, the sorted halves are merged back together.

## How it works

The program uses the pthread library to create multiple threads for sorting the array. The array is divided into two halves, and each half is sorted in a separate thread. This process is repeated recursively until each sub-array has only one element. The sorted sub-arrays are then merged back together.

## Usage

The program is executed from the command line, and it takes two arguments:
1. Input file path containing the unsorted array.
2. Output file path to store the sorted array and execution time.

```bash
./multithreaded_merge_sort input.txt output.txt
```

## Input
The input file should follow this format:

[number of elements]

element1 element2 ... elementN

For example:

10

100 20 15 3 4 8 7 -1 0 33

## Output
The program outputs the sorted array to the specified output file along with the execution time.

Example output:

Sorted array: -1 0 3 4 7 8 15 20 33 100

Time: 0.001234 s

