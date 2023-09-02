#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "core.h"

void clearInputBuffer(void) {
    while (getchar() != '\n') {
        ;
    }
}

void suspend(void) {
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

int inputInt(void) {
    char newLine = '\0';
    int value = 0;
    
    while (newLine != '\n') {
        scanf("%d%c", &value, &newLine);
        
        if (newLine != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    }
    
    return value;
}

int inputIntPositive(void) {
    int value;
    
    do {
        value = inputInt();
        
        if (value <= 0) {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);
    
    return value;
}

int inputIntRange(int lowerBound, int upperBound) {
    int value;
    
    do {
        value = inputInt();
        
        if (lowerBound > value || value > upperBound) {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (lowerBound > value || value > upperBound);
    
    return value;
}

char inputCharOption(const char validChars[]) {
    char inputChar = '\0';
    char chars[50];
    
    while (inputChar == '\0') {
        scanf("%49[^\n]", chars);
        clearInputBuffer();
        
        if (strlen(chars) == 1 && strstr(validChars, chars)) {
            int i;
            for (i = 0; validChars[i] != '\0'; i++) {
                if (validChars[i] == chars[0]) {
                    inputChar = chars[0];
                }
            }
        } else {
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
    }
    
    return inputChar;
}

void inputCString(char* str, int minChars, int maxChars) {
    int valid = 0;
    char strChars[50];
    
    while (!valid) {
        scanf("%49[^\n]", strChars);
        clearInputBuffer();
        
        long int len = strlen(strChars);
        if (minChars <= len && len <= maxChars) {
            valid = 1;
        }
        
        if (!valid) {
            if (minChars == maxChars) {
                printf("ERROR: String length must be exactly %d chars: ", minChars);
            } else if (len < minChars) {
                printf("ERROR: String length must be between %d and %d chars: ", minChars, maxChars);
            } else {
                printf("ERROR: String length must be no more than %d chars: ", maxChars);
            }
        }
    }
    strcpy(str, strChars);
}

void displayFormattedPhone(const char* phoneNum) {
    int digit = 0;
    
    if (phoneNum == NULL) {
        printf("(___)___-____");
        return;
    }
    
    int i;
    for (i = 0; phoneNum[i] != '\0'; i++) {
        if (isdigit(phoneNum[i])) {
            digit++;
        }
    }
    
    if (digit == 10) {
        printf("(%c%c%c)%c%c%c-%c%c%c%c",
               phoneNum[0], phoneNum[1], phoneNum[2],
               phoneNum[3], phoneNum[4], phoneNum[5],
               phoneNum[6], phoneNum[7], phoneNum[8], phoneNum[9]);
    } else {
        printf("(___)___-____");
    }
}
