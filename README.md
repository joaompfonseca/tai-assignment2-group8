# TAI Assignment 2 - Markov Models for Text Classification

## Description

This second assignment's goal was to explore the usage of markov models for text classification. This repository contains the [report](report/report.pdf), and the source code and [executable](bin/was_chatted) of the `was_chatted` program. 

**Course:** Algorithmic Theory of Information (2023/2024)

## The `was_chatted` program

The `was_chatted` program is a command-line tool that ...

### Compile

It's optional, since you can use the provided executable inside the `bin` directory.

- Run `cd bin` in root.
- Run `cmake .. && make` to compile the program.

### Execute

- Run `cd bin` in root to change to the executable's directory.
- Run `./was_chatted REQUIRED OPTIONAL` to execute the program.

#### Required arguments

- `-n rh_file_path`: path to the file containing the text not rewritten by ChatGPT (string).
- `-r ch_file_path`: path to the file containing the text rewritten by ChatGPT (string).
- `-t t_file_path`: path to the file containing the text under analysis (string).
- `-a alphabet_file_path`: path to the file containing the considered alphabet (string).
- `-k markov_model_order`: order of the Markov model (int).
- `-s smoothing_factor`: parameter to smooth the first probability estimation (double).

#### Optional arguments

- `-h`: shows how to use the program.
- `-d reduce_factor`: factor to reduce the counts of the Markov model to prevent overflow (int, default is 2).
- `-l log_file_path`: path to the file where the log will be written (string, default is empty).

#### Example

`./was_chatted -n ../example/no.txt -r ../example/yes.txt -t ../example/test.txt -a ../example/alphabet.txt -k 6 -s 0.1`

## Authors

- Diogo Paiva, 103183
- João Fonseca, 103154
- Rafael Gonçalves, 102534
