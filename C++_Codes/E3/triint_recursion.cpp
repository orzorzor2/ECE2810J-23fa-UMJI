#include "triint_recursion.h"


// continueRecursion: return a RecursionResult struct，which contains three integers and a Continue state
RecursionResult continueRecursion(int value1, int value2, int value3){
    RecursionResult result;
    result.values[0] = value1;
    result.values[1] = value2;

    result.values[2] = value3;
    result.state = RecursionState::Continue;
    return result;
}

// stopRecursion:  return a RecursionResult struct，which contains three integers and a stop state
RecursionResult stopRecursion(int returnValue){
    RecursionResult result;
    result.values[0] = returnValue;
    result.state = RecursionState::Stop;
    return result;
}

// recurse: accept three integers and a function pointer as parameters and return an integer as the result of the recursion
int recurse(RecursionFunction f, int initialValue1, int initialValue2, int initialValue3){
    RecursionResult res = f(initialValue1, initialValue2, initialValue3); // use f to get a RecursionResult struct
    if(res.state == RecursionState::Stop){ // if "Stop", end the recursion and return the first integer
        return res.values[0];
    }
    else{ // if "Continue", go on the recursion. use tht three integers in struct as new parameters and call recurse again
        return recurse(f, res.values[0], res.values[1], res.values[2]);
    }
}
