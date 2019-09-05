While I was writing a piece of code to solve a problem, I wrote an innocent looking for loop which I had to break when a particular condition was met. Hence wrote the most obvious looking code ever - it used `break` once condition was met and this way the flow broke out of the loop. Once my solution was accepted by an online judge I thought could I have done anything else here?

This triggered me to benchmark different ways to get out of an iterating loop. The two of the most common ways to stop iterating a loop are

* use `break` statement
* write the condition of the loop in a way that is becomes `false` when you want to stop the iteration

# The Example

Everything is better with an example. Let's say we need to find if character `a` is present in the array and we need to set the value of `bool` variable `a_found` accordingly.

## Using break statement

```cpp
bool a_found = false;

for (int i = 0 ; i < n ; i++) {
    if (str[i] == 'a') {
    	a_found = true;
        break;
    }
}
```

## Using loop condition

```cpp
bool a_found = false;

for (int i = 0 ; a_found == false && i < n ; i++) {
    if (str[i] == 'a') {
    	a_found = true;
    }
}
```

Should there be considerable difference in performance? My efforts to write an article about this gives you the obvious answer. YES! there is a significant difference.

## Benchmark

The code to benchmark iterates over a string to see if `a` is present or not.  The length of the string is variable and goes from 500 to 1000000000. We measure the time taken for each approach - standard benchmark practice. You can find the code here - [code to benchmark stopping the loop iteration](https://gist.github.com/arpitbbhayani/d06cb7f4bb0cfdc8daa596dd77e8de10)

Following graph shows the time taken by the two approaches varied w.r.t number of iterations of the loop.

[ ![benchmark-time-taken-for-break-loop](https://user-images.githubusercontent.com/4745789/64257295-bdc36080-cf42-11e9-8ffa-783ca39c1a0f.png) ](https://user-images.githubusercontent.com/4745789/64257295-bdc36080-cf42-11e9-8ffa-783ca39c1a0f.png)

We see that a diverging graph that suggests one approach is significantly and always better than the other. The blue line shows the approach where we break the loop and it is always below the red one which represents the approach of stopping the iteration using condition.

The following graph shows the performance difference between the two approach. Here we calculate how much better is one approach than the other.

[ ![performance-gain-in-breaking-the-loop](https://user-images.githubusercontent.com/4745789/64257307-c4ea6e80-cf42-11e9-8da5-078287bfbca2.png) ](https://user-images.githubusercontent.com/4745789/64257307-c4ea6e80-cf42-11e9-8da5-078287bfbca2.png)

We observe that using break to stop the iteration is 45% better and it does not change with the number of iterations. The raw data used for plotting this graph can be found [here](https://plot.ly/\~arpitbbhayani/1).

# Conclusion

**Using `break` statement to break the loop is 45% better than using condition to stop the iteration and get out of the loop.**
