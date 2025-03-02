#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define DEFAULT_ROTATION 1

const char ALPHABET[ALPHABET_SIZE] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

void usage() {
  printf("Usage: caesar [direction] [string] \n"
         "-d, --decode         Decodes provided string\n"
         "-e, --encode         Encodes provided string\n");
}

int find_index(char target, const char coll[], int coll_size) {
  for (int i = 0; i < coll_size; i++) {
    if (coll[i] == target)
      return i;
  }

  return -1;
}

char encode_char(char character, int rotation) {
  int calculated_index =
      find_index(character, ALPHABET, ALPHABET_SIZE) + rotation;
  int alphabet_max_index = ALPHABET_SIZE - 1;

  if (calculated_index > alphabet_max_index)
    return ALPHABET[calculated_index - ALPHABET_SIZE];

  return ALPHABET[calculated_index];
}

char *encode(char input[], int rotation) {
  int input_len = strlen(input);
  char *output = malloc(input_len + 1);
  if (!output) {
    fprintf(stderr, "Memory allocation error.\n");
    exit(1);
  }

  for (int i = 0; input[i] != '\0'; i++) {
    output[i] = encode_char(input[i], rotation);
  }
  output[input_len] = '\0';

  return output;
}

char decode_char(char character, int rotation) {
  int calculated_index =
      find_index(character, ALPHABET, ALPHABET_SIZE) - rotation;
  int alphabet_min_index = 0;

  if (calculated_index < alphabet_min_index)
    return ALPHABET[calculated_index + ALPHABET_SIZE];

  return ALPHABET[calculated_index];
}

char *decode(char input[], int rotation) {
  int input_len = strlen(input);
  char *output = malloc(input_len + 1);
  if (!output) {
    fprintf(stderr, "Memory allocation error.\n");
    exit(1);
  }

  for (int i = 0; i < input_len; i++) {
    output[i] = decode_char(input[i], rotation);
  }
  output[input_len] = '\0';

  return output;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    usage();
    return 1;
  }

  char *cypher_direction = argv[1];
  char *entry_string = argv[2];

  char *result;

  if (strcmp(cypher_direction, "-e") == 0 ||
      strcmp(cypher_direction, "--encode") == 0) {
    result = encode(entry_string, DEFAULT_ROTATION);

    printf("Encoded version of %s: %s\n", entry_string, result);

    free(result);
  }

  if (strcmp(cypher_direction, "-d") == 0 ||
      strcmp(cypher_direction, "--decode") == 0) {
    result = decode(entry_string, DEFAULT_ROTATION);

    printf("Decoded version of %s: %s\n", entry_string, result);

    free(result);
  }

  return 0;
}
