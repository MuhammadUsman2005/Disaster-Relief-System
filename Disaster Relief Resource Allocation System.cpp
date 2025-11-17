#include <iostream> 
#include <fstream> 
#include <string> 
#include <limits> 
 
using namespace std; 
 
struct CityNode { 
    string cityName; 
    int urgencyScore;   
    int population; 
    string damageLevel; 
    CityNode* next; 
     
    CityNode(string name, int urgency, int pop, string damage)  
        : cityName(name), urgencyScore(urgency), population(pop),  
          damageLevel(damage), next(nullptr) {} 
}; 
 
class PriorityQueue { 
private: 
    CityNode* front; 
    int size; 
 
public: 
    PriorityQueue() : front(nullptr), size(0) {} 
     
    ~PriorityQueue() { 
        while (front != nullptr) { 
            CityNode* temp = front; 
            front = front->next; 
            delete temp; 
        } 
    } 
     
    void enqueue(string cityName, int urgency, int population, string damage) { 
        CityNode* newNode = new CityNode(cityName, urgency, population, damage); 
         
        if (front == nullptr || front->urgencyScore < urgency) { 
            newNode->next = front; 
            front = newNode; 
        } else { 
            CityNode* current = front; 
            while (current->next != nullptr && current->next->urgencyScore >= 
urgency) { 
                current = current->next; 
            } 
            newNode->next = current->next; 
            current->next = newNode; 
        } 
        size++; 
    } 
     
    CityNode* dequeue() { 
        if (front == nullptr) return nullptr; 
         
        CityNode* temp = front; 
        front = front->next; 
        size--; 
        return temp; 
    } 
     
    bool isEmpty() { 
        return front == nullptr; 
    } 
     
    int getSize() { 
        return size; 
    } 
     
    void display() { 
        CityNode* current = front; 
        int index = 1; 
        while (current != nullptr) { 
            cout << index << ". " << current->cityName  
                 << " (Urgency: " << current->urgencyScore  
                 << ", Population: " << current->population  
                 << ", Damage: " << current->damageLevel << ")" << endl; 
            current = current->next; 
            index++; 
        } 
    } 
}; 
 
struct TruckNode { 
    int truckID; 
    string destination; 
    int capacity; 
    string status;  
    TruckNode* next; 
     
    TruckNode(int id, int cap)  
        : truckID(id), capacity(cap), status("Available"), destination(""), 
next(nullptr) {} 
}; 
 
class TruckQueue { 
private: 
    TruckNode* front; 
    TruckNode* rear; 
    int size; 
 
public: 
    TruckQueue() : front(nullptr), rear(nullptr), size(0) {} 
     
    ~TruckQueue() { 
        while (front != nullptr) { 
            TruckNode* temp = front; 
            front = front->next; 
            delete temp; 
        } 
    } 
     
    void enqueue(int truckID, int capacity) { 
        TruckNode* newNode = new TruckNode(truckID, capacity); 
         
        if (rear == nullptr) { 
            front = rear = newNode; 
        } else { 
            rear->next = newNode; 
            rear = newNode; 
        } 
        size++; 
    } 
     
    TruckNode* dequeue() { 
        if (front == nullptr) return nullptr; 
         
        TruckNode* temp = front; 
        front = front->next; 
         
        if (front == nullptr) { 
            rear = nullptr; 
        } 
         
        size--; 
        return temp; 
    } 
     
    TruckNode* peek() { 
        return front; 
    } 
     
    bool isEmpty() { 
        return front == nullptr; 
    } 
     
    void display() { 
        TruckNode* current = front; 
        while (current != nullptr) { 
            cout << "Truck #" << current->truckID  
                 << " (Capacity: " << current->capacity  
                 << " tons, Status: " << current->status << ")" << endl; 
            current = current->next; 
        } 
    } 
}; 
 
struct GraphNode { 
    string cityName; 
    GraphNode* next; 
}; 
 
struct GraphEdge { 
    string source; 
    string destination; 
    int distance; 
    GraphEdge* next; 
}; 
 
class CityGraph { 
private: 
    GraphNode** adjacencyList; 
    GraphEdge* edgeList; 
    int capacity; 
    int cityCount; 
 
    int findCityIndex(string cityName) { 
        for (int i = 0; i < cityCount; i++) { 
            if (adjacencyList[i]->cityName == cityName) { 
                return i; 
            } 
        } 
        return -1; 
    } 
 
public: 
    CityGraph(int maxCities) { 
        capacity = maxCities; 
        cityCount = 0; 
        adjacencyList = new GraphNode*[maxCities]; 
        edgeList = nullptr; 
         
        for (int i = 0; i < maxCities; i++) { 
            adjacencyList[i] = nullptr; 
        } 
    } 
     
