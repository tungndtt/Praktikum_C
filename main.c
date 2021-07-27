#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registers.h"

// ================================ TASK 1 =============================
// task 1a
void sprintf_concatenator(char *dest, const char *a, const char *b) {
    sprintf(dest, "%s%s", a, b);
}

// task 1c
void strcpy_concatenator(char *dest, const char *a, const char *b) {
    strcpy(dest, a);
    strcpy(dest, b);
}

// task 1d
void concat(char* dest, const char* src) {
    int i = 0, j = 0;
    while(dest[i]) ++i;
    while(src[j]) dest[i++] = src[j++];
    dest[i] = '\0';
}
void loop_concatenator(char *dest, const char *a, const char *b) {
    dest[0] = '\0';
    concat(dest, a);
    concat(dest, b);
}

// task 1b
char *concatenate(
    void (*func)(char*, const char*, const char*), 
    const char* a, 
    const char* b
) {
    char* res = malloc(strlen(a) + strlen(b));
    func(res, a, b);
    return res;
}

void testTask1() {
    char *str;
    str = concatenate(sprintf_concatenator, "Sprintf ", "Words!");
    puts(str);

    str = concatenate(sprintf_concatenator, "Concatenate ", "Words!");
    puts(str);

    str = concatenate(loop_concatenator, "Concatenating Loop ", "Words!");
    puts(str);

    free(str);
}

// ================================ TASK 2 =============================
// task 2a
int substring(char* dest, const char* src, size_t start, size_t n) {
    size_t i = 0, j = start;
    while(dest[i]) ++i;
    while(src[j] && n-- > 0) dest[i++] = src[j++];
    dest[i] = '\0';
    return n == 0 ? 0 : -1;
}

// task 2b
int containString(const char* src, const char* str, size_t from) {
    size_t s = strlen(src), o = strlen(str), i = 0;
    if(s - from >= o) {
        while(from < s && i < o) {
            if(src[from] != str[i]) break;
            i++;
            from++;
        }
    } 
    return i==o ? 1 : 0;
}

size_t split(char** dest, const char* src, const char* splitStr) {
    size_t idx = 0, i = 0, j = 0, len = strlen(src), s = strlen(splitStr);
    char* str = malloc(len);
    while(i < len) {
        int contain = containString(src, splitStr, i);
        if(contain) {
            i += s;
            dest[idx] = malloc(strlen(str));
            dest[idx][0] = '\0';
            str[j] = '\0';
            concat(dest[idx++], str);
            memset(str, 0, strlen(str));
            j = 0;
        }
        else {
            str[j++] = src[i++];
        }
    }
    str[j] = '\0';
    dest[idx] = malloc(strlen(str));    
    dest[idx][0] = '\0';
    concat(dest[idx++], str);

    free(str);

    return idx;
}

// task 2c
void replace(
    char* dest, const char* src, 
    const char* id, const char* replaceStr
) {
    dest[0] = '\0';
    size_t i = 0, j = 0, len = strlen(src), s = strlen(id);
    char* str = malloc(len);
    while(i < len) {
        int contain = containString(src, id, i);
        if(contain) {
            substring(str, src, i, s);
            i += s;
            str[j] = '\0';
            concat(dest, str);
            concat(dest, replaceStr);
            memset(str, 0, sizeof str);
            j = 0;
        }
        else {
            str[j++] = src[i++];
        }
    }
    str[j] = '\0';
    concat(dest, str);
    free(str);
}

// task 2d 
// write test outside main to keep clear to track
void runTask2d() {
    size_t size = 11;
    char* str = malloc(size);
    str[0] = '\0';

    // get substring "{}::is::fun"
    substring(str, "00000000{}::is::fun00000000", 8, size);
    puts(str);

    char* newStr = malloc(strlen(str));
    replace(newStr, str, "{}", "C++");
    puts(newStr);

    char** arr = malloc(strlen(newStr) * 4);
    size = split(arr, newStr, "::");
    for(size_t i=0; i<size; i++) puts(arr[i]);

    for(size_t i=0; i<size; i++) free(arr[i]);
    free(arr);

    free(newStr);
    free(str);
}

void testTask2() {
    char* str0 = malloc(4 * 12);
    str0[0] = '\0';
    int success = substring(str0, "Hello World!", 6, 7);
    printf("status: %d, string: %s\n", success, str0);
    free(str0);

    char** arr = malloc(strlen("Hello;;World;;It;;!!;;;;!!!;;time to;;;;Shine ! !") * 4);
    size_t size = split(arr, "Hello;;World;;It;;!!;;;;!!!;;time to;;;;Shine ! !", ";;");
    for(size_t i=0; i<size; i++) puts(arr[i]);

    for(size_t i=0; i<size; i++) free(arr[i]);
    free(arr);

    char* dest = malloc(strlen("He;;;;o Wor;;d!"));
    replace(dest, "He;;;;o Wor;;d!", ";;", "l");
    puts(dest);
    free(dest);

    // test all functions in task 2
    runTask2d();  
}

// ================================ Task 3 =============================
// task 3a
void manipulateWithOperator() {
    puts("Operator mode");

    Register_t enable_adc67 = ADCCON3 | EN_ADC_6_7;
    printf("enable adc 6 and 7 : %04x\n",enable_adc67);

    Register_t internalVrefh_AVss = ADCCON3 | REFH_AVSS;
    printf("set internal V_refh and AV_ss : %04x\n",internalVrefh_AVss);

    Register_t divider60 = ADCCON3 & NULL_24 | DIV_60;
    printf("set T_q divider to 60 : %04x\n",divider60);

    Register_t settings = (ADCCON3 | EN_ADC_6_7 | REFH_AVSS) & NULL_24 | DIV_60;
    printf("set all modes : %04x\n",settings);
}

// task 3b
void manipulateWithStruct() {
    puts("Struct mode");

    unsigned int mRegister = ADCCON3;
    struct RegisterManipulator *manipulator = & mRegister;

    manipulator->refh_avss = 13;
    printf("set internal V_refh and AV_ss : %04x\n", mRegister);

    manipulator->adc_67 = 12;
    printf("enable adc 6 and 7 : %04x\n", mRegister);

    manipulator->div_60 = 188;
    printf("set T_q divider to 60 : %04x\n", mRegister);
}

void testTask3() {
    #ifdef F
        manipulateWithOperator();
    #else
        manipulateWithStruct();
    #endif
}

// ================================ MAIN =============================
// main for testing
int main() {
    
    // run task 1
    puts("------------------ TASK 1 ------------------");
    testTask1();

    // run task 2
    puts("------------------ TASK 2 ------------------");
    testTask2();

    // run task 3a
    puts("------------------ TASK 3 ------------------");
    testTask3();

    return 0;
}