#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>

#define SYS_track_syscall_usage 549

struct syscall_usage {
    unsigned long syscall_number;
    unsigned long count;
    unsigned long long last_invocation_ns;
};

int main() {
    // Agregar rastreo para la syscall 'open'
    if (syscall(SYS_track_syscall_usage, 0, __NR_open, NULL) != 0) {
        perror("Error rastreando syscall");
        return 1;
    }
    printf("Rastreo habilitado para syscall 'open'.\n");

    // Llamar a 'open' algunas veces
    FILE *f = fopen("/dev/null", "r");
    if (f) fclose(f);

    // Consultar estadísticas
    struct syscall_usage stats[10];
    int num_tracked = syscall(SYS_track_syscall_usage, 1, 0, stats);

    if (num_tracked < 0) {
        perror("Error consultando estadísticas");
        return 1;
    }

    printf("Número de syscalls rastreadas: %d\n", num_tracked);
    for (int i = 0; i < num_tracked; i++) {
        printf("Syscall: %lu, Invocaciones: %lu, Última: %llu ns\n",
               stats[i].syscall_number, stats[i].count, stats[i].last_invocation_ns);
    }

    return 0;
}
