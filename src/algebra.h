#ifndef RUDOLPH_ALGEBRA_H
#define RUDOLPH_ALGEBRA_H

namespace algebra {

int* mult_matrix(float* matrixA, float* matrixB) {

    int product[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};  

    for (int row = 0; row < 3; row++) {  
        for (int col = 0; col < 3; col++) {  
            // Multiply the row of A by the column of B to get the row, column of product.  
            for (int inner = 0; inner < 2; inner++) {  
                product[row][col] += aMatrix[row][inner] * bMatrix[inner][col];  
            }  
            std::cout << product[row][col] << "  ";  
        }  
        std::cout << "\n";  
    }  
}  

}
#endif