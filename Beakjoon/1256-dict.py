import math


def solve(string:str, N, M, K):
    if N == 0:
        for i in range(M):
            string = string + 'z'
        return string
    elif M == 0:
        for i in range(N):
            string = string + 'a'
        return string
    num = math.factorial(N + M - 1) / (math.factorial(M) * math.factorial(N - 1))
    if num < K:
        string = string + 'z'
        return solve(string, N, M-1, K - num)
    else:
        string = string + 'a'
        return solve(string, N - 1, M, K)


_string = ''
_N, _M, _K = map(int, input().split())

if math.factorial(_N + _M) / (math.factorial(_M) * math.factorial(_N)) < _K:
    print(-1)
else:
    _string = solve(str(_string), _N, _M, _K)
    print(_string)
