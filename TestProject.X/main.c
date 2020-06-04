/*
 * File:   main.c
 * Author: I15232
 *
 * Created on February 12, 2020, 11:52 PM
 */


#include "xc.h"
#include <stdlib.h>
#include <string.h>

void test1_func_to_show_mem_leak();
void test2_dereference_null_pointer(const char *input_str);
int test3_use_of_uninitalized_data();
void test4_memory_corruption();
void test5_buffer_overrun();
void test6_using_bitwise_as_conditional_operator();
void test7_modify_string_literal();
static int useByVal(const int int_val);
static void useByReference(int* const int_ptr);
static int getID();
static int getAge();

// driver code 
int main() 
{ 
    int a = 10;
    char ch;
    // Call the function 
    // to get the memory leak 
    test1_func_to_show_mem_leak(); 
    test2_dereference_null_pointer(NULL);
    test3_use_of_uninitalized_data();
    test4_memory_corruption();
    test5_buffer_overrun();
    test6_using_bitwise_as_conditional_operator();
    test7_modify_string_literal();
    return 0; 
} 
void test1_func_to_show_mem_leak() 
{ 
    int *ptr = (int *) malloc(10 * sizeof(int));
    ptr++;
    // return without deallocating ptr 
    return; 
}

void test2_dereference_null_pointer(const char *input_str) {
  size_t size = strlen(input_str) + 1;
  char *c_str = (char *)malloc(size);
  memcpy(c_str, input_str, size);
  free(c_str);
  //Accessing freed memory
  strcpy(c_str, "Hello");
}

int test3_use_of_uninitalized_data()
{
    int i,j,temp;
    useByVal(i);
    useByReference(&j);
    int result = temp+10;
    return result;
}

static int useByVal(const int int_val) 
{
    return int_val + 1;
}

static void useByReference(int* const int_ptr) 
{
    if (int_ptr != (void*)0) 
    {
        (*int_ptr)++;
    }
}

void test4_memory_corruption()
{
    char* ptr = (char *) malloc(20 * sizeof(char));
    char c,d;
    // 20 bytes allocated on the heap
    ptr[0] = 12;
    // ok
    ptr[20] = 12;
    // Error! We've written a value after the allocation end

    c = *(ptr - 1);
    // Error! We've read a value before the beginning of the allocation

    free(ptr);

    d = ptr[2];
    // Error! we're reading the memory after it was freed!

    ptr = (char*) 0x12345; // point to a random address
    *ptr = 2;

}

void test5_buffer_overrun()
{
    char *ptr  = (char*) malloc(10);
    ptr[10] = 'c';
}


void test6_using_bitwise_as_conditional_operator(void)
{
    if(getID() & getAge() == 0)
    {
       
    }
}

static int getID()
{
    return 1;
}

static int getAge()
{
    return 20;
}


void test7_modify_string_literal()
{
    char *str  = "coverity";
    str[0] = 'C';
}
