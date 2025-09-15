found_solution = [False]


def is_valid(solution, target_sum):
    for i in range(len(solution) - 1):
        if solution[i] > solution[i + 1]:
            return False
    return sum(solution) <= target_sum


def is_solution(solution, target_target_sum):
    return target_target_sum == sum(solution)


def print_solution(solution):
    print(solution)
    found_solution[0] = True


def recursive_backtracking(step, coins, target_sum, solution):
    for i in range(len(coins)):
        solution.append(coins[i])
        if is_valid(solution, target_sum):
            if is_solution(solution, target_sum):
                print_solution(solution)
            else:
                recursive_backtracking(step + 1, coins, target_sum, solution)
        solution.pop()


def read_input():
    while True:
        n = input("Enter the number of coins: ")
        try:
            n = int(n)
            coins = []
            for i in range(n):
                while True:
                    coin = input("Enter the value of coin " + str(i + 1) + ": ")
                    try:
                        coin = int(coin)
                        coins.append(coin)
                        break
                    except ValueError:
                        print("Invalid input")
            break
        except ValueError:
            print("Invalid input")

    while True:
        target_target_sum = input("Enter the target_target_sum: ")
        try:
            target_target_sum = int(target_target_sum)
            break
        except ValueError:
            print("Invalid input")
    return coins, target_target_sum


def option_1():
    coins, target_target_sum = read_input()
    solution = []
    recursive_backtracking(0, coins, target_target_sum, solution)

    if not found_solution[0]:
        print("No payment modality exists")


def is_valid_it(k, coins, x, target_sum):
    for i in range(1, k):
        if coins[x[i] - 1] > coins[x[i + 1] - 1]:
            return False

    return sum(coins[x[i] - 1] for i in range(1, k + 1)) <= target_sum


def is_solution_it(k, coins, x, target_sum):
    return sum(coins[x[i] - 1] for i in range(1, k + 1)) == target_sum


def print_solution_it(k, coins, x):
    print([coins[x[i] - 1] for i in range(1, k + 1)])


def iterative_backtracking(coins, target_sum):
    n = len(coins)
    x = [0] * (target_sum + 1)
    k = 1
    x[1] = 0
    found_sol = False

    while k > 0:
        found = False
        while not found and x[k] < n:
            x[k] += 1
            if x[k] <= n and is_valid_it(k, coins, x, target_sum):
                found = True

        if not found:
            k -= 1
        else:
            if is_solution_it(k, coins, x, target_sum):
                print_solution_it(k, coins, x)
                found_sol = True
            if k < target_sum:
                k += 1
                x[k] = 0

    if not found_sol:
        print("No payment modality exists")


def option_2():
    coins, target_sum = read_input()
    coins.sort()
    iterative_backtracking(coins, target_sum)


def read_input_dp():
    while True:
        S1 = input("Enter a set of numbers: ")
        S = list(set(S1.split(' ')))
        for i in range(len(S)):
            try:
                S[i] = int(S[i])
            except ValueError:
                print("Invalid input")
                return [], 0
        break

    while True:
        k = input("Enter the target sum: ")
        try:
            k = int(k)
            break
        except ValueError:
            print("Invalid input")
    return S, k


def solve_naive(S, k):
    n = len(S)

    # Generate all possible subsets (there are 2^n subsets)
    # Each number i in the range 0 to 2^n - 1 represents a unique subset.
    # The binary representation of i determines which elements are included in the subset.
    # The inner loop checks each bit of i.
    # If the bit is set, the corresponding element from S is included in the subset.
    for i in range(1 << n):
        subset = []
        for j in range(n):
            if i & (1 << j):
                subset.append(S[j])
        if sum(subset) == k:
            return subset
    return []

def option_3():
    S, k = [], 0
    while not S:
        S, k = read_input_dp()
    subset = solve_naive(S, k)
    if subset:
        print(subset)
    else:
        print("No subset found")


def generate_dp_matrix(S, k, dp):
    n = len(S)
    for i in range(n + 1):
        dp[i][0] = True

    for j in range(1, k + 1):
        dp[0][j] = False

    for i in range(1, n + 1):
        for j in range(1, k + 1):
            if j < S[i - 1]:
                dp[i][j] = dp[i - 1][j]
            else:
                dp[i][j] = dp[i - 1][j] or dp[i - 1][j - S[i - 1]]

    return dp


