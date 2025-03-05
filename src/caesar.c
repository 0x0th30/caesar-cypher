#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define ENCODE 1
#define DECODE -1

char cipher_char(char character, int rotation, int mode) {
  if (isupper(character))
    return 'A' + (character - 'A' + (rotation * mode) + ALPHABET_SIZE) %
                     ALPHABET_SIZE;

  if (islower(character))
    return 'a' + (character - 'a' + (rotation * mode) + ALPHABET_SIZE) %
                     ALPHABET_SIZE;

  return character;
}

int get_mode(char char_mode) {
  if (char_mode == 'E')
    return ENCODE;
  if (char_mode == 'D')
    return DECODE;

  printf("Invalid input, mode should be (D)ecode or (E)ncode.");
  exit(EXIT_FAILURE);
}

int main() {
  char mode_input;
  printf("Type the desired mode (D)ecode/(E)ncode: ");
  scanf("%c", &mode_input);
  getchar();

  int mode = get_mode(mode_input);

  int rotation;
  printf("Type the rotation key: ");
  scanf("%d", &rotation);
  getchar();

  char input[500];
  printf("Type the entry string: ");
  fgets(input, sizeof(input), stdin);

  size_t input_len = strlen(input);

  char *result = malloc(input_len + 1);
  if (!result) {
    printf("Memory allocation error.");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < input_len; i++) {
    result[i] = cipher_char(input[i], rotation, mode);
  }
  result[input_len] = '\0';

  printf("\n%s string: %s\n", mode == 1 ? "Encoded" : "Decoded", result);

  free(result);

  return 0;
}