    ~CityGraph() { 
        for (int i = 0; i < cityCount; i++) { 
            delete adjacencyList[i]; 
        } 
        delete[] adjacencyList; 
         
        GraphEdge* currentEdge = edgeList; 
        while (currentEdge != nullptr) { 
            GraphEdge* temp = currentEdge; 
            currentEdge = currentEdge->next; 
            delete temp; 
        } 
    } 
     
    void addCity(string cityName) { 
        if (cityCount >= capacity) { 
            cout << "Cannot add more cities. Graph capacity reached." << endl; 
            return; 
        } 
         
        GraphNode* newNode = new GraphNode; 
        newNode->cityName = cityName; 
        newNode->next = nullptr; 
        adjacencyList[cityCount] = newNode; 
        cityCount++; 
    } 
     
    void addRoad(string source, string destination, int distance) { 
        
        GraphEdge* newEdge = new GraphEdge; 
        newEdge->source = source; 
        newEdge->destination = destination; 
        newEdge->distance = distance; 
        newEdge->next = edgeList; 
        edgeList = newEdge; 
         
        cout << "Road added: " << source << " - " << destination  
             << " (" << distance << " km)" << endl; 
    } 
     
    void displayCities() { 
        cout << "\n--- Cities in Network ---" << endl; 
        for (int i = 0; i < cityCount; i++) { 
            cout << (i + 1) << ". " << adjacencyList[i]->cityName << endl; 
        } 
    } 
     
    void displayRoads() { 
        cout << "\n--- Roads in Network ---" << endl; 
        GraphEdge* current = edgeList; 
        int index = 1; 
        while (current != nullptr) { 
            cout << index << ". " << current->source << " <-> "  
                 << current->destination << " (" << current->distance << " km)" 
<< endl; 
            current = current->next; 
            index++; 
        } 
    } 
     
    bool findPath(string fromCity, string toCity) { 
         
        GraphEdge* current = edgeList; 
        while (current != nullptr) { 
            if ((current->source == fromCity && current->destination == toCity) 
|| 
                (current->source == toCity && current->destination == fromCity)) 
{ 
                return true; 
            } 
            current = current->next; 
        } 
        return false; 
    } 
     
    int getDistance(string fromCity, string toCity) { 
        GraphEdge* current = edgeList; 
        while (current != nullptr) { 
            if ((current->source == fromCity && current->destination == toCity) 
|| 
                (current->source == toCity && current->destination == fromCity)) 
{ 
                return current->distance; 
            } 
            current = current->next; 
        } 
        return -1;  
    } 
}; 
 
class ResourceManager { 
private: 
    int foodPackets; 
    int medicineKits; 
    int waterBottles; 
    int blankets; 
 
public: 
    ResourceManager() : foodPackets(0), medicineKits(0), waterBottles(0), 
blankets(0) {} 
     
    void addResources(int food, int medicine, int water, int blanket) { 
        foodPackets += food; 
        medicineKits += medicine; 
        waterBottles += water; 
        blankets += blanket; 
    } 
     
    bool allocateResources(int food, int medicine, int water, int blanket) { 
        if (foodPackets >= food && medicineKits >= medicine &&  
            waterBottles >= water && blankets >= blanket) { 
            foodPackets -= food; 
            medicineKits -= medicine; 
            waterBottles -= water; 
            blankets -= blanket; 
            return true; 
        } 
        return false; 
    } 
     
    void displayResources() { 
        cout << "\n--- Current Resources ---" << endl; 
        cout << "Food Packets: " << foodPackets << endl; 
        cout << "Medicine Kits: " << medicineKits << endl; 
        cout << "Water Bottles: " << waterBottles << endl; 
        cout << "Blankets: " << blankets << endl; 
    } 
     
    int getTotalResources() { 
        return foodPackets + medicineKits + waterBottles + blankets; 
    } 
}; 
 
class DataLogger { 
private: 
    string logFileName; 
 
public: 
    DataLogger(string filename) : logFileName(filename) {} 
     
    void logDispatch(int truckID, string destination, int distance, string 
urgency, string resources) { 
        ofstream file(logFileName, ios::app); 
        if (file.is_open()) { 
            file << "Truck #" << truckID << " dispatched to " << destination  
                 << " | Distance: " << distance << " km | Urgency: " << urgency  
                 << " | Resources: " << resources << endl; 
            file.close(); 
        } 
    } 
     
    void logResourceUpdate(string operation, int food, int medicine, int water, 
int blankets) { 
        ofstream file(logFileName, ios::app); 
        if (file.is_open()) { 
            file << "Resource " << operation << " | Food: " << food  
                 << " | Medicine: " << medicine << " | Water: " << water  
                 << " | Blankets: " << blankets << endl; 
            file.close(); 
        } 
    } 
     
