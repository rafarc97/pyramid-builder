#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cassert>

class CannotBuildPyramidException : public std::exception {
public:
    const char *what() const throw() {
        return "Cannot build pyramid with given input";
    }
};

class PyramidBuilder {
public:
    std::vector<std::vector<int>> buildPyramid(std::vector<int> inputNumbers) {
        int length = inputNumbers.size();
        int n_rows = (-1 + sqrt(1 + 8 * length)) / 2;
        int n_cols = 2 * n_rows - 1;

        // Check whether exists a null value
        bool containNull = false;
        for (int i = 0; i < length; i++) {
            if (inputNumbers[i] == -1) {
                containNull = true;
                break;
            }
        }

        // Check if list size meets pyramid condition
        bool check_num = false;
        int formula_size = 0;
        for (int i = 0; i < INT_MAX && !check_num && formula_size <= length; i++) {
            formula_size = i * (i + 1) / 2;
            if (length == formula_size) {
                check_num = true;
            }
        }
        // Throw Exception
        if (!check_num || containNull) {
            throw CannotBuildPyramidException();
        }
            // Build Pyramid
        else {
            std::vector<std::vector<int>> result(n_rows, std::vector<int>(n_cols, 0));
            std::sort(inputNumbers.begin(), inputNumbers.end(), std::greater<int>());
            int m = 0;

            for (int i = 0; i < n_rows; i++) {
                if (i == 0) { // set last row
                    for (int h = n_cols - 1; h >= 0; h--) { // manage n_cols
                        if (h % 2 == 0) { // write a number > 0
                            result[n_rows - 1][h] = inputNumbers[m];
                            m++;
                        }
                    }
                } else { // set other rows i != 0
                    // draw first zeros
                    for (int ii = 0; ii < i; ii++) {
                        result[n_rows - i - 1][n_cols - ii - 1] = 0;
                    }

                    // draw center
                    for (int c = 0; c < 2 * (n_rows - i) - 1; c++) {
                        if (c % 2 == 0) {
                            result[n_rows - i - 1][n_cols - i - c - 1] = inputNumbers[m];
                            if (m < length) {
                                m++;
                            }
                        }
                    }

                    // draw lasts zeros
                    for (int ii = 0; ii < i; ii++) result[n_rows - i - 1][ii] = 0;
                }
            }
            return result;
        }
    }
};

void comparePyramids(std::vector<std::vector<int>> expected, std::vector<std::vector<int>> pyramid) {
    if (expected.size() != pyramid.size()) std::cout << "Amount of rows is different." << std::endl;

    bool aux = false;
    for (int i = 0; i < expected.size() && aux == false; i++) {
        if (expected[i] != pyramid[i]) {
            std::cout << "Pyramid arrays are not equal." << std::endl;
            aux = true;
        }
    }
}


int main() {
    PyramidBuilder pyramidBuilder{};

    // -----------TEST 1------------
    std::vector<int> input = {1, 15, 2};
    std::vector<std::vector<int>> expected = {{0, 1, 0},
                                              {2, 0, 15}};
    // run
    std::vector<std::vector<int>> pyramid = pyramidBuilder.buildPyramid(input);
    // assert
    comparePyramids(expected, pyramid);



    // -----------TEST 2------------
    std::vector<int> input2 = {1, 3, 2, 9, 4, 5};
    std::vector<std::vector<int>> expected2 = {
            {0, 0, 1, 0, 0},
            {0, 2, 0, 3, 0},
            {4, 0, 5, 0, 9}};

    // run
    std::vector<std::vector<int>> pyramid2 = pyramidBuilder.buildPyramid(input2);
// assert
    comparePyramids(expected2, pyramid2);


    // -----------TEST 3------------
    std::vector<int> input3 = {1, 3, 2, 9, 4, 5, 10, 8, 7, 6};
    std::vector<std::vector<int>> expected3 = {
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 2, 0, 3, 0, 0},
            {0, 4, 0, 5, 0, 6, 0},
            {7, 0, 8, 0, 9, 0, 10}};

    // run
    std::vector<std::vector<int>> pyramid3 = pyramidBuilder.buildPyramid(input3);
