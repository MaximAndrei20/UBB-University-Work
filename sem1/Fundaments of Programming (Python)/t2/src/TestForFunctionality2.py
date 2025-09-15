import unittest
from src.repository import Repository
from src.services import Service
from src.domain import Address, Driver

class TestForFunctionality2(unittest.TestCase):
    def tests(self):
        address_repo = Repository()
        driver_repo = Repository()
        service = Service(address_repo, driver_repo)
        addresses = []
        drivers = []
        with open("../addresses.txt", "r") as f:
            for line in f:
                if line:
                    parts = line.strip().split(",")
                    address = Address(int(parts[0]), parts[1], int(parts[2]), int(parts[3]))
                    addresses.append(address)

        with open("../drivers.txt", "r") as f:
            for line in f:
                d_id = 1
                if line:
                    parts = line.strip().split(",")
                    driver = Driver(d_id, parts[0], int(parts[1]), int(parts[2]))
                    d_id += 1
                    drivers.append(driver)
        for address in addresses:
            #for address in addresses: find(address.id) -> not None
            self.assertIsNotNone(service.find_address(address.id))

        address = service.find_address(1)
        drivers = service.get_drivers_sorted_by_distance(address)
        distances = [abs(driver.x - address.x) + abs(driver.y - address.y) for driver in drivers]
        for i in range(len(distances) - 1):
            self.assertLessEqual(distances[i], distances[i + 1])