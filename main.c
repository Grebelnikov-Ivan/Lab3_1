#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char* convertStrToLongBv(char* str, size_t* cells);
char* convertBvToStr(unsigned char* vec, size_t sz);
unsigned char* addBitVectors(unsigned char* vec, unsigned char* vec2, size_t cells, size_t cells2);
unsigned char* multiplyBitVectors(unsigned char* vec, unsigned char* vec2, size_t cells, size_t cells2);
unsigned char* xorBitVectors(unsigned char* vec, unsigned char* vec2, size_t cells, size_t cells2);
int set_bit_1(unsigned char *vec, size_t len, size_t k);
int set_bit_0(unsigned char *vec, size_t len, size_t k);
unsigned char* inversBitVectorCopy(unsigned char* vec, size_t len);


int main() {
    char* str = NULL;
    char* str2 = NULL;
    unsigned char* vec = NULL;
    unsigned char* vec2 = NULL;
    unsigned char* result = NULL;

    str = "01101010";
    str2 = "01101010";

    size_t cells = 0;
    size_t cells2 = 0;
    size_t len = strlen(str);
    cells = ((len - 1) / 8) + 1;

    vec = convertStrToLongBv(str, &cells);  // if (vec == NULL){printf("error1");  return 1;} и т.д должно быть тут, но мешает тестам
    vec2 = convertStrToLongBv(str, &cells2);
    str = convertBvToStr(vec, cells);
    result = addBitVectors(vec, vec2, cells, cells2);
    result = multiplyBitVectors(vec, vec2, cells, cells2);
    result = xorBitVectors(vec, vec2, cells, cells2);
    result = inversBitVectorCopy(vec, len);

    int r = set_bit_1(vec, len, 0);
    int r2 = set_bit_0(vec, len, 0);

    if (r != 0){
        printf("error1");
        return 1;
    }

    if (r2 != 0){
        printf("error1");
        return 1;
    }

    if (vec == NULL){
        printf("error1");
        return 1;
    }

    if (vec2 == NULL){
        printf("error1");
        return 1;
    }

    if (str == NULL){
        printf("error2");
        return 1;
    }

    if (result == NULL){
        printf("error3");
        return 1;
    }

    printf("%s", str);
    free(vec);
    vec = NULL;
    free(vec2);
    vec = NULL;
    free(str);
    str = NULL;
    free(str2);
    str2 = NULL;
    free(result);
    result = NULL;
    return 0;
}

unsigned char* convertStrToLongBv(char* str, size_t* cells){
    if (!(str && cells))
        return NULL;
    size_t len = 0, ix = 0;
    unsigned char mask = (1 << 7);
    len = strlen(str);
    *cells = ((len - 1) / 8) + 1;
    unsigned char* vec = (unsigned char*)malloc(sizeof (unsigned char) * (*cells));
    if (!(vec))
        return NULL;
    for (size_t i = 0; i < *cells; i++)
        vec[i] = 0;
    for (size_t i = 0; i < *cells; i++){
        for (size_t j = 0; j < 8 && (ix < len); j++){
            vec[i] = vec[i] >> 1;
            if (str[ix] != '0')
                vec[i] |= mask;
            ix ++;
        }
    }
    return vec;
}


char* convertBvToStr(unsigned char* vec, size_t sz) {
    if (!vec)
        return NULL;

    size_t bit_count = sz * 8;
    char* str = (char*)malloc(bit_count + 1);
    if (!str)
        return NULL;

    size_t str_idx = 0;

    for (size_t byte_idx = 0; byte_idx < sz; byte_idx++) {
        unsigned char mask = 1;
        for (size_t bit = 0; bit < 8; bit++) {
            if ((vec[byte_idx] & mask) != 0)
                str[str_idx] = '1';
            else
                str[str_idx] = '0';
            mask = mask << 1;
            str_idx++;
        }
    }

    str[bit_count] = '\0';
    return str;
}

unsigned char* addBitVectors(unsigned char* vec, unsigned char* vec2, size_t cells, size_t cells2) {
    if (!vec || !vec2 || (cells != cells2))
        return NULL;

    unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char) * cells);
    if (!result)
        return NULL;

    for (size_t i = 0; i < cells; i++) {
        result[i] = vec[i] | vec2[i];  // побитовое ИЛИ
    }

    return result;
}

unsigned char* multiplyBitVectors(unsigned char* vec, unsigned char* vec2, size_t cells, size_t cells2) {
    if (!vec || !vec2 || (cells != cells2))
        return NULL;

    unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char) * cells);
    if (!result)
        return NULL;

    for (size_t i = 0; i < cells; i++) {
        result[i] = vec[i] & vec2[i];  // побитовое И
    }

    return result;
}

unsigned char* xorBitVectors(unsigned char* vec, unsigned char* vec2, size_t cells, size_t cells2) {
    if (!vec || !vec2 || (cells != cells2))
        return NULL;

    unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char) * cells);
    if (!result)
        return NULL;

    for (size_t i = 0; i < cells; i++) {
        result[i] = vec[i] ^ vec2[i];  // побитовое XOR
    }

    return result;
}

int set_bit_1(unsigned char *vec, size_t len, size_t k)
{
    if (!vec || k >= len)
        return 1;
    size_t byte = k / 8;
    size_t bit = k % 8;
    unsigned char mask = 1;
    size_t shift = 7 - bit; //01000000 при 2

    mask = mask << shift;
    vec[byte] = vec[byte] | mask;
    return 0;
}

int set_bit_0(unsigned char *vec, size_t len, size_t k)
{
    if (!vec || k >= len)
        return 1;
    size_t byte = k / 8;
    size_t bit = k % 8;
    unsigned char mask = 1;
    size_t shift = 7 - bit;

    mask = mask << shift;
    vec[byte] = mask & ~mask;
    return 0;
}

unsigned char* inversBitVectorCopy(unsigned char* vec, size_t len)
{
    if (!vec)
        return NULL;

    size_t bytes = ((len - 1) / 8) + 1;
    size_t last_bits = len % 8;

    unsigned char* result = (unsigned char*)malloc(bytes);
    if (!result)
        return NULL;

    for (size_t i = 0; i < bytes; i++) {
        result[i] = ~vec[i]; // всё инвертируем
    }

    // Очищаем хвост
    if (last_bits != 0) {
        size_t last_byte_idx = bytes - 1; // нужен только последний(там хвост)
        unsigned char mask = 0;
        for (size_t j = 0; j < last_bits; j++) {
            mask = mask | (1 << (7 - j));  // нужна маска где 11..и нужное кол-во нулей 100 010 001 111
        }
        result[last_byte_idx] &= mask;
    }
    else
        return NULL;

    return result;
}