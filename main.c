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
int shift_left_bit_vector(unsigned char *vec, size_t len, size_t k);
int shift_right_bit_vector(unsigned char *vec, size_t len, size_t k);

int main() {
    char* str1 = "10011000";
    char* str2 = "00011010";
    //char* str1 = "00000000";


    size_t cells1 = 0, cells2 = 0;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    cells1 = ((len1 - 1) / 8) + 1;
    cells2 = ((len2 - 1) / 8) + 1;

    // Конвертация строк в битовые векторы
    unsigned char* vec1 = convertStrToLongBv(str1, &cells1);
    if (vec1 == NULL) {
        printf("error1");
        return 1;
    }

    unsigned char* vec2 = convertStrToLongBv(str2, &cells2);
    if (vec2 == NULL) {
        printf("error1");
        free(vec1);
        return 1;
    }

    // исходные векторы
    char* vec1_str = convertBvToStr(vec1, cells1);
    if (vec1_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        return 1;
    }

    char* vec2_str = convertBvToStr(vec2, cells2);
    if (vec2_str == NULL) {
        printf("error2");
        free(vec1_str);
        free(vec1);
        free(vec2);
        return 1;
    }

    printf("v1: %s\n", vec1_str);
    printf("v2: %s\n", vec2_str);
    free(vec1_str);
    free(vec2_str);
    printf("\n");

    // +
    unsigned char* add_res = addBitVectors(vec1, vec2, cells1, cells2);
    if (add_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* add_str = convertBvToStr(add_res, cells1);
    if (add_str == NULL) {
        printf("error2");
        free(add_res);
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("+    %s\n", add_str);
    free(add_str);
    free(add_res);

    // *
    unsigned char* mul_res = multiplyBitVectors(vec1, vec2, cells1, cells2);
    if (mul_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* mul_str = convertBvToStr(mul_res, cells1);
    if (mul_str == NULL) {
        printf("error2");
        free(mul_res);
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("*    %s\n", mul_str);
    free(mul_str);
    free(mul_res);

    // xor
    unsigned char* xor_res = xorBitVectors(vec1, vec2, cells1, cells2);
    if (xor_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* xor_str = convertBvToStr(xor_res, cells1);
    if (xor_str == NULL) {
        printf("error2");
        free(xor_res);
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("xor  %s\n", xor_str);
    free(xor_str);
    free(xor_res);

    // ~
    unsigned char* inv_res = inversBitVectorCopy(vec1, len1);
    printf("xor * inv %s\n", convertBvToStr(multiplyBitVectors(xorBitVectors(vec1, vec2, cells1, cells2), inv_res, cells1, cells2), 1));
    if (inv_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* inv_str = convertBvToStr(inv_res, cells1);
    if (inv_str == NULL) {
        printf("error2");
        free(inv_res);
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("~    %s\n", inv_str);
    free(inv_str);
    free(inv_res);

    // установка бита 3 в 1
    int r1 = set_bit_1(vec1, len1, 6);
    if (r1 != 0) {
        printf("error1");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* set1 = convertBvToStr(vec1, cells1);
    if (set1 == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("set1 %s\n", set1);
    free(set1);

    // сброс бита 3 в 0
    int r2 = set_bit_0(vec1, len1, 7);
    if (r2 != 0) {
        printf("error1");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* set0 = convertBvToStr(vec1, cells1);
    if (set0 == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("set0 %s\n", set0);
    free(set0);

    free(vec1);
    free(vec2);

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
    vec[byte] = vec[byte] & ~mask;
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

    return result;
}

int shift_left_bit_vector(unsigned char *vec, size_t len, size_t k)
{

    return 0;
}

int shift_right_bit_vector(unsigned char *vec, size_t len, size_t k)
{

    return 0;
}