// assert
    comparePyramids(expected3, pyramid3);




    // -----------TEST 4------------
    std::vector<int> input4 = {11, 1, 12, 3, 2, 13, 9, 4, 5, 14, 10, 8, 7, 15, 6};
    std::vector<std::vector<int>> expected4 = {
            {0,  0, 0,  0, 1,  0, 0,  0,  0},
            {0,  0, 0,  2, 0,  3, 0,  0,  0},
            {0,  0, 4,  0, 5,  0, 6,  0,  0},
            {0,  7, 0,  8, 0,  9, 0,  10, 0},
            {11, 0, 12, 0, 13, 0, 14, 0,  15}
    };

    // run
    std::vector<std::vector<int>> pyramid4 = pyramidBuilder.buildPyramid(input4);
// assert
    comparePyramids(expected4, pyramid4);




    // -----------TEST 5------------
    std::vector<int> input5 = {11, 1, 21, 12, 3, 16, 2, 13, 9, 4, 17, 5, 14, 10, 18, 8, 7, 19, 15, 6, 20};
    std::vector<std::vector<int>> expected5 = {
            {0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0},
            {0,  0,  0,  0,  2,  0,  3,  0,  0,  0,  0},
            {0,  0,  0,  4,  0,  5,  0,  6,  0,  0,  0},
            {0,  0,  7,  0,  8,  0,  9,  0,  10, 0,  0},
            {0,  11, 0,  12, 0,  13, 0,  14, 0,  15, 0},
            {16, 0,  17, 0,  18, 0,  19, 0,  20, 0,  21}
    };

    // run
    std::vector<std::vector<int>> pyramid5 = pyramidBuilder.buildPyramid(input5);
    // assert
    comparePyramids(expected5, pyramid5);




    // -----------TEST 6------------
    /*std::vector<int> input6 = {1, 3, 2, 9, 4, null};
    std::vector<std::vector<int>> expected6 = {
            {0, 0, 1, 0, 0},
            {0, 2, 0, 3, 0},
            {4, 0, 5, 0, 9}};

    // run
    std::vector<std::vector<int>> pyramid6 = pyramidBuilder.buildPyramid(input6);
    // assert
    //comparePyramids(expected6, pyramid6);*/




    // -----------TEST 7------------
    /*std::vector<int> input7 = {1, 3, 2, 9, 4, 5, null};
    std::vector<std::vector<int>> expected7 = {
            {0, 0, 1, 0, 0},
            {0, 2, 0, 3, 0},
            {4, 0, 5, 0, 9}};

    // run
    std::vector<std::vector<int>> pyramid7 = pyramidBuilder.buildPyramid(input7);
    // assert
     comparePyramids(expected7, pyramid7);
     */




    // -----------TEST 8------------
    /*  std::vector<int*> input8;
      for (int i = 1; i < 256; i++) {
          int* ptr = new int(i);
          input8.push_back(ptr);
      }
      // run
      std::vector<std::vector<int>> pyramid8 = pyramidBuilder.buildPyramid(input8);
      // assert
      comparePyramids(expected8, pyramid8);
      */




    // -----------TEST 9------------
    /*std::vector<int> input9;
    for (int i = 1; i < 10000; i++) {
        input.push_back(i);
    }
    // run
    std::vector<std::vector<int>> pyramid9 = pyramidBuilder.buildPyramid(input9);
    // assert
     comparePyramids(expected9, pyramid9);
    */



    // -----------TEST 10------------
    //std::vector<int> input10(std::numeric_limits<int>::max() - 1, 0);
    // run
    //std::vector<std::vector<int>> pyramid10 = pyramidBuilder.buildPyramid(input10);
    // assert
    //comparePyramids(expected10, pyramid10);




    // -----------TEST 11------------
    std::vector<int> input11 = {1, 3, 2, 0, 4, 5};
    std::vector<std::vector<int>> expected11 = {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 2, 0},
            {3, 0, 4, 0, 5}};
    // run
    std::vector<std::vector<int>> pyramid11 = pyramidBuilder.buildPyramid(input11);
    // assert
    comparePyramids(expected11, pyramid11);



/*
    for (std::vector<int> elem: pyramid8) {
        for (int num: elem) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

     for (std::vector<int> elem: expected8) {
         for (int num: elem) {
             std::cout << num << " ";
         }
         std::cout << std::endl;
     }
*/
    return 0;
}
