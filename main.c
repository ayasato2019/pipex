#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    int i = 0;

    /*  argc の確認 */
    printf("argc = %d\n", argc);

    /* argv の確認 */
    printf("argv = [");
    for (i = 0; i < argc; i++)
    {
        printf("\'%s\' ", argv[i]);
    }
    printf("]\n");

    /* envp の確認 */
    printf("envp = [");
    for (i = 0; envp[i]; i++)
    {
        printf("\'%s\' ", envp[i]);
    }
    printf("]\n");

    return 0;
}