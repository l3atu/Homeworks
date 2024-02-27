#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <algorithm>
#include "Network.h"


Network::Network() {

}

void Network::process_commands(vector<Client> &clients, vector<string> &commands, int message_limit,
                               const string &sender_port, const string &receiver_port) {
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* timeInfo = std::localtime(&currentTime);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    std::string timestamp(buffer);
    for (const auto& row : commands) {
        std::istringstream iss(row);
        std::string command;
        iss>>command;
        if (command=="MESSAGE"){
            std::string sender;
            std::string receiver;
            size_t starting = row.find("#");
            size_t ending = row.find("#", starting + 1);
            std::string message=row.substr(starting + 1, ending - starting - 1);
            iss>>sender>>receiver;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Command: "<<row<<std::endl;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Message to be sent: "<<'"'<<message<<'"'<<"\n"<<std::endl;

            int frameCount=0;
            std::string senderIP;
            std::string receiverIP;
            std::string senderMAC;
            std::string receiverMAC;

            for (int i =0; i <message.size() ; i+=message_limit) {
                frameCount++;
                std::string chunk = message.substr(i,message_limit);

                int senderIndex=0;
                for (int j = 0; j < clients.size(); ++j) {
                    if (clients[j].client_id==sender){
                        senderIndex=j;
                        senderIP=clients[j].client_ip;
                        senderMAC=clients[j].client_mac;
                        for (const auto& pair : clients[senderIndex].routing_table) {
                            if(pair.first==receiver){
                                for (int k = 0; k < clients.size(); ++k) {
                                    if (clients[k].client_id==pair.second){
                                        receiverMAC=clients[k].client_mac;
                                    }
                                }
                            }
                        }
                    }
                    if (clients[j].client_id==receiver){
                        receiverIP=clients[j].client_ip;
                    }
                }

                auto applicationLayerPacket = new ApplicationLayerPacket(0, sender, receiver, chunk);
                auto transportLayerPacket = new TransportLayerPacket(1, sender_port, receiver_port);
                auto networkLayerPacket = new NetworkLayerPacket(2, senderIP, receiverIP);
                auto physicalLayerPacket = new PhysicalLayerPacket(3, senderMAC, receiverMAC);
                physicalLayerPacket->hops=0;

                std::stack<Packet*> Stack;
                Stack.push(applicationLayerPacket);
                Stack.push(transportLayerPacket);
                Stack.push(networkLayerPacket);
                Stack.push(physicalLayerPacket);
                clients[senderIndex].outgoing_queue.push(Stack);

                std::cout<<"Frame #"<<frameCount<<std::endl;
                physicalLayerPacket->print();
                networkLayerPacket->print();
                transportLayerPacket->print();
                applicationLayerPacket->print();
                std::cout<<"Message chunk carried: "<<'"'<<chunk<<'"'<<std::endl;
                std::cout<<"Number of hops so far: "<<physicalLayerPacket->hops<<std::endl;
                std::cout<<"--------"<<std::endl;
            }
        }else if (command=="SHOW_FRAME_INFO"){
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Command: "<<row<<std::endl;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::string message;
            std::string client;
            std::string position;
            std::string frameNum;
            int hops;
            iss>>client>>position>>frameNum;
            std::stack<Packet*> Stack;
            std::stack<Packet*> frame;
            std::vector<Packet*> tempVector;
            for (int i = 0; i < clients.size(); ++i) {
                if (clients[i].client_id==client){
                    if (position=="out"){
                        if (clients[i].outgoing_queue.empty() || stoi(frameNum)>clients[i].outgoing_queue.size()) {
                            std::cout<<"No such frame."<<std::endl;
                        }
                        else {
                            std::cout<<"Current Frame #"<<frameNum<<" on the outgoing queue of client "<<client<<std::endl;

                            for (int j = 0; j < clients[i].outgoing_queue.size(); ++j) {
                                if (stoi(frameNum)-1==j){
                                    frame= clients[i].outgoing_queue.front();
                                    clients[i].outgoing_queue.pop();
                                    clients[i].outgoing_queue.push(frame);
                                }else{
                                    Stack=clients[i].outgoing_queue.front();
                                    clients[i].outgoing_queue.pop();
                                    clients[i].outgoing_queue.push(Stack);
                                }

                            }
                            for (int j = 0; j < frame.size(); ++j) {
                                tempVector.push_back(frame.top());
                                frame.pop();
                                j--;
                            }
                            for (int j = 0; j < tempVector.size(); ++j) {
                                if (auto applicationLayerPacket= dynamic_cast<ApplicationLayerPacket*>(tempVector[j])){
                                    message=applicationLayerPacket->message_data;
                                }
                            }
                            std::cout<<"Carried Message: "<<'"'<<message<<'"'<<std::endl;
                            for (int j = tempVector.size()-1; j >=0; --j) {
                                if (auto physicalLayerPacket = dynamic_cast<PhysicalLayerPacket*>(tempVector[j])) {
                                    hops = physicalLayerPacket->hops;
                                }
                                std::cout << "Layer " << tempVector[j]->layer_ID << " info: ";
                                tempVector[j]->print();
                            }
                            std::cout<<"Number of hops so far: "<<hops<<std::endl;
                        }

                    }else if(position=="in"){
                        if (clients[i].incoming_queue.empty() || stoi(frameNum)>clients[i].incoming_queue.size() ){
                            std::cout<<"No such frame."<<std::endl;
                        }
                        else{
                            std::cout<<"Current Frame #"<<frameNum<<" on the incoming queue of client "<<client<<std::endl;
                            for (int j = 0; j < clients[i].incoming_queue.size(); ++j) {
                                if (stoi(frameNum)-1==j){
                                    frame= clients[i].incoming_queue.front();
                                    clients[i].incoming_queue.pop();
                                    clients[i].incoming_queue.push(frame);
                                }else{
                                    Stack=clients[i].incoming_queue.front();
                                    clients[i].incoming_queue.pop();
                                    clients[i].incoming_queue.push(Stack);
                                }

                            }
                            for (int j = 0; j < frame.size(); ++j) {
                                tempVector.push_back(frame.top());
                                frame.pop();
                                j--;
                            }
                            for (int j = 0; j < tempVector.size(); ++j) {
                                if (auto applicationLayerPacket= dynamic_cast<ApplicationLayerPacket*>(tempVector[j])){
                                    message=applicationLayerPacket->message_data;
                                }
                            }
                            std::cout<<"Carried Message: "<<'"'<<message<<'"'<<std::endl;
                            for (int j = tempVector.size()-1; j >=0; --j) {
                                if (auto physicalLayerPacket = dynamic_cast<PhysicalLayerPacket*>(tempVector[j])) {
                                    hops = physicalLayerPacket->hops;
                                }
                                std::cout<<"Layer "<<tempVector[j]->layer_ID<<" info: ";
                                tempVector[j]->print();
                            }
                            std::cout<<"Number of hops so far: "<<hops<<std::endl;
                        }
                    }
                }
            }
        }else if (command=="SHOW_Q_INFO"){
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Command: "<<row<<std::endl;
            std::cout << std::string(row.size()+9, '-') << std::endl;

            std::string client;
            std::string position;
            iss>>client>>position;
            for (int i = 0; i < clients.size(); ++i) {
                if (clients[i].client_id==client){
                    if (position=="in"){
                        int inSize= clients[i].incoming_queue.size();
                        std::cout<<"Client "<<client<<" Incoming Queue Status"<<std::endl;
                        std::cout<<"Current total number of frames: "<<inSize<<std::endl;
                    }else if(position=="out"){
                        int outSize= clients[i].outgoing_queue.size();
                        std::cout<<"Client "<<client<<" Outgoing Queue Status"<<std::endl;
                        std::cout<<"Current total number of frames: "<<outSize<<std::endl;
                    }
                }
            }
        }else if (command=="SEND"){
            int hops;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Command: "<<row<<std::endl;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            int frame=0;
            std::string receiverMAC;
            std::string receiverID;
            std::string message;
            std::string senderID;
            std::stack<Packet*> Stack;
            std::stack<Packet*> Stack2;
            std::vector<Packet*> tempVector;
            for (int i = 0; i < clients.size(); ++i) {
               while (!clients[i].outgoing_queue.empty()){
                    tempVector.clear();
                    Stack=clients[i].outgoing_queue.front();
                    Stack2=clients[i].outgoing_queue.front();
                    for (int k = 0; k < Stack.size(); ++k) {
                        tempVector.push_back(Stack.top());
                        if (auto physicalLayerPacket = dynamic_cast<PhysicalLayerPacket*>(Stack.top())) {
                            hops = physicalLayerPacket->hops;
                            receiverMAC=physicalLayerPacket->receiver_MAC_address.substr(0,1);
                        }
                        if (auto applicationLayerPacket= dynamic_cast<ApplicationLayerPacket*>(Stack.top())){
                            senderID=applicationLayerPacket->sender_ID;
                            receiverID=applicationLayerPacket->receiver_ID;
                        }
                        Stack.pop();
                        k--;
                    }
                    for (int k = 0; k < clients.size(); ++k) {
                        if (clients[k].client_id==receiverMAC){
                            clients[k].incoming_queue.push(Stack2);
                            clients[i].outgoing_queue.pop();

                        }
                    }
                    for (int j = 0; j < tempVector.size(); ++j) {
                        if (auto physicalLayerPacket = dynamic_cast<PhysicalLayerPacket*>(tempVector[j])) {
                            physicalLayerPacket->hops+=1;
                            hops=physicalLayerPacket->hops;
                        }
                        if (j%4==0){
                            frame++;
                            std::cout<<"Client " << clients[i].client_id<<" sending frame #"<<frame<<" to client "<<receiverMAC<<std::endl;
                        }
                        tempVector[j]->print();
                        if (auto applicationLayerPacket= dynamic_cast<ApplicationLayerPacket*>(tempVector[j])){
                            std::cout<<"Message chunk carried: "<<'"'<<applicationLayerPacket->message_data<<'"'<<std::endl;
                            std::cout<<"Number of hops so far: "<<hops<<std::endl;
                            std::cout<<"--------"<<std::endl;
                            message+=applicationLayerPacket->message_data;

                            char lastChar =applicationLayerPacket->message_data[applicationLayerPacket->message_data.size() - 1];

                            if (lastChar=='.' || lastChar=='!' ||lastChar=='?'){
                                if (clients[i].client_id==senderID){
                                    ActivityType activityType=ActivityType::MESSAGE_SENT;
                                    Log log1= Log(timestamp,message,frame,0,senderID,receiverID,true,activityType);
                                    clients[i].log_entries.push_back(log1);
                                }
                                frame=0;
                                message.clear();
                            }
                        }
                    }
                }
            }
        }else if (command=="RECEIVE"){
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Command: "<<row<<std::endl;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            int frame=0;
            int hops;
            std::string message;
            std::string receiverID;
            std::string receiverMAC;
            std::string receiverMac;
            std::string senderID;
            std::string senderMac;
            std::vector<std::string> IDs;
            std::stack<Packet*> Stack1;
            std::stack<Packet*> Stack2;
            std::vector<Packet*> tempVector;
            for (int i = 0; i < clients.size(); ++i) {
                while (!clients[i].incoming_queue.empty()){
                    tempVector.clear();
                    Stack1= clients[i].incoming_queue.front();
                    Stack2 = clients[i].incoming_queue.front();
                    for (int j = 0; j < Stack1.size(); ++j) {
                        tempVector.push_back( Stack1.top());
                        if (auto physicalLayerPacket = dynamic_cast<PhysicalLayerPacket*>(Stack1.top())) {
                            hops=physicalLayerPacket->hops;
                            receiverMac=physicalLayerPacket->receiver_MAC_address.substr(0,1);
                            receiverMAC=physicalLayerPacket->receiver_MAC_address;
                            senderMac=physicalLayerPacket->sender_MAC_address.substr(0,1);
                        }

                        if (auto applicationLayerPacket= dynamic_cast<ApplicationLayerPacket*>(Stack1.top())){
                            senderID=applicationLayerPacket->sender_ID;
                            receiverID=applicationLayerPacket->receiver_ID;
                        }
                        Stack1.pop();
                        j--;
                    }
                    if (receiverMac==receiverID){
                        for (int j = 0; j < tempVector.size(); ++j) {
                            if (j%4==0){
                                frame++;
                                std::cout<<"Client "<<clients[i].client_id<<" receiving frame #"<<frame<<" from client "<<
                                         senderMac<<", originating from client "<<senderID<<std::endl;
                            }
                            tempVector[j]->print();
                            if (auto applicationLayerPacket= dynamic_cast<ApplicationLayerPacket*>(tempVector[j])){
                                std::cout<<"Message chunk carried: "<<'"'<<applicationLayerPacket->message_data<<'"'<<std::endl;
                                std::cout<<"Number of hops so far: "<<hops<<std::endl;
                                std::cout<<"--------"<<std::endl;
                                message+=applicationLayerPacket->message_data;

                                char lastChar =applicationLayerPacket->message_data[applicationLayerPacket->message_data.size() - 1];

                                if (lastChar=='.' || lastChar=='!' ||lastChar=='?'){
                                    ActivityType activityType=ActivityType::MESSAGE_RECEIVED;
                                    Log log2= Log(timestamp,message,frame,hops,senderID,receiverID, true,activityType);
                                    clients[i].log_entries.push_back(log2);
                                    std::cout<<"Client "<<receiverID<<" received the message "<<'"'<<message<<'"'<<" from client "<<senderID<<"."<<std::endl;
                                    std::cout<<"--------"<<std::endl;
                                    frame=0;
                                    message.clear();

                                }
                            }
                        }
                        clients[i].incoming_queue.pop();
                        while (!Stack2.empty()){
                            Packet* packet=Stack2.top();
                            delete packet;
                            Stack2.pop();
                        }
                    }else if (receiverID!=receiverMac){
                        for (int l = 0; l < clients.size(); ++l) {
                            IDs.push_back(clients[l].client_id);
                        }
                        int count=0;
                        for (const auto& pair : clients[i].routing_table) {
                            if(pair.first==receiverID) {
                                count = std::count(IDs.begin(), IDs.end(), pair.second);
                                if (count > 0) {
                                    for (int k = 0; k < clients.size(); ++k) {
                                        if (clients[k].client_id == pair.second) {
                                            receiverMAC = clients[k].client_mac;
                                        }
                                    }
                                }
                            }
                        }
                        if (count>0) {
                            for (int j = 0; j < Stack2.size(); ++j) {
                                if (auto physicalLayerPacket = dynamic_cast<PhysicalLayerPacket *>(Stack2.top())) {
                                    physicalLayerPacket->receiver_MAC_address = receiverMAC;
                                    physicalLayerPacket->sender_MAC_address = clients[i].client_mac;
                                }
                            }
                            clients[i].outgoing_queue.push(Stack2);
                            clients[i].incoming_queue.pop();
                            for (int j = 0; j < tempVector.size(); ++j) {
                                if (frame == 0) {
                                    std::cout << "Client " << clients[i].client_id
                                              << " receiving a message from client " << senderMac
                                              << ", but intended for client " << receiverID << ". Forwarding... "
                                              << std::endl;
                                }
                                if (j % 4 == 0) {
                                    frame++;
                                    std::cout << "Frame #" << frame << " MAC address change: New sender MAC " <<
                                              clients[i].client_mac << ", new receiver MAC " << receiverMAC
                                              << std::endl;
                                }
                                if (auto applicationLayerPacket = dynamic_cast<ApplicationLayerPacket *>(tempVector[j])) {
                                    message += applicationLayerPacket->message_data;

                                    char lastChar = applicationLayerPacket->message_data[
                                            applicationLayerPacket->message_data.size() - 1];

                                    if (lastChar == '.' || lastChar == '!' || lastChar == '?') {
                                        ActivityType activityType = ActivityType::MESSAGE_FORWARDED;
                                        Log log3 = Log(timestamp, message, frame, hops, senderID, receiverID, true,
                                                       activityType);
                                        clients[i].log_entries.push_back(log3);
                                        std::cout << "--------" << std::endl;
                                        frame = 0;
                                        message.clear();
                                    }
                                }
                            }
                        }else if (count==0){
                            for (int j = 0; j < tempVector.size(); ++j) {
                                if (j%4==0){
                                    frame++;
                                    std::cout<<"Client "<<clients[i].client_id<<" receiving frame #"<<frame<<" from client "<<senderMac
                                             <<", but intended for client "<<receiverID<<". Forwarding... "<<std::endl;
                                    std::cout<<"Error: Unreachable destination. Packets are dropped after "<<hops<<" hops!"<<std::endl;
                                }
                                if (auto applicationLayerPacket= dynamic_cast<ApplicationLayerPacket*>(tempVector[j])){
                                    message+=applicationLayerPacket->message_data;
                                    char lastChar =applicationLayerPacket->message_data[applicationLayerPacket->message_data.size() - 1];

                                    if (lastChar=='.' || lastChar=='!' ||lastChar=='?'){
                                        ActivityType activityType=ActivityType::MESSAGE_DROPPED;
                                        Log log4= Log(timestamp,message,frame,hops,senderID,receiverID, false,activityType);
                                        clients[i].log_entries.push_back(log4);
                                        std::cout<<"--------"<<std::endl;
                                        frame=0;
                                        message.clear();
                                    }
                                }
                            }
                            clients[i].incoming_queue.pop();
                            while (!Stack2.empty()){
                                Packet* packet=Stack2.top();
                                delete packet;
                                Stack2.pop();
                            }
                        }
                    }
                }
            }
        }else if (command=="PRINT_LOG"){
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Command: "<<row<<std::endl;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::string client;
            iss>>client;
            for (int i = 0; i < clients.size(); ++i) {
                if (clients[i].client_id==client && !clients[i].log_entries.empty()){
                    std::cout<<"Client "<<client<<" Logs:"<<std::endl;
                    std::cout << std::string(client.size()+13, '-') << std::endl;
                    for (int j = 0; j < clients[i].log_entries.size(); ++j) {
                        std::cout<<"Log Entry #"<<j+1<<":"<<std::endl;
                        if (clients[i].log_entries[j].activity_type==ActivityType::MESSAGE_SENT){
                            std::cout<<"Activity: Message Sent"<<std::endl;
                            std::cout<<"Timestamp: "<<clients[i].log_entries[j].timestamp<<std::endl;
                            std::cout<<"Number of frames: "<<clients[i].log_entries[j].number_of_frames<<std::endl;
                            std::cout<<"Number of hops: "<<clients[i].log_entries[j].number_of_hops<<std::endl;
                            std::cout<<"Sender ID: "<<clients[i].log_entries[j].sender_id<<std::endl;
                            std::cout<<"Receiver ID: "<<clients[i].log_entries[j].receiver_id<<std::endl;
                            if (clients[i].log_entries[j].success_status){
                                std::cout<<"Success: Yes"<<std::endl;
                            } else{
                                std::cout<<"Success: No"<<std::endl;
                            }
                            std::cout<<"Message: "<<'"'<<clients[i].log_entries[j].message_content<<'"'<<std::endl;
                            if (j!=clients[i].log_entries.size()-1){
                                std::cout << std::string(client.size()+13, '-') << std::endl;
                            }
                        }else if (clients[i].log_entries[j].activity_type==ActivityType::MESSAGE_FORWARDED){
                            std::cout<<"Activity: Message Forwarded"<<std::endl;
                            std::cout<<"Timestamp: "<<clients[i].log_entries[j].timestamp<<std::endl;
                            std::cout<<"Number of frames: "<<clients[i].log_entries[j].number_of_frames<<std::endl;
                            std::cout<<"Number of hops: "<<clients[i].log_entries[j].number_of_hops<<std::endl;
                            std::cout<<"Sender ID: "<<clients[i].log_entries[j].sender_id<<std::endl;
                            std::cout<<"Receiver ID: "<<clients[i].log_entries[j].receiver_id<<std::endl;
                            if (clients[i].log_entries[j].success_status){
                                std::cout<<"Success: Yes"<<std::endl;
                            } else{
                                std::cout<<"Success: No"<<std::endl;
                            }
                            if (j!=clients[i].log_entries.size()-1){
                                std::cout << std::string(client.size()+13, '-') << std::endl;
                            }
                        }else if (clients[i].log_entries[j].activity_type==ActivityType::MESSAGE_RECEIVED){
                            std::cout<<"Activity: Message Received"<<std::endl;
                            std::cout<<"Timestamp: "<<clients[i].log_entries[j].timestamp<<std::endl;
                            std::cout<<"Number of frames: "<<clients[i].log_entries[j].number_of_frames<<std::endl;
                            std::cout<<"Number of hops: "<<clients[i].log_entries[j].number_of_hops<<std::endl;
                            std::cout<<"Sender ID: "<<clients[i].log_entries[j].sender_id<<std::endl;
                            std::cout<<"Receiver ID: "<<clients[i].log_entries[j].receiver_id<<std::endl;
                            if (clients[i].log_entries[j].success_status){
                                std::cout<<"Success: Yes"<<std::endl;
                            } else{
                                std::cout<<"Success: No"<<std::endl;
                            }
                            std::cout<<"Message: "<<'"'<<clients[i].log_entries[j].message_content<<'"'<<std::endl;
                            if (j!=clients[i].log_entries.size()-1){
                                std::cout << std::string(client.size()+13, '-') << std::endl;
                            }
                        }else if (clients[i].log_entries[j].activity_type==ActivityType::MESSAGE_DROPPED){
                            std::cout<<"Activity: Message Dropped"<<std::endl;
                            std::cout<<"Timestamp: "<<clients[i].log_entries[j].timestamp<<std::endl;
                            std::cout<<"Number of frames: "<<clients[i].log_entries[j].number_of_frames<<std::endl;
                            std::cout<<"Number of hops: "<<clients[i].log_entries[j].number_of_hops<<std::endl;
                            std::cout<<"Sender ID: "<<clients[i].log_entries[j].sender_id<<std::endl;
                            std::cout<<"Receiver ID: "<<clients[i].log_entries[j].receiver_id<<std::endl;
                            if (clients[i].log_entries[j].success_status){
                                std::cout<<"Success: Yes"<<std::endl;
                            } else{
                                std::cout<<"Success: No"<<std::endl;
                            }
                            if (j!=clients[i].log_entries.size()-1){
                                std::cout << std::string(client.size()+13, '-') << std::endl;
                            }
                        }
                    }
                }
            }
        }else{
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Command: "<<row<<std::endl;
            std::cout << std::string(row.size()+9, '-') << std::endl;
            std::cout<<"Invalid command."<<std::endl;
        }
    }

    // TODO: Execute the commands given as a vector of strings while utilizing the remaining arguments.
    /* Don't use any static variables, assume this method will be called over and over during testing.
     Don't forget to update the necessary member variables after processing each command. For example,
     after the MESSAGE command, the outgoing queue of the sender must have the expected frames ready to send. */
}

