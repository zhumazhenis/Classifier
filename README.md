# Classifier

1.) The aim of the project: Comparing the true errors of different classifiers.

2.) How it is done: We were given source files that were written by professor, and we should remove all redundant codes, and add new codes of different classifiers. I, Zhumazhenis Dairabay, have coded all classifiers during this group project as my part was coding. 

4.) Language: C++

5.) What topics included: Loops, Arrays, Functions, Struct, working with files (reading and writing .txt files)

6.) Difficulties I have faced during coding: In the project, determinant of the matrix should be evaluated. At the beginning I used recursion to code the determinant and it worked nice for small dimension matrices(e.g. 5x5, 6x6). But, it did not work for larger dimension matrices(e.g. 20x20, 50x50). After some brainstorming, I have found out that recursion does too much operations and it leads non-responding of the computer (computer freezes and does not repond even the click of the mouse). Then, I found out that, Cholesky decomposition can be used for evaluating the determinant of the matrix. Then I used it, after that, determinant of high dimension matrix is evaluated. See classifiers.cpp and matrixOperations.cpp source file.