def solve_dp(S, k, dp):
    n = len(S)
    print(S)
    dp = generate_dp_matrix(S, k, dp)

    print("\nDP matrix:")
    for i in range(len(dp)):
        print(dp[i])
    print()

    if dp[n][k]:
        subset = []
        i = n
        j = k
        while j > 0:
            if dp[i][j] and not dp[i - 1][j]:
                subset.append(S[i - 1])
                j -= S[i - 1]
            i -= 1
        print(subset)
    else:
        print("No subset found")


def option_4():
    S, k = [], 0
    while not S:
        S, k = read_input_dp()
    n = len(S)
    S.sort()
    dp = [[False] * (k + 1) for _ in range(n + 1)]
    solve_dp(S, k, dp)


def print_menu():
    print(
        "A number of n coins are given, with values of a1, ..., an and a value s. Display all payment modalities for the target_target_sum s.")
    print("1. Recursive solution")
    print("2. Iterative solution")
    print(
        "Given the set of positive integers S and the natural number k, display one of the subsets of S which sum to k. For example, if S = { 2, 3, 5, 7, 8 } and k = 14, subset { 2, 5, 7 } sums to 14.")
    print("3. Naive implementation")
    print("4. Dynamic programming")
    print("0. Exit Program")


def test_is_valid():
    assert is_valid([1, 2, 3], 10) == True
    assert is_valid([3, 2, 1], 10) == False
    assert is_valid([], 5) == True
    assert is_valid([1, 2], 2) == False


def test_is_solution():
    assert is_solution([1, 2, 3], 6) == True
    assert is_solution([1, 2, 3], 5) == False
    assert is_solution([], 0) == True
    assert is_solution([1, 2], 3) == True


def test_is_valid_it():
    assert is_valid_it(3, [1, 2, 3], [0, 1, 2, 3], 10) == True
    assert is_valid_it(3, [3, 2, 1], [0, 1, 2, 3], 10) == False
    assert is_valid_it(0, [], [0], 5) == True
    assert is_valid_it(2, [1, 2], [0, 1, 2], 2) == False


def test_is_solution_it():
    assert is_solution_it(3, [1, 2, 3], [0, 1, 2, 3], 6) == True
    assert is_solution_it(3, [1, 2, 3], [0, 1, 2, 3], 5) == False
    assert is_solution_it(0, [], [0], 0) == True
    assert is_solution_it(2, [1, 2], [0, 1, 2], 3) == True
    assert is_solution_it(2, [1, 2], [0, 1, 2], 2) == False


def test_solve_naive():
    assert solve_naive([1, 2, 3], 6) == [1, 2, 3]
    assert solve_naive([1, 2, 3], 5) == [2, 3]
    assert solve_naive([], 0) == []
    assert solve_naive([1, 2, 3], 3) == [1, 2]
    assert solve_naive([1, 2, 3], 4) == [1, 3]

def test_generate_dp_matrix():
    dp = [[False] * 6 for _ in range(4)]
    assert generate_dp_matrix([1, 2, 3], 5, dp) == [
        [True, False, False, False, False, False],
        [True, True, False, False, False, False],
        [True, True, True, True, False, False],
        [True, True, True, True, True, True]
    ]

    dp = [[False] * 2 for _ in range(2)]
    assert generate_dp_matrix([1], 1, dp) == [
        [True, False],
        [True, True]
    ]

def test_functions():
    test_is_valid()
    test_is_solution()
    test_is_valid_it()
    test_is_solution_it()
    test_solve_naive()
    test_generate_dp_matrix()


def main():
    test_functions()

    while True:
        print_menu()
        option = input("Enter option: ")
        match option:
            case "1":
                print()
                option_1()
                print()
            case "2":
                print()
                option_2()
                print()
            case "3":
                print()
                option_3()
                print()
            case "4":
                print()
                option_4()
                print()
            case "0":
                print("Exiting program...\n")
                return
            case _:
                print("Invalid option\n")


if __name__ == "__main__":
    main()
