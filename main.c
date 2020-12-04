
#include <stdio.h>
#include <math.h>
#include <time.h>

unsigned short crcCheck(unsigned char * dataBuf,int len)
{
        int i = 0;
        unsigned short checkSumCon = 0;
        for (i=0; i<len; i++)
        {
        checkSumCon= (checkSumCon >> 8) | (checkSumCon << 8);
        checkSumCon ^= dataBuf[i];
        checkSumCon ^= (checkSumCon & 0xff) >> 4;
        checkSumCon ^= checkSumCon << 12;
        checkSumCon ^= (checkSumCon & 0xff) << 5;
        }
        return checkSumCon;
}


int main(int argc,char **argv)
{
    unsigned char data[5] = {0x31,0x32,0x33,0x34,0x35}; //需要校验的数据
    //使用calculateBytesCRC(data,sizeof(data)/sizeof(data[0]))计算一串数据的CRC
    start = clock();
    for(int i = 0;i < 10000;i++)
        printf("0x%x\r\n",crcCheck(data,5));
    end = clock();
    printf("time=%f",(double)(end-start)/CLK_TCK);
}