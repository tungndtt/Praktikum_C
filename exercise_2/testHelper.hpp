#pragma once

#ifndef TESTHEPER_HPP
#define TESTHEPER_HPP

#include <iostream>
#include <iomanip>

struct AssertException {
    explicit AssertException(std::ostream& os){
        os<<std::endl;
    }
};

#define BEGIN_TEST(TestName)          \
struct TestName{                  \
    void test_##TestName(void) 
            
    
#define END_TEST(TestName)     \
    TestName(){                 \
       std::cout << std::left << std::setfill('-')                            \
       << std::setw(30) << #TestName " ";     system("COLOR 00");             \
       try{ test_##TestName();                                                \
           std::cout << std::setw(10)                                           \
              << std::left << "\x1b[38;5;40m   OK \x1b[0m"                  \
              << std::endl;                                                        \
       }catch(AssertException e){                                                  \
           std::cout << std::setw(10)                                              \
              << std::left << "\x1b[38;5;160m   FAILED \x1b[0m"             \
              << std::endl;                                                        \
    }}                                \
} instance_##TestName;
        
#define ASSERT_EQUAL(actual, expected)                              \
if(!(actual == expected)) throw AssertException(std::cout<<std::endl<<"\x1b[38;5;160m Expected:" <<expected << " but actual:" <<actual <<"\x1b[0m");


#define ASSERT_THROW(code, exception)                              \
try{                                                               \
    code;                                                    \
    throw AssertException(std::cout<<std::endl<<"\x1b[38;5;160m Expected throw: " <<#exception<<" but nothing \x1b[0m");\
}catch(exception& e){}


#endif