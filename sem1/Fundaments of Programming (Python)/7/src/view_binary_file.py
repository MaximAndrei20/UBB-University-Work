import pickle
from src.domain.student import Student

def view_binary_file(filename):
    with open(filename, 'rb') as file:
        students = pickle.load(file)
        for student in students:
            print(f"ID: {student.student_id}, Name: {student.name}, Group: {student.group}")

if __name__ == "__main__":
    view_binary_file('students.bin')