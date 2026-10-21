#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30000
#define MAXL 25

typedef struct {
    char str[MAXL + 1];
    int dist;
} Gene;

Gene database[MAXN];
Gene result[MAXN];

// 求三个整数的最小值
int min3(int a, int b, int c) {
    int min = a;

    if (b < min) {
        min = b;
    }

    if (c < min) {
        min = c;
    }

    return min;
}

// 计算两个字符串的编辑距离
int editDistance(const char *a, const char *b) {
    int n = strlen(a);
    int m = strlen(b);

    int dp[MAXL + 1][MAXL + 1];

    // 初始化第一列
    for (int i = 0; i <= n; i++) {
        dp[i][0] = i;
    }

    // 初始化第一行
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j;
    }

    // 填充动态规划数组
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            int cost;

            if (a[i - 1] == b[j - 1]) {
                cost = 0;
            } else {
                cost = 1;
            }

            // 删除、插入、替换或匹配
            dp[i][j] = min3(
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + cost
            );
        }
    }

    return dp[n][m];
}

// 排序：先按照距离升序，再按照字典序升序
int cmp(const void *a, const void *b) {
    const Gene *x = (const Gene *)a;
    const Gene *y = (const Gene *)b;

    if (x->dist < y->dist) {
        return -1;
    }

    if (x->dist > y->dist) {
        return 1;
    }

    return strcmp(x->str, y->str);
}

int main() {
    int D, N;
    char target[MAXL + 1];

    // 读取最大允许突变距离和数据库序列数量
    scanf("%d", &D);
    scanf("%d", &N);

    // 读取数据库
    for (int i = 0; i < N; i++) {
        scanf("%25s", database[i].str);
    }

    // 读取待测基因序列
    scanf("%25s", target);

    // 第一步：检查是否存在完全匹配
    for (int i = 0; i < N; i++) {
        if (strcmp(database[i].str, target) == 0) {
            printf("%s\n", database[i].str);
            return 0;
        }
    }

    // 第二步：查找满足距离限制的序列
    int count = 0;

    for (int i = 0; i < N; i++) {
        int d = editDistance(database[i].str, target);

        if (d <= D) {
            strcpy(result[count].str, database[i].str);
            result[count].dist = d;
            count++;
        }
    }

    // 第三步：没有匹配结果
    if (count == 0) {
        printf("None\n");
        return 0;
    }

    // 第四步：排序
    qsort(result, count, sizeof(Gene), cmp);

    // 第五步：输出结果
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf(" ");
        }

        printf("%s", result[i].str);
    }

    printf("\n");

    return 0;
}
