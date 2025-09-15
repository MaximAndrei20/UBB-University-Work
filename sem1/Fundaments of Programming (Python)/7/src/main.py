from src.ui.ui import UI
from src.services.services import Services
from src.repository.memory_repository import MemoryRepository
from src.repository.text_file_repository import TextFileRepository
from src.repository.binary_file_repository import BinaryFileRepository

def generate_students(services):
    """
    Generate a list of students and add them to the services.

    :param services: The services object to add students to.
    """
    services.add_student(1, "Ana", 911)
    services.add_student(2, "Andrei", 913)
    services.add_student(3, "George", 912)
    services.add_student(4, "Mihai", 911)
    services.add_student(5, "Maria", 912)
    services.add_student(6, "Ion", 913)
    services.add_student(7, "Diana", 911)
    services.add_student(8, "Alex", 912)
    services.add_student(9, "Cristina", 913)
    services.add_student(10, "Marius", 911)

if __name__ == "__main__":
    # Choose the repository type
    repo_type = input("Enter repository type (memory/text/binary): ").strip().lower()

    if repo_type == "memory":
        repository = MemoryRepository()
    elif repo_type == "text":
        filename = "students.txt"
        repository = TextFileRepository(filename)
    elif repo_type == "binary":
        filename = "students.bin"
        repository = BinaryFileRepository(filename)
    else:
        print("Invalid repository type")
        exit(1)

    services = Services(repository)
    if repo_type == "memory":
        generate_students(services)

    ui = UI(services)
    ui.run()