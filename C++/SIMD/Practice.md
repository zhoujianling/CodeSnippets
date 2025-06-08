

# 条件分支消除
任务：将数组中所有负数替换为0，用SIMD实现无分支操作
函数签名：
```c++
void replace_negative(float* data, size_t n);
```
关键技巧：
- 用比较指令生成掩码（_mm_cmplt_ps）
- 用位操作混合结果（_mm_and_ps/_mm_andnot_ps）

# 水平归约求和
任务：计算float数组所有元素之和
函数签名：
```c++
float sum_reduce(const float* data, size_t n);
```
挑战：
- 用_mm_hadd_ps或更高效的洗牌指令
- 避免标量循环处理尾部

参考：
```c++
__m128 acc = _mm_setzero_ps();
for(...) {
    __m128 v = _mm_loadu_ps(data + i);
    acc = _mm_add_ps(acc, v);
}
// 水平相加：acc = [a0+a1, a2+a3, ...]
__m128 shuf = _mm_shuffle_ps(acc, acc, _MM_SHUFFLE(2,3,0,1));
acc = _mm_add_ps(acc, shuf);
shuf = _mm_movehl_ps(shuf, acc);
acc = _mm_add_ss(acc, shuf);
return _mm_cvtss_f32(acc);
```

# 结构体数组优化 (AOS→SOA)
任务：优化以下结构体数组的归一化操作
```c++
struct Vec3 { float x, y, z; };
void normalize(Vec3* points, size_t n);
```

要求：

- 将数据重组为SOA布局（x[], y[], z[]）
- 用SIMD同时计算多个点的模长
- 结果写回原结构体

关键点：
- 使用_mm_movelh_ps/_mm_movehl_ps重组数据
- 利用_mm_rsqrt_ps快速计算倒数平方根

# 查找最大值位置
任务：在数组中找出最大值及其首次出现的位置
函数签名：
```c++
size_t find_max_index(const float* data, size_t n);
```

挑战：

- 用SIMD并行比较（_mm_max_ps）
- 用_mm_cmpeq_ps定位最大值位置
- 处理多个候选位置的冲突

优化技巧：
```c++
__m256 max_val = _mm256_set1_ps(-FLT_MAX);
__m256i max_indices = _mm256_set1_epi32(-1);
for(...) {
    __m256 vals = _mm256_loadu_ps(data + i);
    __m256 mask = _mm256_cmp_ps(vals, max_val, _CMP_GT_OQ);
    max_val = _mm256_max_ps(max_val, vals);
    // 更新候选索引：mask ? 当前索引 : 旧索引
}
```

# 字节流处理 (过滤空格)
任务：从字节流中快速移除空格字符（ASCII 32）
函数签名：
```c++
size_t filter_spaces(char* dst, const char* src, size_t len);
```

高级技巧：

- 用16字节SSE寄存器同时处理16个字符
- 用_mm_cmpeq_epi8比较空格
- 用_mm_movemask_epi8生成掩码位图
- 用_pdep_u32/_pext_u32加速压缩操作


# 矩阵转置优化
任务：优化4x4浮点矩阵转置
函数签名：
```c++
void transpose_4x4(float* matrix);
```

核心指令：
- _mm_unpacklo_ps / _mm_unpackhi_ps
- _mm_shuffle_ps
理想情况仅需6条指令完成转置

# 直方图统计 (冲突处理)
任务：统计字节流中0-255值的出现次数
函数签名：
```c++
void histogram(const uint8_t* data, size_t len, uint32_t* hist);
```

难点：
- SIMD无法直接原子更新内存
- 解决方案：局部直方图+最终合并
- 用_mm_i32gather_epi32加速随机访问

进阶挑战
- 双精度矩阵乘法：用AVX-512优化8x8矩阵乘
- 图像行间滤波：处理RGB图像边界（需对齐访问）
- 字符串匹配：SIMD加速Boyer-Moore算法
- 粒子系统：同时更新N个粒子的物理属性
