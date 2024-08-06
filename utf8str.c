#include <stdlib.h>
#include <string.h>

unsigned int num_bytes(char b) {
  if((b & 0b10000000) == 0) { return 1; }
  else if((b & 0b11100000) == 0b11000000) { return 2; }
  else if((b & 0b11110000) == 0b11100000) { return 3; }
  else if((b & 0b11111000) == 0b11110000) { return 4; }
  else { return -1; }
}
unsigned int utf8_strlen(char* unicode) {
  unsigned int len = strlen(unicode); // count of bytes in this string
  unsigned int bytes_seen = 0;
  unsigned int unicode_characters_seen = 0;
  while(bytes_seen < len) {
    unsigned int bytes_this_char = num_bytes(unicode[bytes_seen]);
    bytes_seen += bytes_this_char;
    unicode_characters_seen += 1;
  }
  return unicode_characters_seen;
}
unsigned int bytes_for(char* unicode, unsigned int n) {
  unsigned int unicode_characters_seen = 0;
  unsigned int bytes_seen = 0;
  unsigned int total_chars = utf8_strlen(unicode);
  if(total_chars < n) { return -1; }
  if(n < 0) { return -1; }
  while(unicode_characters_seen < n) {
    unsigned int bytes_this_char = num_bytes(unicode[bytes_seen]);
    bytes_seen += bytes_this_char;
    unicode_characters_seen += 1;
  }
  return bytes_seen;
}

/*
  char long_str[] = "José Ülo 成龙";
  utf8_substring(long_str, 0, 4) -> José
  utf8_substring(long_str, 5, 8) -> Ülo
  utf8_substring(long_str, 9, 11) -> 成龙
*/
char* utf8_substring(char* utf8str, unsigned int start, unsigned int end) {
  // Should check start <= end, check that end <= utf8_strlen(utf8str), and so on
  unsigned int start_bytes = bytes_for(utf8str, start);
  char* start_char = utf8str + start_bytes;
  unsigned int size = end - start;
  unsigned int bytes_to_copy = bytes_for(start_char, size);

  // Make a new string! Use malloc
  // +1 is because all of our char* c strings end in \0
  char* to_return = malloc(bytes_to_copy + 1);

  for(int i = 0; i < bytes_to_copy; i += 1) {
    to_return[i] = start_char[i];
  }
  to_return[bytes_to_copy] = '\0';
  return to_return;
}














// Find the index (in terms of utf8 characters) where utf8_str_to_find appears
// in utf8str_to_search, or -1 if it does not appear
int utf8_find(char* utf8str_to_search, char* utf8str_to_find) {
  return -1;
}

// Return a reversed version of the utf8str.
// utf8_reverse("Ülo") -> "olÜ"
char* utf8_reverse(char* utf8str) {
  // The number of UTF8 characters (Ü counts as 1)
  unsigned int len = utf8_strlen(utf8str);
  // The number of bytes (of chars) in the string (Ü counts as 2)
  unsigned int size = bytes_for(utf8str, len);
  // Allocate enough space for all the bytes in a new string
  char* new_str = malloc(size + 1);

  // copy_to_index will start at the end of the string and move
  // “backwards” to copy UTF8 characters in reversed order
  unsigned int copy_to_index = size;
  new_str[copy_to_index] = '\0';

  // index will be which *byte* we are looking at in the input
  unsigned int index = 0;
  // utf8_index will be which *UTF8 character* we are looking at
  unsigned int utf8_index = 0;
  while(utf8_index < len) {
    // How many bytes is the current UTF8 character?
    unsigned int this_utf8_size = num_bytes(utf8str[index]);
    // We will start writing a chunk of that size at copy_to_index
    copy_to_index -= this_utf8_size;
    // Copy the bytes for the current character (at index) to the
    // copy_to_index one at a time. So the two bytes for Ü end up
    // in order, but at the end of the output string
    for(unsigned int i = 0; i < this_utf8_size; i += 1) {
      new_str[i + copy_to_index] = utf8str[index + i];
    }
    // Update indices
    index += this_utf8_size;
    utf8_index += 1;
  }
  return new_str;
}
