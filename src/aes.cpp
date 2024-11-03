#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <aes.h>
const uint8_t gf02[256] = {
	0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 
	0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 
	0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 
	0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 
	0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 
	0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 
	0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde, 
	0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe, 
	0x1b, 0x19, 0x1f, 0x1d, 0x13, 0x11, 0x17, 0x15, 0x0b, 0x09, 0x0f, 0x0d, 0x03, 0x01, 0x07, 0x05, 
	0x3b, 0x39, 0x3f, 0x3d, 0x33, 0x31, 0x37, 0x35, 0x2b, 0x29, 0x2f, 0x2d, 0x23, 0x21, 0x27, 0x25, 
	0x5b, 0x59, 0x5f, 0x5d, 0x53, 0x51, 0x57, 0x55, 0x4b, 0x49, 0x4f, 0x4d, 0x43, 0x41, 0x47, 0x45, 
	0x7b, 0x79, 0x7f, 0x7d, 0x73, 0x71, 0x77, 0x75, 0x6b, 0x69, 0x6f, 0x6d, 0x63, 0x61, 0x67, 0x65, 
	0x9b, 0x99, 0x9f, 0x9d, 0x93, 0x91, 0x97, 0x95, 0x8b, 0x89, 0x8f, 0x8d, 0x83, 0x81, 0x87, 0x85, 
	0xbb, 0xb9, 0xbf, 0xbd, 0xb3, 0xb1, 0xb7, 0xb5, 0xab, 0xa9, 0xaf, 0xad, 0xa3, 0xa1, 0xa7, 0xa5, 
	0xdb, 0xd9, 0xdf, 0xdd, 0xd3, 0xd1, 0xd7, 0xd5, 0xcb, 0xc9, 0xcf, 0xcd, 0xc3, 0xc1, 0xc7, 0xc5, 
	0xfb, 0xf9, 0xff, 0xfd, 0xf3, 0xf1, 0xf7, 0xf5, 0xeb, 0xe9, 0xef, 0xed, 0xe3, 0xe1, 0xe7, 0xe5, 
};

const uint8_t gf03[256] = {
	0x00, 0x03, 0x06, 0x05, 0x0c, 0x0f, 0x0a, 0x09, 0x18, 0x1b, 0x1e, 0x1d, 0x14, 0x17, 0x12, 0x11, 
	0x30, 0x33, 0x36, 0x35, 0x3c, 0x3f, 0x3a, 0x39, 0x28, 0x2b, 0x2e, 0x2d, 0x24, 0x27, 0x22, 0x21, 
	0x60, 0x63, 0x66, 0x65, 0x6c, 0x6f, 0x6a, 0x69, 0x78, 0x7b, 0x7e, 0x7d, 0x74, 0x77, 0x72, 0x71, 
	0x50, 0x53, 0x56, 0x55, 0x5c, 0x5f, 0x5a, 0x59, 0x48, 0x4b, 0x4e, 0x4d, 0x44, 0x47, 0x42, 0x41, 
	0xc0, 0xc3, 0xc6, 0xc5, 0xcc, 0xcf, 0xca, 0xc9, 0xd8, 0xdb, 0xde, 0xdd, 0xd4, 0xd7, 0xd2, 0xd1, 
	0xf0, 0xf3, 0xf6, 0xf5, 0xfc, 0xff, 0xfa, 0xf9, 0xe8, 0xeb, 0xee, 0xed, 0xe4, 0xe7, 0xe2, 0xe1, 
	0xa0, 0xa3, 0xa6, 0xa5, 0xac, 0xaf, 0xaa, 0xa9, 0xb8, 0xbb, 0xbe, 0xbd, 0xb4, 0xb7, 0xb2, 0xb1, 
	0x90, 0x93, 0x96, 0x95, 0x9c, 0x9f, 0x9a, 0x99, 0x88, 0x8b, 0x8e, 0x8d, 0x84, 0x87, 0x82, 0x81, 
	0x9b, 0x98, 0x9d, 0x9e, 0x97, 0x94, 0x91, 0x92, 0x83, 0x80, 0x85, 0x86, 0x8f, 0x8c, 0x89, 0x8a, 
	0xab, 0xa8, 0xad, 0xae, 0xa7, 0xa4, 0xa1, 0xa2, 0xb3, 0xb0, 0xb5, 0xb6, 0xbf, 0xbc, 0xb9, 0xba, 
	0xfb, 0xf8, 0xfd, 0xfe, 0xf7, 0xf4, 0xf1, 0xf2, 0xe3, 0xe0, 0xe5, 0xe6, 0xef, 0xec, 0xe9, 0xea, 
	0xcb, 0xc8, 0xcd, 0xce, 0xc7, 0xc4, 0xc1, 0xc2, 0xd3, 0xd0, 0xd5, 0xd6, 0xdf, 0xdc, 0xd9, 0xda, 
	0x5b, 0x58, 0x5d, 0x5e, 0x57, 0x54, 0x51, 0x52, 0x43, 0x40, 0x45, 0x46, 0x4f, 0x4c, 0x49, 0x4a, 
	0x6b, 0x68, 0x6d, 0x6e, 0x67, 0x64, 0x61, 0x62, 0x73, 0x70, 0x75, 0x76, 0x7f, 0x7c, 0x79, 0x7a, 
	0x3b, 0x38, 0x3d, 0x3e, 0x37, 0x34, 0x31, 0x32, 0x23, 0x20, 0x25, 0x26, 0x2f, 0x2c, 0x29, 0x2a, 
	0x0b, 0x08, 0x0d, 0x0e, 0x07, 0x04, 0x01, 0x02, 0x13, 0x10, 0x15, 0x16, 0x1f, 0x1c, 0x19, 0x1a, 
};

