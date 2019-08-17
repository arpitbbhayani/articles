```
/*
 *  Author: Arpit Bhayani
 *  https://arpitbhayani.me
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <deque>
#include <iostream>
#include <list>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#define ll long long

#define MIN(a, b) a < b ? a : b
#define MAX(a, b) a > b ? a : b

using namespace std;

int readline(char *str) {
    int i = 0;
    char ch;
    while((ch = getchar()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}

int main(int argc, char *argv[]) {
    int n, k;
    scanf("%d%d", &n, &k);

    int * arr = (int *) calloc(n + 1, sizeof(int));
    for(int i = 1 ; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 0;
    int book_page_numer = 0;
    for(int i = 1 ; i <= n; i++) {
        int chapter_pages = arr[i] / k + (arr[i] % k ? 1 : 0);
        // cout << "Chapter " << i << " has " << chapter_pages << " pages" << endl;
        for(int page_num = 1; page_num <= chapter_pages; page_num++) {
            book_page_numer ++;

            int prob_num = ((page_num - 1) * k) + 1;
            int prob_last = page_num * k;
            // cout << "Page Number: " << page_num << " has probs from " << prob_num << " to " << prob_last << endl;
            while(prob_num <= prob_last && prob_num <= arr[i]) {
                if(book_page_numer == prob_num) {
                    // cout << "Book Page number: " << book_page_numer<< endl;
                    count++;
                }
                prob_num++;
            }
        }
    }

    printf("%d\n", count);

    free(arr);
    return 0;
}
```
