# Virtual Machine Translator (with C++)

C++ implementation of a translator that translates virtal machine code to assembly code

## Description

This repository is created for the final project of Online course  <a href="https://www.nand2tetris.org/"> From Nand to Tetris </a>. The relevant detailed background regarding this project can be found <a href="https://www.nand2tetris.org/project07"> here </a>.

The main idea is based on Jack Programming Language and Virtual Machine (Emulator) of this online course. Instead of compiling directly from programming language to assembly code. We use 2-tier method that translates programming language to the code of a Virtual machine, e.g. bytecode for Java Virtual Machine. Then, this virtual machine code is translated into assembly code. 

## Getting Started

### Dependencies

* C++ compiler

### Installing

* To download this repository, it is enough to run the following command in a command-line shell (e.g. bash)

`!git clone `

### Executing program
After installing, run the following commands in a commmand shell
To ensure that these files are executable:
* ` chmod +x configure.sh build.sh run.sh`

To determine the structure of source and build folders before createing makefiles; and create makefiles

* ` ./configure.sh`

To build executable binary files
* `./build.sh `

To run make files binaries
* ` ./run.sh`


## License

This project is licensed under the MIT License - see the LICENSE.md file for details