    void displayLogs() { 
        ifstream file(logFileName); 
        if (file.is_open()) { 
            cout << "\n--- System Logs ---" << endl; 
            string line; 
            while (getline(file, line)) { 
                cout << line << endl; 
            } 
            file.close(); 
        } 
    } 
}; 
 
class DisasterReliefSystem { 
private: 
    PriorityQueue urgentAreas; 
    TruckQueue availableTrucks; 
    CityGraph* cityNetwork; 
    ResourceManager resources; 
    DataLogger logger; 
    int nextTruckID; 
 
public: 
    DisasterReliefSystem(int maxCities)  
        : cityNetwork(new CityGraph(maxCities)), logger("relief_log.txt"), 
nextTruckID(1) {} 
     
    ~DisasterReliefSystem() { 
        delete cityNetwork; 
    } 
     
    void initializeSystem() { 
       
        availableTrucks.enqueue(nextTruckID++, 5);   
        availableTrucks.enqueue(nextTruckID++, 8);   
        availableTrucks.enqueue(nextTruckID++, 10);  
         
        cout << "Disaster Relief System Initialized!" << endl; 
    } 
     
    void addAffectedArea() { 
        string cityName, damageLevel; 
        int population, urgencyScore; 
         
        cout << "\n--- Add Affected Area ---" << endl; 
        cout << "Enter city name: "; 
        cin.ignore(); 
        getline(cin, cityName); 
         
        cout << "Enter population affected: "; 
        cin >> population; 
         
        cout << "Enter damage level (Severe/Medium/Low): "; 
        cin >> damageLevel; 
         
        if (damageLevel == "Severe") { 
            urgencyScore = population * 10; 
        } else if (damageLevel == "Medium") { 
            urgencyScore = population * 5; 
        } else { 
            urgencyScore = population * 2; 
        } 
         
        urgentAreas.enqueue(cityName, urgencyScore, population, damageLevel); 
        cityNetwork->addCity(cityName); 
         
        cout << "Area added to priority queue with urgency score: " << 
urgencyScore << endl; 
    } 
     
    void addResources() { 
        int food, medicine, water, blankets; 
         
        cout << "\n--- Add Resources ---" << endl; 
        cout << "Enter number of food packets: "; 
        cin >> food; 
         
        cout << "Enter number of medicine kits: "; 
        cin >> medicine; 
         
        cout << "Enter number of water bottles: "; 
        cin >> water; 
         
        cout << "Enter number of blankets: "; 
        cin >> blankets; 
         
        resources.addResources(food, medicine, water, blankets); 
        logger.logResourceUpdate("ADDED", food, medicine, water, blankets); 
         
        cout << "Resources added successfully!" << endl; 
    } 
     
    void dispatchTruck() { 
        if (urgentAreas.isEmpty()) { 
            cout << "No urgent areas in queue!" << endl; 
            return; 
        } 
         
        if (availableTrucks.isEmpty()) { 
            cout << "No trucks available!" << endl; 
            return; 
        } 
         
        if (resources.getTotalResources() == 0) { 
            cout << "No resources available for dispatch!" << endl; 
            return; 
        } 
         
        CityNode* urgentArea = urgentAreas.dequeue(); 
        TruckNode* truck = availableTrucks.dequeue(); 
         
        int foodNeeded, medicineNeeded, waterNeeded, blanketsNeeded; 
         
        if (urgentArea->damageLevel == "Severe") { 
            foodNeeded = urgentArea->population * 3; 
            medicineNeeded = urgentArea->population / 10; 
            waterNeeded = urgentArea->population * 5; 
            blanketsNeeded = urgentArea->population; 
        }  
         
        else if (urgentArea->damageLevel == "Medium") { 
            foodNeeded = urgentArea->population * 2; 
            medicineNeeded = urgentArea->population / 20; 
            waterNeeded = urgentArea->population * 3; 
            blanketsNeeded = urgentArea->population / 2; 
        }  
         
        else { 
            foodNeeded = urgentArea->population; 
            medicineNeeded = urgentArea->population / 50; 
            waterNeeded = urgentArea->population * 2; 
            blanketsNeeded = urgentArea->population / 4; 
        } 
         
        if (resources.allocateResources(foodNeeded, medicineNeeded, waterNeeded, 
blanketsNeeded)) { 
            string resourceInfo = "Food:" + to_string(foodNeeded) +  
                                ", Medicine:" + to_string(medicineNeeded) + 
                                ", Water:" + to_string(waterNeeded) + 
                                ", Blankets:" + to_string(blanketsNeeded); 
             
            int distance = cityNetwork->getDistance("Warehouse", urgentArea->cityName); 
            if (distance == -1) distance = 50;  
             
            cout << "\n--- TRUCK DISPATCHED ---" << endl; 
            cout << "Truck #" << truck->truckID << " dispatched to " << 
urgentArea->cityName << endl; 
            cout << "Distance: " << distance << " km" << endl; 
            cout << "Urgency Level: " << urgentArea->damageLevel << endl; 
            cout << "Resources Delivered: " << resourceInfo << endl; 
  
            logger.logDispatch(truck->truckID, urgentArea->cityName, distance,  
                             urgentArea->damageLevel, resourceInfo); 
            
            availableTrucks.enqueue(truck->truckID, truck->capacity); 
             
        } else { 
            cout << "Insufficient resources for this dispatch!" << endl; 
             
            urgentAreas.enqueue(urgentArea->cityName, urgentArea->urgencyScore,  
                              urgentArea->population, urgentArea->damageLevel); 
            availableTrucks.enqueue(truck->truckID, truck->capacity); 
        } 
         
        delete urgentArea; 
        delete truck; 
    } 
     
