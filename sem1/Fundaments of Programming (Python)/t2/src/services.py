from src.domain import Address, Driver, AddressValidator, DriverValidator

class Service:
    def __init__(self, address_repo, driver_repo):
        self._address_repo = address_repo
        self._driver_repo = driver_repo

        with open("../addresses.txt", "r") as f:
            for line in f:
                if line:
                    parts = line.strip().split(",")
                    address = Address(int(parts[0]), parts[1], int(parts[2]), int(parts[3]))
                    self._address_repo.add(address)
        driver_id = 1
        with open("../drivers.txt", "r") as f:
            for line in f:
                if line:
                    parts = line.strip().split(",")
                    driver = Driver(driver_id, parts[0], int(parts[1]), int(parts[2]))
                    driver_id += 1
                    self._driver_repo.add(driver)


    def get_all_addresses(self):
        return self._address_repo.get_all()

    def get_all_drivers(self):
        return self._driver_repo.get_all()

    def find_address(self, address_id):
        return self._address_repo.find(address_id)

    def get_drivers_sorted_by_distance(self, address):
        drivers = self._driver_repo.get_all()
        drivers.sort(key=lambda x: abs(x.x - address.x) + abs(x.y - address.y))
        return drivers
