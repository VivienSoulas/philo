# philo - Dining Philosophers with Robust Concurrency

A multithreaded simulation of the dining philosophers problem, focused on preventing deadlocks, races, and starvation while keeping memory and resource management disciplined.

## Overview

philo models philosophers sharing forks (mutex-protected resources) while eating, thinking, and sleeping under timing constraints. The project emphasizes correct synchronization and orderly cleanup so that failures in one part do not cascade through the system.

## Core Concepts

- **Deadlock Avoidance**: Fork acquisition order and timing are structured to prevent circular wait conditions.
- **Mutual Exclusion**: Forks are protected by mutexes to avoid simultaneous access.
- **Starvation Prevention**: Timing and monitoring ensure that each philosopher gets opportunities to eat within required limits.
- **Precise Timing**: Millisecond-accurate measurements gate transitions between thinking, eating, sleeping, and death checks.
- **Resource Ownership**: Threads, mutexes, and allocations are created, tracked, and destroyed predictably to avoid leaks.

## Implementation Highlights

- Pthreads for philosopher routines and a monitor loop for death detection and enough meal eaten.
- One mutex per fork; additional mutexes for printing and shared state updates.
- Centralized error handling: on allocation or initialization failure, already-created resources are released before exiting.
- Clean shutdown: joins all threads, destroys mutexes, and frees dynamic allocations to prevent lingering resources.

## Build & Run

```bash
make
./philo <number_of_philosophers> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms> [optional_meals_to_eat]
```

Example:
```bash
./philo 5 800 200 200 5
```

## Failure Containment & Memory Management

- Validate inputs before starting threads to avoid partial initialization states.
- On any failure during setup, release all allocated structures and destroy initialized mutexes.
- After simulation, join all threads and destroy mutexes before freeing heap allocations.
- Logging and state updates are mutex-protected to avoid interleaved output or inconsistent shared state.

## Learning Outcomes

- Practical deadlock avoidance strategies in shared-resource systems.
- Race-free coordination using mutexes and deterministic fork ordering.
- Timing-sensitive simulation with consistent state observation.
- Disciplined resource lifetime management to prevent cascading failures in concurrent programs.

---

*A 42 School project showcasing concurrency control, timing, and resource safety.*
