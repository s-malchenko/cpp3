// #include "profile.h"
#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <map>
// #include <fstream>

using namespace std;

struct Entry
{
    long long int time;
    int client = 0;
    int rooms = 0;
};

struct Hotel
{
    queue<Entry> bookings;
    map<int, int> clientRooms;
    int totalRooms = 0;
};

class BookingManager
{
public:
    BookingManager()
    {}

    void Book(long long int time, const string &hotel, int client, int roomCnt)
    {
        // clearList(time);

        Hotel &h = bookingList[hotel];

        h.bookings.push({time, client, roomCnt});
        h.clientRooms[client] += roomCnt;
        h.totalRooms += roomCnt;
        lastTime = time;
    }

    int Clients(const string &hotel)
    {
        clearList(hotel);
        try
        {
            return bookingList.at(hotel).clientRooms.size();
        }
        catch (...)
        {
            return 0;
        }
    }

    int Rooms(const string &hotel)
    {
        clearList(hotel);
        try
        {
            return bookingList.at(hotel).totalRooms;
        }
        catch (...)
        {
            return 0;
        }
    }
private:
    map<string, Hotel> bookingList;
    long long lastTime;

    void clearList(long long int time)
    {
        for (auto &i : bookingList)
        {
            auto &entryQueue = i.second.bookings;
            while (!entryQueue.empty() && (time - 86400 >= entryQueue.front().time))
            {
                auto entry = entryQueue.front();
                entryQueue.pop();
                i.second.totalRooms -= entry.rooms;
                auto client = i.second.clientRooms.find(entry.client);
                client->second -= entry.rooms;
                if (client->second == 0)
                {
                    i.second.clientRooms.erase(client);
                }
            }
        }
    }

    void clearList(const string &hotel)
    {
        try
        {
            auto &hotelStruct = bookingList.at(hotel);
            auto &entryQueue = hotelStruct.bookings;
            while (!entryQueue.empty() && (lastTime - 86400 >= entryQueue.front().time))
            {
                auto entry = entryQueue.front();
                entryQueue.pop();
                hotelStruct.totalRooms -= entry.rooms;
                auto client = hotelStruct.clientRooms.find(entry.client);
                client->second -= entry.rooms;
                if (client->second == 0)
                {
                    hotelStruct.clientRooms.erase(client);
                }
            }
        }
        catch (...) {}
    }
};

void makeInput(int queries)
{
    ofstream os("input.txt");

    for (int i = 0; i < queries; ++i)
    {
        os << "BOOK " << i * 100 << " " << "hotel" + to_string(i / 10) << " " << to_string(i / 3) << " " << (i % 3) + 1 << endl;

        if (! (i % 3))
        {
            os << "CLIENTS " << "hotel" + to_string(i / 10) << endl;
            os << "ROOMS " << "hotel" + to_string(i / 10) << endl;
        }
    }
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // makeInput(100000);
    // return 0;

    // LOG_DURATION("booking");
    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK")
        {
            long long int time;
            string hotel;
            int client;
            int rooms;
            cin >> time >> hotel >> client >> rooms;
            manager.Book(time, hotel, client, rooms);
        }
        else if (query_type == "CLIENTS")
        {
            string hotel;
            cin >> hotel;
            cout << manager.Clients(hotel) << "\n";
        }
        else if (query_type == "ROOMS")
        {
            string hotel;
            cin >> hotel;
            cout << manager.Rooms(hotel) << "\n";
        }
    }

    return 0;
}