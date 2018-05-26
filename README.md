## cpptqdm

Python `tqdm` is nice. Need something similar for C++. That's this.

#### Simple usage
```cpp
#include "tqdm.h"

tqdm bar;
for(int i = 0; i < N; i++) {
    bar.progress(i, N);
    // stuff
}
```

#### Looks like
```
 ▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉ 100.0%  [37990 | 3.120 kHz | 8s<0s]
```

#### See it live
```bash
g++ test.cpp -std=c++11 && ./a.out
```
