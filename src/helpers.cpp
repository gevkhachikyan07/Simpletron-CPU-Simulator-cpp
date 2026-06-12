
#include "../include/helpers.h"


using namespace std;
#include <iostream>
#include <format>
#include <array>
#include <limits>
#include <cmath>

void load(int *  instructionCounter, int * memory){
     while (*instructionCounter < 1000)
    {
        cout << format("{:03} ? ",*instructionCounter);
        cin >> memory[*instructionCounter];
        if (memory[*instructionCounter] == -999999)
            break;
        int memToDecimal = memory[*instructionCounter];    
        if ( memToDecimal > 99999 ||  memToDecimal < -99999)
        {   
            cout << "*** Invalid instruction format ***\n";
            break;
        }
            
        (*instructionCounter)++;
    }
   
    cout<<"***         Program loading completed           ***\n";
}

void memoryDump(int * const accumulator, int * const instructionCounter,
    int * const instructionRegister,int * memory,
    int * const operationCode, int * const operand){
    cout << "REGISTERS:\n";
    cout << format("accumulator:                {:+06}\n", *accumulator);
    cout << format("instructionCounter:           {:04}\n", *instructionCounter);
    cout << format("instructionRegister:        {:+06}\n", *instructionRegister);
    cout << format("operationCode:                 {:03}\n", *operationCode);
    cout << format("operand:                        {:02}\n", *operand);

    cout << "MEMORY:\n\n";
    array<array<string, 11>,101>dump{};
    dump.at(0).at(0) = "  ";
    for (size_t i = 1; i < dump.at(0).size(); i++)
    {   
        dump.at(0).at(i) = format("{}",i - 1);
    }
    for (size_t i = 1; i < dump.size(); i++)
    {
        dump.at(i).at(0) = format("{}",(i - 1)*10);
    }
    
    int count{0};
    for (size_t i = 1; i < dump.size(); i++)
    {
        for (size_t j = 1; j < dump.at(i).size(); j++)
        {
           dump.at(i).at(j) = format("{:+06}",memory[count++]);
        }
        
    }
    
    
    for(const auto& memory :dump){
        for(const string& loc : memory){
            cout << format("{:>8}",loc);
        }
        cout << endl;
    }
}

void execute(int *  accumulator, int *  instructionCounter,
    int *  instructionRegister,int * memory,
    int *  operationCode, int *  operand){
        
    enum operationCodes{
        read        = 10,   
        write       = 11,
        newline     = 12,
        readString  = 13,
        writeString = 14,   
        load        = 20,   
        store       = 21,   
        add         = 30,   
        subtract    = 31,   
        divide      = 32,   
        multiply    = 33,
        remainder   = 34,  
        exponentiation = 35, 
        branch      = 40,   
        branchNeg   = 41,   
        branchZero  = 42,   
        halt        = 43    
    };
    
    cout<<"***         Program execution begins            ***\n\n";
    *instructionCounter = 0;
    while (*instructionCounter < 1000)
    {   
        *instructionRegister = memory[*instructionCounter];
        *operand = *instructionRegister % 1000;
        *operationCode = *instructionRegister / 1000;
        switch (*operationCode)
        {   
            case  read:
                cin >> memory[*operand];
                break;
            case write:
                cout << memory[*operand]<<endl;
                break;
            case newline:
                cout << endl;
                break;   
            case readString:{
                string word;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, word);
                memory[*operand] = word.length() * 256 + word.at(0) %256 ;
                (*operand)++;
                for(size_t i{1}; i < word.length(); i+=2){
                    int left = word.at(i) % 256;
                    if (i + 1 >= word.length())
                    {
                        memory[(*operand)++] = left*256;
                    }else{
                        
                        memory[(*operand)++] = left*256 + (word.at(i+1) % 256);
                    }
                }
                break;  
            }
            case writeString:{
                size_t length = memory[*operand] / 256;
                cout << (char) (memory[*operand] % 256);
                (*operand)++;
                for (size_t i = 1; i < length; i++)
                {  
                    cout << (char)(memory[*operand] / 256);
                    if (memory[*operand] % 256 != 0)
                    {
                        cout << (char)(memory[*operand] % 256);
                    }
                    (*operand)++;
                }
                cout << endl;
                
                break;
            }   
            case load:
                *accumulator = memory[*operand];
                break;
            case store:
                memory[*operand] =*accumulator;
                break;
            case add:
                if (*accumulator + memory[*operand] > 99999 || *accumulator + memory[*operand] < -99999)
                {
                    cout << "Error: Arithmetic overflow\n";
                    break;
                }
                
                *accumulator += memory[*operand];
                break;
            case subtract:
                 if (*accumulator - memory[*operand] < -99999 || *accumulator - memory[*operand] > 99999 )
                {
                    cout << "Error: Arithmetic overflow\n";
                    break;
                }
                *accumulator -= memory[*operand];
                break;
            case divide:
                if (memory[*operand] == 0)
                {
                   cout <<"Error: Division by zero\n";
                   break;
                }
                
                *accumulator /= memory[*operand];
                break;
            case multiply:
                 if (*accumulator * memory[*operand] > 99999
                     || *accumulator * memory[*operand] < -99999)
                {
                    cout << "Error: Arithmetic overflow\n";
                    break;
                }
                *accumulator *= memory[*operand];
                break;
            case remainder:
                if (memory[*operand] == 0)
                {
                   cout <<"Error: Division by zero\n";
                   break;
                }
                *accumulator %= memory[*operand];
                break;
            case exponentiation:{
                int result = pow(*accumulator,memory[*operand]);
                if (result > 99999 || result < -99999)
                {
                    cout << "Error: Arithmetic overflow\n";
                    break;
                }
                *accumulator = result;
                break; 
            }       
            case branch:
                *instructionCounter = *operand -1;
                break;
            case branchNeg:
                if(*accumulator < 0){
                    *instructionCounter = *operand - 1;
                }
                break;   
            case branchZero:
                if (*accumulator == 0)
                {
                    *instructionCounter = *operand - 1;
                }
                break;
            case halt:
                cout << "*** Simpletron execution terminated ***\n\n";              
                return;   
            default:
                break;
        }
        (*instructionCounter)++;
    }

}