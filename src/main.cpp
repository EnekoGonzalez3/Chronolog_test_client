#include <iostream>
#include <map>
#include <vector>
#include "chronolog_client.h" // Adjust the include path as needed

using namespace chronolog;

int main() {
    // ---------------------------------------------------------------------
    // Setup configuration
    // ---------------------------------------------------------------------
    // For demonstration purposes, we assume that a default or dummy configuration
    // object can be created. Replace the following with your actual configuration.
    ClientPortalServiceConf dummyConf;
    
    // Create a Chronolog client instance using the configuration.
    Client client(dummyConf);
    
    // ---------------------------------------------------------------------
    // Connect to the Chronolog service
    // ---------------------------------------------------------------------
    int rc = client.Connect();
    if (rc != 0) {
        std::cerr << "Failed to connect to Chronolog service. Error code: " << rc << std::endl;
        return rc;
    }
    std::cout << "Connected to Chronolog service." << std::endl;
    
    // ---------------------------------------------------------------------
    // Create a new chronicle
    // ---------------------------------------------------------------------
    int flags = 0;
    std::map<std::string, std::string> chronicleAttrs; // Attributes can be populated as needed
    rc = client.CreateChronicle("TestChronicle", chronicleAttrs, flags);
    if (rc != 0) {
        std::cerr << "Failed to create chronicle. Error code: " << rc << std::endl;
    } else {
        std::cout << "Chronicle 'TestChronicle' created." << std::endl;
    }
    
    // ---------------------------------------------------------------------
    // Acquire a story from the chronicle
    // ---------------------------------------------------------------------
    std::map<std::string, std::string> storyAttrs; // Attributes for the story
    int storyFlags = 0;
    auto storyPair = client.AcquireStory("TestChronicle", "TestStory", storyAttrs, storyFlags);
    if (storyPair.first != 0 || storyPair.second == nullptr) {
        std::cerr << "Failed to acquire story. Error code: " << storyPair.first << std::endl;
    } else {
        std::cout << "Story 'TestStory' acquired." << std::endl;
        StoryHandle* story = storyPair.second;
        
        // -----------------------------------------------------------------
        // Log an event to the story
        // -----------------------------------------------------------------
        int event_rc = story->log_event("This is a test event log.");
        if (event_rc != 0) {
            std::cerr << "Failed to log event. Error code: " << event_rc << std::endl;
        } else {
            std::cout << "Event logged successfully." << std::endl;
        }
        
        // -----------------------------------------------------------------
        // Playback events from the story
        // -----------------------------------------------------------------
        std::vector<Event> events;
        event_rc = story->playback_story(0, 1000000, events);
        if (event_rc != 0) {
            std::cerr << "Failed to playback story events. Error code: " << event_rc << std::endl;
        } else {
            std::cout << "Playback of story events:" << std::endl;
            for (const auto& event : events) {
                std::cout << event.toString() << std::endl;
            }
        }
        
        // -----------------------------------------------------------------
        // Release the story when done
        // -----------------------------------------------------------------
        rc = client.ReleaseStory("TestChronicle", "TestStory");
        if (rc != 0) {
            std::cerr << "Failed to release story. Error code: " << rc << std::endl;
        } else {
            std::cout << "Story 'TestStory' released." << std::endl;
        }
    }
    
    // ---------------------------------------------------------------------
    // Disconnect from the Chronolog service
    // ---------------------------------------------------------------------
    rc = client.Disconnect();
    if (rc != 0) {
        std::cerr << "Failed to disconnect from Chronolog service. Error code: " << rc << std::endl;
    } else {
        std::cout << "Disconnected from Chronolog service." << std::endl;
    }
    
    return 0;
}