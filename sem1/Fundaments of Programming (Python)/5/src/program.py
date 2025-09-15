# No. 2
# Write the implementation for A5 in this file
#
import re


#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def initialize(complex_numbers):
    return []


def add_initial_numbers(list_of_complex_numbers):
    list_of_complex_numbers.append([-1, 2])
    list_of_complex_numbers.append([3, -4])
    list_of_complex_numbers.append([-5, -6])
    list_of_complex_numbers.append([-5, -7])
    list_of_complex_numbers.append([7, 5])
    list_of_complex_numbers.append([0, 0])
    list_of_complex_numbers.append([0, 1])


def add_a_complex_number(complex_number, list_of_complex_numbers):
    list_of_complex_numbers.append(complex_number)


def format_complex_number(real, imag):
    if imag == 0:
        return f"{real}"
    elif real == 0:
        if imag == 1:
            return "i"
        elif imag == -1:
            return "-i"
        else:
            return f"{imag}i"
    elif imag == 1:
        return f"{real}+i"
    elif imag == -1:
        return f"{real}-i"
    elif imag > 0:
        return f"{real}+{imag}i"
    else:
        return f"{real}{imag}i"


def add_numbers_to_string_to_print(string, complex_numbers):
    formatted_numbers = []
    for real, imag in complex_numbers:
        formatted_numbers.append(format_complex_number(int(real), imag))
    string += ", ".join(formatted_numbers)
    return string


#   Set A -> Display a longest subarray of numbers having the same modulus.
def solve_problem_A(complex_numbers):
    counter = 0
    max_subarray_length = -1
    start_max_subarray_pos = -1
    last_modulus = -1
    for complex_number in complex_numbers:
        if modulus(complex_number) == last_modulus:
            counter += 1
        else:
            if counter > max_subarray_length:
                max_subarray_length = counter
                start_max_subarray_pos = complex_numbers.index(complex_number) - counter
            counter = 1
            last_modulus = modulus(complex_number)

    result = ""
    for i in range(start_max_subarray_pos, start_max_subarray_pos + max_subarray_length):
        result += format_complex_number(complex_numbers[i][0], complex_numbers[i][1]) + " "
    return result.strip()


def solve_problem_B(complex_numbers):
    n = len(complex_numbers)
    if n == 0:
        return ""

    # Initialize the dp array where dp[i] will store the length of the longest increasing subsequence ending at index i
    dp = [1] * n
    # To reconstruct the subsequence, we need to keep track of the previous index
    prev = [-1] * n

    # Fill the dp array
    for i in range(1, n):
        for j in range(i):
            if complex_numbers[i][0] > complex_numbers[j][0] and dp[i] < dp[j] + 1:
                dp[i] = dp[j] + 1
                prev[i] = j

    # Find the index of the maximum value in dp
    max_index = 0
    for i in range(1, n):
        if dp[i] > dp[max_index]:
            max_index = i

    # Reconstruct the longest increasing subsequence
    lis = []
    while max_index != -1:
        lis.append(complex_numbers[max_index])
        max_index = prev[max_index]

    # Reverse the list to get the correct order
    lis.reverse()

    # Format the result as a string
    result = ""
    for real, imag in lis:
        result += format_complex_number(real, imag) + " "
    return result.strip()

def test_parse_complex_number():
    assert parse_complex_number("1+2i") == [1, 2]
    assert parse_complex_number("1-2i") == [1, -2]
    assert parse_complex_number("-1+2i") == [-1, 2]
    assert parse_complex_number("-1-2i") == [-1, -2]
    assert parse_complex_number("0+2i") == [0, 2]
    assert parse_complex_number("0-2i") == [0, -2]
    assert parse_complex_number("1+1i") == [1, 1]
    assert parse_complex_number("1-1i") == [1, -1]
    assert parse_complex_number("-1+1i") == [-1, 1]
    assert parse_complex_number("-1-1i") == [-1, -1]
    assert parse_complex_number("0+1i") == [0, 1]
    assert parse_complex_number("0-1i") == [0, -1]
    assert parse_complex_number("1+0i") == [1, 0]
    assert parse_complex_number("-1+0i") == [-1, 0]

def test_add_numbers_to_string_to_print():
    assert add_numbers_to_string_to_print("", [[1, 2], [3, 4], [5, 6]]) == "1+2i, 3+4i, 5+6i"
    assert add_numbers_to_string_to_print("", [[1, 2]]) == "1+2i"
    assert add_numbers_to_string_to_print("", []) == ""

