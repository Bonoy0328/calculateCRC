const static unsigned char polyValue = 0x07; //CRC-8/ITU固定参数
const static unsigned char initValue = 0x00; //CRC-8/ITU固定参数，crc校验值的初始值
const static unsigned char checkValue = 0x55; //CRC-8固定参数,最后结果与此值进行异或后再输出
/********计算单个字节的CRC校验**********/
/********输入参数为8bits的数据*********/
unsigned char calculateSingleByteCRC(unsigned char data)
{
    unsigned char singleCrc;
    singleCrc = data;
    for(int i = 0; i < 8 ;i++)
    {
        if(singleCrc&0x80) //判断最高位是否为1
        {
            //最高位位1的话，将crc左移一位，并与poly做异或运算
            singleCrc = (singleCrc << 1)^polyValue;
        }
        else //如果最高位不为1的话
        {
            //crc直接左移一位
            singleCrc = singleCrc << 1;
        }
    }
    return singleCrc;
}

/*****计算多个字节的CRC值*********/
/*****多个CRC计算即用前一个的CRC值与当前值异或，利用其结果再进行CRC计算****/
/*****类似于对单个CRC计算的递归调用****/
/*******第一个参数为数组头指针，第二个为数组长度n***********/
unsigned char calculateBytesCRC(unsigned char *data,unsigned int n)
{
    unsigned char crc1 = data[0];
    unsigned char crc2;
    for(int i = 0;i < n; i++)
    {
        if(i == 0) //初始化，第一个数需要先和Initvalue做异或后再进行单个RCR计算
        {
            crc1 = calculateSingleByteCRC(data[i]^initValue);
            crc2 = crc1;           
        }
        else //其余值需要和前一个值进行异或运算后，利用异或运算后的值再进行CRC计算
        {
            crc1 = calculateSingleByteCRC(data[i]^crc2);
            crc2 = crc1;
        }

    }
    return (crc2^checkValue);
}



int main(int argc,char **argv)
{
    unsigned char data[6] = {0x31,0x32,0x33,0x34,0x35,0x36}; //需要校验的数据
    //使用calculateBytesCRC(data,sizeof(data)/sizeof(data[0]))计算一串数据的CRC
    printf("0x%x",calculateBytesCRC(data,sizeof(data)/sizeof(data[0])));
}


