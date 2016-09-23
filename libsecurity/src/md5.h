
#ifndef _MD5FILE_H_
#define _MD5FILE_H_

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned int state[4];     
    unsigned int count[2];     
    unsigned char buffer[64];     
} MD5Context;

void MD5_Init(MD5Context * context);
void MD5_Update(MD5Context * context, unsigned char * buf, unsigned int len);
void MD5_Final(MD5Context * context, unsigned char digest[16]);
void MD5_Calculate (const char* pContent, unsigned int nLen,char* md5);

#ifdef  __cplusplus
}
#endif

#endif
