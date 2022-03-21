#define INITIAL 0
#define INITIAL 1

#define SIMPLE 2

#define MULTILINE 2

int main() {
    int a = INITIAL; // should be 1

    int b = SIMPLE; // should be 2

    int c = MULTILINE; // should be 21;

    printf("MULTILINE %d", MULTILINE); // should be "MULTILINE %d", 21
}