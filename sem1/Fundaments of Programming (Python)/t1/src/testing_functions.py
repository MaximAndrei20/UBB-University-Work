from functions import *

def test_delete_flight():
    flights = [("123", 45, "cluj", "londra"), ("abc", 25, "bucuresti", "iasi"), ("xyz", 30, "iasi", "cluj"), ("def", 40, "iasi", "londra"), ("ghi", 35, "cluj", "iasi")]
    delete_flight("123", flights)
    assert len(flights) == 4
    assert flights == [("abc", 25, "bucuresti", "iasi"), ("xyz", 30, "iasi", "cluj"), ("def", 40, "iasi", "londra"), ("ghi", 35, "cluj", "iasi")]

    delete_flight("abc", flights)
    assert len(flights) == 3
    assert flights == [("xyz", 30, "iasi", "cluj"), ("def", 40, "iasi", "londra"), ("ghi", 35, "cluj", "iasi")]