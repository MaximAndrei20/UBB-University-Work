"""
6. Determine a calendar date (as year, month, day) starting from two integer numbers representing the year and the day number inside that year (e.g. day number 32 is February 1st). Take into account leap years. Do not use Python's inbuilt date/time functions.
7. Determine the twin prime numbers p1 and p2 immediately larger than the given non-null natural number n. Two prime numbers p and q are called twin if q - p = 2.
8. Find the smallest number m from the Fibonacci sequence, defined by f[0]=f[1]=1, f[n]=f[n-1] + f[n-2], for n > 2, larger than the given natural number n. (e.g. for n = 6, m = 8).
9. Consider a given natural number n. Determine the product p of all the proper factors of n.
10. The palindrome of a number is the number obtained by reversing the order of its digits (e.g. the palindrome of 237 is 732). For a given natural number n, determine its palindrome.
11. The numbers n1 and n2 have the property P if their writing in base 10 uses the same digits (e.g. 2113 and 323121). Determine whether two given natural numbers have property P.
"""

from p1 import isprime
from p1 import try_covert_to_int

#start task6
#checks if it is a leap year and returns true or false accordingly
def is_leap_year(year):
    if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
        return True
    return False

def day_to_date(year, day):
    #creating an array to store the days of each month
    months = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    #if year is leap february has 29 days
    if is_leap_year(year):
        months[1] = 29


    #itterating through the months in order to find the day and month
    month = 0
    while day > months[month]:
        day -= months[month]
        month += 1

    #returns answer
    return year, month + 1, day

def solve_task6():
    year = input("Enter the year: ")
    #checking if year input is correct
    if try_covert_to_int(year) == ValueError:
        print("Invalid year input")
        return
    elif try_covert_to_int(year) < 0:
        print("Invalid year input")
        return
    else:
        year = int(year)

    # checking if day input is correct
    day = input("Enter the day: ")
    if try_covert_to_int(day) == ValueError:
        print("Invalid day input")
        return
    elif try_covert_to_int(day) < 0:
        print("Invalid year input")
        return
    else:
        day = int(day)

    year, month, day = day_to_date(year, day)

    #printing answer to console
    print(f"year: {year} | month: {month} | day: {day}")

#end task6

#start task7
def solve_task7():
    n = input("Enter a natural number: ")
    #checking if input is valid
    if try_covert_to_int(n) == ValueError:
        print("Invalid input")
        return
    if try_covert_to_int(n) <= 0:
        print("Invalid input")
        return
    n = int(n)

    #initializing p and q such that q-p=2 and then incrementing them until both are prime
    p = n+1
    q = n+3
    while not isprime(p) or not isprime(q):
        p+=1
        q+=1
    print(f"The twin primes greater than {n} are {p} and {q}")
#end task7

#start task8
def solve_task8():
    n = input("Enter a natural number: ")
    #checking if input is valid
    if try_covert_to_int(n) == ValueError:
        print("Invalid input")
        return
    if try_covert_to_int(n) <= 2:
        print("Invalid input")
        return
    n = int(n)
    a=1
    b=2
    while b < n:
        b=b+a
        a=b-a
    print(f"The smallest number from the Fibonacci sequence larger than {n} is {b}")
#end task8

#start task9
def solve_task9():
    n = input("Enter a natural number: ")
    if try_covert_to_int(n) == ValueError:
        print("Invalid input")
        return
    if try_covert_to_int(n) <= 0:
        print("Invalid input")
        return
    n = int(n)
    product = 1
    for d in range(2, n // 2 +1):
        if n % d == 0:
            product *= d
    if product == 1:
        print(f"{n} is a prime number so it doesn't have proper factors.")
    else:
        print(f"The product of all the proper factors of {n} is {product}")
#end task9

#start task10
def solve_task10():
    n = input("Enter a natural number: ")
    if try_covert_to_int(n) == ValueError:
        print("Invalid input")
        return
    if try_covert_to_int(n) <= 0:
        print("Invalid input")
        return
    n = int(n)
    m = n
    palindrome = 0
    while n:
        palindrome = palindrome*10 + n%10
        n //=10
    print(f"The palindrome of {m} is {palindrome}")
#end task10

#start task11
def solve_task11():
    n = input("Enter first natural number: ")
    if try_covert_to_int(n) == ValueError:
        print("Invalid input")
        return
    if try_covert_to_int(n) <= 0:
        print("Invalid input")
        return
    n = int(n)
    m = input("Enter second natural number: ")
    if try_covert_to_int(m) == ValueError:
        print("Invalid input")
        return
    if try_covert_to_int(m) <= 0:
        print("Invalid input")
        return
    m = int(m)

    digitsN = []
    digitsM = []
    P = True
    while n:
        if n%10 not in digitsN:
            digitsN.append(int(n%10))
        n //= 10
    while m:
        if m%10 not in digitsM:
            digitsM.append(int(m%10))
        m //= 10
    digitsN.sort()
    digitsM.sort()
    if digitsN != digitsM:
        P = False
    if P:
        print("The numbers have the property P")
    else:
        print("The numbers do NOT have the property P")

#end task11

def setup():
    print("\n")
    problems = "6. Determine a calendar date (as year, month, day) starting from two integer numbers representing the year and the day number inside that year (e.g. day number 32 is February 1st). Take into account leap years. Do not use Python's inbuilt date/time functions.\n7. Determine the twin prime numbers p1 and p2 immediately larger than the given non-null natural number n. Two prime numbers p and q are called twin if q - p = 2.\n8. Find the smallest number m from the Fibonacci sequence, defined by f[0]=f[1]=1, f[n]=f[n-1] + f[n-2], for n > 2, larger than the given natural number n. (e.g. for n = 6, m = 8).\n9. Consider a given natural number n. Determine the product p of all the proper factors of n.\n10. The palindrome of a number is the number obtained by reversing the order of its digits (e.g. the palindrome of 237 is 732). For a given natural number n, determine its palindrome.\n11. The numbers n1 and n2 have the property P if their writing in base 10 uses the same digits (e.g. 2113 and 323121). Determine whether two given natural numbers have property P."
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
            case 6:
                solve_task6()
            case 7:
                solve_task7()
            case 8:
                solve_task8()
            case 9:
                solve_task9()
            case 10:
                solve_task10()
            case 11:
                solve_task11()
            case _:
                print("Invalid problem Id")


if __name__ == '__main__':
    main()