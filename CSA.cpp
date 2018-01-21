#include <bits/stdc++.h>

using namespace std;

int main() {

    /*Constant data: Writing data*/

    clock_t start, end;
    int *a, a_temp;
    float *b, b_temp;
    char *c, c_temp;
    double *d, d_temp;

    double a_speed = 0, b_speed = 0, c_speed = 0, d_speed = 0, difference;

    cout << fixed;
    cout << setprecision(3);

    cout << "Constant data:\nWriting data time (sec)\n";
    cout << "array_size\t" << "int(" << sizeof(int) << ")\t";
    cout << "flot(" << sizeof(float) << ")\t";
    cout << "char(" << sizeof(char) << ")\t";
    cout << "double(" << sizeof(double) << ")\n";

    for (int i = 0; i < 10; i++) {
        int k = (i + 1) * (int) 1e7;
        cout << k << "\t";

        /* int start*/
        a = new int[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            a[j] = 0;
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        a_speed = a_speed + k * sizeof(int) / (difference * 1e9);
        delete[]a;
        /* int end*/


        /* float start*/
        b = new float[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            b[j] = 0.0;
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        b_speed = b_speed + k * sizeof(float) / (difference * 1e9);
        delete[]b;
        /* float end*/


        /* char start*/
        c = new char[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            c[j] = 'c';
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        c_speed = c_speed + k * sizeof(char) / (difference * 1e9);
        delete[]c;
        /* char end*/


        /* double start*/
        d = new double[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            d[j] = 0.0;
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << endl;
        d_speed = d_speed + k * sizeof(double) / (difference * 1e9);
        delete[]d;
        /* double end*/
    }

    /*Average write through puts (GBytes/sec)*/
    cout << "\nAverage write through puts (GBytes/sec)" << endl;
    cout << "int(" << sizeof(int) << ")\t";
    cout << "flot(" << sizeof(float) << ")\t";
    cout << "char(" << sizeof(char) << ")\t";
    cout << "double(" << sizeof(double) << ")\n";
    cout << a_speed / 10 << "\t";
    cout << b_speed / 10 << "\t";
    cout << c_speed / 10 << "\t";
    cout << d_speed / 10 << "\t" << endl << endl;

    a_speed = 0;
    b_speed = 0;
    c_speed = 0;
    d_speed = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* RANDOM: Writing data*/

    cout << "Random data:\nWriting data time (sec)\n";
    cout << "array_size\t" << "int(" << sizeof(int) << ")\t";
    cout << "flot(" << sizeof(float) << ")\t";
    cout << "char(" << sizeof(char) << ")\t";
    cout << "double(" << sizeof(double) << ")\n";

    for (int i = 0; i < 10; i++) {
        int k = (i + 1) * (int) 1e7;
        cout << k << "\t";

        /* int start*/
        a = new int[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            a[j] = rand();
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        a_speed = a_speed + k * sizeof(int) / (difference * 1e9);
        delete[]a;
        /* int end*/


        /* float start*/
        b = new float[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            b[j] = rand();
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        b_speed = b_speed + k * sizeof(float) / (difference * 1e9);
        delete[]b;
        /* float end*/


        /* char start*/
        c = new char[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            c[j] = "AB"[rand() % 2];
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        c_speed = c_speed + k * sizeof(char) / (difference * 1e9);
        delete[]c;
        /* char end*/


        /* double start*/
        d = new double[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            d[j] = rand();
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << endl;
        d_speed = d_speed + k * sizeof(double) / (difference * 1e9);
        delete[]d;
        /* double end*/
    }

    /*Average write through puts (GBytes/sec)*/
    cout << "\nAverage write through puts (GBytes/sec)" << endl;
    cout << "int(" << sizeof(int) << ")\t";
    cout << "flot(" << sizeof(float) << ")\t";
    cout << "char(" << sizeof(char) << ")\t";
    cout << "double(" << sizeof(double) << ")\n";
    cout << a_speed / 10 << "\t";
    cout << b_speed / 10 << "\t";
    cout << c_speed / 10 << "\t";
    cout << d_speed / 10 << endl;

    a_speed = 0;
    b_speed = 0;
    c_speed = 0;
    d_speed = 0;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* Reading data*/

    cout << "\nReading data time (sec)\n";
    cout << "array_size\t" << "int(" << sizeof(int) << ")\t";
    cout << "flot(" << sizeof(float) << ")\t";
    cout << "char(" << sizeof(char) << ")\t";
    cout << "double(" << sizeof(double) << ")\n";

    for (int i = 0; i < 10; i++) {
        int k = (i + 1) * (int) 1e7;
        cout << k << "\t";

        /* int start*/
        a = new int[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            a_temp = a[j];
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        a_speed = a_speed + k * sizeof(int) / (difference * 1e9);
        delete[]a;
        /* int end*/


        /* float start*/
        b = new float[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            b_temp = b[j];
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        b_speed = b_speed + k * sizeof(float) / (difference * 1e9);
        delete[]b;
        /* float end*/


        /* char start*/
        c = new char[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            c_temp = c[j];
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << "\t";
        c_speed = c_speed + k * sizeof(char) / (difference * 1e9);
        delete[]c;
        /* char end*/


        /* double start*/
        d = new double[k];
        start = clock();
        for (int j = 0; j < k; j++) {
            d_temp = d[j];
        }
        end = clock();
        difference = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << difference << endl;
        d_speed = d_speed + k * sizeof(double) / (difference * 1e9);
        delete[]d;
        /* double end*/
    }

    /*Average reading (GBytes/sec)*/
    cout << "\nAverage reading (GBytes/sec)" << endl;
    cout << "int(" << sizeof(int) << ")\t";
    cout << "flot(" << sizeof(float) << ")\t";
    cout << "char(" << sizeof(char) << ")\t";
    cout << "double(" << sizeof(double) << ")\n";
    cout << a_speed / 10 << "\t";
    cout << b_speed / 10 << "\t";
    cout << c_speed / 10 << "\t";
    cout << d_speed / 10 << "\n\n";


    cout << "Enter any character in order to exit . . .";
    getchar();

    return 0;
}
