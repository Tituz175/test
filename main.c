#include "main.h"

int main(int ac, char **argv, char **env)
{
    if (ac == 1)
        shell_loop(argv, env);
    return (0);
}
