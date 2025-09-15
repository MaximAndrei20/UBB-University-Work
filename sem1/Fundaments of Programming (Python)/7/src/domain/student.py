class Student:
    """
    A class to represent a student.

    Attributes:
    ----------
    student_id : int
        The unique identifier for the student.
    name : str
        The name of the student.
    group : int
        The group number of the student.
    """

    def __init__(self, student_id, name, group):
        """
        Constructs all the necessary attributes for the student object.

        Parameters:
        ----------
        student_id : int
            The unique identifier for the student.
        name : str
            The name of the student.
        group : int
            The group number of the student. Must be a positive integer.
        """
        if group < 0:
            raise ValueError("Group must be a positive integer")

        self.__id = student_id
        self.__name = name
        self.__group = group

    @property
    def student_id(self):
        """
        Gets the student's ID.

        Returns:
        -------
        int
            The unique identifier for the student.
        """
        return self.__id

    @property
    def name(self):
        """
        Gets the student's name.

        Returns:
        -------
        str
            The name of the student.
        """
        return self.__name

    @property
    def group(self):
        """
        Gets the student's group number.

        Returns:
        -------
        int
            The group number of the student.
        """
        return self.__group

    def __str__(self):
        """
        Returns a string representation of the student.

        Returns:
        -------
        str
            A string representation of the student.
        """
        return f"ID: {self.student_id}, Name: {self.name}, Group: {self.group}"