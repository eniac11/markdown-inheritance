#include <stdlib.h>
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

void nob_read_entire_file_to_sb(char *filepath, Nob_String_Builder *output_sb) {
  if (!nob_read_entire_file(filepath, output_sb))
    exit(1);
}

void compile_pandoc_sh(Nob_String_Builder *sb) {
#define OUT(buf, size) sb_append_buf(sb, buf, size);
#define READ_ENTIRE_FILE(filepath) nob_read_entire_file_to_sb((filepath), sb);
#include "make_pandoc.tt.h"
#undef OUT
#undef READ_ENTIRE_FILE
}

int main(int argc, char *argv[]) {
  Nob_String_Builder sb = {0};
  compile_pandoc_sh(&sb);
  if (!nob_write_entire_file("pandoc.sh", sb.items, sb.count))
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
