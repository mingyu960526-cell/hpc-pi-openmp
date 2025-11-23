# 使用 OpenMP 平行計算蒙地卡羅估算 π 值
C 語言高效能計算期末微專題

程式網址：https://github.com/mingyu960526-cell/hpc-pi-openmp

### 編譯執行
```bash
gcc -fopenmp pi_monte_carlo_openmp.c -o pi -lm
./pi 1000000000
