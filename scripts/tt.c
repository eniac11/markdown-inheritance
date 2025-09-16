#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Document the whole tt paradigm (I could probably write an entire blog
// post about it)
// - C code mixed with text,
// - Inclusion of compiled templates into the body of C functions with macro
// parameters like OUT, ESCAPE_OUT, etc.,
// - Implied semicolons in template parameter macros,
// - Nested macros with %#include BODY% pattern,
// - HTML escaping,
// - ...

#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

void compile_c_code(String_View s, Nob_String_Builder *sb) {
  nob_sb_appendf(sb, "%.*s\n", (int)s.count, s.data);
}

void compile_byte_array(String_View s, Nob_String_Builder *sb) {
  nob_sb_append_cstr(sb, "OUT(\"");
  for (uint64_t i = 0; i < s.count; ++i) {
    nob_sb_appendf(sb, "\\x%02x", s.data[i]);
  }
  nob_sb_appendf(sb, "\", %lu);\n", s.count);
}

int main(int argc, char *argv[]) {
  String_View output_file = {0};
  String_View input_file = {0};
  char *command_name = shift(argv, argc);
  if (argc < 2) {
    fprintf(stderr, "Usage: %s -o output_file input_file\n", command_name);
    return 1;
  }
  int i = 0;
  while (argc > 0) {
    char *option = nob_shift(argv, argc);
    printf("%s", option);
    String_View sv = nob_sv_from_cstr(option);
    if (nob_sv_starts_with(sv, nob_sv_from_cstr("-"))) {
      if (nob_sv_eq(sv, nob_sv_from_cstr("-o"))) {
        option = shift(argv, argc);
        output_file = nob_sv_from_cstr(option);
      }
    } else {
      input_file = nob_sv_from_cstr(option);
      i++;
    }
    if (i == 1) {
      break;
    }
  }

  if (output_file.count == 0) {
    nob_log(NOB_ERROR, "need an output file got nothing");
    return 1;
  }

  if (input_file.count == 0) {
    nob_log(NOB_ERROR, "need an input file got nothing");
    return 1;
  }

  String_Builder sb = {0};
  if (!nob_read_entire_file(input_file.data, &sb))
    return 1;
  String_View temp = sb_to_sv(sb);
  String_Builder output_sb = {0};
  int c_code_mode = 0;
  // TODO: Generate line control preprocessor directives
  // - GCC: https://gcc.gnu.org/onlinedocs/cpp/Line-Control.html
  // - MSVC:
  // https://learn.microsoft.com/en-us/cpp/preprocessor/hash-line-directive-c-cpp
  while (temp.count) {
    String_View token = sv_chop_by_delim(&temp, '%');
    if (c_code_mode) {
      compile_c_code(token, &output_sb);
    } else {
      compile_byte_array(token, &output_sb);
    }
    c_code_mode = !c_code_mode;
  }

  if (output_sb.count) {
    nob_write_entire_file(output_file.data, output_sb.items, output_sb.count);
  }

  return 0;
}
