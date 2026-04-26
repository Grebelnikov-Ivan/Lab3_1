// define 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char* convertStrToLongBv(char* str, size_t* bits);
char* convertBvToStr(unsigned char* vec, size_t bits);
unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB);
unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB);
unsigned char* sumMod2(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB);
void set1(unsigned char *vec, size_t bits, size_t bit);
void set0(unsigned char *vec, size_t bits, size_t bit);
void inversion(unsigned char *vec, size_t bits);
void shiftLeft(unsigned char *vec, size_t bits, size_t k);
void shiftRight(unsigned char *vec, size_t bits, size_t k);
void printVectAsInMemory(unsigned char* vec, size_t bits);

int main() {
    char* str1 = NULL;
    char* str2 = NULL;
    str1 = "10011000";
    str2 = "00011010";

    size_t bits1 = strlen(str1);
    size_t bits2 = strlen(str2);

    // Конвертация строк в битовые векторы
    unsigned char* vec1 = convertStrToLongBv(str1, &bits1); // & адрес на bits1
    if (vec1 == NULL) {
        printf("error11");
        return 1;
    }

    unsigned char* vec2 = convertStrToLongBv(str2, &bits2);
    if (vec2 == NULL) {
        printf("error12");
        free(vec1);
        return 1;
    }

    // исходные векторы
    char* vec1_str = convertBvToStr(vec1, bits1);
    if (vec1_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        return 1;
    }

    char* vec2_str = convertBvToStr(vec2, bits2);
    if (vec2_str == NULL) {
        printf("error2");
        free(vec1_str);
        free(vec1);
        free(vec2);
        return 1;
    }

    printf("v1 %s\n", vec1_str);
    printf("v2 %s\n", vec2_str);
    free(vec1_str);
    free(vec2_str);
    printf("\n");

    // +
    unsigned char* add_res = logSum(vec1, bits1, vec2, bits2);
    if (add_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* add_str = convertBvToStr(add_res, bits1);
    if (add_str == NULL) {
        printf("error2");
        free(add_res);
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("+  %s\n", add_str);
    free(add_str);
    free(add_res);

    // *
    unsigned char* mul_res = logMul(vec1, bits1, vec2, bits2);
    if (mul_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* mul_str = convertBvToStr(mul_res, bits1);
    if (mul_str == NULL) {
        printf("error2");
        free(mul_res);
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("&  %s\n", mul_str);
    free(mul_str);
    free(mul_res);

    // xor
    unsigned char* xor_res = sumMod2(vec1, bits1, vec2, bits2);
    if (xor_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        return 1;
    }
    char* xor_str = convertBvToStr(xor_res, bits1);
    if (xor_str == NULL) {
        printf("error2");
        free(xor_res);
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("xor %s\n", xor_str);
    free(xor_str);
    free(xor_res);

    // инверсия
    inversion(vec1, bits1);
    char* inv_str = convertBvToStr(vec1, bits1);
    if (inv_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("~ v1 %s\n", inv_str);
    free(inv_str);

    // инвертируем обратно для дальнейших тестов
    inversion(vec1, bits1);

    // установка бита 7 в 0
    set1(vec1, bits1, 7);
    char* set1_str = convertBvToStr(vec1, bits1);
    if (set1_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("set bit 1 7 in 0 %s\n", set1_str);
    free(set1_str);

    // сброс бита 0 в 0
    set0(vec1, bits1, 0);
    char* set0_str = convertBvToStr(vec1, bits1);
    if (set0_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        return 1;
    }
    printf("set bit 0 0 in 0 %s\n", set0_str);
    free(set0_str);

    printf("v1 in memory ");
    printVectAsInMemory(vec1, bits1);
    printf("\n");

    free(vec1);
    free(vec2);

    return 0;
}

unsigned char* convertStrToLongBv(char* str, size_t* bits){
    if (!(str && bits))
        return NULL;
    size_t len = 0, ix = 0;
    unsigned char mask = 1;
    len = strlen(str);
    *bits = len;  // сохраняем длину в битах
    size_t bytes = ((len - 1) / 8) + 1;
    unsigned char* vec = (unsigned char*)malloc(sizeof(unsigned char) * bytes);
    if (!(vec))
        return NULL;
    for (size_t i = 0; i < bytes; i++)
        vec[i] = 0;
    for (size_t i = 0; i < bytes; i++){
        for (size_t j = 0; j < 8 && (ix < len); j++){
            if (str[ix] != '0')
                vec[i] |= mask;
            mask = mask << 1;
            ix++;
        }
        mask = 1;
    }
    return vec;
}

char* convertBvToStr(unsigned char* vec, size_t bits) {
    if (!vec)
        return NULL;

    size_t bytes = ((bits - 1) / 8) + 1;
    char* str = (char*)malloc(bits + 1);
    if (!str)
        return NULL;

    size_t str_idx = 0;

    for (size_t byte_idx = 0; byte_idx < bytes; byte_idx++) {
        unsigned char mask = 1;
        for (size_t bit = 0; bit < 8 && str_idx < bits; bit++) {
            if ((vec[byte_idx] & mask) != 0)
                str[str_idx] = '1';
            else
                str[str_idx] = '0';
            mask = mask << 1;
            str_idx++;
        }
    }

    str[bits] = '\0';
    return str;
}

// +
unsigned char* logSum(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if (!vecA || !vecB || bitsA != bitsB)
        return NULL;

    size_t bytes = ((bitsA - 1) / 8) + 1;
    unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char) * bytes);
    if (!result)
        return NULL;

    for (size_t i = 0; i < bytes; i++) {
        result[i] = vecA[i] | vecB[i];
    }

    return result;
}

// &
unsigned char* logMul(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if (!vecA || !vecB || bitsA != bitsB)
        return NULL;

    size_t bytes = ((bitsA - 1) / 8) + 1;
    unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char) * bytes);
    if (!result)
        return NULL;

    for (size_t i = 0; i < bytes; i++) {
        result[i] = vecA[i] & vecB[i];
    }

    return result;
}

// xor
unsigned char* sumMod2(unsigned char* vecA, size_t bitsA, unsigned char* vecB, size_t bitsB) {
    if (!vecA || !vecB || bitsA != bitsB)
        return NULL;

    size_t bytes = ((bitsA - 1) / 8) + 1;
    unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char) * bytes);
    if (!result)
        return NULL;

    for (size_t i = 0; i < bytes; i++) {
        result[i] = vecA[i] ^ vecB[i];
    }

    return result;
}

void set1(unsigned char *vec, size_t bits, size_t bit) {
    if (!vec || bit >= bits)
        return;
    size_t byte = bit / 8;
    size_t b = bit % 8;
    vec[byte] |= (1 << b);
}

void set0(unsigned char *vec, size_t bits, size_t bit) {
    if (!vec || bit >= bits)
        return;
    size_t byte = bit / 8;
    size_t b = bit % 8;
    vec[byte] &= ~(1 << b);
}

void inversion(unsigned char *vec, size_t bits) {
    if (!vec)
        return;

    size_t bytes = ((bits - 1) / 8) + 1;
    size_t last_bits = bits % 8;

    for (size_t i = 0; i < bytes; i++) {
        vec[i] = ~vec[i];
    }

    // очищаем незначащие биты (хвост)
    if (last_bits != 0) {
        size_t last_byte_idx = bytes - 1;
        unsigned char mask = 0;
        for (size_t j = 0; j < last_bits; j++) {
            mask |= (1 << j);  // маска младших битов
        }
        vec[last_byte_idx] &= mask;
    }
}

void shiftRight(unsigned char *vec, size_t bits, size_t k) {
    if (!vec || !bits || k == 0)
        return;

    size_t bytes = ((bits - 1) / 8) + 1;
    size_t byte_k = k / 8;
    k = k % 8;

    // сдвиг справа налево начинаем с последнего байта
    for (size_t i = bytes - 1; i > 0; i--) {
        size_t addr = i - byte_k;  // откуда берём данные

        if (addr < bytes) {
            // основной сдвиг вправо
            vec[i] = vec[addr] >> k;

            // перенос битов из соседнего байта
            if (k && addr > 0) {
                unsigned char mask = vec[addr - 1];
                mask = mask << (8 - k);
                vec[i] |= mask;
            }
        } else {
            vec[i] = 0;
        }
    }

    // обрабатываем нулевой байт
    if (byte_k == 0) {
        vec[0] = vec[0] >> k;
    } else {
        vec[0] = 0;
    }

    // очищаем хвост
    if (bits % 8) {
        size_t tail_len = 8 - (bits % 8);
        unsigned char ones = ~0;  // все биты = 1
        ones = ones >> tail_len;   // маска для значащих битов
        vec[bytes - 1] &= ones;
    }
}

void shiftLeft(unsigned char *vec, size_t bits, size_t k) {
    if (!vec || !bits || !k) return;

    size_t bytes = ((bits - 1) / 8) + 1;
    size_t byte_k = k / 8;
    k = k % 8;

    // сдвиг слева направо (начинаем с первого байта)
    for (size_t i = 0; i < bytes - 1; i++) {
        size_t addr = i + byte_k;  // откуда берём данные

        if (addr < bytes) {
            vec[i] = vec[addr] << k;

            // перенос битов из соседнего байта
            if (k && (addr + 1) < bytes) {
                unsigned char mask = vec[addr + 1];
                mask = mask >> (8 - k);
                vec[i] |= mask;
            }
        } else {
            vec[i] = 0;
        }
    }

    // обрабатываем последний байт
    if (byte_k == 0) {
        vec[bytes - 1] = vec[bytes - 1] << k;  // ← правильно
    } else {
        vec[bytes - 1] = 0;
    }

    // очищаем хвост
    if (bits % 8) {
        size_t tail_len = 8 - (bits % 8);
        unsigned char ones = ~0;
        ones = ones >> tail_len;
        vec[bytes - 1] &= ones;
    }
}


void printVectAsInMemory(unsigned char* vec, size_t bits) {
    if (!vec) {
        printf("NULL");
        return;
    }

    size_t bytes = ((bits - 1) / 8) + 1;

    for (size_t i = 0; i < bytes; i++) {
        unsigned char mask = 1 << 7;  // начинаем со старшего бита
        for (size_t j = 0; j < 8; j++) {
            if ((vec[i] & mask) != 0)
                printf("1");
            else
                printf("0");
            mask = mask >> 1;  // сдвигаем к младшим битам
        }
    }
}
