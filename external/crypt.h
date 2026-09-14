/*
 * Originally derived from: https://github.com/the4chancup/pesXdecrypter
 * Modified by jasonjk192 (WinterCrestal) for this project.
 * The original code was released under the Unlicense given below
 */

/*
    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <http://unlicense.org>
 */

#ifndef _CRYPT_H
#define _CRYPT_H

#include <windows.h>
#include <Wincrypt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_LIBRARY

#ifdef _WIN32
#define CRYPTER_EXPORT __declspec(dllexport)
#else
#define CRYPTER_EXPORT __attribute__ ((visibility ("protected")))
#endif

#else

#define CRYPTER_EXPORT

#endif /* BUILDING_LIBRARY */

struct FileHeaderNew
{
    uint8_t mysteryData[64];
    uint32_t dataSize;
    uint32_t logoSize;
    uint32_t descSize;
    uint32_t serialLength;
    uint8_t hash[64];
    uint8_t fileTypeString[32];
    uint8_t gameVersionString[32];
};

struct FileHeaderOld
{
    uint8_t mysteryData[64];
    uint32_t dataSize;
    uint32_t logoSize;
    uint32_t descSize;
    uint32_t serialLength;
    uint8_t hash[64];
    uint8_t fileTypeString[32];
};

struct FileDescriptorNew
{
    uint8_t *encryptionHeader;
    struct FileHeaderNew *fileHeader;

    uint8_t *description;
    uint8_t *logo;
    uint8_t *data;
    uint8_t *serial;
};

struct FileDescriptorOld
{
    uint8_t *encryptionHeader;
    struct FileHeaderOld *fileHeader;

    uint8_t *description;
    uint8_t *logo;
    uint8_t *data;
    uint8_t *serial;
};

struct FileDescriptor15
{
    uint32_t dataSize;
    unsigned char startByte;
    uint32_t chunk0Size; //384
    uint32_t chunk1Size;
    uint32_t chunk2Size;

    uint8_t* chunk0; //Fixed length "Edit file" string
    uint8_t* chunk1lenBytes; //4 bytes that encode length of chunk 1
    uint8_t* chunk1; //PNG
    uint8_t* chunk2lenBytes; //4 bytes that encode length of chunk 2
    uint8_t* data; //Main edit data (chunk 2)
};

typedef enum
{
    UNKNOWN = -1, // Couldn't identify failure or a general failure
    OK = 0, // File read successfully.
    READ_FILE_STAT_FAILED, // stat() failed
    INVALID_ARGUMENT, // One or more arguments are invalid or null
    OPEN_FAILED, // Failed to open the file (with fopen)
    ALLOC_FAILED, // Failed to allocate memory for the file content (with malloc)
} OpResult;

#pragma region Utility functions

int32_t bitsToInt32(const unsigned char* bits, bool little_endian);
void getChunkSizes(const uint8_t*, int*, int);
void generateHeader(char* input, char* output, int* chunkSize, int outSize, const char startByte);
uint32_t md5(uint8_t* input, int inputLen, uint8_t* computedHash);

#pragma endregion

#pragma region Encrypt Decrypt functions

struct FileDescriptorNew CRYPTER_EXPORT *createFileDescriptorNew();
void CRYPTER_EXPORT destroyFileDescriptorNew(struct FileDescriptorNew *desc);
struct FileDescriptorOld CRYPTER_EXPORT *createFileDescriptorOld();
void CRYPTER_EXPORT destroyFileDescriptorOld(struct FileDescriptorOld *desc);
struct FileDescriptor15 CRYPTER_EXPORT *createFileDescriptor15();
void CRYPTER_EXPORT destroyFileDescriptor15(struct FileDescriptor15 *desc);

void CRYPTER_EXPORT decryptWithKeyNew(struct FileDescriptorNew *descriptor, const uint8_t *input, const char *masterKey);
uint8_t CRYPTER_EXPORT *encryptWithKeyNew(const struct FileDescriptorNew *descriptor, int *size, const char *masterKey);
void CRYPTER_EXPORT decryptWithKeyOld(struct FileDescriptorOld *descriptor, const uint8_t *input, const char *masterKey);
uint8_t CRYPTER_EXPORT *encryptWithKeyOld(const struct FileDescriptorOld *descriptor, int *size, const char *masterKey);
void CRYPTER_EXPORT decryptFile15(struct FileDescriptor15 *descriptor, const uint8_t *input);
uint8_t CRYPTER_EXPORT *encryptFile15(const struct FileDescriptor15 *descriptor, int *outputLen);

#pragma endregion

#pragma region Read Write functions

/// <summary>
/// Reads a file completely into a dynamically allocated buffer.
/// </summary>
/// <param name="path">Path to the file (<b>must be in UTF-8 format</b>).</param>
/// <param name="outData">Pointer to a <c>uint8_t*</c> that will receive the allocated file buffer. 
/// <para><i>Note: The caller is responsible for freeing this memory.</i></para></param>
/// <param name="sizePtr">Optional. Pointer to a <c>uint32_t</c> that receives the size of the file in bytes. Pass <c>NULL</c> if not needed.</param>
/// <returns>
/// An <c>OpResult</c> indicating the outcome
/// </returns>
OpResult CRYPTER_EXPORT readFile(const char *path, uint8_t** outData, uint32_t *sizePtr);

/// <summary>
/// Writes a binary buffer to a specified file path. Overwrites the file if it already exists.
/// </summary>
/// <param name="path">Path to the file to create or overwrite (<b>must be in UTF-8 format</b>).</param>
/// <param name="data">Pointer to the constant <c>uint8_t</c> buffer containing the data to be written.</param>
/// <param name="size">The total number of bytes to write from the buffer.</param>
/// <returns>
/// An <c>OpResult</c> indicating the outcome
/// </returns>
OpResult CRYPTER_EXPORT writeFile(const char* path, const uint8_t* data, int size);

#pragma endregion

#ifdef __cplusplus
}
#endif

#endif /* _CRYPT_H */
