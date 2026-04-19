#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char* convertStrToLongBv(char* str, int* cells);
char* convertBvToStr(unsigned char* vec, size_t sz);
unsigned char* addBitVectors(unsigned char* vec, unsigned char* vec2, int cells);

int main() {
    char* str = NULL;
    char* str2 = NULL;
    unsigned char* vec = NULL;

    str = "01101010";
    str2 = "01101010";

    int cells = 0;
    int len = strlen(str);
    cells = ((len - 1) / 8) + 1;

    vec = convertStrToLongBv(str, &cells);
    str = convertBvToStr(vec, cells);

    if (vec == NULL){
        printf("error1");
        return 1;
    }

    if (str == NULL){
        printf("error2");
        return 1;
    }
    printf("%s", str);
    free(vec);
    vec = NULL;
    free(str);
    str = NULL;
    free(str2);
    str = NULL;
    return 0;
}

unsigned char* convertStrToLongBv(char* str, int* cells){
    if (!(str && cells))
        return NULL;
    int len = 0, ix = 0;
    unsigned char mask = (1 << 7);
    len = strlen(str);
    *cells = ((len - 1) / 8) + 1;
    unsigned char* vec = (unsigned char*)malloc(sizeof (unsigned char) * (*cells));
    if (!(vec))
        return NULL;
    for (int i = 0; i < *cells; i++)
        vec[i] = 0;
    for (int i = 0; i < *cells; i++){
        for (int j = 0; j < 8 && (ix < len); j++){
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
        for (int bit = 0; bit < 8; bit++) {
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

unsigned char* addBitVectors(unsigned char* vec, unsigned char* vec2, int cells) {
    if (!vec || !vec2)
        return NULL;

    unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char) * cells);
    if (!result)
        return NULL;

    for (int i = 0; i < cells; i++) {
        result[i] = vec[i] | vec2[i];  // побитовое ИЛИ
    }

    return result;
}



