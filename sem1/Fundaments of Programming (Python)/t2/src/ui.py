class UI:
    def __init__(self, service):
        self._service = service

    @staticmethod
    def print_menu():
        print("1. Display all addresses and drivers sorted by name")
        print("2. For an address given print drivers sorted by distance to that address (d(<x1,y1>,<x2,y2>) = abs(x1-x2) + abs(y1-y2))")
        print("3. For each address print the driver closest to it alongside the driver's information."
              "Sort the list in decreasing order of the distance between each address and driver pair. Use the same distance formula")

    def display_all(self):
        addresses = self._service.get_all_addresses()
        drivers = self._service.get_all_drivers()
        addresses.sort(key=lambda x: x.name)
        drivers.sort(key=lambda x: x.name)
        print("Addresses:")
        for address in addresses:
            print(address)
        print("\nDrivers:")
        for driver in drivers:
            print(driver)

    def display_drivers(self):
        address_id = input("Enter address id: ")
        try:
            address_id = int(address_id)
        except ValueError:
            print("Invalid id!")
            return
        address = self._service.find_address(address_id)
        if address is None:
            print("Address not found!")
            return
        drivers = self._service.get_drivers_sorted_by_distance(address)
        print("Drivers sorted by distance:")
        for driver in drivers:
            print(driver)

    def display_closest(self):
        addresses = self._service.get_all_addresses()
        drivers = self._service.get_all_drivers()
        addresses.sort(key=lambda x: x.name)
        drivers.sort(key=lambda x: x.name)
        # print("Closest drivers to each address:")
        # for address in addresses:
        #     #find min distance driver
        #     min_distance = 9999999
        #     closest_driver = None
        #     for driver in drivers:
        #         distance = abs(driver.x - address.x) + abs(driver.y - address.y)
        #         if distance < min_distance:
        #             min_distance = distance
        #             closest_driver = driver
        #
        #
        #     #drivers.sort(key=lambda x: abs(x.x - address.x) + abs(x.y - address.y))
        #     print(f'Address: {address.name},', end=' ')
        #     driver = closest_driver
        #     print(f'Closest Driver: {driver} - distance: {abs(driver.x - address.x) + abs(driver.y - address.y)}')
        address_driver_distance = []
        for address in addresses:
            min_distance = 9999999
            closest_driver = None
            for driver in drivers:
                distance = abs(driver.x - address.x) + abs(driver.y - address.y)
                if distance < min_distance:
                    min_distance = distance
                    closest_driver = driver
            address_driver_distance.append((address, closest_driver, min_distance))
        #sort this list in descending order by distance and print
        address_driver_distance.sort(key=lambda x: x[2], reverse=True)
        print("Sorted by distance:")
        for address, driver, distance in address_driver_distance:
            print(f'Address: {address.name}, Closest Driver: {driver.name}, x-coordinate = {driver.x}, y-coordinate = {driver.y} - distance: {distance}')


    def run(self):
        while True:
            self.print_menu()
            command = input("Enter command: ")
            match command:
                case "1":
                    self.display_all()
                case "2":
                    self.display_drivers()
                case "3":
                    self.display_closest()
                case "exit":
                    break
                case _:
                    print("Invalid command!")
                    continue

