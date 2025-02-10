class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        s_size, t_size = len(s), len(t)
    
        last = [0 for _ in range(t_size + 1)]
        actual = [0 for _ in range(t_size + 1)]

        last[0],actual[0] = 1, 1

        for i in range(1, s_size + 1):
            for j in range(1, t_size + 1):
                if s[i - 1] == t[j - 1]:
                    actual[j] = last[j - 1] + last[j]
                else:
                    actual[j] = last[j]

            last, actual = actual, [0] * (t_size + 1)
            last[0] = 1 

        return last[t_size]