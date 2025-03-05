#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define DEFAULT_ROTATION 1

#define ENCODE 1
#define DECODE -1

const char ALPHABET[ALPHABET_SIZE] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

void usage() {
  printf("Usage: caesar [mode] [string] \n"
         "-d         Decodes provided string\n"
         "-e         Encodes provided string\n");
}

int find_index(char target) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (ALPHABET[i] == target)
      return i;
  }

  // how to return a value to indicate out-of-bound character?
  return 0;
}

char cipher_char(char character, int rotation, int mode) {
  int index = find_index(character);
  if (index == 0)
    return character;

  int ciphered_char_index = (index + (rotation * mode)) % ALPHABET_SIZE;
  if (ciphered_char_index < 0) {
    ciphered_char_index += ALPHABET_SIZE;
  }

  return ALPHABET[ciphered_char_index];
}

int get_mode(char arg[]) {
  if (arg[0] == '-') {
    if (arg[1] == 'e')
      return ENCODE;
    if (arg[1] == 'd')
      return DECODE;
  }

  usage();
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    usage();
    exit(EXIT_FAILURE);
  }

  int mode = get_mode(argv[1]);
  char *input = argv[2];
  size_t input_len = strlen(input);

  char *result = malloc(input_len + 1);
  if (!result) {
    printf("Memory allocation error.");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < input_len; i++) {
    result[i] = cipher_char(input[i], DEFAULT_ROTATION, mode);
  }
  result[input_len] = '\0';

  printf("%s version of \"%s\": %s\n", mode == 1 ? "Encoded" : "Decoded", input,
         result);

  free(result);

  return 0;
}