const int MAXLEN=2000000;
uint8_t key[16]={1, 35, 69, 103, 137, 171, 205, 239, 254, 220, 186, 152, 118, 84, 50, 16};
uint8_t ctr[16]={240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};

int len;

// S盒
static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

const uint32_t Rcon[10] = { 0x01000000, 0x02000000,
    0x04000000, 0x08000000,
    0x10000000, 0x20000000,
    0x40000000, 0x80000000,
    0x1b000000, 0x36000000 };

// 列混合矩阵
const int colM[4][4] = { 2, 3, 1, 1,
    1, 2, 3, 1,
    1, 1, 2, 3,
    3, 1, 1, 2 };
// inline uint32_t getNumFromSBox(int index) {
//     return S[(index>>4)&15][index&15];
// }

uint8_t convertStrToHex(char str[]){
    int one,two;
    if('0'<=str[0] && str[0]<='9')one=str[0]-'0';
    else one=str[0]-'a'+10;
    if('0'<=str[1] && str[1]<='9')two=str[1]-'0';
    else two=str[1]-'a'+10;
    return (one<<4)|two;
}

void splitIntToArray(uint32_t num, uint8_t array[4]) {
    // 32位int -> 长度为4的int数组
    for(int i=0;i<4;++i){
        array[3-i]=num&0x000000ff;
        num>>=8;
    }
}

 void leftLoop4int(uint8_t array[4], int step) {
    //数组循环左移step位
    uint8_t temp[4];
    for(int i = 0; i < 4; i++)temp[i] = array[(i+step)%4];
    for(int i=0;i<4;++i)array[i]=temp[i];
}

uint32_t T(uint32_t num, int round) {
    // 密钥扩展的T函数
    uint8_t numArray[4];
    
    splitIntToArray(num, numArray);
    leftLoop4int(numArray, 1);//字循环

    // S盒
    for(int i = 0; i < 4; i++)
        numArray[i] = sbox[numArray[i]];

    return (((uint32_t)numArray[0]<<24)|((uint32_t)numArray[1]<<16)|((uint32_t)numArray[2]<<8)|((uint32_t)numArray[3])) ^ Rcon[round];
}
uint32_t w[44];
 void extendKey(const uint8_t key[]) {
    // 扩展密钥
    for(int i = 0; i < 4; i++)
        w[i] = ((uint32_t)key[i*4]<<24) | ((uint32_t)key[i*4+1]<<16) | ((uint32_t)key[i*4+2]<<8) | ((uint32_t)key[i*4+3]);

    int num=0;
    for(int i = 4; i < 44; i++) {
        if( i % 4 == 0) {
            w[i] = w[i - 4] ^ T(w[i - 1], num);
            num++;
        }
        else {
            w[i] = w[i - 4] ^ w[i - 1];
        }
    }
}

