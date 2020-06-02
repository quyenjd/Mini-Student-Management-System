#include "interface.h"
#include <limits>

std::istream& operator>> (std::istream& in, Csv::multitype& e)
{
    std::istream::sentry cerberos(in);
    if (cerberos)
    {
        e.init();
        std::istreambuf_iterator<char> it(in), end;
        if (it != end)
        {
            std::ctype<char> const& ctype(std::use_facet<std::ctype<char> >(in.getloc()));
            Csv::list<char> buf;
            for (; it != end && !ctype.is(std::ctype_base::space, *it); ++it)
                buf.push_back(*it);

            // write to string
            int i = 0;
            char *str = new char[buf.size() + 1];
            str[buf.size()] = '\0';
            while (!buf.empty())
                str[i++] = buf.pop_front();
            e.assign(str);
        }
    }
    else
        in.setstate(std::ios_base::failbit);
    return in;
}

std::ostream& operator<< (std::ostream& out, const Csv::multitype& e)
{
    return out << e.to_str();
}

void readline (std::istream& in, Csv::multitype& e)
{
    // flush the buffer
    in.sync();

    char c;
    Csv::list<char> buf;
    e.init();
    while (true)
    {
        in.get(c);
        if (c == '\n')
            break;
        if (c == '\r')
            continue;
        buf.push_back(c);
    }

    // write to string
    int i = 0;
    char *str = new char[buf.size() + 1];
    str[buf.size()] = '\0';
    while (!buf.empty())
        str[i++] = buf.pop_front();
    e.assign(str);
}

void Interface::print_table (const table& Table,
                             const multitype& Table_head,
                             bool clrscr,
                             std::ostream& out)
{
    if (clrscr)
        system("cls"); // windows only
    out << "[ TABLE: " << Table_head << " ]" << std::endl
        << "____" << std::endl
        << std::endl;

    list<int> maxl;
    int Ncols = Table.get_keys().size(),
        Nrows = Table.num_rows();
    maxl.push_back(2);
    for (int i = 0; i < Ncols; ++i)
        maxl.push_back(strlen(Table.get_keys().at(i).to_str()));
    for (int i = 0; i < Nrows; ++i)
    {
        maxl.at(0) = Max(maxl.at(0), (int)strlen(multitype(i + 1).to_str()));
        for (int j = 0; j < Ncols; ++j)
            maxl.at(j + 1) = Max(maxl.at(j + 1), (int)strlen(Table.get_row(i).at(j).to_str()));
    }

    // write
    out << "No  ";
    for (int i = 0; i < maxl.at(0) - 2; ++i)
        out << " ";
    for (int i = 0; i < Ncols; ++i)
    {
        multitype e = Table.get_keys().at(i);
        out << e << "  ";
        for (int j = 0; j < maxl.at(i + 1) - (int)strlen(e.to_str()); ++j)
            out << " ";
    }
    out << std::endl;
    for (int i = 0; i < maxl.at(0); ++i)
        out << "-";
    out << "  ";
    for (int i = 0; i < Ncols; ++i)
    {
        for (int j = 0; j < maxl.at(i + 1); ++j)
            out << "-";
        out << "  ";
    }
    out << std::endl;
    for (int i = 0; i < Nrows; ++i)
    {
        multitype e = i + 1;
        out << e << "  ";
        for (int j = 0; j < maxl.at(0) - (int)strlen(e.to_str()); ++j)
            out << " ";
        for (int j = 0; j < Ncols; ++j)
        {
            multitype e = Table.get_row(i).at(j);
            out << e << "  ";
            for (int k = 0; k < maxl.at(j + 1) - (int)strlen(e.to_str()); ++k)
                out << " ";
        }
        out << std::endl;
    }
    out << "____" << std::endl
        << std::endl;
}
