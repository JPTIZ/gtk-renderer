#ifndef RUDOLPH_ALGEBRA_H
#define RUDOLPH_ALGEBRA_H

#include <iostream>

namespace algebra {

int* mult_matrix(float* matrixA, float* matrixB) {

    int product[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};  

    for (int row = 0; row < 3; row++) {  
        for (int col = 0; col < 3; col++) {  
            for (int inner = 0; inner < 2; inner++) {
                product[row][col] += matrixA[row][inner] * matrixB[inner][col];  
            }  
            std::cout << product[row][col] << "  ";
        }  
        std::cout << "\n";  
    }  
}  

}
#endif