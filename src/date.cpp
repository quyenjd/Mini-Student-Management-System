#include "date.h"
#include <ctime>

#define is_leap(Y) (((Y)&3)==0&&((Y)%25!=0||((Y)&15)==0))
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))

date::date (const Csv::multitype& _year, const Csv::multitype& _month, const Csv::multitype& _day,
            const Csv::multitype& _hour, const Csv::multitype& _minute)
{
    year = _year.to_int();
    month = Max(1, Min(12, _month.to_int()));
    if (month == 4 || month == 6 || month == 9 || month == 11)
        day = Max(1, Min(30, _day.to_int()));
    else
    if (month == 2)
        day = Max(1, Min(28 + is_leap(year), _day.to_int()));
    else
        day = Max(1, Min(31, _day.to_int()));
    static int _t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int ty = year - month < 3;
    wday = (ty + ty / 4 - ty / 100 + ty / 400 + _t[month - 1] + day) % 7;
    hour = Max(0, Min(23, _hour.to_int()));
    minute = Max(0, Min(59, _minute.to_int()));
}

void date::now()
{
    std::time_t t = std::time(0);
    std::tm *cur = std::localtime(&t);
    year = cur->tm_year + 1900;
    month = cur->tm_mon + 1;
    day = cur->tm_mday;
    wday = cur->tm_wday;
    hour = cur->tm_hour;
    minute = cur->tm_min;
}

date& date::parse (const Csv::multitype& e, const Csv::multitype& format)
{
    year = month = day = 1;
    hour = minute = 0;
    char *_e = e.to_str(),
         *_f = format.to_str();
    int Ne = strlen(_e),
        Nf = strlen(_f);
    if (Ne != Nf)
        return *this;
    bool _year = false,
         _month = false,
         _day = false,
         _hour = false,
         _minute = false;
    for (int i = 0; i < Nf; ++i)
    {
        if (_f[i] == 'Y' && !_year)
        {
            _year = true;
            Csv::multitype __year = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'Y')
                __year = __year.append(_e[++i]);
            year = __year.to_int();
        }
        if (_f[i] == 'M' && !_month)
        {
            _month = true;
            Csv::multitype __month = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'M')
                __month = __month.append(_e[++i]);
            month = __month.to_int();
        }
        if (_f[i] == 'D' && !_day)
        {
            _day = true;
            Csv::multitype __day = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'D')
                __day = __day.append(_e[++i]);
            day = __day.to_int();
        }
        if (_f[i] == 'h' && !_hour)
        {
            _hour = true;
            Csv::multitype __hour = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'h')
                __hour = __hour.append(_e[++i]);
            hour = __hour.to_int();
        }
        if (_f[i] == 'm' && !_minute)
        {
            _minute = true;
            Csv::multitype __minute = _e[i];
            while (i + 1 < Nf && _f[i + 1] == 'm')
                __minute = __minute.append(_e[++i]);
            minute = __minute.to_int();
        }
    }
    static int _t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int ty = year - month < 3;
    wday = (ty + ty / 4 - ty / 100 + ty / 400 + _t[month - 1] + day) % 7;
    return *this;
}

Csv::multitype date::compile (const Csv::multitype& format) const
{
    char *s = format.to_str();
    int Ns = strlen(s);
    for (int i = 0; i < Ns / 2; ++i)
    {
        char tmp = s[i];
        s[i] = s[Ns - 1 - i];
        s[Ns - 1 - i] = tmp;
    }
    for (int i = 0; i < Ns; ++i)
    {
        if (s[i] == 'Y')
        {
            int _year = year;
            s[i] = char(_year % 10 + '0');
            _year /= 10;
            while (i + 1 < Ns && s[i + 1] == 'Y')
            {
                s[++i] = char(_year % 10 + '0');
                _year /= 10;
            }
        }
        if (s[i] == 'M')
        {
            int _month = month;
            s[i] = char(_month % 10 + '0');
            _month /= 10;
            while (i + 1 < Ns && s[i + 1] == 'M')
            {
                s[++i] = char(_month % 10 + '0');
                _month /= 10;
            }
        }
        if (s[i] == 'D')
        {
            int _day = day;
            s[i] = char(_day % 10 + '0');
            _day /= 10;
            while (i + 1 < Ns && s[i + 1] == 'D')
            {
                s[++i] = char(_day % 10 + '0');
                _day /= 10;
            }
        }
        if (s[i] == 'h')
        {
            int _hour = hour;
            s[i] = char(_hour % 10 + '0');
            _hour /= 10;
            while (i + 1 < Ns && s[i + 1] == 'h')
            {
                s[++i] = char(_hour % 10 + '0');
                _hour /= 10;
            }
        }
        if (s[i] == 'm')
        {
            int _minute = minute;
            s[i] = char(_minute % 10 + '0');
            _minute /= 10;
            while (i + 1 < Ns && s[i + 1] == 'm')
            {
                s[++i] = char(_minute % 10 + '0');
                _minute /= 10;
            }
        }
    }
    for (int i = 0; i < Ns / 2; ++i)
    {
        char tmp = s[i];
        s[i] = s[Ns - 1 - i];
        s[Ns - 1 - i] = tmp;
    }
    return Csv::multitype(s);
}

date date::add_day (const Csv::multitype& _day) const
{
    int day = this->day,
        month = this->month,
        year = this->year,
        hour = this->hour,
        minute = this->minute,
        cday = _day.to_int();
    while (cday != 0)
    {
        if (cday < 0)
        {
            --day;
            if (day == 0)
            {
                --month;
                if (month == 0)
                {
                    --year;
                    month = 12;
                }
                day = (month == 4 || month == 6 || month == 9 || month == 11 ? 30 :
                      (month == 2 ? (28 + is_leap(year)) : 31));
            }
            ++cday;
        }
        else
        {
            ++day;
            if (day > (month == 4 || month == 6 || month == 9 || month == 11 ? 30 :
                      (month == 2 ? (28 + is_leap(year)) : 31)))
            {
                ++month;
                if (month > 12)
                {
                    ++year;
                    month = 1;
                }
                day = 1;
            }
            --cday;
        }
    }
    return date(year, month, day, hour, minute);
}

bool date::operator< (const date& d) const
{
    return year != d.year ? (year < d.year) : (month != d.month ? (month < d.month) : (day != d.day ? (day < d.day) : (hour != d.hour ? (hour < d.hour) : (minute < d.minute))));
}

bool date::operator> (const date& d) const
{
    return year != d.year ? (year > d.year) : (month != d.month ? (month > d.month) : (day != d.day ? (day > d.day) : (hour != d.hour ? (hour > d.hour) : (minute > d.minute))));
}

bool date::operator== (const date& d) const
{
    return !(*this < d) && !(*this > d);
}

bool date::operator!= (const date& d) const
{
    return !(*this == d);
}

bool date::operator<= (const date& d) const
{
    return (*this < d) || (*this == d);
}

bool date::operator>= (const date& d) const
{
    return (*this > d) || (*this == d);
}

int date::substract (date d) const
{
    if (*this == d)
        return 0;
    if (*this < d)
        return -d.substract(*this);
    int cnt = 0;
    d.hour = hour;
    d.minute = minute;
    while (*this != d)
    {
        d = d.add_day(1);
        ++cnt;
    }
    return cnt;
}
