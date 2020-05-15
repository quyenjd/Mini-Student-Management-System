#ifndef CSV_IMPL_QUYENJD_H
#define CSV_IMPL_QUYENJD_H

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cinttypes>

namespace Csv
{
    inline void string_copy (const Pchar from, Pchar& to)
    {
        to = (Pchar)malloc(strlen(from) + 1);
        for (Pchar p = to; (*p = *from) != '\0'; ++p, ++from);
    }

    inline multitype::multitype()
    {
        init();
    }

    inline multitype::multitype (const Int e)
    {
        assign(e);
    }

    inline multitype::multitype (const Long e)
    {
        assign(e);
    }

    inline multitype::multitype (const Char e)
    {
        assign(e);
    }

    inline multitype::multitype (const Pchar e)
    {
        assign(e);
    }

    inline multitype::multitype (const Double e)
    {
        assign(e);
    }

    inline multitype::multitype (const multitype& e)
    {
        assign(e);
    }

    inline void multitype::init()
    {
        string_copy("unknown", _type);
        values = _tunknown();
    }

    inline void multitype::assign (const Int e)
    {
        string_copy("int", _type);
        values._tint = e;
    }

    inline void multitype::assign (const Long e)
    {
        string_copy("long", _type);
        values._tlong = e;
    }

    inline void multitype::assign (const Char e)
    {
        string_copy("char", _type);
        values._tchar = e;
    }

    inline void multitype::assign (const Pchar e)
    {
        string_copy("str", _type);
        string_copy(e, values._tpchar);
    }

    inline void multitype::assign (const Double e)
    {
        string_copy("double", _type);
        values._tdouble = e;
    }

    inline void multitype::assign (const multitype& e)
    {
        string_copy(e.type(), _type);
        if (e.is_type("int"))
            values._tint = e.to_int();
        if (e.is_type("long"))
            values._tlong = e.to_long();
        if (e.is_type("char"))
            values._tchar = e.to_char();
        if (e.is_type("str"))
            string_copy(e.to_str(), values._tpchar);
        if (e.is_type("double"))
            values._tdouble = e.to_double();
    }

    inline multitype& multitype::operator= (const Int e)
    {
        assign(e);
        return *this;
    }

    inline multitype& multitype::operator= (const Long e)
    {
        assign(e);
        return *this;
    }

    inline multitype& multitype::operator= (const Char e)
    {
        assign(e);
        return *this;
    }

    inline multitype& multitype::operator= (const Pchar e)
    {
        assign(e);
        return *this;
    }

    inline multitype& multitype::operator= (const Double e)
    {
        assign(e);
        return *this;
    }

    inline multitype& multitype::operator= (const multitype& e)
    {
        assign(e);
        return *this;
    }

    inline char* multitype::type() const
    {
        return _type;
    }

    inline bool multitype::is_type (const Pchar e) const
    {
        return strcmp(_type, e) == 0;
    }

    inline bool multitype::is_unknown() const
    {
        return is_type("unknown");
    }

    inline Int multitype::to_int() const
    {
        if (is_type("int"))
            return values._tint;
        if (is_type("long"))
            return values._tlong;
        if (is_type("char"))
            return values._tchar >= '0' && values._tchar <= '9' ? (values._tchar - '0') : (Int)values._tchar;
        if (is_type("str"))
        {
            bool neg = values._tpchar[0] == '-';
            Int ret = 0;
            for (Int i = neg; i < (Int)strlen(values._tpchar); ++i)
                if (values._tpchar[i] >= '0' && values._tpchar[i] <= '9')
                    ret = ret*10 + values._tpchar[i] - '0';
                else
                    break;
            if (neg)
                ret = -ret;
            return ret;
        }
        if (is_type("double"))
            return (Int)values._tdouble;
        return 0;
    }

