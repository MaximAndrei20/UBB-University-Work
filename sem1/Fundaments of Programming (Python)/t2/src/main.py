from src.repository import Repository
from src.ui import UI
from src.services import Service

def main():
    address_repo = Repository()
    driver_repo = Repository()
    service = Service(address_repo, driver_repo)
    ui = UI(service)
    ui.run()


if __name__ == "__main__":
    main()