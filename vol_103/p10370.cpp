#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

typedef uint32_t u32;

int main(int argc, char **argv)
{
    u32 C;
    int r = scanf("%u",&C);
    assert(r == 1);
    while (C--)
    {
        u32 N;
        r = scanf("%u",&N);
        assert(r == 1);
        assert(1 <= N and N <= 1000);
        float sum = 0.0F, f;
        std::vector<float> nums;
        for (u32 z = 0; z < N; ++z)
        {
            r = scanf("%f",&f);
            assert(r == 1);
            sum += f;
            nums.push_back(f);
        }
        float avg = sum / float(N);
        u32 above_count = 0;
        for (float z : nums) if (z > avg) ++above_count;
        printf("%.3f%%\n",100.0F*float(above_count)/float(N));
    }
    return 0;
}
