#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values) {\
for (auto i : (values))                      \
{                                            \
    if (i.first == #field)                   \
    {                                        \
        stringstream ss(i.second);           \
        ss >> ticket.field;                  \
    }                                        \
}}  // Реализуйте этот макрос, а также необходимые операторы для классов Date и Time


istream &operator>>(istream &is, Date &date)
{
    char c;
    is >> date.year >> c >> date.month >> c >> date.day;
}

ostream &operator<<(ostream &os, const Time &time)
{
    return os << time.hours << ":" << time.minutes;
}


istream &operator>>(istream &is, Time &time)
{
    char c;
    is >> time.hours >> c >> time.minutes;
}

bool operator==(const Time &lhs, const Time &rhs)
{
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

bool operator<(const Time &lhs, const Time &rhs)
{
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

ostream &operator<<(ostream &os, const Date &date)
{
    return os << date.year << "/" << date.month << "/" << date.day;
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Date &lhs, const Date &rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

void TestUpdate()
{
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 =
    {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 =
    {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
