#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>

char getSoundexCode(char c) {
    c = toupper(c);
    switch (c) {
        case 'B': case 'F': case 'P': case 'V': return '1';
        case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z': return '2';
        case 'D': case 'T': return '3';
        case 'L': return '4';
        case 'M': case 'N': return '5';
        case 'R': return '6';
        default: return '0'; // For A, E, I, O, U, H, W, Y
    }
}

char getFirstLetter(const char *name) {
    return toupper(name[0]);
}

void padWithZeros(char *soundex, int &index) {
    while (index < 4) {
        soundex[index++] = '0';
    }
    soundex[4] = '\0';
}

bool isDuplicateCode(char currentCode, char lastCode) {
    return currentCode == lastCode && currentCode != '0';
}

void encodeRemainingLetters(const char *name, char *soundex, int &index, char &lastCode) {
    for (int i = 1; name[i] != '\0' && index < 4; i++) {
        char currentCode = getSoundexCode(name[i]);
        if (!isDuplicateCode(currentCode, lastCode)) {
            if (currentCode != '0') {
                soundex[index++] = currentCode;
            }
            lastCode = currentCode;
        }
    }
}

void generateSoundex(const char *name, char *soundex) {
    if (name == nullptr || soundex == nullptr || strlen(name) == 0) {
        soundex[0] = '\0';
        return;
    }

    soundex[0] = getFirstLetter(name);
    int index = 1;
    char lastCode = getSoundexCode(name[0]);

    encodeRemainingLetters(name, soundex, index, lastCode);
    padWithZeros(soundex, index);
}
#endif // SOUNDEX_H
