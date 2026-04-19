#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char* convertStrToLongBv(char* str, int* cells);


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

    if (vec == NULL){
        printf("error1");
        return 1;
    }

    printf("%s", str);
    free(vec);
    vec = NULL;
    free(str);
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


