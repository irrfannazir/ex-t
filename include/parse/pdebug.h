/* For word-by-word parsing analysis*/
#ifndef P_PARSE_DEBUG_MODE
//  #define P_PARSE_DEBUG_MODE
#endif


/* For AST analysis*/
#ifndef P_TREE_MODE
//  #define P_TREE_MODE
#endif


/* For checking word from syntax directory */
#ifndef P_CHECKING_WORD
//   #define P_CHECKING_WORD
#endif


/* Displays the tree */
#ifndef DISPLAY_TREE
  // #define DISPLAY_TREE
#endif

// #define LINE_ANALYSIS
#ifdef LINE_ANALYSIS
  #define LINE_FILENAME_MAX 1024
  extern char src_filename[LINE_FILENAME_MAX];
  static inline int print_line(int line_number) {
      if (line_number <= 0) return -1;

      FILE *file = fopen(src_filename, "r");
      if (file == NULL) return -1;
  
      char buffer[1024];
      int current_line = 0;

      while (fgets(buffer, sizeof(buffer), file) != NULL) {
          current_line++;
          if (current_line == line_number) {
              printf("%s", buffer);
              fclose(file);
              return 1;
          }
      }
  
      fclose(file);
      return 0;
  }
#else
  #define LINE_FILENAME_MAX 1024
  #define print_line(NUM)
#endif