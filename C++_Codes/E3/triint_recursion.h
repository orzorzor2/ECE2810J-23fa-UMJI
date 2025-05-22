
#ifndef E3_TRIINT_RECURSION_H
#define E3_TRIINT_RECURSION_H

//contained in struct RecursionResult to decide whether the recursion will go on
enum class RecursionState{
    Continue,
    Stop
};

//
struct RecursionResult{
    int values[3];
    RecursionState state;
};

//Typedef for a function pointer that takes three integers as parameters and returns a RecursionResult.
typedef RecursionResult (*RecursionFunction)(int, int, int);

// continueRecursion: return a RecursionResult struct，which contains three integers and a Continue state
RecursionResult continueRecursion(int value1, int value2, int value3);
// stopRecursion:  return a RecursionResult struct，which contains three integers and a stop state
RecursionResult stopRecursion(int returnValue);

// 声明recurse函数，接受一个函数指针和三个初始整数作为参数，返回一个整数作为递归的结果
//A function pointer that takes three integers as parameters and returns a RecursionResult
int recurse(RecursionFunction f, int initialValue1, int initialValue2, int initialValue3);



#endif