    inline Long multitype::to_long() const
    {
        if (is_type("int"))
            return values._tint;
        if (is_type("long"))
            return values._tlong;
        if (is_type("char"))
            return values._tchar >= '0' && values._tchar <= '9' ? (values._tchar - '0') : (Long)values._tchar;
        if (is_type("str"))
        {
            bool neg = values._tpchar[0] == '-';
            Long ret = 0;
            for (Int i = neg; i < (Int)strlen(values._tpchar); ++i)
                if (values._tpchar[i] >= '0' && values._tpchar[i] <= '9')
                    ret = ret*10 + values._tpchar[i] - '0';
                else
                    break;
            if (neg)
                ret = -ret;
            return ret;
        }
        if (is_type("double"))
            return (Long)values._tdouble;
        return 0;
    }

    inline Char multitype::to_char() const
    {
        if (is_type("int"))
        {
            Char buf[2];
            snprintf(buf, 2, "%d", values._tint);
            return buf[0];
        }
        if (is_type("char"))
            return values._tchar;
        if (is_type("str"))
            return values._tpchar[0];
        if (is_type("double"))
        {
            Char buf[2];
            snprintf(buf, 2, "%f", values._tdouble);
            return buf[0];
        }
        return 0;
    }

    inline Pchar multitype::to_str() const
    {
        if (is_type("int"))
        {
            Char *buf = new char[STR_BUFFER];
            snprintf(buf, STR_BUFFER, "%d", values._tint);
            return buf;
        }
        if (is_type("long"))
        {
            Char *buf = new char[STR_BUFFER];
            snprintf(buf, STR_BUFFER, "%" PRId64, values._tlong);
            return buf;
        }
        if (is_type("char"))
        {
            Char *buf = new char[2];
            buf[0] = values._tchar;
            return buf;
        }
        if (is_type("str"))
            return values._tpchar;
        if (is_type("double"))
        {
            Char *buf = new char[STR_BUFFER];
            snprintf(buf, STR_BUFFER, "%.15f", values._tdouble);
            return buf;
        }
        return new char;
    }

    inline Double multitype::to_double() const
    {
        if (is_type("int"))
            return (Double)values._tint;
        if (is_type("long"))
            return (Double)values._tlong;
        if (is_type("char"))
        {
            if (values._tchar >= '0' && values._tchar <= '9')
                return values._tchar - '0';
        }
        if (is_type("str"))
        {
            bool neg = values._tpchar[0] == '-';
            Double ret = 0;
            Int i = neg;
            for (; i < (Int)strlen(values._tpchar); ++i)
                if (values._tpchar[i] >= '0' && values._tpchar[i] <= '9')
                    ret = ret*10 + values._tpchar[i] - '0';
                else
                    break;
            if (i < (Int)strlen(values._tpchar) && values._tpchar[i++] == '.')
            {
                for (Double j = 0.1; i < (Int)strlen(values._tpchar); ++i, j /= 10)
                    if (values._tpchar[i] >= '0' && values._tpchar[i] <= '9')
                        ret += j * (values._tpchar[i] - '0');
                    else
                        break;
            }
            if (neg)
                ret = -ret;
            return ret;
        }
        if (is_type("double"))
            return values._tdouble;

        #ifdef NAN
        return NAN;
        #elif defined INFINITY
        return INFINITY;
        #else
        return 0;
        #endif
    }

    inline bool multitype::equal (const multitype& e) const
    {
        if (is_type(e.type()))
            return strict_equal(e);
        if (is_type("str") || e.is_type("str"))
            return strcmp(to_str(), e.to_str()) == 0;
        if (is_type("double") || e.is_type("double"))
            return fabs(to_double() - e.to_double()) < REAL_EPS;
        return to_long() == e.to_long();
    }

    inline bool multitype::strict_equal (const multitype& e) const
    {
        if (!is_type(e.type()))
            return false;
        if (is_type("int"))
            return values._tint == e.to_int();
        if (is_type("long"))
            return values._tlong == e.to_long();
        if (is_type("char"))
            return values._tchar == e.to_char();
        if (is_type("str"))
            return strcmp(values._tpchar, e.to_str()) == 0;
        if (is_type("double"))
            return fabs(values._tdouble - e.to_double()) < REAL_EPS;
        return false;
    }

