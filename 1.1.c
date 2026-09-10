#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void multiply(const char* x, const char* y) {
    int len_a = strlen(x);
    int len_b = strlen(y);
    
    int* ans = (int*)calloc(len_a + len_b, sizeof(int));
    
    for (int i = 0; i < len_b; i++) {
        int h = 0; 
        int b_digit = y[len_b - 1 - i] - '0';
        
        for (int j = 0; j < len_a; j++) {
            int a_digit = x[len_a - 1 - j] - '0';
            
            int q = a_digit * b_digit + h + ans[i + j];
            
            h = q / 10;
            ans[i + j] = q % 10; 
        }
        
        if (h > 0) {
            ans[i + len_a] += h;
        }
    }
    
    int max_len = len_a + len_b;
    while (max_len > 1 && ans[max_len - 1] == 0) {
        max_len--;
    }
    
    printf("Multiplication result: ");
    for (int k = max_len - 1; k >= 0; k--) {
        printf("%d", ans[k]);
    }
    printf("\n");
    
    free(ans);
}
int main() {
    const char* num1 = "674";
    const char* num2 = "123";
    
    multiply(num1, num2);
    
    return 0;
}
