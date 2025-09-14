//#include "Tests.h"
//#include <assert.h>
//#include <exception>
//#include <stdexcept>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <iostream>
//#include "Service.h"
//
//void Tests::testAddEvent()
//{
//	// Create a repository and a service
//	Repository repo;
//	Repository userRepo;
//	Service service(repo, userRepo);
//	// Add an event to the repository
//	service.addEvent("Test Event", "This is a test event", std::chrono::system_clock::now(), 10, "http://test.com");
//	// Check if the event was added correctly
//	std::vector<Event> events = service.getEvents();
//	assert(events.size() == 1);
//	assert(events[0].getTitle() == "Test Event");
//	assert(events[0].getDescription() == "This is a test event");
//	assert(events[0].getNumberOfPeople() == 10);
//	assert(events[0].getLink() == "http://test.com");
//}
//
//void Tests::testDeleteEvent()
//{
//	// Create a repository and a service
//	Repository repo;
//	Repository userRepo;
//	Service service(repo, userRepo);
//	// Add an event to the repository
//	service.addEvent("Test Event", "This is a test event", std::chrono::system_clock::now(), 10, "http://test.com");
//	// Delete the event
//	service.deleteEvent("Test Event");
//	// Check if the event was deleted correctly
//	std::vector<Event> events = service.getEvents();
//	assert(events.size() == 0);
//
//	try {
//		service.deleteEvent("1234event");
//		assert(false);
//	}
//	catch (std::exception e){}
//}
//
//void Tests::testEventSetters()
//{
//	Event e{ "Test Event", "This is a test event", std::chrono::system_clock::now(), 10, "http://test.com" };
//	e.setTitle("New Title");
//	e.setDescription("New Description");
//	e.setNumberOfPeople(1);
//	e.setLink("New Link");
//	e.setDateTime(std::chrono::system_clock::now());
//	auto time = e.getDateTime();
//	assert(e.getTitle() == "New Title");
//	assert(e.getDescription() == "New Description");
//	assert(e.getDateTime() == time);
//	assert(e.getNumberOfPeople() == 1);
//	assert(e.getLink() == "New Link");
//	
//}
//
//void Tests::testToString()
//{
//	Event e{ "Test Event", "This is a test event", std::chrono::system_clock::now(), 10, "http://test.com" };
//	std::string str = e.toString();
//	assert(str.find("Test Event") != std::string::npos);
//	assert(str.find("This is a test event") != std::string::npos);
//	assert(str.find("10") != std::string::npos);
//	assert(str.find("http://test.com") != std::string::npos);
//}
//
//void Tests::testRepo()
//{
//	// Create a repository and a service
//	Repository repo;
//	Repository userRepo;
//	Service service(repo, userRepo);
//	// Add an event to the repository
//	service.addEvent("Test Event", "This is a test event", std::chrono::system_clock::now(), 10, "http://test.com");
//	// Check if the event was added correctly
//	std::vector<Event> events = service.getEvents();
//	assert(events.size() == 1);
//	assert(events[0].getTitle() == "Test Event");
//	assert(events[0].getDescription() == "This is a test event");
//	assert(events[0].getNumberOfPeople() == 10);
//	assert(events[0].getLink() == "http://test.com");
//}
//
//void testAddEventToData() {
//    Repository repo;
//    Event event("Test Event", "Description", std::chrono::system_clock::now(), 100, "http://test.com");
//    repo.addEventToData(event);
//
//    std::vector<Event> events = repo.getEventsForMonth(0); // Get all events
//    assert(events.size() == 1);
//    assert(events[0].getTitle() == "Test Event");
//    assert(events[0].getDescription() == "Description");
//    assert(events[0].getNumberOfPeople() == 100);
//    assert(events[0].getLink() == "http://test.com");
//}
//
//void testDeleteEvent() {
//    Repository repo;
//    Event event("Test Event", "Description", std::chrono::system_clock::now(), 100, "http://test.com");
//    repo.addEventToData(event);
//
//    repo.deleteEvent("Test Event");
//    std::vector<Event> events = repo.getEventsForMonth(0); // Get all events
//    assert(events.size() == 0);
//
//    try {
//        repo.deleteEvent("Nonexistent Event");
//        assert(false); // Should not reach here
//    }
//    catch (const std::runtime_error& e) {
//        assert(std::string(e.what()) == "Event with title Nonexistent Event not found");
//    }
//}
//
//void testGetEventsForMonth2() {
//    Repository repo;
//    std::tm tm = {};
//    tm.tm_year = 2025 - 1900; // Year 2025
//    tm.tm_mon = 3 - 1;        // March
//    tm.tm_mday = 15;
//    auto dateTime = std::chrono::system_clock::from_time_t(std::mktime(&tm));
//
//    Event event1("Event1", "Description1", dateTime, 50, "http://link1.com");
//    Event event2("Event2", "Description2", std::chrono::system_clock::now(), 30, "http://link2.com");
//    repo.addEventToData(event1);
//    repo.addEventToData(event2);
//
//    std::vector<Event> marchEvents = repo.getEventsForMonth(3);
//    assert(marchEvents.size() == 1);
//    assert(marchEvents[0].getTitle() == "Event1");
//
//    std::vector<Event> allEvents = repo.getEventsForMonth(0);
//    assert(allEvents.size() == 2);
//}
//
//void testReadFromFile() {
//    Repository repo;
//
//    // Create a temporary file
//    std::ofstream file("test_input.txt");
//    file << "Event1|Description1|2025-03-15 12:00:00|50|http://link1.com\n";
//    file << "Event2|Description2|2025-04-20 15:30:00|30|http://link2.com\n";
//    file.close();
//
//    repo.readFromFile("test_input.txt");
//
//    std::vector<Event> events = repo.getEventsForMonth(0); // Get all events
//    assert(events.size() == 2);
//    assert(events[0].getTitle() == "Event1");
//    assert(events[1].getTitle() == "Event2");
//
//    // Clean up
//    std::remove("test_input.txt");
//}
//
//void testWriteToFile() {
//    Repository repo;
//    Event event1("Event1", "Description1", std::chrono::system_clock::now(), 50, "http://link1.com");
//    Event event2("Event2", "Description2", std::chrono::system_clock::now(), 30, "http://link2.com");
//    repo.addEventToData(event1);
//    repo.addEventToData(event2);
//
//    // Write to a temporary file
//    repo.writeToFile("test_output.txt");
//
//    // Read the file and verify its contents
//    std::ifstream file("test_output.txt");
//    std::string line;
//    std::getline(file, line);
//    assert(line.find("Event1") != std::string::npos);
//    std::getline(file, line);
//    assert(line.find("Event2") != std::string::npos);
//    file.close();
//
//    // Clean up
//    std::remove("test_output.txt");
//}
//
//void runAllRepositoryTests() {
//    testAddEventToData();
//    testDeleteEvent();
//    testGetEventsForMonth2();
//    testReadFromFile();
//    testWriteToFile();
//}
//
//void testReadFromFileStreamError() {
//    Repository repo;
//
//    try {
//        // Attempt to read from a non-existent file
//        repo.readFromFile("non_existent_file.txt");
//        assert(false); // Should not reach here
//    }
//    catch (const std::runtime_error& e) {
//        assert(std::string(e.what()).find("Failed to open file") != std::string::npos);
//    }
//}
//
//void testWriteToFileStreamError() {
//    Repository repo;
//
//    try {
//        // Attempt to write to a file in a non-writable directory
//        repo.writeToFile("/non_writable_directory/test_output.txt");
//        assert(false); // Should not reach here
//    }
//    catch (const std::runtime_error& e) {
//        assert(std::string(e.what()).find("Failed to open file for writing") != std::string::npos);
//    }
//}
//
//void runStreamErrorTests() {
//    testReadFromFileStreamError();
//    testWriteToFileStreamError();
//}
//
//void testReadFromFileInvalidDateTime() {
//    Repository repo;
//	assert(repo.getNumberOfEvents() == 0); // Ensure the repository is empty before the test
//
//    // Create a temporary file with invalid date/time entries
//    std::ofstream file("invalid_datetime_test.txt");
//    file << "   Event1|Description1|2025-13-15 12:00:00|50|http://link1.com\n"; // Invalid month
//    file << "Event3|Description2|InvalidDate|20|http://link3.com\n";         // Completely invalid format
//    file << "Event4|Description3|2025-03-15T12:00:00|100|http://link4.com\n"; // Invalid separator
//    file << "Event5|2025-03-15 12:00|10|http://link5.com\n";   // Missing seconds
//    file.close();
//
//    // Redirect std::cerr to capture error messages
//    std::streambuf* originalCerr = std::cerr.rdbuf();
//    std::ostringstream capturedErrors;
//    std::cerr.rdbuf(capturedErrors.rdbuf());
//
//    // Attempt to read the file
//    repo.readFromFile("invalid_datetime_test.txt");
//
//    // Restore std::cerr
//    std::cerr.rdbuf(originalCerr);
//
//    // Verify that all invalid lines were skipped and errors were logged
//    std::string errors = capturedErrors.str();
//    assert(errors.find("Error parsing line 1: Invalid date/time format") != std::string::npos);
//
//    // Verify that no events were added to the repository
//    std::vector<Event> events = repo.getEventsForMonth(0); // Get all events
//    assert(events.size() == 0);
//
//}
//
//void testIteratorIncrement() {
//    std::vector<int> vec;
//    vec.push_back(1);
//    vec.push_back(2);
//    vec.push_back(3);
//
//    auto it = vec.begin();
//    assert(*it == 1); // Check initial value
//    ++it;
//    assert(*it == 2); // Check after pre-increment
//    it++;
//    assert(*it == 3); // Check after post-increment
//}
//
//
//void testIteratorDereference() {
//    std::vector<std::string> vec;
//    vec.push_back("Hello");
//    vec.push_back("World");
//
//    auto it = vec.begin();
//    assert(*it == "Hello"); // Dereference to get the first element
//    ++it;
//    assert(*it == "World"); // Dereference to get the second element
//}
//
//void testIteratorComparison() {
//    std::vector<int> vec;
//    vec.push_back(5);
//    vec.push_back(10);
//
//    auto it1 = vec.begin();
//    auto it2 = vec.begin();
//    auto it3 = vec.end();
//
//    assert(it1 == it2); // Both point to the beginning
//    assert(it1 != it3); // Beginning and end are not equal
//}
//
//void testIteratorArithmetic() {
//    std::vector<int> vec;
//    vec.push_back(10);
//    vec.push_back(20);
//    vec.push_back(30);
//    vec.push_back(40);
//
//    auto it = vec.begin();
//    auto it2 = it + 2; // Move iterator forward by 2
//    assert(*it2 == 30);
//
//    auto it3 = it2 - 1; // Move iterator backward by 1
//    assert(*it3 == 20);
//}
//
//void testIteratorArrowOperator() {
//    struct TestStruct {
//        int value;
//        std::string name;
//    };
//
//    std::vector<TestStruct> vec;
//    vec.push_back({ 1, "First" });
//    vec.push_back({ 2, "Second" });
//
//    auto it = vec.begin();
//    assert(it->value == 1); // Access member using arrow operator
//    assert(it->name == "First");
//    ++it;
//    assert(it->value == 2);
//    assert(it->name == "Second");
//}
//
//void runIteratorTests() {
//    testIteratorIncrement();
//    testIteratorArithmetic();
//    testIteratorComparison();
//    testIteratorDereference();
//    testIteratorArrowOperator();
//}
//
//void testCopyConstructor() {
//    // Create a std::vector and add elements
//    std::vector<int> original(5);
//    original.push_back(10);
//    original.push_back(20);
//    original.push_back(30);
//
//    // Use the copy constructor (line 102)
//    std::vector<int> copy(original);
//    std::vector<int> copy2;
//	copy2 = original;
//
//    // Verify that the copy has the same elements as the original
//    assert(copy.size() == original.size());
//    for (int i = 0; i < original.size(); ++i) {
//        assert(copy[i] == original[i]);
//    }
//
//    // Verify that modifying the copy does not affect the original
//    copy.push_back(40);
//    assert(copy.size() == 4);
//    assert(original.size() == 3); // Original size remains unchanged
//}
//
//void testRemoveFunction() {
//    // Create a std::vector and add elements
//    std::vector<int> vec;
//    vec.push_back(10);
//    vec.push_back(20);
//    vec.push_back(30);
//
//    // Remove the first element (line 120)
//    vec.erase(vec.begin());
//    assert(vec.size() == 2); // Line 122
//    assert(vec[0] == 20);
//    assert(vec[1] == 30);
//
//    // Remove the last element
//    vec.erase(vec.begin()+1);
//    assert(vec.size() == 1); // Line 122
//    assert(vec[0] == 20);
//
//    // Attempt to remove an element at an invalid index (no-op)
//    vec.erase(vec.begin()-1); // Invalid index
//    vec.erase(vec.begin()+10); // Out-of-bounds index
//    assert(vec.size() == 1); // Size should remain unchanged
//}
//
//void testGetEventsForMonth() {
//    Repository repo;
//    Repository userRepo;
//    Service service(repo, userRepo);
//
//    // Add events with different months
//    std::tm tm1 = {};
//    tm1.tm_year = 2025 - 1900; // Year 2025
//    tm1.tm_mon = 2 - 1;        // February
//    tm1.tm_mday = 15;
//    auto dateTime1 = std::chrono::system_clock::from_time_t(std::mktime(&tm1));
//
//    std::tm tm2 = {};
//    tm2.tm_year = 2025 - 1900; // Year 2025
//    tm2.tm_mon = 3 - 1;        // March
//    tm2.tm_mday = 20;
//    auto dateTime2 = std::chrono::system_clock::from_time_t(std::mktime(&tm2));
//
//    service.addEvent("Event1", "Description1", dateTime1, 50, "http://link1.com");
//    service.addEvent("Event2", "Description2", dateTime2, 30, "http://link2.com");
//
//    // Get events for February
//    std::vector<Event> februaryEvents = service.getEventsForMonth(2);
//    assert(februaryEvents.size() == 1);
//    assert(februaryEvents[0].getTitle() == "Event1");
//
//    // Get events for all months
//    std::vector<Event> allEvents = service.getEventsForMonth(0);
//    assert(allEvents.size() == 2);
//}
//
//void testUpdateEvent() {
//    Repository repo;
//    Repository userRepo;
//    Service service(repo, userRepo);
//
//    // Add and update an event
//    service.addEvent("Test Event", "This is a test event", std::chrono::system_clock::now(), 100, "http://test.com");
//    service.updateEvent("Test Event", "Updated Event", "Updated description", std::chrono::system_clock::now(), 200, "http://updated.com");
//
//    // Verify the event was updated
//    std::vector<Event> events = service.getEventsForMonth(0); // Get all events
//    assert(events.size() == 1);
//    assert(events[0].getTitle() == "Updated Event");
//    assert(events[0].getDescription() == "Updated description");
//    assert(events[0].getNumberOfPeople() == 200);
//    assert(events[0].getLink() == "http://updated.com");
//}
//
//void testDeleteEvent2() {
//    Repository repo;
//    Repository userRepo;
//    Service service(repo, userRepo);
//
//    // Add and delete an event
//    service.addEvent("Test Event", "This is a test event", std::chrono::system_clock::now(), 100, "http://test.com");
//    service.deleteEvent("Test Event");
//
//    // Verify the event was deleted
//    std::vector<Event> events = service.getEventsForMonth(0); // Get all events
//    assert(events.size() == 0);
//
//    // Attempt to delete a non-existent event
//    try {
//        service.deleteEvent("Nonexistent Event");
//        assert(false); // Should not reach here
//    }
//    catch (const std::runtime_error& e) {
//        assert(std::string(e.what()).find("not found") != std::string::npos);
//    }
//}
//
//void testAddEvent() {
//    Repository repo;
//    Repository userRepo;
//    Service service(repo, userRepo);
//
//
//
//    // Add an event
//    service.addEvent("Test Event", "This is a test event", std::chrono::system_clock::now(), 100, "http://test.com");
//
//    // Verify the event was added
//    std::vector<Event> events = service.getEventsForMonth(0); // Get all events
//    assert(events.size() == 1);
//    assert(events[0].getTitle() == "Test Event");
//	std::vector<Event> events2 = service.getUserEvents();
//    int nr = service.getUserNumberOfEvents();
//	assert(events2.size() == 0);
//	assert(nr == 0);
//    assert(events[0].getDescription() == "This is a test event");
//    assert(events[0].getNumberOfPeople() == 100);
//    assert(events[0].getLink() == "http://test.com");
//
//	service.addEventToUserRepo(events[0]);
//	nr = service.getUserNumberOfEvents();
//	assert(nr == 1);
//	service.deleteEventFromUserRepo("Test Event");
//	events2 = service.getUserEvents();
//	nr = service.getUserNumberOfEvents();
//	assert(events2.size() == 0);
//}
//
//void runServiceTests() {
//    testAddEvent();
//    testDeleteEvent2();
//    testUpdateEvent();
//    testGetEventsForMonth();
//}
//
//void Tests::runAllTests()
//{
//	testAddEvent();
//	testDeleteEvent();
//	testEventSetters();
//	testToString();
//	testRepo();
//	runAllRepositoryTests();
//	runStreamErrorTests();
//	testReadFromFileInvalidDateTime();
//	runIteratorTests();
//	runServiceTests();
//}