    template<typename T>
    inline list<T>::list (Int num_elms)
    {
        head = new iter();
        _size = 0;
        for (Int i = 0; i < num_elms; ++i)
            push_back(T());
    }

    template<typename T>
    inline void list<T>::push_back (const T& e)
    {
        iter *root = head;
        while (root->next != nullptr)
            root = root->next;
        root->next = new iter();
        root->next->value = e;
        ++_size;
    }

    template<typename T>
    inline void list<T>::push_front (const T& e)
    {
        iter *add = new iter();
        add->next = head->next;
        add->next->value = e;
        head->next = add;
        ++_size;
    }

    template<typename T>
    inline T list<T>::pop_back()
    {
        if (empty())
            return T();
        iter *root = head;
        while (root->next->next != nullptr)
            root = root->next;
        T value = root->next->value;
        delete[] root->next;
        root->next = nullptr;
        --_size;
        return value;
    }

    template<typename T>
    inline T list<T>::pop_front()
    {
        if (empty())
            return T();
        iter *next = head->next->next;
        T value = head->next->value;
        delete[] head->next;
        head->next = next;
        --_size;
        return value;
    }

    template<typename T>
    inline void list<T>::insert (Int pos, const T& e)
    {
        iter *root = head;
        while (pos-- && root->next != nullptr)
            root = root->next;
        iter *add = new iter();
        add->next = root->next;
        add->next->value = e;
        root->next = add;
        ++_size;
    }

    template<typename T>
    inline void list<T>::destroy_util (iter *root)
    {
        if (root->next != nullptr)
            destroy_util(root->next);
        delete[] root;
        root = nullptr;
        --_size;
    }

    template<typename T>
    inline void list<T>::destroy()
    {
        destroy_util(head);
    }

    template<typename T>
    inline bool list<T>::empty() const
    {
        return head->next == nullptr;
    }

    template<typename T>
    inline Int list<T>::size() const
    {
        return _size;
    }

    template<typename T>
    inline T& list<T>::at (Int pos)
    {
        if (pos < 0 || pos >= _size)
            return *new T();
        iter *root = head;
        while (pos-- && root->next != nullptr)
            root = root->next;
        return root->next->value;
    }

    template<typename T>
    inline T list<T>::at (Int pos) const
    {
        if (pos < 0 || pos >= _size)
            return T();
        iter *root = head;
        while (pos-- && root->next != nullptr)
            root = root->next;
        return root->next->value;
    }

    template<typename T>
    inline void list<T>::delete_at (Int pos)
    {
        if (pos < 0 || pos >= _size)
            return;
        iter *root = head;
        while (pos-- && root->next != nullptr)
            root = root->next;
        iter *next = root->next->next;
        delete[] root->next;
        root->next = next;
        --_size;
    }

    inline table::table()
    {
        rows = new plist();
        _num_rows = 0;
    }

    inline void table::add_key (const multitype& e)
    {
        if (has_key(e))
            return;
        keys.push_back(e);
        plist *head = rows;
        while (head->next != nullptr)
        {
            head->next->value.push_back(multitype());
            head = head->next;
        }
    }

    inline void table::rm_key (const multitype& e)
    {
        for (Int i = 0; i < keys.size(); ++i)
            if (e.strict_equal(keys.at(i)))
            {
                keys.delete_at(i);
                plist *head = rows;
                while (head->next != nullptr)
                {
                    head->next->value.delete_at(i);
                    head = head->next;
                }
                return;
            }
    }

    inline bool table::has_key (const multitype& e) const
    {
        return get_key(e) != -1;
    }

    inline Int table::get_key (const multitype& e) const
    {
        for (Int i = 0; i < keys.size(); ++i)
            if (e.strict_equal(keys.at(i)))
                return i;
        return -1;
    }

    inline list<multitype> table::get_keys() const
    {
        return keys;
    }

    inline void table::add_row()
    {
        plist *head = rows;
        while (head->next != nullptr)
            head = head->next;
        head->next = new plist();
        head->next->value = list<multitype>(keys.size());
        ++_num_rows;
    }

