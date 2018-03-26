//编写函数： unsigned int reverse_bit(unsigned int value); 
//这个函数的返回值value的二进制位模式从左到右翻转后的值

#include<stdio.h>

int reverse_bit(unsigned int value)
{
    unsigned int new_value = 0;
    int i = 0;
    for (i = 31; i >= 0; i--)
    {
        //判断第一位是否为1，如果是，
        //将new_value的最后一位置1，以此类推，遍历完32位比特位
        if (((value >> i) & 1) == 1) 
        {
            new_value = new_value | (1 << (31 - i));
        }                             
    }                               
    return new_value;                   
} 

int main()
{
    unsigned int x = 0;
    printf("Please Enter a number :");
    scanf("%u", &x);
    printf("%u\n" , reverse_bit(x));
    return 0;
}