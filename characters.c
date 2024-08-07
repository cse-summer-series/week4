#include <stdio.h>
#include <string.h>
#include "utf8str.c"

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Try running with ./welcome your-name\n");
    return 1;
  }

  printf("bytes_for(\"José\", 3) -> 3: %d\n", bytes_for("José", 3));
  printf("bytes_for(\"Ülo\", 3) -> 4: %d\n", bytes_for("Ülo", 3));
  printf("bytes_for(\"José\", 4) -> 5: %d\n", bytes_for("José", 4));
  printf("bytes_for(\"成龙\", 1) -> 3: %d\n", bytes_for("成龙", 1));
  printf("bytes_for(\"成龙\", 2) -> 6: %d\n", bytes_for("成龙", 2));
  printf("bytes_for(\"成龙\", 3) -> -1: %d\n", bytes_for("成龙", 3));
  // gave wrong answer of 7! Needed to check total_chars < n

// <-----------    成   ----------> <-------------  龙   ----------->   \0, null terminator
// 0b11100000 0bxxxxxxxx 0bxxxxxxxx 0b11100000 0bxxxxxxxx 0bxxxxxxxx   0b00000000










  char long_str[] = "José Ülo 成龙";
  printf("utf8_substring(long_str, 0, 4) -> José: %s\n", utf8_substring(long_str, 0, 4));
  printf("utf8_substring(long_str, 5, 8) -> Ülo: %s\n", utf8_substring(long_str, 5, 8));
  printf("utf8_substring(long_str, 9, 11) -> 成龙: %s\n", utf8_substring(long_str, 9, 11));

  printf("utf8_substring(long_str, 2, 10) -> sé Ülo 成: %s\n", utf8_substring(long_str, 2, 10));

  printf("reverse(\"Ülo\") -> \"olÜ\": %s\n", utf8_reverse("Ülo"));

  char* name = argv[1];
  int length = strlen(name);
  unsigned int ulen = utf8_strlen(name);
  printf("Hi %s, your name is %d characters long according to utf8_strlen.\n", name, ulen);
  printf("The number of bytes needed for the first character are: %c\n", name[0]);

  printf("The invididual characters are: \n");
  for(int i = 0; i < length; i += 1) {
    unsigned char letter = name[i];
    printf("%d(%x) ", letter, letter);
  }
  printf("\n");

  return 0;
}