def test_format_complex_number():
    assert format_complex_number(1, 2) == "1+2i"
    assert format_complex_number(1, -2) == "1-2i"
    assert format_complex_number(-1, 2) == "-1+2i"
    assert format_complex_number(-1, -2) == "-1-2i"
    assert format_complex_number(0, 2) == "2i"
    assert format_complex_number(0, -2) == "-2i"
    assert format_complex_number(1, 1) == "1+i"
    assert format_complex_number(1, -1) == "1-i"
    assert format_complex_number(-1, 1) == "-1+i"
    assert format_complex_number(-1, -1) == "-1-i"
    assert format_complex_number(0, 1) == "i"
    assert format_complex_number(0, -1) == "-i"
    assert format_complex_number(1, 0) == "1"
    assert format_complex_number(-1, 0) == "-1"
    assert format_complex_number(0, 0) == "0"

def test_functions():
    test_parse_complex_number()
    test_add_numbers_to_string_to_print()
    test_format_complex_number()


#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

# def initialize(self):
#     return {}
#
# def add_initial_numbers(complex_numbers):
#     complex_numbers.setdefault('-1', []).append(2)
#     complex_numbers.setdefault('3', []).append(-4)
#     complex_numbers.setdefault('-5', []).append(-6)
#     complex_numbers.setdefault('-5', []).append(-7)
#     complex_numbers.setdefault('0', []).append(0)
#     complex_numbers.setdefault('0', []).append(1)
#
#
# def add_a_complex_number(complex_number: list, complex_numbers: dict):
#     complex_numbers.setdefault(str(complex_number[0]), []).append(complex_number[1])
#
# def format_complex_number(real, imag):
#     if imag == 0:
#         return f"{real}"
#     elif real == 0:
#         if imag == 1:
#             return "i"
#         elif imag == -1:
#             return "-i"
#         else:
#             return f"{imag}i"
#     elif imag == 1:
#         return f"{real}+i"
#     elif imag == -1:
#         return f"{real}-i"
#     elif imag > 0:
#         return f"{real}+{imag}i"
#     else:
#         return f"{real}{imag}i"
#
# def add_numbers_to_string_to_print(string, complex_numbers):
#     formatted_numbers = []
#     for real, imag_list in complex_numbers.items():
#         for imag in imag_list:
#             formatted_numbers.append(format_complex_number(int(real), imag))
#     string += ", ".join(formatted_numbers)
#     return string
#
# def convert_dict_to_list(complex_numbers):
#     result = []
#     for real, imag_list in complex_numbers.items():
#         for imag in imag_list:
#             result.append([int(real), imag])
#     return result
#
# #   Set A -> Display a longest subarray of numbers having the same modulus.
# def solve_problem_A(complex_numbers):
#     complex_numbers = convert_dict_to_list(complex_numbers)
#     counter = 0
#     max_subarray_length = -1
#     start_max_subarray_pos = -1
#     last_modulus = -1
#     for complex_number in complex_numbers:
#         if modulus(complex_number) == last_modulus:
#             counter += 1
#         else:
#             if counter > max_subarray_length:
#                 max_subarray_length = counter
#                 start_max_subarray_pos = complex_numbers.index(complex_number) - counter
#             counter = 1
#             last_modulus = modulus(complex_number)
#
#     result = ""
#     for i in range(start_max_subarray_pos, start_max_subarray_pos + max_subarray_length):
#         result += format_complex_number(complex_numbers[i][0], complex_numbers[i][1]) + " "
#     return result.strip()
#
#
# def solve_problem_B(complex_numbers):
#     complex_numbers = convert_dict_to_list(complex_numbers)
#     n = len(complex_numbers)
#     if n == 0:
#         return ""
#
#     # Initialize the dp array where dp[i] will store the length of the longest increasing subsequence ending at index i
#     dp = [1] * n
#     # To reconstruct the subsequence, we need to keep track of the previous index
#     prev = [-1] * n
#
#     # Fill the dp array
#     for i in range(1, n):
#         for j in range(i):
#             if complex_numbers[i][0] > complex_numbers[j][0] and dp[i] < dp[j] + 1:
#                 dp[i] = dp[j] + 1
#                 prev[i] = j
#
#     # Find the index of the maximum value in dp
#     max_index = 0
#     for i in range(1, n):
#         if dp[i] > dp[max_index]:
#             max_index = i
#
#     # Reconstruct the longest increasing subsequence
#     lis = []
#     while max_index != -1:
#         lis.append(complex_numbers[max_index])
#         max_index = prev[max_index]
#
#     # Reverse the list to get the correct order
#     lis.reverse()
#
#     # Format the result as a string
#     result = ""
#     for real, imag in lis:
#         result += format_complex_number(real, imag) + " "
#     return result.strip()
#
# def test_convert_dict_to_list():
#     complex_numbers = {'1': [2, 3], '4': [5, 6]}
#     assert convert_dict_to_list(complex_numbers) == [[1, 2], [1, 3], [4, 5], [4, 6]]
#     complex_numbers = {}
#     assert convert_dict_to_list(complex_numbers) == []
#     complex_numbers = {'1': [2]}
#     assert convert_dict_to_list(complex_numbers) == [[1, 2]]
#
# def test_parse_complex_number():
#     assert parse_complex_number("1+2i") == [1, 2]
#     assert parse_complex_number("1-2i") == [1, -2]
#     assert parse_complex_number("-1+2i") == [-1, 2]
#     assert parse_complex_number("-1-2i") == [-1, -2]
#     assert parse_complex_number("0+2i") == [0, 2]
#     assert parse_complex_number("0-2i") == [0, -2]
#     assert parse_complex_number("-1+1i") == [-1, 1]
#     assert parse_complex_number("-1-1i") == [-1, -1]
#     assert parse_complex_number("0+1i") == [0, 1]
#     assert parse_complex_number("0-1i") == [0, -1]
#
# def test_add_numbers_to_string_to_print():
#     assert add_numbers_to_string_to_print("", {'1': [2, 3], '4': [5, 6]}) == "1+2i, 1+3i, 4+5i, 4+6i"
#     assert add_numbers_to_string_to_print("", {'1': [2]}) == "1+2i"
#     assert add_numbers_to_string_to_print("", {}) == ""
#
# def test_format_complex_number():
#     assert format_complex_number(1, 2) == "1+2i"
#     assert format_complex_number(1, -2) == "1-2i"
#     assert format_complex_number(-1, 2) == "-1+2i"
#     assert format_complex_number(-1, -2) == "-1-2i"
#     assert format_complex_number(0, 2) == "2i"
#     assert format_complex_number(0, -2) == "-2i"
#     assert format_complex_number(1, 1) == "1+i"
#     assert format_complex_number(1, -1) == "1-i"
#     assert format_complex_number(-1, 1) == "-1+i"
#     assert format_complex_number(-1, -1) == "-1-i"
#     assert format_complex_number(0, 1) == "i"
#     assert format_complex_number(0, -1) == "-i"
#     assert format_complex_number(1, 0) == "1"
#     assert format_complex_number(-1, 0) == "-1"
#     assert format_complex_number(0, 0) == "0"
#
# def test_functions():
#     test_convert_dict_to_list()
#     test_parse_complex_number()
#     test_add_numbers_to_string_to_print()
#     test_format_complex_number()




