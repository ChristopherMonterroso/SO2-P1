# Informe técnico final

Universidad de San Carlos de Guatemala

Curso: Sistemas Operativos 2

**Autor:** Christopher Iván Monterroso Alegría
**Carné:** 201902363

---

## Introducción y objetivos del proyecto

Este proyecto tiene como propósito principal personalizar y expandir el kernel de Linux mediante la implementación de nuevas funcionalidades y la creación de llamadas al sistema personalizadas. A través de estas modificaciones, se busca que los estudiantes adquieran una comprensión profunda del funcionamiento interno del kernel, desarrollando habilidades clave en programación de sistemas y contribuyendo al desarrollo de sistemas operativos.

Los objetivos específicos incluyen:

- Modificación del nombre del sistema.
- Creación de nuevas llamadas al sistema.
- Desarrollo de módulos para ver estadísticas clave del sistema.

---

## Configuración del entorno

El entorno de desarrollo se configuró utilizando una máquina virtual basada en Linux, específicamente Linux Mint. Se instalaron las herramientas necesarias para la compilación y modificación del kernel, siguiendo estos pasos:

1. Descargar la imagen del kernel desde [Kernel.org](https://www.kernel.org/pub/linux/kernel/v6.x/linux-6.8.tar.xz).
2. Instalar las dependencias necesarias:

   ```bash
   sudo apt-get install build-essential kernel-package libncurses5-dev fakeroot wget bzip2 openssl
   sudo apt-get install build-essential libncurses-dev bison flex libssl-dev libelf-dev
   ```
3. Descomprimir la imagen y entrar al directorio:

   ```bash
   tar -xf linux-6.8.tar.xz
   cd linux-6.8
   ```
4. Configurar el kernel:

   ```bash
   cp -v /boot/config-$(uname -r) .config
   scripts/config --disable SYSTEM_TRUSTED_KEYS
   scripts/config --disable SYSTEM_REVOCATION_KEYS
   ```
5. Editar el archivo `Makefile` para personalizar el kernel:

   ```bash
   nano Makefile
   ```

   Modificar la línea:

   ```makefile
   EXTRAVERSION = -49-chris
   ```
6. Compilar el kernel:

   ```bash
   sudo -s
   make oldconfig
   make localmodconfig
   make -j$(nproc --ignore=1)
   make modules_install
   make install
   make headers_install
   update-grub2
   ```
7. Reiniciar el sistema para utilizar el kernel personalizado.

---

## Descripción de las modificaciones en el kernel

### Personalización del nombre del sistema

El nombre del sistema se personalizó mediante la edición del archivo `Makefile`, agregando el sufijo `-49-chris` a la variable `EXTRAVERSION`. Esto garantiza que el nombre personalizado aparezca durante el arranque del sistema.

### Mensajes de Inicio Personalizados

---

## Detalles de las nuevas llamadas al sistema

Se implementaron las siguientes llamadas al sistema, documentadas con su propósito, diseño y ejemplos de uso:

1. **`capture_memory_snapshot`:**

   Captura un "snapshot" del estado de la memoria que accede a la tabla de páginas del sistema y devuelve información estructurada del uso de memoria.
2. **`track_syscall_usage`:**

   Monitorea cuántas veces se ejecutan llamadas al sistema específicas. Modifica la tabla de llamadas del sistema para rastrear su ejecución.
3. **`get_io_throttle`:**

   Proporciona estadísticas de uso de I/O de procesos para esto se Integra las operaciones de entrada/salida del kernel.

## Reflexión Personal

La personalización del kernel de Linux fue bastante interesante y de un buen aprendizaje ya que además de personalizar el kernel de linux también aprendí sobre hyper-visor ya que al inicio la maquina virtual me iba un poco lenta y eran problemas que anteriormente ya había visto  al usar maquinas virtuales y que no sabía como modificar para mejorar el uso tal y como el auxiliar lo presentó en su guía.
