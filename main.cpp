#include "include/helpers.h"
using namespace std;

int main(){

    int memory[1000]{};
    int accumulator{0};
    int instructionCounter{0}; //stores the number of memory location
    int operationCode{0};//stores the opperation currently being performed(left 2 digits)
    int operand{0};//to store the number of memory location on which the current instruction operates(right 3 digits)
    int instructionRegister{0};// for transfering the next instruction into yhis variable and then picking left 2 and right 3 digs
    cout << endl;
    cout<<"***           Welcome to Simpletron             ***\n";
    cout<<"***                                             ***\n";
    cout<<"***  Please enter your program one instruction  ***\n";
    cout<<"***  (or data word) at a time. I will type the  ***\n";
    cout<<"***  location number and a question mark (?).   ***\n";
    cout<<"***  You then type the word for that location.  ***\n";
    cout<<"***  Type the sentinel -999999 to stop entering ***\n";
    cout<<"***  your program.                              ***\n\n";
    
    load(&instructionCounter,memory);
    execute(&accumulator,&instructionCounter,&instructionRegister,memory,&operationCode,&operand);
    memoryDump(&accumulator,&instructionCounter,&instructionRegister,memory,&operationCode,&operand);     
   
}