#include <stdio.h>

struct SecretData {
    int code;
    char message[20];
};

int main() {
    int student_id, target_code;
    struct SecretData read_data;

    printf("Please enter your student ID: ");
    scanf("%d", &student_id);

    // BLANK 1: Write the mathematical operation (Modulo) to find the last two digits of the student ID.
    target_code = student_id % 100;

    // BLANK 2: Open the binary file in READ-ONLY mode.
    FILE *file = fopen("secrets.dat", "rb");

    // BLANK 3: Check if the file was opened successfully.
    if (file == NULL) {
        printf("File could not be opened! Please ensure secrets.dat is in the same directory.\n");
        return 1;
    }

    // BLANK 4: Write the loop that reads the structures (struct) until the end of the file using fread.
    // Hint: fread returns the number of successfully read elements. (Here we are trying to read 1 item at a time)
    while (fread(&read_data, sizeof(struct SecretData), 1, file) == 1) {
        
        if (read_data.code == target_code) {
            printf("\nCongratulations! The code worked.\n");
            printf("Your Special Message: %s\n\n", read_data.message);
            break; 
        }
    }

    // BLANK 5: Do not forget to close the file when done.
    fclose(file);

    return 0;
}