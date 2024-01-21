#include "array_operations.hh"

int greatest_v1(int* itemptr, int size)
{
    int max_value = *itemptr;
    int i = 0;

    while(i < size) 
    {
        int value = *(itemptr + i);
        if(value > max_value)
        {
            max_value = value;
        }
        
        i++;
    }

    return max_value;
}

int greatest_v2(int* itemptr, int* endptr)
{
    int max_value = *itemptr;

    while(itemptr != endptr)
    {
        int value = *itemptr;
        if(value > max_value)
        {
            max_value = value;
        }

        itemptr++;
    }

    return max_value;
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    int i = 0;
    while(itemptr != endptr)
    {
        *(targetptr + i) = *itemptr;
        
        i++;
        itemptr++;
    }
}

void reverse(int* leftptr, int* rightptr) {
    rightptr--;

    while (leftptr < rightptr) {
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;

        leftptr++;
        rightptr--;
    }
}
