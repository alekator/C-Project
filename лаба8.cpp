#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"  // для 8-битного конвертера
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

char* pak(const char* str) { // функция упаковки символов
    char* str_pak = malloc(sizeof(char)); // Функция malloc выделяет блок памяти, размером sizemem байт, и возвращает указатель на начало блока.
    float comp_r; // коэф уплотнения
    size_t size = 1;
    for (int i = 0, j = 0; i < strlen(str); ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str_pak = realloc(str_pak, size += 4); // если встречается заглавная буква то выделяется дополнительно 4 байта
            int a = 0;
            i += 2;    // перемещение позиции в строке на 2 вперёд
            int l = 0; // количество упакованных символов
            for (int k = 2; k >= 0; --k) { // идем в обратном порядке
                if (str[i] >= 'A' && str[i] <= 'Z') { // если встречается заглавная буква
                    a <<= 5; // приводим её к пятибитному виду
                    a += str[i] - 'A' + 1; // биты в 4х байтном блоке сдвигаются вправо и прибавляется код буквы (прибавляем единицу чтобы буква 'A' не была нулевой)
                    l += 1;
                }
                else { // если между заглавными буквами встречается прописная
                    a = 0; // блок данных сбрасывается в ноль
                    l = 0;
                }
                i--;
            }

            // После нахождения стоящих впереди больших букв

            a |= 2147483648; // устанавливаем первый бит единицу

            str_pak[j++] = (a >> 24) & 0xFF;  // записывам старшими разрядами вперёд
            str_pak[j++] = (a >> 16) & 0xFF;
            str_pak[j++] = (a >> 8) & 0xFF;
            str_pak[j++] = a & 0xFF;
            i += l;
        }
        // Строчные буквы запиваются в виде однобайтовых кодов с первым битом равным нулю
        else {
            str_pak = realloc(str_pak, ++size);
            str_pak[j] = str[i];
            str_pak[j] &= 0b01111111; // устанавливаем первый бит ноль
            j++;
        }
    }
    str_pak[size - 1] = 0;
    comp_r = (float)strlen(str) / (float)strlen(str_pak); // вычисление коэффициента уплотнения (количество символов строки на количество упакованных символов)
    printf("%f\n", comp_r);
    return str_pak;
}

char* unpak(char* str_pak) {  // функция распаковки символов
    char* result = malloc(sizeof(char));
    size_t size = 1;
    int p = 0;
    for (int i = 0; str_pak[i] != 0; ++i) {
        if (str_pak[i] & 0b10000000) { // если первый бит еденица
            int a = 0;
            char* tmp = (char*)&a;
            tmp[3] = str_pak[i]; // следующие четыре байта преобразуются в четырёх байтную целую переменную первый бит которой обнуляется
            tmp[2] = str_pak[i + 1];
            tmp[1] = str_pak[i + 2];
            tmp[0] = str_pak[i + 3];
            a &= 2147483647; // обнуляем первый бит
            for (int j = 0; j < 3; ++j) {
                if (a) {
                    result = realloc(result, ++size);
                    result[p++] = (char)((a & 0b11111) + 'A' - 1); // первые 5 бит числа преобразуем их в стандартные char коды после чего добавляем в разжатую строку
                    a >>= 5;
                }
                else {
                    break;
                }
            }
            i += 3;
        }
        else {
            result = realloc(result, ++size);
            result[p++] = str_pak[i];
        }
    }
    result[size] = 0; // повторяем пока не станет = 0
    return result;
}

int main() {
    char* string = "FNjmKOFNjIKFNjIKFNIFN";
    char* pak_str = pak(string);
    char* unpak_str = unpak(pak_str);
    printf("%s\n", pak_str);
    printf("%s\n", unpak_str);


    return 0;
}