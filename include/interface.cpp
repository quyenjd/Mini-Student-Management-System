#include "interface.h"

std::istream& operator>> (std::istream& in, multitype& e)
{
    std::istream::sentry cerberos(in);
    if (cerberos)
    {
        e.init();
        std::istreambuf_iterator<char> it(in), end;
        if (it != end)
        {
            std::ctype<char> const& ctype(std::use_facet<std::ctype<char> >(in.getloc()));
            list<char> buf;
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

std::ostream& operator<< (std::ostream& out, const multitype& e)
{
    return out << e.to_str();
}

void readline (std::istream& in, multitype& e)
{
    char c;
    list<char> buf;

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
        << std::endl
        << "----" << std::endl;

    list<int> maxl;
    int Ncols = Table.get_keys().size(),
        Nrows = Table.num_rows();
    for (int i = 0; i < Ncols; ++i)
        maxl.push_back(strlen(Table.get_keys().at(i).to_str()));
    for (int i = 0; i < Nrows; ++i)
        for (int j = 0; j < Ncols; ++j)
            maxl.at(j) = Max(maxl.at(j), (int)strlen(Table.get_row(i).at(j).to_str()));

    // write
    for (int i = 0; i < Ncols; ++i)
    {
        multitype e = Table.get_keys().at(i);
        out << e << " ";
        for (int j = 0; j < maxl.at(i) - (int)strlen(e.to_str()); ++j)
            out << " ";
    }
    out << std::endl;
    for (int i = 0; i < Nrows; ++i)
    {
        for (int j = 0; j < Ncols; ++j)
        {
            multitype e = Table.get_row(i).at(j);
            out << e << " ";
            for (int j = 0; j < maxl.at(i) - (int)strlen(e.to_str()); ++j)
                out << " ";
        }
        out << std::endl;
    }
    out << "----" << std::endl
        << std::endl;
}
