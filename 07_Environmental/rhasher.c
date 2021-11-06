#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "rhash.h"

#ifdef HAVE_READLINE
#include <readline/readline.h>
#define CHECK_WHILE(cmd, cmd_len) (cmd = readline(NULL)) != NULL
#else
#define CHECK_WHILE(cmd, cmd_len) getline(& cmd, & cmd_len, stdin) != -1
#endif

void tolower_string(char* str)
{
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; str[i] != '\0'; ++i) {
        str[i] = tolower(str[i]);
    }
}

void calculate_hash(char* algo, const char* arg)
{
    enum rhash_print_sum_flags flag = RHPR_BASE64;
    enum rhash_ids algo_id = RHASH_MD4;
    if (isupper(algo[0])) {
        flag = RHPR_HEX;
    }
    tolower_string(algo);
    if (strcmp(algo, "sha1") == 0) {
        algo_id = RHASH_SHA1;
    }
    else if (strcmp(algo, "sha224") == 0) {
        algo_id = RHASH_SHA224;
    }
    else if (strcmp(algo, "sha256") == 0) {
        algo_id = RHASH_SHA256;
    }
    else if (strcmp(algo, "sha384") == 0) {
        algo_id = RHASH_SHA384;
    }
    else if (strcmp(algo, "md5") == 0) {
        algo_id = RHASH_MD5;
    }
    else if (strcmp(algo, "tth") == 0) {
        algo_id = RHASH_TTH;
    }
    else {
        fprintf(stderr, "Unsupported hash algorithm\n");
        return;
    }
    unsigned char digest[64];

    if (arg[0] == '\"') {
        if (rhash_msg(algo_id, arg + 1, strlen(arg) - 1, digest) < 0) {
            fprintf(stderr, "Message digest calculation error\n");
            return;
        }
    }
    else {
        if (rhash_file(algo_id, arg, digest) < 0) {
            fprintf(stderr, "File hash calculation error:\n%s: %s\n", arg, strerror(errno));
            return;
        }
    }
    char output[130];
    rhash_print_bytes(output, digest, rhash_get_digest_size(algo_id), flag);
    printf("%s\n", output);
}

void usage()
{
    fprintf(stderr, "Incorrect input. Usage:\n");
    fprintf(stderr, "\talorithm <file_or_string>\n");
}

int main()
{
    rhash_library_init();

    char* command = NULL;
    const char* delim = " \n";
    size_t command_len = 0;

    while (CHECK_WHILE(command, command_len)) {
        char* hash_command = command;
        char* hash_algo = strtok(hash_command, delim);
        if (hash_algo == NULL) {
            usage();
            continue;
        }
        const char* string_or_file = strtok('\0', delim);
        if (string_or_file == NULL) {
            usage();
            continue;
        }
        const char* tail = strtok('\0', delim);
        if (tail != NULL) {
            usage();
        }
        else {
            calculate_hash(hash_algo, string_or_file);
        }
    }
    free(command);
    return 0;
}
