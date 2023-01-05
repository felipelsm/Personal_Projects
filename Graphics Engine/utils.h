#pragma once

typedef unsigned char u8;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

#define global_variable static
#define internal static

int clamp(int min, int val, int max);