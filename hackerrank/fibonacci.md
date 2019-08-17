#
#  Author: Arpit Bhayani
#  https://arpitbhayani.me
#

x = raw_input().split()

dp = {}


def fib(t1, t2, n):
    if n == 1:
        return t1

    if n == 2:
        return t2

    t3 = dp.get(n)
    if t3 is None:
        t3 = fib(t1, t2, n-2) + fib(t1, t2, n-1) ** 2
        dp[n] = t3

    return t3

print fib(int(x[0]), int(x[1]), int(x[2]))
