//
//  EncDec.cpp
//  Server
//
//  Created by mac on 16/9/2.
//  Copyright © 2016年 mac. All rights reserved.
//

#include <string.h>
#include "EncDec.h"
#include "UtilPdu.h"
#include "Base64.h"

CAes::CAes(const string &strKey)
{
    AES_set_encrypt_key((const unsigned char*)strKey.c_str(), 256, &m_cEncKey);
    AES_set_decrypt_key((const unsigned char*)strKey.c_str(), 256, &m_cEncKey);
}

int CAes::Encrypt(const char *pInData, uint32_t nInLen, char **ppOutData, uint32_t &nOutLen)
{
    if( pInData == NULL || nInLen <= 0)
    {
        return -1;
    }
    uint32_t nRemain = nInLen % 16;
    uint32_t nBlocks = (nInLen + 15) /16;
    
    if( nRemain > 12 || nRemain == 0 )
    {
        nBlocks += 1;
    }
    
    uint32_t nEncryptLen = nBlocks * 16;
    unsigned char *pData = (unsigned char *)calloc(nEncryptLen, 1);
    memcpy(pData, pInData, nInLen);
    unsigned char *pEncData = (unsigned char *)malloc(nEncryptLen);
    
    CByteStream::WriteUint32((pData + nEncryptLen -4), nInLen );
    for (uint32_t i = 0; i < nBlocks; ++i) {
        AES_encrypt(pData+i*16, pEncData + i*16, &m_cEncKey);
    }
    
    free(pData);
    string strEnc((char*)pEncData, nEncryptLen);
    free(pEncData);
    string strDec = base64_encode(strEnc);
    nOutLen = (uint32_t)strDec.length();
    
    char *pTmp = (char*)malloc(nOutLen + 1);
    memcpy(pTmp, strDec.c_str(), nOutLen);
    pTmp[nOutLen] = 0;
    *ppOutData = pTmp;
    return 0;
}

