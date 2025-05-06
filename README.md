# Dining Philosophers in C

This project is a detailed and robust implementation of the classic **Dining Philosophers Problem** in C, focusing on concurrency, synchronization, and deadlock avoidance using `pthread` and `mutex`.

## 🧠 Overview

The simulation is divided into **four main phases**:

1. **Parsing Input**
2. **Initializing Data Structures**
3. **Starting the Simulation**
4. **Cleaning Up Resources**

Each philosopher is modeled as a thread, and forks are represented using mutexes. Special attention is given to prevent **deadlocks**, **race conditions**, and ensure **fairness**.

## ⚙️ Program Flow

### 1. Input Parsing (`parse_input`)

- Expects:  
  `./program philosophers time_to_die time_to_eat time_to_nap [hm_meals]`
- Validates arguments and converts them 
- Converts times from milliseconds to microseconds.
- Rejects values < 60ms to ensure realism.
- Optional `hm_meals` defaults to `-1` (unlimited).

### 2. Data Initialization (`data_init`)

- Allocates memory for:
  - Array of `philos` structs.
  - Array of `mutex` forks.
- Initializes:
  - Forks using `ft_mutex_caller`.
  - Each philosopher using `ft_global_init`.
  - Thread-safe table and internal mutexes.
- **Fork Assignment Strategy**:  
  Odd philosophers: right → left.  
  Even philosophers: left → right.  
  Prevents deadlock via asymmetric access.

### 3. Simulation Start (`ft_start`)

#### Special Cases:
- **0 meals** → exits immediately.
- **1 philosopher** →  (takes one fork, waits to die).

#### General Case:
- Starts all philosopher threads via `ft_thread_handle`.
- Synchronization .
- Launches a **monitor thread** to detect starvation.
- Uses thread-safe operations .
- Joins all threads after simulation ends.

### 4. Philosopher Routine (`dinner_simulation`)

Each philosopher:
- Waits for start flag.
- Tracks last meal time, meals counter, and status.
- Uses **odd-even fork locking** to avoid deadlock.
- Enters main loop:
  1. **Eat**  
     - Locks forks  
     - Updates meal time  
     - Sleeps (eating duration)
  2. **Sleep**
  3. **Think**  
     - Adaptive delay to improve fairness in odd-sized systems
- Uses secured usleep for accurate timing.
- Marks self full when meal count limit is reached.

### 5. Monitor Routine (`monitor_dinner`)

- Waits until all philosopher threads are active.
- Continuously checks:
  - If any philosopher has **starved** .
  - If so, sets an `end simulation` flag and writes death status.
- Thread-safe access to shared data (`last meal time`, `full`, etc.).

### 6. Cleanup (`clean`)

- Destroys:
  - All philosopher-level and table-level mutexes.
- Frees:
  - `forks` array  
  - `philosophers` array

## 🔒 Synchronization and Safety

- **Thread-Safe Wrappers**:  
  All access to shared data is mutex-protected .
- **Deadlock Avoidance**:  
  Forks are assigned based on philosopher parity.
- **Starvation Detection**:  
  Centralized monitor detects and handles deaths.

## 📁 Project Structure (Simplified)

```
philo/
├── main.c
├── parser.c
├── data_init.c
├── philo_creator.c
├── synchro.c
├── gnam.c
├── guardians.c
├── philo.h
├── utils.c
Makefile
README.md
```

## 🛠 Compilation

```bash
make
```

Run with:

```bash
./philo <number of philosophers> <time to die> <time to eat> <time to nap> [number_of_meals]
```

## 📌 Notes

- Works with any POSIX-compliant system supporting `pthread`.

## 👨‍🔬 

This implementation is inspired by classical CS concurrency patterns and customized with thread-safe abstractions, precise sleep handling, and fairness mechanisms to simulate real-world concurrent systems.