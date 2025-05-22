#include <iostream>
#include "triint_recursion.h"

using namespace std;

//give an example of one recursion function: factorial
RecursionResult factorial(int n, int acc, int _){
    if(n == 0){
        return stopRecursion(acc);
    }
    return continueRecursion(n-1, acc*n, _);
}

int main(){
    int result = recurse(factorial, 5, 1, 0); // pass the factorial function inside here, and is convenient for other recursion function to passed
    cout << result << endl;
}
