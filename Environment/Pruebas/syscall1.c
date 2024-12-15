#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>

// Define el número de syscall (asegúrate de usar el correcto)
#define SYS_CAPTURE_MEMORY_SNAPSHOT 548

// Define la estructura que coincide con la del kernel
struct memory_snapshot {
    unsigned long total_memory;
    unsigned long free_memory;
    unsigned long used_memory;
    unsigned long swap_total;
    unsigned long swap_free;
};

int main() {
    struct memory_snapshot snapshot;
    long result;

    // Invocar la syscall y pasar la dirección de la estructura
    result = syscall(SYS_CAPTURE_MEMORY_SNAPSHOT, &snapshot);

    if (result == 0) {
        // Imprimir los datos recibidos
        printf("Memory Snapshot:\n");
        printf("  Total Memory: %lu bytes\n", snapshot.total_memory);
        printf("  Free Memory: %lu bytes\n", snapshot.free_memory);
        printf("  Used Memory: %lu bytes\n", snapshot.used_memory);
        printf("  Swap Total: %lu bytes\n", snapshot.swap_total);
        printf("  Swap Free: %lu bytes\n", snapshot.swap_free);
    } else {
        // Imprimir error
        fprintf(stderr, "Error al invocar la syscall: %s\n", strerror(errno));
    }

    return 0;
}
