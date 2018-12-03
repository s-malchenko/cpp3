#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <map>

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
        clearList(time);

        Hotel h;

        h.bookings.push({time, client, roomCnt});
        h.clientRooms[client] += roomCnt;

        bookingList[hotel] = h;
    }

    int Clients(const string &hotel) const
    {
        try
        {
            return bookingList.at(hotel).clientRooms.size();
        }
        catch (...)
        {
            return 0;
        }
    }

    int Rooms(const string &hotel) const
    {
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

    void clearList(long long int time)
    {
        for (auto &i : bookingList)
        {
            auto entry = i.second.bookings.front();
            while (time - entry.time >= 86400)
            {
                i.second.bookings.pop();
                i.second.totalRooms -= entry.rooms;
                auto client = i.second.clientRooms.find(entry.client);
                client->second -= entry.rooms;
                if (client->second == 0)
                {
                    i.second.clientRooms.erase(client);
                }

                
                entry = i.second.bookings.front();
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // LOG_DURATION("ebook");
    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

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
            cout << manager.Clients(hotel) << "\n";
        }
        else if (query_type == "ROOMS")
        {
            string hotel;
            cout << manager.Rooms(hotel) << "\n";
        }
    }

    return 0;
}