    inline void table::rm_row (Int row)
    {
        if (row < 0 || row >= _num_rows)
            return;
        plist *head = rows;
        while (row-- && head->next != nullptr)
            head = head->next;
        plist *next = head->next->next;
        delete[] head->next;
        head->next = next;
        --_num_rows;
    }

    inline Int table::num_rows() const
    {
        return _num_rows;
    }

    inline list<multitype>& table::get_row (Int row)
    {
        if (row < 0 || row >= _num_rows)
            return *new list<multitype>();
        plist *head = rows;
        while (row-- && head->next != nullptr)
            head = head->next;
        return head->next->value;
    }

    inline list<multitype> table::get_row (Int row) const
    {
        if (row < 0 || row >= _num_rows)
            return *new list<multitype>();
        plist *head = rows;
        while (row-- && head->next != nullptr)
            head = head->next;
        return head->next->value;
    }

    inline list<multitype>& table::get_row_where (const multitype& key_search, const multitype& e)
    {
        Int key_id = get_key(key_search);
        if (key_id == -1)
            return *new list<multitype>();
        plist *head = rows;
        while (head->next != nullptr)
        {
            if (head->next->value.at(key_id).equal(e))
                return head->next->value;
            head = head->next;
        }
        return *new list<multitype>();
    }

    inline list<multitype> table::get_row_where (const multitype& key_search, const multitype& e) const
    {
        Int key_id = get_key(key_search);
        if (key_id == -1)
            return list<multitype>();
        plist *head = rows;
        while (head->next != nullptr)
        {
            if (head->next->value.at(key_id).equal(e))
                return head->next->value;
            head = head->next;
        }
        return list<multitype>();
    }

    inline multitype& table::get (Int row, const multitype& key)
    {
        if (row < 0 || row >= _num_rows)
            return *new multitype("bad_access");
        plist *head = rows;
        while (row-- && head->next != nullptr)
            head = head->next;
        Int pos = get_key(key);
        return pos == -1 ? (*new multitype("bad_access")) : head->next->value.at(pos);
    }

    inline multitype table::get (Int row, const multitype& key) const
    {
        if (row < 0 || row >= _num_rows)
            return multitype("bad_access");
        plist *head = rows;
        while (row-- && head->next != nullptr)
            head = head->next;
        Int pos = get_key(key);
        return pos == -1 ? (*new multitype("bad_access")) : head->next->value.at(pos);
    }

    inline multitype& table::get_where (const multitype& key_search, const multitype& e, const multitype& key_get)
    {
        Int key_sid = get_key(key_search),
            key_gid = get_key(key_get);
        if (key_sid == -1 || key_gid == -1)
            return *new multitype("bad_access");
        plist *head = rows;
        while (head->next != nullptr)
        {
            if (head->next->value.at(key_sid).equal(e))
                return head->next->value.at(key_gid);
            head = head->next;
        }
        return *new multitype("bad_access");
    }

    inline multitype table::get_where (const multitype& key_search, const multitype& e, const multitype& key_get) const
    {
        Int key_sid = get_key(key_search),
            key_gid = get_key(key_get);
        if (key_sid == -1 || key_gid == -1)
            return multitype("bad_access");
        plist *head = rows;
        while (head->next != nullptr)
        {
            if (head->next->value.at(key_sid).equal(e))
                return head->next->value.at(key_gid);
            head = head->next;
        }
        return multitype("bad_access");
    }

    inline bool table::del_row_where (const multitype& key_search, const multitype& e)
    {
        Int key_sid = get_key(key_search);
        if (key_sid == -1)
            return false;
        plist *head = rows;
        while (head->next != nullptr)
        {
            if (head->next->value.at(key_sid).equal(e))
            {
                plist *next = head->next->next;
                delete[] head->next;
                head->next = next;
                return true;
            }
            head = head->next;
        }
        return false;
    }

