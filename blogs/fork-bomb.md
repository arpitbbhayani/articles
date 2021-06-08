In this essay, we explore a simple yet effective [DoS attack](https://en.wikipedia.org/wiki/Denial-of-service_attack) called [Fork Bomb](https://en.wikipedia.org/wiki/Fork_bomb), also called Rabbit Virus. This attack forks out processes infinitely, starving them for any resources.

Online Coding Platforms and Code Evaluators are susceptible to this attack as they accept raw code from the user and execute it. So, if you are building one, do ensure you are protected against it and infinite loops. We will also discuss how to prevent and defend against Fork Bomb in the final section of this essay.

# How do they work?

Fork bombs can be summarized in just three words: *Fork until possible*. When executed, fork bombs continuously fork out non-terminating processes, demanding machine resources like CPU (mostly) and memory.

![Fork Bomb](https://user-images.githubusercontent.com/4745789/121252662-e752ae00-c8c5-11eb-9524-a1c7d4fc24fc.png)

Fork Bomb

With so many processes competing for the CPU and other resources (if provisioned), the scheduler and CPU are put under tremendous load. After a specific limit, the entire system stalls.

# Implementing Fork Bombs

Before we take a look at how to prevent or stop a Fork Bomb, let's look at something more interesting - how to implement a Fork Bomb?

A quick detour, let's see what `fork` does: Upon every invocation, the forked child process is an exact duplicate of the parent process except for a [few details](https://man7.org/linux/man-pages/man2/fork.2.html), but nonetheless what matters to us is that it runs the exact same code as the parent.

## C implementation

A simple C implementation of a Fork Bomb could be, to fork child processes within an infinite for loop, resulting in exponential forking of child processes.

```c
#include <unistd.h>
int main(void) {
    for (;;) {
        fork();
    }
}
```

With the `fork` being invoked inside the infinite for loop, every single child process and the parent process will continue to remain stuck in the infinite loop while continuously forking out more and more child processes that execute the same code and stuck in the same loop; and thus resulting in exponential child forks.

These child processes start consuming the resources and blocking the legitimate programs. This prevents the creation of any new processes. This also freezes the process that responds to Keystrokes, putting the entire system to a standstill.

## Bash implementation

There is a very famous Fork Bomb implementation in Bash, and the code that does this has no alphabets or numbers in it, just pure symbols.

```bash
:(){ :|:& };:
```

Although the shell statement looks gibberish, it is effortless to understand. In the statement above, we are defining a function named `:` having body `:|:&` and at the end invoking it using the name `:`, just like any usual shell function.

As part of the function body, we are again invoking the same function `:` and piping its output to the input of a background process executing another instance of `:`. This way, we are recursively invoking the same function (command) and stalling it by creating a pipe between the two.

A cleaner way to redefine this very implementation of Fork Bomb would be

```bash
bomb() { 
    bomb| bomb& 
};bomb
```

# How to prevent them?

To protect our system against Form Bombs, we can cap the processes owned by a certain user, thus blocking process creation at that cap.

Using the *nix utility called `ulimit`, we can set the maximum number of processes that a user can execute in the system, using the flag `-u`. By setting this value to an appropriate (lower) value, we can cap the process creation for a user, ensuring we can never be fork bombed by that user.

# References

- [Fork Bomb](https://en.wikipedia.org/wiki/Fork_bomb)
- [ulimit - Man Page](https://linuxcommand.org/lc3_man_pages/ulimith.html)
- [Understanding Bash Fork Bomb](https://www.cyberciti.biz/faq/understanding-bash-fork-bomb/)
- [Preventing Fork Bombs on Linux](https://resources.cs.rutgers.edu/docs/preventing-fork-bomb-on-linux/)
- [Fork bomb attack (Rabbit virus) - Imperva](https://www.imperva.com/learn/ddos/fork-bomb/)
