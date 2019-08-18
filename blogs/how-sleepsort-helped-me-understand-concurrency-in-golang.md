For me learning concurrency have always been tricky; Every language has a different way to handle/emulate concurrency, for example, old languages like Java uses [Threads](https://docs.oracle.com/javase/tutorial/essential/concurrency/) and modern languages like NodeJS and Python uses something called as [event loops](https://nodejs.org/en/docs/guides/event-loop-timers-and-nexttick/) for its asynchronous IO which is there to make IO based things concurrent.

Recently I started diving deep into concurrency in [Golang](https://golang.org/) and I wanted to start with a good `"Hello World"` program for it. This time I thought of taking an unconventional way to write my first concurrent program. Going through various examples over the Internet I could not find anything that made it fun. I suddenly recalled [Sleepsort](http://www.geeksforgeeks.org/sleep-sort-king-laziness-sorting-sleeping/) and it was the ideal way (fun + new = <3) to learn concurrency.

### The Concept
For people who do not know what Sleep Sort is, the basic goes something like this:
spin `n` threads/co-routine (or whatever concurrent element the language has) for `n` numbers (to sort) and for each number `x` wait for time proportional to `x` (lets say `x` seconds) and then print/collect the number.

### Implementation in Go
This is a very basic Implementation of Sleep Sort in Golang using Go Routines and [WaitGroup](https://golang.org/pkg/sync/#WaitGroup).

```go
// prints a number of sleeping for n seconds
func sleepAndPrint(x int, wg *sync.WaitGroup) {
	defer wg.Done()

	// Sleeping for time proportional to value
	time.Sleep(time.Duration(x) * time.Millisecond)

	// Printing the value
	fmt.Println(x)
}

// Sorts given integer slice using sleep sort
func Sort(numbers []int) {
	var wg sync.WaitGroup

	// Creating wait group that waits of len(numbers) of go routines to finish
	wg.Add(len(numbers))

	for _, x := range numbers {
		// Spinning a Go routine
		go sleepAndPrint(x, &wg)
	}

	// Waiting for all go routines to finish
	wg.Wait()
}
```

I have published the code in a [Github Repository](https://github.com/arpitbbhayani/go-sleep-sort). Feel
free to fork and play around with it.

### What else can you do with it
I encourage you to try it out, and trust me it is really fun to learn concurrency through this; Apart from running the basic sleep sort you should also try to do/learn with it. For example,

Concurrency essentials
 - Go Channels for inter go-routine communication
 - Mutex for synchronization making things routine-safe

You can also try to
 - collect the elements in a slice, in place of printing
 - make Sleep Sort handle negative numbers too
 - sort the numbers in descending order

If you find any interesting way to learn concurrency or any new use case here, please post a comment below.
I would love to know them.
