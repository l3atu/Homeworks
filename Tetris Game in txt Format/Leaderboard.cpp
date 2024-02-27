#include <fstream>
#include <sstream>
#include <iostream>
#include "Leaderboard.h"

void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {
    if (!head_leaderboard_entry) {
        head_leaderboard_entry = new_entry;

    } else {
        LeaderboardEntry* current = head_leaderboard_entry;
        LeaderboardEntry* previous = nullptr;

        while (current && new_entry->score <= current->score) {
            previous = current;
            current = current->next_leaderboard_entry;
        }

        if (!previous) {
            new_entry->next_leaderboard_entry = head_leaderboard_entry;
            head_leaderboard_entry = new_entry;

        } else {
            previous->next_leaderboard_entry = new_entry;
            new_entry->next_leaderboard_entry = current;
        }
    }

    if (get_leaderboard_size() > 10) {
        remove_last_entry();
    }
    // TODO: Insert a new LeaderboardEntry instance into the leaderboard, such that the order of the high-scores
    //       is maintained, and the leaderboard size does not exceed 10 entries at any given time (only the
    //       top 10 all-time high-scores should be kept in descending order by the score).
}

void Leaderboard::write_to_file(const string& filename) {
    ofstream outfile(filename);

    LeaderboardEntry* current = head_leaderboard_entry;

    while (current != nullptr) {
        outfile << current->score << " "  << current->last_played<< " "<<current->player_name << endl;

        current = current->next_leaderboard_entry;

    }

    outfile.close();
    // TODO: Write the latest leaderboard status to the given file in the format specified in the PA instructions
}

void Leaderboard::read_from_file(const string& filename) {
    ifstream infile(filename);
    string line;

    LeaderboardEntry* current = nullptr;
    LeaderboardEntry* prev = nullptr;

    while (getline(infile, line)) {

        istringstream iss(line);
        int score;
        time_t last_time;
        string player_name;

        if (iss >> score >> last_time >> player_name) {
            LeaderboardEntry* new_entry = new LeaderboardEntry(score, last_time, player_name);

            if (!head_leaderboard_entry) {
                head_leaderboard_entry = new_entry;

            } else {
                if (!prev) {
                    head_leaderboard_entry->next_leaderboard_entry = new_entry;
                } else {
                    prev->next_leaderboard_entry = new_entry;
                }
            }
            current = new_entry;
            prev = current;
        }
    }

    infile.close();

    // TODO: Read the stored leaderboard status from the given file such that the "head_leaderboard_entry" member
    //       variable will point to the highest all-times score, and all other scores will be reachable from it
    //       via the "next_leaderboard_entry" member variable pointer.
}


void Leaderboard::print_leaderboard() {
    int order = 1;
    LeaderboardEntry* current = head_leaderboard_entry;

    cout << "Leaderboard" << endl;
    cout << "-----------" << endl;

    while (current != nullptr) {

        cout << order << ". " << current->player_name << " " << current->score << " ";

        time_t lastPlayedTime = current->last_played;
        tm* localTime = std::localtime(&lastPlayedTime);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%H:%M:%S/%d.%m.%Y", localTime);

        cout << buffer << endl;

        current = current->next_leaderboard_entry;
        order++;
    }
    // TODO: Print the current leaderboard status to the standard output in the format specified in the PA instructions
}

Leaderboard::~Leaderboard() {
    LeaderboardEntry* current = head_leaderboard_entry;

    while (current) {
        LeaderboardEntry* next = current->next_leaderboard_entry;
        delete current;
        current = next;
    }

    head_leaderboard_entry = nullptr;
    // TODO: Free dynamically allocated memory used for storing leaderboard entries
}

int Leaderboard::get_leaderboard_size() const {
    int size = 0;
    LeaderboardEntry* current = head_leaderboard_entry;


    while (current) {
        size++;
        current = current->next_leaderboard_entry;
    }

    return size;
}

void Leaderboard::remove_last_entry() {
    if (!head_leaderboard_entry) {
        return;
    }

    if (!head_leaderboard_entry->next_leaderboard_entry) {
        delete head_leaderboard_entry;
        head_leaderboard_entry = nullptr;
    } else {
        LeaderboardEntry* current = head_leaderboard_entry;
        LeaderboardEntry* previous = nullptr;

        while (current->next_leaderboard_entry) {
            previous = current;
            current = current->next_leaderboard_entry;
        }

        delete current;
        previous->next_leaderboard_entry = nullptr;
    }
}
