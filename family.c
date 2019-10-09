#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "family.h"

/* Number of word pointers allocated for a new family.
   This is also the number of word pointers added to a family
   using realloc, when the family is full.
*/
static int family_increment = 2;


/* Set family_increment to size, and initialize random number generator.
   The random number generator is used to select a random word from a family.
   This function should be called exactly once, on startup.
*/
void init_family(int size) {
    family_increment = size;
    srand(time(0));
}


/* Given a pointer to the head of a linked list of Family nodes,
   print each family's signature and words.

   Do not modify this function. It will be used for marking.
*/
void print_families(Family* fam_list) {
    int i;
    Family *fam = fam_list;
    
    while (fam) {
        printf("***Family signature: %s Num words: %d\n",
               fam->signature, fam->num_words);
        for(i = 0; i < fam->num_words; i++) {
            printf("     %s\n", fam->word_ptrs[i]);
        }
        printf("\n");
        fam = fam->next;
    }
}


/* Return a pointer to a new family whose signature is 
   a copy of str. Initialize word_ptrs to point to 
   family_increment+1 pointers, numwords to 0, 
   maxwords to family_increment, and next to NULL.
*/
Family *new_family(char *str) {
    Family *fam = malloc(sizeof(Family));
    int length = strlen(str);
    fam->signature = malloc(sizeof(char) * (length + 1));
    strcpy(fam->signature, str);  
    fam->num_words = 0; 
    fam->word_ptrs = malloc(sizeof(char*) * family_increment+1);
    fam->max_words = family_increment; 
    fam->word_ptrs[fam->max_words] = NULL; //NEW
    fam->next = NULL; 
    return fam;
}


/* Add word to the next free slot fam->word_ptrs.
   If fam->word_ptrs is full, first use realloc to allocate family_increment
   more pointers and then add the new pointer.
*/
void add_word_to_family(Family *fam, char *word) {
    if (fam->num_words < fam->max_words) { 
        fam->word_ptrs[fam->num_words] = word; 
        fam->num_words++; 
    } else {
        char **new_word_ptrs;
        new_word_ptrs = realloc(fam->word_ptrs, fam->max_words + family_increment); //NEW
        fam->word_ptrs = new_word_ptrs;
        fam->max_words = fam->max_words + family_increment; //NEW 
        fam->word_ptrs[fam->max_words] = NULL; //NEW
        fam->word_ptrs[fam->num_words] = word; 
        fam->num_words++;
    }
    return;
}


/* Return a pointer to the family whose signature is sig;
   if there is no such family, return NULL.
   fam_list is a pointer to the head of a list of Family nodes.
*/
Family *find_family(Family *fam_list, char *sig) {
    Family *curr_fam = fam_list;
    while (curr_fam != NULL) {
      if (strcmp(curr_fam->signature, sig) == 0) {
          return curr_fam;
      } else {
          curr_fam = curr_fam->next;
      }
    }
    return fam_list;
}


/* Return a pointer to the family in the list with the most words;
   if the list is empty, return NULL. If multiple families have the most words,
   return a pointer to any of them.
   fam_list is a pointer to the head of a list of Family nodes.
*/
Family *find_biggest_family(Family *fam_list) {
    Family *curr_fam = fam_list;
    Family *most_fam = fam_list;
    int most_num = fam_list->num_words;
    if (fam_list == NULL) {
      return NULL;
    }
    while (curr_fam != NULL) {
      if (curr_fam->num_words >= most_num) {
        most_fam = curr_fam; 
        most_num = curr_fam->num_words;
        curr_fam = curr_fam->next;
      } else {
        curr_fam = curr_fam->next; 
      }
    } 
    return most_fam; 
}


/* Deallocate all memory rooted in the List pointed to by fam_list. */
void deallocate_families(Family *fam_list) {
    Family *curr_fam = fam_list;
    Family *next_fam;
    while (curr_fam != NULL) {
      next_fam = curr_fam->next; 
      free(curr_fam->word_ptrs);
      free(curr_fam->signature);
      free(curr_fam);
      curr_fam = next_fam;
    }
    return;
}

/*Checks if the family with given signature exists.  
*/
int does_family_exist(Family *fam_list, char *sig) {
  Family *curr_fam = fam_list;
  if (fam_list == NULL) {
    return 0;
  }
  while (curr_fam != NULL) {
    if (strcmp(curr_fam->signature, sig) == 0) {
      return 1; 
    }
    curr_fam = curr_fam->next; 
  }
  return 0; 
}

/* Generate and return a linked list of all families using words pointed to
   by word_list, using letter to partition the words.

   Implementation tips: To decide the family in which each word belongs, you
   will need to generate the signature of each word. Create only the families
   that have at least one word from the current word_list.
*/
Family *generate_families(char **word_list, char letter) {
    int i = 0; 
    Family *fam_list = NULL; 
    while (word_list[i] != NULL) {
      int length = strlen(word_list[i]);
      char sig[length + 1];
      sig[length] = '\0';
      for (int j = 0; j < length; j++) {
          if (word_list[i][j] == letter) {
            sig[j] = letter; 
          } else {
            sig[j] = '-';
          }
      }
      if (does_family_exist(fam_list, sig) == 0) {
        Family *fam = new_family(sig);
        fam->next = fam_list;
        fam_list = fam; 
      } else if (does_family_exist(fam_list, sig) == 1) {
        Family *curr_fam = fam_list;
        while (curr_fam != NULL) {
          if (strcmp(curr_fam->signature, sig) == 0) {
            add_word_to_family(curr_fam, word_list[i]);
          } else {
            curr_fam = curr_fam->next;
          }
        }
      }
      i++;
    }
    return fam_list;
}


/* Return the signature of the family pointed to by fam. */
char *get_family_signature(Family *fam) {
    return fam->signature;
}


/* Return a pointer to word pointers, each of which
   points to a word in fam. These pointers should not be the same
   as those used by fam->word_ptrs (i.e. they should be independently malloc'd),
   because fam->word_ptrs can move during a realloc.
   As with fam->word_ptrs, the final pointer should be NULL.
*/
char **get_new_word_list(Family *fam) {
    char **new_list = malloc(sizeof(char*) * (fam->max_words + 1));
    new_list[fam->max_words] = NULL; 
    for (int i = 0; i < fam->max_words; i++) {
      new_list[i] = fam->word_ptrs[i];
    }
    return new_list;
}

/* Return a pointer to a random word from fam. 
   Use rand (man 3 rand) to generate random integers.
*/
char *get_random_word_from_family(Family *fam) {
    srand(time(NULL));
    int index = rand()%((fam->num_words));
    return fam->word_ptrs[index];
}
