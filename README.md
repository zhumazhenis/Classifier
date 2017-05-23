# Classifiers

1.) The aim of the project: Comparing the true errors of different classifiers.

2.) How it is done: We were given source files that were written by professor Amin Zollanvari, and we should remove all redundant codes, and add new codes of different classifiers. I, Zhumazhenis Dairabay, have coded all classifiers during this group project as my part was coding and math. 

4.) Language that is used in project: C++

5.) What topics included: Loops, Arrays, Functions, Struct, working with files (reading and writing .txt files)

6.) Difficulties I have faced during coding: In the project, determinant of the matrix should be evaluated. At the beginning I used recursion to code the determinant and it worked nice for small dimension matrices(e.g. 5x5, 6x6). But, it did not work for larger dimension matrices(e.g. 20x20, 50x50). After some brainstorming, I have found out that recursion does too much operations and it leads non-responding of the computer (computer freezes and does not repond even the click of the mouse). Then, I found out that, Cholesky decomposition can be used for evaluating the determinant of the matrix. Then I used it, after that, determinant of high dimension matrix is evaluated. See classifiers.cpp and matrixOperations.cpp source file.

7.) The source files I have worked with: calculateErrors.cpp, classifiers.cpp, main.cpp, calculateErrors.h, classifiers.h.

8.) Project is too big and there are some parts of source files that I do not understand. But, for this project it does not need to understand all parts of source files. 

9.) The project also concerns math as we need to deal with probability and matrices.

10.) BENG 146 Programming for engineers course: It covers C++ and Java. See BENG146_course_specification.pdf file.

11.) My achievements:
International Zhautykov Math Olympiad - bronze (individual)
Asian-Pacific Math Olympiad - bronze (individual)
Silk-Road International Math Olympiad - bronze (individual)
Republican Math Olympiad - bronze (individual)
NU Math Battle - 3rd place (team)

12.) How this project helps me for participating nFactorial Incubator: I got acquainted with basic theories about machine learning (classifiers). I understood how classifiers work. For developing my application, I need to learn TensorFlow which is an open source library. In addition, I started to learn developing android apps from thenewboston android developing for beginner (youtube) and I have some practices with .xml files (layout), activities (java, android library).

13.) How to compile and run project: 
a.) Compile project using command line (Windows+R, cmd.exe). Open the src folder in command line using cd and dir. Then compile the project using mingw32-make. (firstly, change PATH to C:\Program Files (x86)\CodeBlocks\MinGW\bin). Command lines shows some errors, but do not look at them.
b.) Then enter to bin folder using cd and dir. Copy and paste from commands.txt file (project.exe will run). After you have runned, there will occur new .txt files in ChenLiver2004_10237x157 or other folders depending on the command. 
