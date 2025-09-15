import timeit
from random import randint

from texttable import Texttable


# function that tries to convert to int and returns error if not possible
def try_convert_to_int(var):
    try:
        int_var = int(var)
        return int_var
    except ValueError:
        return ValueError


# generates a list of n integers
def generate_list(n: int, lst: list) -> list:
    for i in range(n):
        lst.append(randint(0, 1000))
    return lst


# menu option 1
def option_1(lst: list):
    # read user input
    n = input("Enter the length of the list: ")

    # tries to convert input to int and prints
    # message to the user if not possible
    if try_convert_to_int(n) == ValueError:
        print("Invalid input")
        return
    if try_convert_to_int(n) <= 0:
        print("Invalid input")
        return
    n = int(n)
    # clearing the list of any elements from previous operations
    lst.clear()

    # generating list
    generate_list(n, lst)


# check if list is sorted
def is_sorted(lst: list) -> bool:
    for i in range(len(lst) - 1):
        if lst[i] > lst[i + 1]:
            return False
    return True


# checks if element is in list using recursive binary search
def binary_search_rec(lst: list, element: int, left: int, right: int) -> int:
    # check base case
    if right >= left:
        mid = (left + right) // 2
        #time.sleep(0.01)
        # element might be exactly in the middle
        if lst[mid] == element:
            return mid

        # if mid-element is less than target than check the subarray of the right
        elif lst[mid] < element:
            return binary_search_rec(lst, element, mid + 1, right)

        # otherwise check the left side
        else:
            return binary_search_rec(lst, element, left, mid - 1)

    # element not inside the list
    else:
        return -1


def option_2(lst: list):
    element = input("Enter element: ")
    # validates user input
    if try_convert_to_int(element) == ValueError:
        print("Invalid input")
        return
    element = int(element)

    # stores in position the index of the target element
    position = binary_search_rec(lst, element, 0, len(lst) - 1)

    # prints the position
    if position != -1:
        print(f"{element} is in the list at position {position + 1}")

    # element not in list
    else:
        print(f"{element} is not in the list.")


# sorts list using bubble sort and store if it reached desired "step" and the list at that time
def bubble_sort(lst: list, lstep: list, step: int):
    srt = False
    cnt = 0
    # while list is not sorted keep doing the loop
    while not srt:
        # suppose the list is sorted
        srt = True
        for i in range(0, len(lst) - 1):
            # check if element are not in the right order and swap them
            if lst[i] > lst[i + 1]:
                lst[i], lst[i + 1] = lst[i + 1], lst[i]

                # the list was not sorted
                srt = False
                cnt += 1

                # if we reached the desired step store the elements in a separate list
                """
                if cnt % step == 0:
                    templst = []
                    for j in range(0, len(lst)):
                        templst.append(lst[j])
                    lstep.append(templst)
                """
    reached_step = True
    # if the list is sorted before it reached the certain steps, set it to false
    if cnt < step:
        reached_step = False

    return lst, lstep, reached_step


def option_3(lst: list):
    step = 5#input("Enter step: ")
    # validates user input
    if try_convert_to_int(step) == ValueError:
        print("Invalid input")
        return
    if try_convert_to_int(step) < 0:
        print("Invalid input")
        return
    step = int(step)
    if step == 0:
        print("Bubble Sort step ", step, ": ", lst)
    lstep = []
    lst, lstep, reached_step = bubble_sort(lst, lstep, step)

    # print answer to user
    #if not reached_step:
    #    print(f"List was sorted before it reached {step} steps")
    #else:
    #    for i in range(len(lstep)):
    #        print(f"After {(i + 1) * step} operations the list is: {lstep[i]}.")
    return lst


def gnome_sort(lst: list, lstep: list, step: int):
    i = 0
    cnt = 0

    # keep checking until the end of the list is reached
    while i < len(lst):
        # if we are on the first element just move forward
        if i == 0:
            i += 1
        # if elements are in correct order move forward
        if lst[i] >= lst[i - 1]:
            i += 1
        # otherwise swap the elements and decrement the position to further check them
        else:
            lst[i], lst[i - 1] = lst[i - 1], lst[i]
            i -= 1
            cnt += 1

            # if we reached the desired step store the elements in a separate list
            """
            if cnt % step == 0:
                templst = []
                for j in range(0, len(lst)):
                    templst.append(lst[j])
                lstep.append(templst)
            """
    reached_step = True
    # if the list is sorted before it reached the certain steps, set it to false
    if cnt < step:
        reached_step = False
    return lst, lstep, reached_step


