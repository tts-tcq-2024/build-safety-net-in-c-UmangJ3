#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

char getSoundexCode(char c) {
    switch (toupper(c)) {
        case 'B': case 'F': case 'P': case 'V': return '1';
        case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z': return '2';
        case 'D': case 'T': return '3';
        case 'L': return '4';
        case 'M': case 'N': return '5';
        case 'R': return '6';
        default: return '0';
    }
}

char extractAndCapitalizeInitial(const char *name) {
    return toupper(name[0]);
}

void fillWithZeros(char *soundex, int &index) {
    while (index < 4) {
        soundex[index++] = '0';
    }
    soundex[4] = '\0';
}
bool isCodeDuplicate(char currentCode, char previousCode) {
    return currentCode == previousCode && currentCode != '0';
}

void appendSoundexCode(char *soundex, int &index, char code) {
    if (index < 4) {
        soundex[index++] = code;
    }
}

// Function to process and encode the remaining letters of the name
void processRemainingLetters(const char *name, char *soundex, int &index, char &lastCode) {
    for (int i = 1; name[i] != '\0'; i++) {
        char currentCode = getSoundexCode(name[i]);
        if (!isCodeDuplicate(currentCode, lastCode) && currentCode != '0') {
            appendSoundexCode(soundex, index, currentCode);
        }
        if (currentCode != '0') {
            lastCode = currentCode;
        }
    }
}

void generateSoundex(const char *name, char *soundex) {
    if (name == nullptr || soundex == nullptr || strlen(name) == 0) {
        soundex[0] = '\0';
        return;
    }

    soundex[0] = extractAndCapitalizeInitial(name);
    int index = 1;
    char lastCode = getSoundexCode(name[0]);

    processRemainingLetters(name, soundex, index, lastCode);
    fillWithZeros(soundex, index);
}

#endif // SOUNDEX_H

