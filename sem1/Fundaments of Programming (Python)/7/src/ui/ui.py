from src.services.services import Services

class UI(object):
    def __init__(self, services):
        self.__services = services

    @staticmethod
    def print_menu():
        print("1. Add student")
        print("2. Show students")
        print("3. Filter students so the ones from a certain group are deleted")
        print("4. Undo")
        print("5. Exit")

    def run(self):
        while True:
            self.print_menu()
            command = input("Enter command: ")
            if command == "1":
                self.option1()
            elif command == "2":
                self.option2()
            elif command == "3":
                self.option3()
            elif command == "4":
                self.option4()
            elif command == "5":
                break
            else:
                print("Invalid command")

    def option1(self):
        try:
            student_id = input("Enter student ID: ")
            try:
                student_id = int(student_id)
            except ValueError:
                print("ID must be an integer")
                return
            name = input("Enter student name: ")
            group = input("Enter student group: ")
            try:
                group = int(group)
            except ValueError:
                print("Group must be an integer")
                return
            self.__services.add_student(student_id, name, group)
        except ValueError as ve:
            print(ve)
            return

    def option2(self):
        print(self.__services.print_students())

    def option3(self):
        try:
            group = input("Enter group: ")
            try:
                group = int(group)
            except ValueError:
                print("Group must be an integer")
                return
            self.__services.filter_students(group)
        except ValueError as ve:
            print(ve)
            return

    def option4(self):
        try:
            self.__services.undo_last_operation()
        except ValueError as ve:
            print(ve)
            return