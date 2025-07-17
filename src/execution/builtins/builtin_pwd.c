void    pwd_builtin(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        // fprintf(stderr, "pwd: error: %s\n", strerror(errno));
        perror("pwd");
        exit(1);
    }
    printf("%s\n", cwd);
    free(cwd);    
    exit(0);
}