    inline Char csv_handler::csv_read_char()
    {
        if (fptr == nullptr || feof(fptr))
            return '\0';
        Int ch = fgetc(fptr);
        if (ch == EOF)
            return '\0';
        if (ch != '\n' && ch != '\r' && ch != '\t' && ch != '\v' && ch != '\a' && ch != '\b' && ch != '\f')
            csv_str.push_back((Char)ch);
        return ch;
    }

    inline Char csv_handler::csv_break_line()
    {
        if (fptr == nullptr || feof(fptr))
            return '\0';
        while (true)
        {
            Int ch = fgetc(fptr);
            if (ch == EOF)
                return '\0';
            if (ch == '\n')
                return '\n';
        }
        return '\0';
    }

    inline Pchar csv_handler::csv_export_pchar()
    {
        Pchar ret = new Char[csv_str.size() + 1];
        Int i = 0;
        for (; !csv_str.empty(); ++i)
            ret[i] = csv_str.pop_front();
        ret[i] = '\0';
        return ret;
    }

    inline csv_handler::csv_handler (const Pchar _filename)
    {
        _table = table();
        string_copy(_filename, filename);
        fptr = nullptr;
    }

    inline bool csv_handler::init_read()
    {
        return (fptr = fopen(filename, "r")) != nullptr;
    }

    inline bool csv_handler::init_write()
    {
        return (fptr = fopen(filename, "w")) != nullptr;
    }

    inline void csv_handler::read_and_terminate (const Char delim)
    {
        if (fptr == nullptr)
            return;
        while (!csv_str.empty())
            csv_str.pop_back();
        Char ch;

        // Table head
        do
        {
            ch = csv_read_char();
            if (ch == delim)
                csv_str.pop_back();
            if (ch == delim || ch == '\n')
                _table.add_key(csv_export_pchar());
        }
        while (ch != '\n');

        // Table rows
        bool flag = true;
        for (Int i = 0; flag; ++i)
        {
            _table.add_row();
            Int j = 0;
            while (j < _table.get_keys().size())
            {
                Char ch = csv_read_char();
                if (ch == '\0')
                {
                    flag = false;
                    break;
                }
                if (ch == '\n')
                {
                    _table.get_row(i).at(j++).assign(csv_export_pchar());
                    break;
                }
                if (ch == delim)
                {
                    csv_str.pop_back();
                    _table.get_row(i).at(j++).assign(csv_export_pchar());
                    if (j == _table.get_keys().size())
                        csv_break_line();
                }
            }
        }

        // Pop trailing invalid rows
        for (Int i = _table.num_rows() - 1; i >= 0; --i)
        {
            bool has_unknown = false;
            list<multitype> _row = _table.get_row(i);
            for (Int j = 0; j < _row.size(); ++j)
                has_unknown |= _row.at(j).is_unknown();
            if (has_unknown)
                _table.rm_row(i);
        }

        terminate();
    }

    inline void csv_handler::write_and_terminate (const Char delim)
    {
        if (fptr == nullptr)
            return;

        // Write head
        Int countHeads = _table.get_keys().size();
        for (Int i = 0; i < countHeads; ++i)
            if (i == countHeads - 1)
                fprintf(fptr, "%s", _table.get_keys().at(i).to_str());
            else
                fprintf(fptr, "%s%c", _table.get_keys().at(i).to_str(), delim);
        fprintf(fptr, "\n");

        // Write rows
        for (Int i = 0; i < _table.num_rows(); ++i)
        {
            Int countCols = _table.get_row(i).size();
            for (Int j = 0; j < countCols; ++j)
                if (j == countCols - 1)
                    fprintf(fptr, "%s", _table.get_row(i).at(j).to_str());
                else
                    fprintf(fptr, "%s%c", _table.get_row(i).at(j).to_str(), delim);
            fprintf(fptr, "\n");
        }

        terminate();
    }

    inline void csv_handler::terminate()
    {
        fclose(fptr);
    }

    inline table& csv_handler::get_table()
    {
        return _table;
    }

    inline table csv_handler::get_table() const
    {
        return _table;
    }
}

#endif // CSV_IMPL_QUYENJD_H
