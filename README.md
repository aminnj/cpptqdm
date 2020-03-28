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
bar.finish();
```

#### Looks like
```
 █████████████████▍                  | 46.2%  [4200000 | 103.66 kHz | 35s<47s]
```

#### See it live
```bash
g++ test.cpp -std=c++11 && ./a.out
```

![example](images/example.gif)

### FAQ

#### Won't this slow down my loops?

If your loops are faster than ~200MHz, then maybe!

#### Themes?

You bet. `set_theme_basic(), set_theme_line(), set_theme_circles()`.

#### *For fun*, what if I wanted to use this in python?

If you have ROOT, you can do the following. Note that
due to the fact it uses ROOT to call C++ code in
Python, loops faster than 1kHz start to get slowed 
down by the overhead.
```python
import time
import ROOT as r

r.gROOT.ProcessLine(".L tqdm.h")

bar = r.tqdm()

N = 10000
for i in range(N):
    bar.progress(i,N)
    time.sleep(0.001)
```
