/*
 * Shows user info from local pwfile.
 *  
 * Usage: userinfo username
 */

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwdblib.h"   /* include header declarations for pwdblib.c */

/* Define some constants. */
#define USERNAME_SIZE (32)
#define NOUSER (-1)


int print_info(const char *username)
{
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  if (p != NULL) {
    char prompt[] = "Enter your password: ";
    char password[32]; 
    strcpy(password, getpass(prompt));
    int b = strcmp(crypt(password, p->pw_passwd), p->pw_passwd);
    if (b == 0){
        printf("Success!");
    } else {
        printf("Something went wrong! \n");
    }
    return 0;
  } else {
    return NOUSER;
  }
}

void read_username(char *username)
{
  printf("login: ");
  fgets(username, USERNAME_SIZE, stdin);

  /* remove the newline included by getline() */
  username[strlen(username) - 1] = '\0';
}

int main(int argc, char **argv)
{
  char username[USERNAME_SIZE];
  
  /* 
   * Write "login: " and read user input. Copies the username to the
   * username variable.
   */
  read_username(username);

  /* Show user info from our local pwfile. */
  if (print_info(username) == NOUSER) {
      /* if there are no user with that usename... */
      printf("\nFound no user with name: %s\n", username);   
      return 0;
  }
}
  

  