vector<Client> Network::read_clients(const string &filename) {
    std::ifstream file(filename);
    std::string firstLine;
    std::getline(file, firstLine);
    vector<Client> clients;
    std::string line;
    while (std::getline(file, line)) {
        istringstream iss(line);
        string clientID;
        string clientIP;
        string clientMAC;
        if (iss >> clientID >> clientIP >> clientMAC) {
            Client new_client(clientID, clientIP, clientMAC);
            clients.push_back(new_client);
        }
    }
    file.close();
    // TODO: Read clients from the given input file and return a vector of Client instances.
    return clients;
}

void Network::read_routing_tables(vector<Client> &clients, const string &filename) {
    std::ifstream file(filename);
    std::string line;
    int i=0;
    while (std::getline(file, line)) {
        istringstream iss(line);
        string first;
        string second;
        if (line.empty()) {
            continue;
        }
        if (line == "-") {
            i++;
        }

        if(iss >> first >> second){
            clients[i].routing_table.emplace(first,second); // başa ekleme yapıyor değiştirilebilir!!!
        }

    }
    file.close();
    // TODO: Read the routing tables from the given input file and populate the clients' routing_table member variable.
}

// Returns a list of token lists for each command
vector<string> Network::read_commands(const string &filename) {
    vector<string> commands;
    std::ifstream file(filename);
    std::string firstLine;
    std::getline(file, firstLine);
    std::string line;

    while (std::getline(file, line)) {
        commands.push_back(line);
    }

    file.close();

    // TODO: Read commands from the given input file and return them as a vector of strings.
    return commands;
}

Network::~Network() {


    // TODO: Free any dynamically allocated memory if necessary.
}
