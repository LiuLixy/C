//一个数组中只有两个数字是出现一次，其他所有数字都出现了两次。 
//找出这两个数字，编程实现。


//看到题目，立马让我想起了之前碰到了一个类似的题，
//一个数组中只有一个数字出现了一次，
//其他的数字都是成对出现的，当时想到的办法是
//将该数组的数字整体异或，异或之后得到的结果肯定就是
//那个单独出现的数字了。那么这个题也能用异或做吗？ 
//答案是可以！我们可以先将该数组的元素整体异或，
//得到的结果肯定是这两个不同的数字异或得到的结果；
//而且异或的结果肯定不为0；并且异或的结果比特位为0的位，
//则表示这两个数据的二进制序列在该比特位相同，都为0或者都为1；
//异或的结果为1的位，表示则表示这两个数据的二进制序列在该比特位不同，
//一个为0，一个为1。然后再将异或的结果分成两类：分类之后不同的数据被
//分到不同的两个组中，相同的数据绝对被分到了相同的组中。

//代码实现：
#include<stdio.h>
#include<windows.h>
#include<assert.h>
void find_two_data(int *arr, int sz)
{
    assert(arr);
    assert(sz > 2);

    int data = arr[0];
    int i = 1;
    for (; i < sz; i++)
    {
        data ^= arr[i];
    }
    int flag = 1;
    for (i = 0;i < 32; i++)
    {
        if (data & (flag<<i))
        {
            flag <<= i;
        }
    }
    int data1 = 0;
    int data2 = 0;
    for (i = 0; i < sz; i++)
    {
        if (arr[i] & flag)
        {
            data1 ^= arr[i];
        }
        else
        {
            data2 ^= arr[i];
        }
    }
    printf("%d %d\n", data1, data2);
}

int main()
{
    int arr[] = { 1,1,2,2,3,3,4,5,5,6,6,7,7,8,9,9 };
    int sz = sizeof(arr) / sizeof(arr[0]);
    find_two_data(arr, sz);
    system("pause");
    return 0;
}


//当然要是觉得前面的方法太难理解，我们还有一种方法，这种方法是将整个数组遍历比较，时间复杂度比较大。 
//代码如下： 
#include<stdio.h>
#include<windows.h>

int main()
{
    int arr[] = { 1,1,2,2,3,3,4,5,5,6,6,7,7,8,9,9 };
    int sz = sizeof(arr) / sizeof(arr[0]);
    int i = 0;
    for (; i < sz; i++)
    {
        int j = 0;
        int flag = 0;
        for (; j < sz; j++)
        {
            if (arr[i] == arr[j])
                flag++;
        }
        //因为if语句判断的时候单独出现的数字会与它自身进行一次判断，
        //所以当flag==1的时候，实际上它是单独出现的数字。
        if (flag == 1)
            printf("%d ", arr[i]);
    }
    system("pause");
    return 0;
}