def option_4(lst: list):
    step = 5#input("Enter step: ")
    # validates user input
    if try_convert_to_int(step) == ValueError:
        print("Invalid input")
        return
    if try_convert_to_int(step) < 0:
        print("Invalid input")
        return
    step = int(step)
    if step == 0:
        print("Bubble Sort step ", step, ": ", lst)
    lstep = []
    lst, lstep, reached_step = gnome_sort(lst, lstep, step)

    # print answer to user
    #if not reached_step:
    #    print(f"List was sorted before it reached {step} steps.")
    #else:
    #   for i in range(len(lstep)):
    #        print(f"After {(i + 1) * step} operations the list is: {lstep[i]}.")
    return lst

def build_table_best_case(list_lengths: list):
    table = Texttable()
    table.add_row(['algorithm'] + list_lengths)

    #adding binary_search_rec to the table
    table_row = [binary_search_rec.__name__]
    for list_length in list_lengths:
        data = list(range(list_length))
        t1 = timeit.default_timer()
        # (list_length // 2) + 1 will be checked first
        binary_search_rec(data, list_length // 2 + 1, 0, len(data) - 1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)

    #adding bubble_sort to the table
    table_row = [bubble_sort.__name__]
    for list_length in list_lengths:
        data = list(range(list_length))
        t1 = timeit.default_timer()
        # already sorted list
        bubble_sort(data, [], -1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)


    #adding gnome sort to the table
    table_row = [gnome_sort.__name__]
    for list_length in list_lengths:
        data = list(range(list_length))
        t1 = timeit.default_timer()
        # already sorted list
        gnome_sort(data, [], -1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)
    return table

def option_5():
    list_lengths = [500, 1000, 2000, 4000, 8000]
    print(build_table_best_case(list_lengths).draw())

def build_table_average_case(list_lengths: list):
    table = Texttable()
    table.add_row(['algorithm'] + list_lengths)


    #adding binary_search_rec to the table
    table_row = [binary_search_rec.__name__]
    for list_length in list_lengths:
        data = list(range(list_length))
        t1 = timeit.default_timer()
        binary_search_rec(data, randint(0, len(data)), 0, len(data) - 1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)


    #adding bubble_sort to the table
    table_row = [bubble_sort.__name__]
    for list_length in list_lengths:
        #generating random list
        data = generate_list(list_length, [])
        t1 = timeit.default_timer()
        bubble_sort(data, [], -1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)


    #adding gnome sort to the table
    table_row = [gnome_sort.__name__]
    for list_length in list_lengths:
        #generating random list
        data = generate_list(list_length, [])
        t1 = timeit.default_timer()
        gnome_sort(data, [], -1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)
    return table

def option_6():
    list_lengths = [500, 1000, 2000, 4000, 8000]
    print(build_table_average_case(list_lengths).draw())

def build_table_worst_case(list_lengths: list):
    table = Texttable()
    table.add_row(['algorithm'] + list_lengths)

    #adding binary_search_rec to the table
    table_row = [binary_search_rec.__name__]
    for list_length in list_lengths:
        data = list(range(list_length))
        t1 = timeit.default_timer()
        # last element is among the ones that are checked last
        binary_search_rec(data, list_length-1, 0, len(data) - 1)
        t2 = timeit.default_timer() 
        table_row.append(t2 - t1)
    table.add_row(table_row)

    #adding bubble_sort to the table
    table_row = [bubble_sort.__name__]
    for list_length in list_lengths:
        data = list(range(list_length-1, -1, -1))
        t1 = timeit.default_timer()
        #list is sorted in reverse order
        bubble_sort(data, [], -1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)

    #adding gnome sort to the table
    table_row = [gnome_sort.__name__]
    for list_length in list_lengths:
        data = list(range(list_length-1, -1, -1))
        t1 = timeit.default_timer()
        #list is sorted in reverse order
        gnome_sort(data, [], -1)
        t2 = timeit.default_timer()
        table_row.append(t2 - t1)
    table.add_row(table_row)
    return table

def option_7():
    list_lengths = [500, 1000, 2000, 4000, 8000]
    print(build_table_worst_case(list_lengths).draw())

def test_bubble_sort():
    assert bubble_sort([3, 4, 2], [], 1) == ([2, 3, 4], [], True)
    assert bubble_sort([1, 2, 3], [], 1) == ([1, 2, 3], [], False)
    assert bubble_sort([5, -2, 4], [], 2) == ([-2, 4, 5], [], True)
    assert bubble_sort([1, 2, 3, 5, 4], [], 3) == ([1, 2, 3, 4, 5], [], False)

def test_gnome_sort():
    assert gnome_sort([3, 4, 2], [], 1) == ([2, 3, 4], [], True)
    assert gnome_sort([3, 4, 2], [], 2) == ([2, 3, 4], [], True)
    assert gnome_sort([5, -2, 4], [], 2) == ([-2, 4, 5], [], True)
    assert gnome_sort([4, 2, 3, 5, 1], [], 3) == ([1, 2, 3, 4, 5], [], True)

def test_binary_search_rec():
    assert binary_search_rec([1, 2, 3, 4, 5, 6], 2, 0, 5) == 1
    assert binary_search_rec([1, 2, 3, 4, 5, 6], 5, 0, 5) == 4
    assert binary_search_rec([1, 2, 3, 4, 5, 6], 8, 0, 5) == -1
    assert binary_search_rec([1, 2, 3, 4, 5, 6], 4, 0, 2) == -1
    assert binary_search_rec([1, 2, 3, 4, 5, 6], 1, 0, 2) == 0

def test_is_sorted():
    assert is_sorted([1, 2, 3, 7, 8, 9]) == True
    assert is_sorted([-2, 0, 2]) == True
    assert is_sorted([1, 3, 1]) == False

def test_try_convert_to_int():
    assert try_convert_to_int("123") == 123
    assert try_convert_to_int("fdsgdf") == ValueError
    assert try_convert_to_int("3.14") == ValueError

def print_menu():
    # prints menu to user
    print("1. Generate a list of n random natural numbers.")
    print("2. Search for an item in the list using the algorithm you implemented.")
    print("3. Sort the list using bubble sort.")
    print("4. Sort the list using gnome sort.")
    print("5. Check BEST case scenario for each algorithm's time complexity.")
    print("6. Check AVERAGE case scenario for each algorithm's time complexity.")
    print("7. Check WORST case scenario for each algorithm's time complexity.")
    print("0. Exit program.")


def main():
    test_binary_search_rec()
    test_is_sorted()
    test_gnome_sort()
    test_bubble_sort()
    test_try_convert_to_int()
    task = 1
    lst = []
    while task:
        print_menu()
        task = input("Select option: ")
        print("\n")

        # try to convert input to int
        if try_convert_to_int(task) == ValueError:
            pass
        else:
            task = int(task)

        # check each case
        match task:
            case 1:
                option_1(lst)
                if lst:
                    print(lst)
            case 2:
                # check if list is not empty
                if not lst:
                    print("Please generate a list and sort it first.")

                # check if list is sorted
                elif not is_sorted(lst):
                    print("Please sort the list first.")
                else:
                    option_2(lst)
            case 3:
                if not lst:
                    print("Please generate a list first.")
                else:
                    lst = option_3(lst)
                    if lst:
                        print(f"The sorted list is: {lst}.")
            case 4:
                if not lst:
                    print("Please generate a list first.")
                else:
                    lst = option_4(lst)
                    if lst:
                        print(f"The sorted list is: {lst}.")
            case 5:
                option_5()
            case 6:
                option_6()
            case 7:
                option_7()
            case 0:
                print("Closing program...")
                return
            case _:
                print("Invalid input")
        print("")


if __name__ == '__main__':
    main()

"""
    Binary Search Recursive:
        Best Case: O(1)
            - the element we want to search is exactly in the middle of the list
        Average Case: O(log(n))
            - each time we split the list into 2 and search in the half that contains the element
        Worst Case: O(log(n))
            - the element is either checked at the last search(split of the list) or it is not in the list
            
    Bubble Sort:
        Best Case: O(n)
            - the list is already sorted and we don't need to swap any elements
        Average Case: O(n^2)
            - the list is not sorted
        Worst Case: O(n^2)
            - the list is sorted in reverse order so each time it takes the maximum element and moves it to the back
    
    Gnome Sort:
        Best Case: O(n)
            - the list is already sorted and we don't need to swap any elements
        Average Case: O(n^2)
            - the list is not sorted
        Worst Case: O(n^2)
            - the list is sorted in reverse order so each time it takes the following element and brings it all the way to the front
"""