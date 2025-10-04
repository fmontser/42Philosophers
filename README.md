# Philosophers: Simulación de Concurrencia en C

> Implementación en C del problema clásico de "La cena de los filósofos". Este proyecto del Common Core de 42 Barcelona es un ejercicio práctico y profundo sobre la creación y sincronización de hilos (multithreading) y la prevención de problemas de concurrencia como los deadlocks y las condiciones de carrera.

---

### Stack Tecnológico y Conceptos Clave

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![pthreads](https://img.shields.io/badge/pthreads-POSIX%20Threads-blue?style=for-the-badge)
![Mutex](https://img.shields.io/badge/Mutex-Synchronization-red?style=for-the-badge)
![Concurrency](https://img.shields.io/badge/Concurrency-Deadlock%20Prevention-lightgrey?style=for-the-badge)

---

### El Desafío Técnico

El objetivo es simular a un número de filósofos sentados en una mesa circular. Entre cada par de filósofos hay un tenedor. Para comer, un filósofo necesita coger ambos tenedores, el de su izquierda y el de su derecha. El desafío consiste en diseñar un sistema donde:

*   Cada filósofo es un hilo de ejecución independiente (`pthread`).
*   Los tenedores son recursos compartidos.
*   El sistema debe evitar a toda costa el **deadlock** (un estado en el que todos los filósofos cogen un tenedor y esperan indefinidamente por el otro, bloqueando todo el programa).
*   El sistema debe evitar la **starvation** (que un filósofo nunca consiga comer).
*   Se deben proteger las variables compartidas (como el estado de los tenedores o el contador de comidas) de **condiciones de carrera** mediante el uso de **mutex**.

---

### Características de la Implementación

*   **Creación y Gestión de Hilos:** Utiliza la librería `pthreads` para crear un hilo por cada filósofo y gestionarlos de forma concurrente.
*   **Sincronización con Mutex:** Implementa `mutex` para cada tenedor (recurso compartido), asegurando que solo un filósofo puede usar un tenedor a la vez.
*   **Prevención de Deadlock:** La lógica está diseñada para romper las condiciones de espera circular, la causa principal de los deadlocks en este problema.
*   **Monitorización de Estado:** El programa monitoriza el estado de cada filósofo (pensando, comiendo, durmiendo) y puede incluir una rutina que compruebe si alguno ha muerto de inanición.
*   **Precisión Temporal:** Utiliza funciones de tiempo precisas para gestionar las duraciones de cada acción (comer, dormir) y la simulación en general.

---

### Entorno de Desarrollo y Compilación

Este proyecto fue desarrollado y probado en el ecosistema **macOS**, utilizando el compilador **Clang** y las librerías estándar proporcionadas por dicho sistema operativo, siguiendo las directrices del currículo de 42.

La compilación y el comportamiento esperado están garantizados únicamente para este entorno.

---

### Cómo Compilar y Ejecutar

> Importante este proyecto fue desarrollado en macos Catalina (bsd), no es funcionara en entornos linux sin extensivas modificaciones.

1.  **Compilar el proyecto:**
    ```bash
    make
    ```
2.  **Ejecutar la simulación:**
    ```bash
    ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
    ```