static void AddRoundKey(uint8_t round, uint8_t* state) {
    for (int i = 0; i < 16; ++i) 
        state[i]^=((w[i/4+round*4]>>(3-i%4)*8)&0xff);
}
void subBytes(uint8_t* state){
    // 字节代换
    for(int i = 0; i < 16; i++)state[i]=sbox[state[i]];
}

 void shiftRows(uint8_t* state) {
    // 行移位
    uint8_t tmp[16];
    memcpy(tmp,state,16);
    for(int i=1;i<4;++i)
        for(int j=0;j<4;++j)state[j*4+i]=tmp[((j+i)%4)*4+i];
}


 void mixColumns(uint8_t *state) {
    // 列混合，利用建表加速
    __uint128_t f = 0;
	uint8_t* tmp = (uint8_t*)(&f);
    tmp[0]  = gf02[state[0]] ^ gf03[state[1]] ^ state[2] ^ state[3];
    tmp[1]  = state[0] ^ gf02[state[1]] ^ gf03[state[2]] ^ state[3];
    tmp[2]  = state[0] ^ state[1] ^ gf02[state[2]] ^ gf03[state[3]];
    tmp[3]  = gf03[state[0]] ^ state[1] ^ state[2] ^ gf02[state[3]];
    tmp[4]  = gf02[state[4]] ^ gf03[state[5]] ^ state[6] ^ state[7];
    tmp[5]  = state[4] ^ gf02[state[5]] ^ gf03[state[6]] ^ state[7];
    tmp[6]  = state[4] ^ state[5] ^ gf02[state[6]] ^ gf03[state[7]];
    tmp[7]  = gf03[state[4]] ^ state[5] ^ state[6] ^ gf02[state[7]];
    tmp[8]  = gf02[state[8]] ^ gf03[state[9]] ^ state[10] ^ state[11];
    tmp[9]  = state[8] ^ gf02[state[9]] ^ gf03[state[10]] ^ state[11];
    tmp[10] = state[8] ^ state[9] ^ gf02[state[10]] ^ gf03[state[11]];
    tmp[11] = gf03[state[8]] ^ state[9] ^ state[10] ^ gf02[state[11]];
    tmp[12] = gf02[state[12]] ^ gf03[state[13]] ^ state[14] ^ state[15];
    tmp[13] = state[12] ^ gf02[state[13]] ^ gf03[state[14]] ^ state[15];
    tmp[14] = state[12] ^ state[13] ^ gf02[state[14]] ^ gf03[state[15]];
    tmp[15] = gf03[state[12]] ^ state[13] ^ state[14] ^ gf02[state[15]];

    memcpy(state,tmp,16);
}




void Xor(uint8_t *p,const uint8_t *a){
    //明文和加密后的计数器异或
    for(int i=0;i<16;++i){
        p[i]^=a[i];
    }
}

void aes(const uint8_t mes[], int len, const uint8_t key[], uint8_t cipher[]){
    extendKey(key);//扩展密钥
    uint8_t* cnt=new uint8_t[16];

    for(int k = 0; k < len; k += 16) {	
        memcpy(cnt,mes+k,16);
        
        AddRoundKey(0,cnt);//一开始的轮密钥加
        
        for(int i = 1; i < 10; i++){//前9轮
            subBytes(cnt);//字节代换

            
            shiftRows(cnt);//行移位
            
            mixColumns(cnt);//列混合
            AddRoundKey(i,cnt);
            
        }

        //第10轮
        subBytes(cnt);//字节代换
        shiftRows(cnt);//行移位
        AddRoundKey(10,cnt);
        memcpy(cipher+k,cnt,16);
    }
    delete[] cnt;
}