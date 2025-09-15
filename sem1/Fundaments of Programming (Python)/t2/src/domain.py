class Address:
    def __init__(self, address_id, name, x_coord, y_coord):
        self._id = address_id
        self._name = name
        self._x_coord = x_coord
        self._y_coord = y_coord

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def x(self):
        return self._x_coord

    @property
    def y(self):
        return self._y_coord

    def __str__(self):
        return f'{self.id},{self.name},{self.x},{self.y}'

class Driver:
    def __init__(self, driver_id, name, x_coord, y_coord):
        self._id = driver_id
        self._name = name
        self._x_coord = x_coord
        self._y_coord = y_coord

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def x(self):
        return self._x_coord

    @property
    def y(self):
        return self._y_coord

    def __str__(self):
        return f'{self.name},{self.x},{self.y}'

class AddressValidator:
    @staticmethod
    def validate(address):
        if not isinstance(address.id,int) or not isinstance(address.name,str) or not isinstance(address.x,int) or not isinstance(address.y,int):
            raise ValueError("Invalid address!")
        if address.id < 0:
            raise ValueError("Invalid id!")
        if address.name == "":
            raise ValueError("Invalid name!")
        if address.x < 0:
            raise ValueError("Invalid x coordinate!")
        if address.y < 0:
            raise ValueError("Invalid y coordinate!")

class DriverValidator:
    @staticmethod
    def validate(driver):
        if not isinstance(driver.id,int) or not isinstance(driver.name,str) or not isinstance(driver.x,int) or not isinstance(driver.y,int):
            raise ValueError("Invalid driver!")
        if driver.id < 0:
            raise ValueError("Invalid id!")
        if driver.name == "":
            raise ValueError("Invalid name!")
        if driver.x < 0:
            raise ValueError("Invalid x coordinate!")
        if driver.y < 0:
            raise ValueError("Invalid y coordinate!")