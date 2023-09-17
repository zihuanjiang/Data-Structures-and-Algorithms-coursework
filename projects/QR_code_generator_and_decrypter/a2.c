#include "a2.h"

int bitwise_xor(int value){
    return (int)value^KEY;
}

char* transfer_int_to_bit(int value){
    int value_left;
    value_left = value;
    char* result;
    result = malloc(sizeof(char)*8);

    if (value_left >= 128){return NULL;}

    for (int i = 6; i >= 0; i--){
        int the_power = pow(2,i);
        if (value_left >= the_power){
            value_left = value_left - the_power;
            result[(6-i)] = '1';
        }
        else{
            result[(6-i)] = '0';
        }
    }
    result[7] = '\0';
    return result;
}

char *xor_encrypt(char c){
    int c_int_form = (int)c;
    int bitwise_result = bitwise_xor(c_int_form);
    char* result;
    result = transfer_int_to_bit(bitwise_result);
    return result;
}

int transfer_bit_to_int(char* s){
    int result;
    result = 0;
    for (int i = 6; i >= 0; i--){
        char compare_to = s[(6-i)];
        if (compare_to == '1'){
            result = result + pow(2,i);
        }
    }
    return result;
}

char xor_decrypt(char *s){
    int int_decrypt = transfer_bit_to_int(s);
    int int_result = bitwise_xor(int_decrypt);
    char result;
    result = (char)int_result;
    return result;
}

char* transfer_msg_to_bit(char* msg){
    char* result;
    result = malloc(sizeof(char)* ((strlen(msg)+1)*7)+1);
    
    char c;
    int helper_index;

    for (int i = 0; i<= strlen(msg);i++){
        char* add;
        if (i != strlen(msg)){
            c = msg[i];
        }
        else if (i == strlen(msg)){
            c = '\0';
        }
        add = xor_encrypt(c);
        for (int j = 0; j<7;j++){
            helper_index = 7 * i + j;
            result[helper_index] = add[j];
        }
        free(add);
    }
    helper_index = (strlen(msg)+1)*7;
    result[helper_index] = '\0';
    return result;
}

char *gen_code(char *msg){
    char* result;
    result = malloc(sizeof(char)*257);

    char* transfered_char;
    transfered_char = transfer_msg_to_bit(msg);
    int j = 0;
    int filled = 0;

    for (int i = 0; i< 257; i++){
        // set up 0s
        if (i >= 17 && i <= 19) result[i] = '0';
        else if (i >= 28 && i <= 30) result[i] = '0';
        else if (i == 33 || i == 35) result[i] = '0';
        else if (i == 44 || i == 46) result[i] = '0';
        else if (i >= 49 && i <= 51) result[i] = '0';
        else if (i >= 60 && i <= 62) result[i] = '0';
        else if (i >= 193 && i <= 195) result[i] = '0';
        else if (i == 209 || i == 211) result[i] = '0';
        else if (i >= 225 && i <= 227) result[i] = '0';

        // set up 1s
        else if (i >=  0 && i <=  4) result[i] = '1';
        else if (i >= 11 && i <= 20) result[i] = '1';
        else if (i >= 27 && i <= 36) result[i] = '1';
        else if (i >= 43 && i <= 52) result[i] = '1';
        else if (i >= 59 && i <= 68) result[i] = '1';
        else if (i >= 75 && i <= 79) result[i] = '1';
        else if (i >= 176 && i <= 180) result[i] = '1';
        else if (i >= 192 && i <= 196) result[i] = '1';
        else if (i >= 208 && i <= 212) result[i] = '1';
        else if (i >= 224 && i <= 228) result[i] = '1';
        else if (i >= 240 && i <= 244) result[i] = '1';
        else if (i == 255) result[i] = '1';

        else{
            if (transfered_char[j] != '\0'){
                result[i] = transfered_char[j];
                j++;
            }
            else{
                result[i] = '0';
            }
        }
    }
    free(transfered_char);
    result[256] = '\0';
    return result;
}

char* get_bit_from_code(char* code){
    char* result;
    result = malloc(sizeof(char)*256);
    int filled = 0;
    int j = 0;

    for (int i = 0; i< 256; i++){
        filled = 0;
        if (i >=  0 && i <=  4) filled = 1;
        if (i >= 11 && i <= 20) filled = 1;
        if (i >= 27 && i <= 36) filled = 1;
        if (i >= 43 && i <= 52) filled = 1;
        if (i >= 59 && i <= 68) filled = 1;
        if (i >= 75 && i <= 79) filled = 1;
        if (i >= 176 && i <= 180) filled = 1;
        if (i >= 192 && i <= 196) filled = 1;
        if (i >= 208 && i <= 212) filled = 1;
        if (i >= 224 && i <= 228) filled = 1;
        if (i >= 240 && i <= 244) filled = 1;
        if (i == 255) filled = 1;

        if (filled == 0){
            result[j] = code[i];
            j++;
        }
    }
    return result;
}