#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def modulus(complex_number: list) -> float:
    return (complex_number[0] ** 2 + complex_number[1] ** 2) ** 0.5


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def parse_complex_number(complex_str):
    match = re.match(r'([-+]?\d+)([-+]\d+)i', complex_str)
    if match:
        real_part = int(match.group(1))
        imag_part = int(match.group(2))
        return [real_part, imag_part]
    else:
        raise ValueError("Invalid complex number format")

def read_list_of_complex_numbers(complex_numbers):
    print(
        "Enter a list of complex numbers separated by a comma(a complex number should be of form a+bi, where a and b are integers): ")
    user_input = input("\n")
    new_complex_numbers = user_input.split(",")
    for complex_number in new_complex_numbers:
        parsed_number = parse_complex_number(complex_number.strip())
        add_a_complex_number(parsed_number, complex_numbers)


def option_1(complex_numbers):
    read_list_of_complex_numbers(complex_numbers)


def option_2(complex_numbers):
    string_to_print = ""
    string_to_print = add_numbers_to_string_to_print(string_to_print, complex_numbers)
    print(string_to_print)


def option_3(complex_numbers):
    print("The longest subarray of numbers having the same modulus is: ", end="")
    string_to_print = solve_problem_A(complex_numbers)
    print(string_to_print)
    print("\n\nThe longest increasing subsequence, when considering each number's real part is: ", end="")
    string_to_print = solve_problem_B(complex_numbers)
    print(string_to_print)
    print("\n")


def print_menu():
    print("1. Read a list of complex numbers")
    print("2. Display the list of complex numbers")
    print("3. Set A -> Display a longest subarray of numbers having the same modulus.")
    print("   Set B -> Display a longest increasing subsequence, when considering each number's real part.")
    print("4. Exit")


def main():
    test_functions()

    complex_numbers = []
    complex_numbers = initialize(complex_numbers)
    add_initial_numbers(complex_numbers)

    while True:
        print_menu()
        option = input("Enter option: ")
        match option:
            case "1":
                print()
                option_1(complex_numbers)
                print()
            case "2":
                print()
                option_2(complex_numbers)
                print()
            case "3":
                print()
                option_3(complex_numbers)
                print()
            case "4":
                print("Exiting program...\n")
                return
            case _:
                print("Invalid option\n")


if __name__ == "__main__":
    main()