    void displayStatus() { 
        cout << "\n=== DISASTER RELIEF SYSTEM STATUS ===" << endl; 
         
        cout << "\n--- Urgent Areas (Priority Queue) ---" << endl; 
        if (urgentAreas.isEmpty()) { 
            cout << "No urgent areas in queue." << endl; 
        } else { 
            urgentAreas.display(); 
        } 
         
        cout << "\n--- Available Trucks ---" << endl; 
        if (availableTrucks.isEmpty()) { 
            cout << "No trucks available." << endl; 
        } else { 
            availableTrucks.display(); 
        } 
         
        resources.displayResources(); 
    } 
     
    void addRoadToNetwork() { 
        string source, destination; 
        int distance; 
         
        cout << "\n--- Add Road to Network ---" << endl; 
        cout << "Enter source city: "; 
        cin.ignore(); 
        getline(cin, source); 
         
        cout << "Enter destination city: "; 
        getline(cin, destination); 
         
        cout << "Enter distance (km): "; 
        cin >> distance; 
         
        cityNetwork->addRoad(source, destination, distance); 
    } 
     
    void showNetwork() { 
        cityNetwork->displayCities(); 
        cityNetwork->displayRoads(); 
    } 
     
    void showLogs() { 
        logger.displayLogs(); 
    } 
}; 
 
int getValidatedInput(const string& prompt, int minVal = 0, int maxVal = 1000000) 
{ 
    int value; 
    while (true) { 
        cout << prompt; 
        cin >> value; 
         
        if (cin.fail() || value < minVal || value > maxVal) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a value between "  
                 << minVal << " and " << maxVal << ": "; 
        } else { 
            break; 
        } 
    } 
    return value; 
} 
 
int main() { 
    DisasterReliefSystem reliefSystem(50); 
    reliefSystem.initializeSystem(); 
     
    int choice; 
     
    do { 
        cout << "\n\n=== DISASTER RELIEF RESOURCE ALLOCATION SYSTEM ===" << endl; 
        cout << "1. Add Affected Area" << endl; 
        cout << "2. Add Resources" << endl; 
        cout << "3. Dispatch Truck to Urgent Area" << endl; 
        cout << "4. Add Road to Network" << endl; 
        cout << "5. View System Status" << endl; 
        cout << "6. View Network" << endl; 
        cout << "7. View System Logs" << endl; 
        cout << "8. Exit" << endl; 
        cout << "Enter your choice (1-8): "; 
         
        cin >> choice; 
         
        try { 
            switch (choice) { 
                case 1: 
                    reliefSystem.addAffectedArea(); 
                    break; 
                case 2: 
                    reliefSystem.addResources(); 
                    break; 
                case 3: 
                    reliefSystem.dispatchTruck(); 
                    break; 
                case 4: 
                    reliefSystem.addRoadToNetwork(); 
                    break; 
                case 5: 
                    reliefSystem.displayStatus(); 
                    break; 
                case 6: 
                    reliefSystem.showNetwork(); 
                    break; 
                case 7: 
                    reliefSystem.showLogs(); 
                    break; 
                case 8: 
                    cout << "Thank you for using Disaster Relief System!" << 
endl; 
                    break; 
                default: 
                    cout << "Invalid choice! Please try again." << endl; 
                    break; 
            } 
        } catch (const exception& e) { 
            cout << "An error occurred: " << e.what() << endl; 
            cout << "Please try again." << endl; 
        } 
         
    } while (choice != 8); 
     
    return 0; 
} 
 
 
