// define 1
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
    unsigned char* vec1 = convertStrToLongBv(str1, &bits1);
    if (vec1 == NULL) {
        printf("error11");
        return 1;
    }

    unsigned char* vec2 = convertStrToLongBv(str2, &bits2);
    if (vec2 == NULL) {
        printf("error12");
        free(vec1);
        vec1 = NULL;
        return 1;
    }

    // исходные векторы
    char* vec1_str = convertBvToStr(vec1, bits1);
    if (vec1_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }

    char* vec2_str = convertBvToStr(vec2, bits2);
    if (vec2_str == NULL) {
        printf("error2");
        free(vec1_str);
        free(vec1);
        free(vec2);
        vec1_str = NULL;
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }

    printf("v1 %s\n", vec1_str);
    printf("v2 %s\n", vec2_str);
    free(vec1_str);
    vec1_str = NULL;
    free(vec2_str);
    vec2_str = NULL;
    printf("\n");

    // +
    unsigned char* add_res = logSum(vec1, bits1, vec2, bits2);
    if (add_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    char* add_str = convertBvToStr(add_res, bits1);
    if (add_str == NULL) {
        printf("error2");
        free(add_res);
        free(vec1);
        free(vec2);
        add_res = NULL;
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    printf("+ %s\n", add_str);
    free(add_str);
    add_str = NULL;
    free(add_res);
    add_res = NULL;

    // *
    unsigned char* mul_res = logMul(vec1, bits1, vec2, bits2);
    if (mul_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    char* mul_str = convertBvToStr(mul_res, bits1);
    if (mul_str == NULL) {
        printf("error2");
        free(mul_res);
        free(vec1);
        free(vec2);
        mul_res = NULL;
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    printf("& %s\n", mul_str);
    free(mul_str);
    mul_str = NULL;
    free(mul_res);
    mul_res = NULL;

    // xor
    unsigned char* xor_res = sumMod2(vec1, bits1, vec2, bits2);
    if (xor_res == NULL) {
        printf("error3");
        free(vec1);
        free(vec2);
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    char* xor_str = convertBvToStr(xor_res, bits1);
    if (xor_str == NULL) {
        printf("error2");
        free(xor_res);
        free(vec1);
        free(vec2);
        xor_res = NULL;
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    printf("xor %s\n", xor_str);
    free(xor_str);
    xor_str = NULL;
    free(xor_res);
    xor_res = NULL;

    // инверсия
    inversion(vec1, bits1);
    char* inv_str = convertBvToStr(vec1, bits1);
    if (inv_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    printf("~ %s\n", inv_str);
    free(inv_str);
    inv_str = NULL;

    // инвертируем обратно для дальнейших тестов
    inversion(vec1, bits1);

    // установка бита 7 в 1
    set1(vec1, bits1, 7);
    char* set1_str = convertBvToStr(vec1, bits1);
    if (set1_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    printf("set1 %s\n", set1_str);
    free(set1_str);
    set1_str = NULL;

    // сброс бита 0 в 0
    set0(vec1, bits1, 0);
    char* set0_str = convertBvToStr(vec1, bits1);
    if (set0_str == NULL) {
        printf("error2");
        free(vec1);
        free(vec2);
        vec1 = NULL;
        vec2 = NULL;
        return 1;
    }
    printf("set0 %s\n", set0_str);
    free(set0_str);
    set0_str = NULL;

    printf("memory ");
    printVectAsInMemory(vec1, bits1);
    printf("\n\n");

    free(vec1);
    vec1 = NULL;
    free(vec2);
    vec2 = NULL;

    // ==================== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ====================

    // Тест 1: 1000111010110101
    printf("test1 ");
    int cells = 0;
    unsigned char test1[] = "1000111010110101";
    unsigned char* bv1 = convertStrToLongBv(test1, &cells);
    if (!bv1) {
        printf("error converting str\n");
        return 0;
    }
    printVectAsInMemory(bv1, 16);
    printf("\n\n");
    free(bv1);
    bv1 = NULL;

    // Тест 2: длинная строка 122 бита
    printf("test2 ");
    unsigned char test2[] = "00111000011011100001101110000010001110110100111011010011101110011100001101110000110111000001000111011010011101101001110111";
    unsigned char* bv2 = convertStrToLongBv(test2, &cells);
    if (!bv2) {
        printf("error converting str\n");
        return 0;
    }
    printVectAsInMemory(bv2, 122);
    printf("\n");
    unsigned char* bv2_str = convertBvToStr(bv2, 122);
    if (!bv2_str) {
        printf("error reconverting\n");
        free(bv2);
        bv2 = NULL;
        return 0;
    }
    printf("str %s\n\n", bv2_str);
    free(bv2_str);
    bv2_str = NULL;
    free(bv2);
    bv2 = NULL;

    // Тест 3: сумма по модулю 2 (61 бит)
    printf("test3 xor\n");
    unsigned char test3_1[] = "1100010110110001011011000101101100010110110001011011000101101";
    unsigned char test3_2[] = "1111110111011111011101111101100100101101100010110110001011010";
    unsigned char* vec3_1 = convertStrToLongBv(test3_1, &cells);
    unsigned char* vec3_2 = convertStrToLongBv(test3_2, &cells);
    if (!vec3_1 || !vec3_2) {
        printf("error converting\n");
        free(vec3_1);
        free(vec3_2);
        vec3_1 = NULL;
        vec3_2 = NULL;
        return 0;
    }
    printVectAsInMemory(vec3_1, 61);
    printf("\n");
    printVectAsInMemory(vec3_2, 61);
    printf("\n");
    unsigned char* vec3_3 = sumMod2(vec3_1, 61, vec3_2, 61);
    if (!vec3_3) {
        printf("error xor\n");
        free(vec3_1);
        free(vec3_2);
        vec3_1 = NULL;
        vec3_2 = NULL;
        return 0;
    }
    printVectAsInMemory(vec3_3, 61);
    printf("\n\n");
    free(vec3_1);
    vec3_1 = NULL;
    free(vec3_2);
    vec3_2 = NULL;
    free(vec3_3);
    vec3_3 = NULL;

    // Тест 4: инверсия
    printf("test4 inv\n");
    unsigned char test4[] = "1000111010110011";
    unsigned char* vec4 = convertStrToLongBv(test4, &cells);
    if (!vec4) {
        printf("error converting\n");
        return 0;
    }
    printVectAsInMemory(vec4, 16);
    printf("\n");
    inversion(vec4, 16);
    printVectAsInMemory(vec4, 16);
    printf("\n\n");
    free(vec4);
    vec4 = NULL;

    // Тест 5: сдвиг вправо на 20 с восстановлением
    printf("test5 >>20\n");
    unsigned char test5[] = "0011100001101110000110111000001000111011010011101101001110111";
    unsigned char* vec5 = convertStrToLongBv(test5, &cells);
    if (!vec5) {
        printf("error converting\n");
        return 0;
    }
    printVectAsInMemory(vec5, 66);
    printf("\n");
    shiftRight(vec5, 61, 20);
    printVectAsInMemory(vec5, 66);
    printf("\nback ");
    shiftLeft(vec5, 61, 20);
    printVectAsInMemory(vec5, 66);
    printf("\n\n");
    free(vec5);
    vec5 = NULL;

    // Тест 6: сдвиг влево на 30 с восстановлением
    printf("test6 <<30\n");
    unsigned char test6[] = "0011100001101110000110111000001000111011010011101101001110111";
    unsigned char* vec6 = convertStrToLongBv(test6, &cells);
    if (!vec6) {
        printf("error converting\n");
        return 0;
    }
    printVectAsInMemory(vec6, 61);
    printf("\n");
    shiftLeft(vec6, 61, 30);
    printVectAsInMemory(vec6, 61);
    printf("\nback ");
    shiftRight(vec6, 61, 30);
    printVectAsInMemory(vec6, 61);
    printf("\n\n");
    free(vec6);
    vec6 = NULL;

    // Тест 7: установка/сброс битов
    printf("test7 set1/set0\n");
    unsigned char test7[] = "01111111";
    unsigned char* vec7 = convertStrToLongBv(test7, &cells);
    if (!vec7) {
        printf("error converting\n");
        return 0;
    }
    printVectAsInMemory(vec7, 8);
    printf("\n");
    set1(vec7, 8, 0);
    printVectAsInMemory(vec7, 8);
    printf("\n");
    set0(vec7, 8, 3);
    printVectAsInMemory(vec7, 8);
    printf("\n\n");
    free(vec7);
    vec7 = NULL;

    // Тест 8: преобразование "100001"
    printf("test8 ");
    unsigned char test8[] = "100001";
    unsigned char* bv8 = convertStrToLongBv(test8, &cells);
    if (bv8) {
        printVectAsInMemory(bv8, 6);
        printf("\n\n");
        free(bv8);
        bv8 = NULL;
    }

    // Тест 9: преобразование "10110"
    printf("test9 ");
    unsigned char test9[] = "10110";
    unsigned char* bv9 = convertStrToLongBv(test9, &cells);
    if (bv9) {
        printVectAsInMemory(bv9, 5);
        printf("\n\n");
        free(bv9);
        bv9 = NULL;
    }

    // Тест 10: преобразование "1"
    printf("test10 ");
    unsigned char test10[] = "1";
    unsigned char* bv10 = convertStrToLongBv(test10, &cells);
    if (bv10) {
        printVectAsInMemory(bv10, 1);
        printf("\n\n");
        free(bv10);
        bv10 = NULL;
    }

    printf("test11 errors\n");

    // Пустая строка
    unsigned char test11_1[] = "";
    unsigned char* bv11_1 = convertStrToLongBv(test11_1, &cells);
    if (!bv11_1) {
        printf("empty str - error\n");
    }

    // NULL строка
    unsigned char* bv11_2 = convertStrToLongBv(NULL, &cells);
    if (!bv11_2) {
        printf("NULL str - error\n");
    }

    // NULL bits
    unsigned char* bv11_3 = convertStrToLongBv(test8, NULL);
    if (!bv11_3) {
        printf("NULL cells - error\n");
    }

    // xor с разной длиной
    unsigned char test11_4[] = "1111";
    unsigned char test11_5[] = "11111";
    unsigned char* bv11_4 = convertStrToLongBv(test11_4, &cells);
    unsigned char* bv11_5 = convertStrToLongBv(test11_5, &cells);
    if (bv11_4 && bv11_5) {
        unsigned char* bad_res = sumMod2(bv11_4, 4, bv11_5, 5);
        if (!bad_res) {
            printf("xor dif bits - error\n");
        }
        free(bv11_4);
        free(bv11_5);
        bv11_4 = NULL;
        bv11_5 = NULL;
    }

    // xor с NULL
    unsigned char* bad_res2 = sumMod2(NULL, 4, bv11_5, 4);
    if (!bad_res2) {
        printf("xor NULL vec - error\n");
    }

    // logMul с разной длиной
    if (bv11_4 && bv11_5) {
        unsigned char* bad_mul = logMul(bv11_4, 4, bv11_5, 5);
        if (!bad_mul) {
            printf("logMul diff bits - error\n");
        }
    }

    // logSum с разной длиной
    if (bv11_4 && bv11_5) {
        unsigned char* bad_sum = logSum(bv11_4, 4, bv11_5, 5);
        if (!bad_sum) {
            printf("logSum diff bits - error\n");
        }
    }

    // set1 с битом вне диапазона
    unsigned char test11_6[] = "11111111";
    unsigned char* bv11_6 = convertStrToLongBv(test11_6, &cells);
    if (bv11_6) {
        unsigned char old = bv11_6[0];
        set1(bv11_6, 8, 10);  // бит 10 >= 8
        if (bv11_6[0] == old) {
            printf("set1 out of range - no change (correct)\n");
        }
        free(bv11_6);
        bv11_6 = NULL;
    }

    // set0 с битом вне диапазона
    unsigned char test11_7[] = "00000000";
    unsigned char* bv11_7 = convertStrToLongBv(test11_7, &cells);
    if (bv11_7) {
        unsigned char old = bv11_7[0];
        set0(bv11_7, 8, 10);  // бит 10 >= 8
        if (bv11_7[0] == old) {
            printf("set0 out of range - no change (correct)\n");
        }
        free(bv11_7);
        bv11_7 = NULL;
    }

    printf("\n");

    // Тест 11: циклические сдвиги (100 итераций)
    printf("test11 shift100\n");
    unsigned char* vec100 = (unsigned char*)calloc(13, sizeof(unsigned char));
    if (!vec100) {
        printf("error allocating memory\n");
        return 0;
    }
    inversion(vec100, 100);
    printVectAsInMemory(vec100, 100);
    printf("\n");
    for (int i = 0; i < 100; i++) {
        shiftRight(vec100, 100, 1);
        printVectAsInMemory(vec100, 100);
        printf("\n");
    }
    inversion(vec100, 100);
    printVectAsInMemory(vec100, 100);
    printf("\n");
    for (int i = 0; i < 100; i++) {
        shiftLeft(vec100, 100, 1);
        printVectAsInMemory(vec100, 100);
        printf("\n");
    }
    free(vec100);
    vec100 = NULL;

    return 0;
}

unsigned char* convertStrToLongBv(char* str, size_t* bits){
    if (!(str && bits))
        return NULL;
    size_t len = strlen(str);
    if (len == 0) {
        return NULL;
    }
    size_t  ix = 0;
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
