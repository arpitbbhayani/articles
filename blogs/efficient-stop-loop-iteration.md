While I was writing a piece of code to solve a problem, I wrote a for loop which I had to break when a particular condition was met. Thing being pretty trivial to do, I wrote the required logic and done. Some time later, I was thinking, if I could do something different here. This started my quest to find right way to stop an iterating loop.

## Possible approaches

The two approaches to stop iteration of any loop are

* use `break` statement
* the condition where you want to stop, use that as condition of the loop

## The Example

Let's say we need to find if character `a` is present in the array or not and we need to set the value of boolean variable accordingly. The main piece of code would look something like this

### Using break statement

```cpp
bool a_found = false;

for (int i = 0 ; i < n ; i++) {
    if (str[i] == 'a') {
    	a_found = true;
        break;
    }
}
```

### Using loop condition

```cpp
bool a_found = false;

for (int i = 0 ; a_found == false && i < n ; i++) {
    if (str[i] == 'a') {
    	a_found = true;
    }
}
```

Should there be considerable difference in performance? If I'm taking efforts to write about it, the answer is obvious.

## Benchmark

Just like any other programmer, I decided to benchmark and see for myself if one is better than the other. The code to benchmark iterates over an array with variable number of elements and measures the time taken for each approach - standard benchmarking practice. You can find the code here - [code to benchmark stopping the loop iteration](https://gist.github.com/arpitbbhayani/d06cb7f4bb0cfdc8daa596dd77e8de10)

Following graph shows the time taken by the two approaches varied w.r.t number of iterations of the loop.

[ ![benchmark-time-taken-for-break-loop](https://user-images.githubusercontent.com/4745789/64257295-bdc36080-cf42-11e9-8ffa-783ca39c1a0f.png) ](https://user-images.githubusercontent.com/4745789/64257295-bdc36080-cf42-11e9-8ffa-783ca39c1a0f.png)

You could clearly see the diverging graph that suggests one approach is considerably better than the other. The blue line shows the approach where we break the loop and it is always below the red one that signifies the other approach. For all the number of iterations that were used to benchmark the approach, the blue line never crossed the red line, which means that breaking the loop using `break` is a much better approach than relying on condition that exits the loop.

Following graph shows the performance difference between the two approach. It was calculated by taking time taken by `break` approach as the baselint for calculating the improvement in percentage.

[ ![performance-gain-in-breaking-the-loop](https://user-images.githubusercontent.com/4745789/64257307-c4ea6e80-cf42-11e9-8da5-078287bfbca2.png) ](https://user-images.githubusercontent.com/4745789/64257307-c4ea6e80-cf42-11e9-8da5-078287bfbca2.png)

You could clearly see that the graph is almost a straight line fixed around 45%. The raw data used for plotting this graph can be found [here](https://plot.ly/\~arpitbbhayani/1).

## Conclusion

**Using **`**break**`** statement to break the loop is 45% better than using condition to stop the iteration.**