char *read_code(char *code){
    char* transfered_bit;
    transfered_bit = get_bit_from_code(code);
    char* char_to_decrypt;
    char_to_decrypt = malloc(sizeof(char)*7);
    int helper_index;
    char* result;
    result = malloc(sizeof(char)*1);
    int all_zero = 0;

    for (int i = 0; i<= 40; i++){
        all_zero = 0;
        for (int j = 0; j <= 6; j++ ){
            helper_index = 7 * i + j;
            char_to_decrypt[j] = transfered_bit[helper_index];
            if (char_to_decrypt[j] == '1') all_zero = 1;
        }
        if (all_zero == 0){
            result[i] = '\0';
            break;
        }
        else{
            result[i] = xor_decrypt(char_to_decrypt);
            result = realloc(result,sizeof(char)*(i+2));
        }
    }
    free(char_to_decrypt);
    free(transfered_bit);
    return result;
}


char *compress(char *code){
    char* result;
    result = malloc(sizeof(char)*65);
    int the_number;
    int helper_index;

    for (int i = 0; i < 64; i++){
        the_number = 0;
        for (int j = 0; j < 4; j++){
            helper_index = 4*i + j;
            if (code[helper_index] == '1'){
                the_number = the_number + pow(2,(3-j));
            }
        }
        if (the_number == 0) result[i]='0';
        if (the_number == 1) result[i]='1';
        if (the_number == 2) result[i]='2';
        if (the_number == 3) result[i]='3';
        if (the_number == 4) result[i]='4';
        if (the_number == 5) result[i]='5';
        if (the_number == 6) result[i]='6';
        if (the_number == 7) result[i]='7';
        if (the_number == 8) result[i]='8';
        if (the_number == 9) result[i]='9';
        if (the_number == 10) result[i]='A';
        if (the_number == 11) result[i]='B';
        if (the_number == 12) result[i]='C';
        if (the_number == 13) result[i]='D';
        if (the_number == 14) result[i]='E';
        if (the_number == 15) result[i]='F';
    }
    result[64] = '\0';
    return result;
}

char *decompress(char *code){
    char* result;
    int the_number;
    result = malloc(sizeof(char)*257);
    for (int i = 0; i<= 63; i++){
        if (code[i] == '0'){
            result[4*i] = '0';
            result[4*i+1] = '0';
            result[4*i+2] = '0';
            result[4*i+3] = '0';
        }
        if (code[i] == '1'){
            result[4*i] = '0';
            result[4*i+1] = '0';
            result[4*i+2] = '0';
            result[4*i+3] = '1';
        }
        if (code[i] == '2'){
            result[4*i] = '0';
            result[4*i+1] = '0';
            result[4*i+2] = '1';
            result[4*i+3] = '0';
        }
        if (code[i] == '3'){
            result[4*i] = '0';
            result[4*i+1] = '0';
            result[4*i+2] = '1';
            result[4*i+3] = '1';
        }
        if (code[i] == '4'){
            result[4*i] = '0';
            result[4*i+1] = '1';
            result[4*i+2] = '0';
            result[4*i+3] = '0';
        }
        if (code[i] == '5'){
            result[4*i] = '0';
            result[4*i+1] = '1';
            result[4*i+2] = '0';
            result[4*i+3] = '1';
        }
        if (code[i] == '6'){
            result[4*i] = '0';
            result[4*i+1] = '1';
            result[4*i+2] = '1';
            result[4*i+3] = '0';
        }
        if (code[i] == '7'){
            result[4*i] = '0';
            result[4*i+1] = '1';
            result[4*i+2] = '1';
            result[4*i+3] = '1';
        }
        if (code[i] == '8'){
            result[4*i] = '1';
            result[4*i+1] = '0';
            result[4*i+2] = '0';
            result[4*i+3] = '0';
        }
        if (code[i] == '9'){
            result[4*i] = '1';
            result[4*i+1] = '0';
            result[4*i+2] = '0';
            result[4*i+3] = '1';
        }
        if (code[i] == 'A'){
            result[4*i] = '1';
            result[4*i+1] = '0';
            result[4*i+2] = '1';
            result[4*i+3] = '0';
        }
        if (code[i] == 'B'){
            result[4*i] = '1';
            result[4*i+1] = '0';
            result[4*i+2] = '1';
            result[4*i+3] = '1';
        }
        if (code[i] == 'C'){
            result[4*i] = '1';
            result[4*i+1] = '1';
            result[4*i+2] = '0';
            result[4*i+3] = '0';
        }
        if (code[i] == 'D'){
            result[4*i] = '1';
            result[4*i+1] = '1';
            result[4*i+2] = '0';
            result[4*i+3] = '1';
        }
        if (code[i] == 'E'){
            result[4*i] = '1';
            result[4*i+1] = '1';
            result[4*i+2] = '1';
            result[4*i+3] = '0';
        }
        if (code[i] == 'F'){
            result[4*i] = '1';
            result[4*i+1] = '1';
            result[4*i+2] = '1';
            result[4*i+3] = '1';
        }
    }
    result[256] = '\0';
    return result;
}

int calc_ld(char *sandy, char *cima){
    if (strcmp(sandy,"") == 0) return strlen(cima);
    else if (strcmp(cima ,"") == 0) return strlen(sandy);
    else if (sandy[0] == cima[0]) return calc_ld(sandy+1,cima+1);
    else{
        int result_one = 1 + calc_ld(sandy,cima+1);
        int result_two = 1 + calc_ld(sandy+1,cima);
        int result_three = 1 + calc_ld(sandy+1,cima+1);
        int minimum = result_one;
        if (result_two <= minimum) minimum = result_two;
        if (result_three <= minimum) minimum = result_three;
        return minimum;
    }
}
