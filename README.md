# Philosophers

Project about multithreading. A program that can monitor multiple instances of itself (threads or processes) using mutexes or semaphores.

## Concept
Philosophers (represented by parts of a program) sit around a table, with a big plate of spaghetti at its center. They each have a fork, but they need two forks to eat ; so they need to borrow their neighbor's fork to eat.
Of course, if they borrow a neighbor's fork, the neighbor can't use the fork. The processes / threads must communicate, to know the state of the forks (and of the other philosophers) at all times. There must also be a parent process that monitors everything.
The program does this using threads (or processes) as philosophers, and mutexes (semaphores) as forks.

## How to use it
Using 
> make 

in the directory will create the executable.

You run it specifying, in order :

- The number of philosophers
- The time in milliseconds until a philosopher dies from starvation
- The time in milliseconds it takes for a philosopher to eat
- The time in milliseconds it takes for a philosopher to sleep
- (Optional) The number of meals before the program stops

For instance:
> ./philo_one 4 800 200 200 3

Here, the program will create 4 philosophers, who will die if they go without eating for 800 milliseconds. It takes them 200 milliseconds to eat, and 100 milliseconds to sleep. The program will stop after each philosopher has had 3 meals (or if any one of them dies prematurely).

## Output
The program outputs every action with a timestamp (in milliseconds) and the philosopher's number.

```
$ ./philo 4 800 200 200 3
3       1 has taken a fork
4       1 has taken a fork
4       1 is eating
5       3 has taken a fork
...
```
