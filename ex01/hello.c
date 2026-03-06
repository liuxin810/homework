#include <stdio.h>

int main() {
    char name[50];  // 定义一个字符数组，用于存储用户输入的名字
    
    printf("请输入你的名字：");
    scanf("%s", name);  // 获取用户输入（注意：%s 不能输入空格）
    
    printf("你好，%s！欢迎学习 C 语言。\n", name);
    printf("程序运行完毕。\n");
    
    return 0;
}