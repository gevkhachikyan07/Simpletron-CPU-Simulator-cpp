#ifndef SIMPLETRON_H
#define SIMPLETRON_H


#include <iostream>
#include <format>
#include <array>
#include <limits>
#include <cmath>

void load(int *  instructionCounter, int * memory);
void memoryDump(int * const accumulator, int * const instructionCounter,
    int * const instructionRegister,int * memory,
    int * const operationCode, int * const operand);
    
void execute(int *  accumulator, int *  instructionCounter,
    int *  instructionRegister,int * memory,
    int *  operationCode, int *  operand);





#endif 