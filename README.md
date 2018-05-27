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
 ▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▍                      46.2%  [4200000 | 103.66 kHz | 35s<47s]
```

#### See it live
```bash
g++ test.cpp -std=c++11 && ./a.out
```
