# Solve the problem from the third set here
"""
12. Determine the age of a person, in number of days. Take into account leap years, as well as the date of birth and current date `(year, month, day)`. Do not use Python's inbuilt date/time functions.
13. Determine the `n-th`  element of the sequence `1,2,3,2,5,2,3,7,2,3,2,5,...` obtained from the sequence of natural numbers by replacing composed numbers with their prime divisors, without memorizing the elements of the sequence.
14. Determine the `n-th` element of the sequence `1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,...` obtained from the sequence of natural numbers by replacing composed numbers with their prime divisors, each divisor `d` being written `d` times, without memorizing the elements of the sequence.
15. Generate the largest perfect number smaller than a given natural number `n`. If such a number does not exist, a message should be displayed. A number is perfect if it is equal to the sum of its divisors, except itself. (e.g.  `6 is a perfect number, as 6=1+2+3`).
"""

#probelm no. 15
def is_perfect(n : int) -> bool:
    sum_divisors=1
    #getting all of n's divisors and adding them to a sum
    #we are only going up to the square root of n because if we find d to be a divisor of n then n/d also is a divisor of n
    for d in range(2, int(n**0.5)+1):
        if n % d == 0:
            sum_divisors += d + n/d
    # returning True for n perfect, False otherwise
    return sum_divisors == n

def solve_task15():
    #getting input from user
    n = input("Please enter a natural number: ")
    try:
        #checking if the input is an integer
        n=int(n)
        #checking if input is positive
        if n < 0:
            print("Please enter a natural number")
        found = False
        #itterating through every number smaller than n and checking if it is perfect
        for i in range(n-1,1, -1):
            if is_perfect(i):
                print(i)
                found = True
                break
        if not found:
            print("No solution")
    except ValueError:
        print("Please enter a natural number!")

def main():
    solve_task15()

if __name__ == '__main__':
    main()