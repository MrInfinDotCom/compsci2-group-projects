#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Appointment {
protected:
    string description;
    int year, month, day;
    int hour, minute;

public:
    Appointment(string desc, int y, int m, int d, int h, int min)
        : description(desc), year(y), month(m), day(d), hour(h), minute(min) {}

    virtual ~Appointment() {}

    virtual bool occurs_on(int y, int m, int d) const = 0;

    virtual void print() const {
        cout << description << " at "
             << (hour < 10 ? "0" : "") << hour << ":"
             << (minute < 10 ? "0" : "") << minute
             << " on " << year << "/" << month << "/" << day << endl;
    }
};

class Onetime : public Appointment {
public:
    Onetime(string desc, int y, int m, int d, int h, int min)
        : Appointment(desc, y, m, d, h, min) {}

    bool occurs_on(int y, int m, int d) const override {
        return y == year && m == month && d == day;
    }
};

class Daily : public Appointment {
public:
    Daily(string desc, int y, int m, int d, int h, int min)
        : Appointment(desc, y, m, d, h, min) {}

    bool occurs_on(int y, int m, int d) const override {
        return (y > year) || (y == year && m > month) || (y == year && m == month && d >= day);
    }
};

class Weekly : public Appointment {
public:
    Weekly(string desc, int y, int m, int d, int h, int min)
        : Appointment(desc, y, m, d, h, min) {}

    int day_of_week(int y, int m, int d) const {
        if (m < 3) {
            m += 12;
            y--;
        }
        int K = y % 100;
        int J = y / 100;
        int f = d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J;
        return f % 7;
    }

    bool occurs_on(int y, int m, int d) const override {
        if (y < year) return false;
        if (y == year && m < month) return false;
        if (y == year && m == month && d < day) return false;

        int startDOW = day_of_week(year, month, day);
        int queryDOW = day_of_week(y, m, d);

        if (startDOW != queryDOW) return false;

        auto days_since = [](int y, int m, int d) {
            if (m < 3) {
                y--;
                m += 12;
            }
            return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m + 8) / 5 + d;
        };

        int startDays = days_since(year, month, day);
        int queryDays = days_since(y, m, d);

        return (queryDays - startDays) % 7 == 0;
    }
};

class Monthly : public Appointment {
public:
    Monthly(string desc, int y, int m, int d, int h, int min)
        : Appointment(desc, y, m, d, h, min) {}

    bool occurs_on(int y, int m, int d) const override {
        if (y < year) return false;
        if (y == year && m < month) return false;
        if (d != day) return false;
        return true;
    }
};

int main() {
    vector<Appointment*> appts;

    // Sample data:
    appts.push_back(new Onetime("Doctor visit", 2025, 7, 15, 14, 30));
    appts.push_back(new Daily("Take medicine", 2025, 7, 10, 8, 0));
    appts.push_back(new Weekly("Team meeting", 2025, 7, 8, 10, 0)); 
    appts.push_back(new Monthly("Pay rent", 2025, 1, 1, 9, 0));

    cout << "Enter a date to check appointments, using numbers for all three units: (year month day): ";
    int y, m, d;
    cin >> y >> m >> d;

    cout << "Appointments on " << y << "/" << m << "/" << d << ":" << endl;

    bool found = false;
    for (const auto& appt : appts) {
        if (appt->occurs_on(y, m, d)) {
            appt->print();
            found = true;
        }
    }
    if (!found) {
        cout << "No appointments on this date." << endl;
    }

    for (auto& appt : appts) {
        delete appt;
    }

    return 0;
}
