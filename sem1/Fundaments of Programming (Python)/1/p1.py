# Solve the problem from the first set here
"""
1. Generate the first prime number larger than a given natural number n.
2. Given natural number n, determine the prime numbers p1 and p2 such that n = p1 + p2 (check the Goldbach hypothesis).
3. For a given natural number n find the minimal natural number m formed with the same digits. (e.g. n=3658, m=3568).
4. For a given natural number n find the largest natural number written with the same digits. (e.g. n=3658, m=8653).
5. Generate the largest prime number smaller than a given natural number n. If such a number does not exist, a message should be displayed.
"""


#defining function in order to make checking the input easier
def try_covert_to_int(var):
    try:
        int_var = int(var)
        return int_var
    except ValueError:
        return ValueError

#checks if number is prime and returns True or False accordingly
def isprime(n: int) -> bool:
    if n <= 1 or n % 2 == 0:
        return False
    if n == 2:
        return True
    for d in range(3, n // 2 + 1, 2):
        if n % d == 0:
            return False
    return True

# start task1
#itterates through numbers greater than n and returns the first prime one
def greater_prime(n: int) -> int:
    n += 1
    while not isprime(n):
        n += 1
    return n


def solve_task1(n):
    #check if input correct
    try:
        int_n = int(n)
        if int_n < 0:
            print("Please input a natural number")
        else:
            print(greater_prime(int_n))
    except ValueError:
        print("Please input a natural number")
# end task1

# start task2
def solve_task2(n):
    if try_covert_to_int(n) == ValueError:
        print("Please input a natural number")
    else:
        n = try_covert_to_int(n)
        if n < 0:
            print("Please input a natural number")
        else:
            for i in range(2, n // 2 + 1):
                if isprime(i) and isprime(n - i):
                    print(f"{n} = {i} + {n - i}")
                    return
            print("No solution")


# end task2

# start task3
def solve_task3(n):
    if try_covert_to_int(n) == ValueError:
        print("Please input a natural number")
    else:
        n = try_covert_to_int(n)
        if n < 0:
            print("Please input a natural number")
        else:
            digits = []
            while n:
                digits.append(n % 10)
                n = n // 10
            digits.sort()
            i = 0
            while digits[i] == 0:
                i += 1
            m = digits[i]
            m *= (10 ** i)
            i += 1
            while i < len(digits):
                m = m * 10 + digits[i]
                i += 1
            print(f"m= {m}")


# end task3

# start task4
def solve_task4(n):
    if try_covert_to_int(n) == ValueError:
        print("Please input a natural number")
    else:
        n = try_covert_to_int(n)
        if n < 0:
            print("Please input a natural number")
        else:
            digits = []
            while n:
                digits.append(n % 10)
                n = n // 10
            digits.sort()
            digits.reverse()
            m = 0
            for i in range(0, len(digits)):
                m = m * 10 + digits[i]
            print(f"m= {m}")
# end task4

#start task5
def solve_task5(n):
    if try_covert_to_int(n) == ValueError:
        print("Please input a natural number")
    else:
        n = try_covert_to_int(n)
        if n < 0:
            print("Please input a natural number")
        else:
            for i in range(n-1, 1, -1):
                if isprime(i):
                    print(f"largest prime number smaller than {n} is {i}")
                    return
            print("no solution")
#end task5

def setup():
    #printing the menu
    print("\n")
    problems = "1. Generate the first prime number larger than a given natural number n.\n2. Given natural number n, determine the prime numbers p1 and p2 such that n = p1 + p2 (check the Goldbach hypothesis).\n3. For a given natural number n find the minimal natural number m formed with the same digits. (e.g. n=3658, m=3568).\n4. For a given natural number n find the largest natural number written with the same digits. (e.g. n=3658, m=8653).\n5. Generate the largest prime number smaller than a given natural number n. If such a number does not exist, a message should be displayed."
    print(problems)
    print("Enter the tasks Id (1 to 5)")
    task = input("Enter 0 in order to exit:")
    print("\n")
    if try_covert_to_int(task) == ValueError:
        pass
    else:
        return int(task)


def main():
    task = 1
    while task != 0:
        task = setup()
        match task:
            case 0:
                print("Closing program...")
                break
            case 1:
                n = input("Enter the natural number: ")
                solve_task1(n)
            case 2:
                n = input("Enter the natural number: ")
                solve_task2(n)
            case 3:
                n = input("Enter the natural number: ")
                solve_task3(n)
            case 4:
                n = input("Enter the natural number: ")
                solve_task4(n)
            case 5:
                n = input("Enter the natural number: ")
                solve_task5(n)
            case _:
                print("Invalid problem Id")


if __name__ == '__main__':
    main()
