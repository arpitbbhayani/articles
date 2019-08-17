```
N = int (input());
A = [0,1];
B = [0,1];
i = 2;
while i <= N:
    a = A[i-1]+B[i-1];
    A.append(a);
    B.append(A[i-1]);
    i = i+1;
print(A[N]+B[N]);
```
