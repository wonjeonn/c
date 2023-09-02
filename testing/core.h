void clearInputBuffer(void);
void suspend(void);

int inputInt(void);
int inputIntPositive(void);
int inputIntRange(int lowerBound, int upperBound);
char inputCharOption(const char validChars[]);
void inputCString(char* str, int minChars, int maxChars);

void displayFormattedPhone(const char* phoneNum);
