
#pragma once

#include <stdio.h>

#define 主程序入口    int main() {

#define 字      char
#define 句子    const char*
#define 整数    int
#define 无返回  void

#define __XXXDDEF(x,T)      T x
#define __XXXADEF(x,T,sz)   T x[sz]

#define 定义数组参数(...)    __XXXADEF(__VA_ARGS__,)
#define 定义数组(...)   __XXXADEF(__VA_ARGS__)
#define 长度为  ,
#define 自动长度

#define 定义参数(...)    __XXXDDEF(__VA_ARGS__)
#define 定义变量(...)    __XXXDDEF(__VA_ARGS__)
#define 为              ,
#define 无初值
#define 赋初值 =

#define 乘      *
#define 加      +
#define 除      /
#define 余      %

#define 自增    ++
#define 自减    --

#define 加一    ++
#define 减一    --

#define 啥都不做

#define 若      if (
#define 又若    } else if(
#define 则      ) {
#define 否则    } else {
#define 结束    }

#define 当      while (
#define 时      ) {
#define 循环    }

#define 赋值为  =

#define 等于    ==
#define 大于    >
#define 小于    <
#define 不等于  !=
#define 大于等于 >=
#define 小于等于 <=

#define 且      &&
#define 或      ||

#define 开始    {
#define 结束    }

#define 返回    return

#define 说(...)      printf(__VA_ARGS__)
