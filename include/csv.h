#ifndef CSV_QUYENJD_H
#define CSV_QUYENJD_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cinttypes>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define REAL_EPS 1e-6
#define STR_BUFFER 256
#define Int int
#define Long long long
#define Char char
#define Pchar char*
#define Double double

namespace Csv
{
    // dynamically copy the string 'from' to the string 'to', i.e. to = from. same as
    // strcpy but satisfying the condition sizeof(to) >= sizeof(from) is not necessary.
    inline void string_copy (const Pchar from, Pchar& to)
    {
        to = (Pchar)malloc(strlen(from) + 1);
        for (Pchar p = to; (*p = *from) != '\0'; ++p, ++from);
    }

    // eliminate all C++ variable-type strains with multitype.
    class multitype
    {
    private:
        union _tunknown
        {
            Int    _tint;
            Long   _tlong;
            Char   _tchar;
            Pchar  _tpchar;
            Double _tdouble;
        } values;
        Pchar _type;

    public:
        // constructors.
        multitype()
        {
            init();
        }
        multitype (const Int e)
        {
            assign(e);
        }
        multitype (const Long e)
        {
            assign(e);
        }
        multitype (const Char e)
        {
            assign(e);
        }
        multitype (const Pchar e)
        {
            assign(e);
        }
        multitype (const Double e)
        {
            assign(e);
        }
        multitype (const multitype& e)
        {
            assign(e);
        }

        // set multitype back to default value.
        void init()
        {
            string_copy("unknown", _type);
            values = _tunknown();
        }

        // assign functions
        void assign (const Int e)
        {
            string_copy("int", _type);
            values._tint = e;
        }
        void assign (const Long e)
        {
            string_copy("long", _type);
            values._tlong = e;
        }
        void assign (const Char e)
        {
            string_copy("char", _type);
            values._tchar = e;
        }
        void assign (const Pchar e)
        {
            string_copy("str", _type);
            string_copy(e, values._tpchar);
        }
        void assign (const Double e)
        {
            string_copy("double", _type);
            values._tdouble = e;
        }
        void assign (const multitype& e)
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
        multitype& operator= (const Int e)
        {
            assign(e);
            return *this;
        }
        multitype& operator= (const Long e)
        {
            assign(e);
            return *this;
        }
        multitype& operator= (const Char e)
        {
            assign(e);
            return *this;
        }
        multitype& operator= (const Pchar e)
        {
            assign(e);
            return *this;
        }
        multitype& operator= (const Double e)
        {
            assign(e);
            return *this;
        }
        multitype& operator= (const multitype& e)
        {
            assign(e);
            return *this;
        }

        // append e.to_str() to the end of this->to_str().
        // this changes the type of 'this' to "str".
        multitype& append (const multitype& e)
        {
            Char *cur = to_str(),
                 *app = e.to_str(),
                 *res = new Char[strlen(cur) + strlen(app) + 1];
            Int j = 0;
            for (Int i = 0; i < (Int)strlen(cur); res[j++] = cur[i++]);
            for (Int i = 0; i < (Int)strlen(app); res[j++] = app[i++]);
            res[j] = '\0';
            assign(res);
            return *this;
        }

        // get type of current value. returns "int", "long", "char", "str", "double"
        // or "unknown" (default).
        Pchar type() const
        {
            return _type;
        }

        // check if current value has the type of e. this equals to 'type() == e'.
        bool is_type (const Pchar e) const
        {
            return strcmp(_type, e) == 0;
        }

        // check if the value has not been set so far. this equals to 'type() == "unknown"'
        // and 'is_type("unknown")'
        bool is_unknown() const
        {
            return is_type("unknown");
        }

        // convert current value (of any type) to int.
        Int to_int() const
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

        // convert current value (of any type) to long long.
        Long to_long() const
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

        // convert current value (of any type) to char.
        Char to_char() const
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

        // convert current value (of any type) to string.
        Pchar to_str() const
        {
            if (is_type("int"))
            {
                Pchar buf = new Char[STR_BUFFER];
                snprintf(buf, STR_BUFFER, "%d", values._tint);
                return buf;
            }
            if (is_type("long"))
            {
                Pchar buf = new Char[STR_BUFFER];
                snprintf(buf, STR_BUFFER, "%" PRId64, values._tlong);
                return buf;
            }
            if (is_type("char"))
            {
                Pchar buf = new Char[2];
                buf[0] = values._tchar;
                return buf;
            }
            if (is_type("str"))
                return values._tpchar;
            if (is_type("double"))
            {
                Pchar buf = new Char[STR_BUFFER];
                snprintf(buf, STR_BUFFER, "%.15f", values._tdouble);

                // trim trailing zeroes
                char *p = strchr(buf, '.');
                int count;

                if (p != NULL)
                {
                    count = 10;
                    while (count >= 0)
                    {
                         --count;
                         if (*p == '\0')
                             break;
                         ++p;
                    }
                    *p-- = '\0';
                    while (*p == '0')
                        *p-- = '\0';
                    if (*p == '.')
                        *p = '\0';
                }
                return buf;
            }
            return new Char;
        }

        // convert current value (of any type) to double.
        Double to_double() const
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

        // compare two multitypes. this function first converts the values into the
        // same logical type before making the comparison.
        bool equal (const multitype& e) const
        {
            if (is_type(e.type()))
                return strict_equal(e);
            if (is_type("str") || e.is_type("str"))
                return strcmp(to_str(), e.to_str()) == 0;
            if (is_type("double") || e.is_type("double"))
                return fabs(to_double() - e.to_double()) < REAL_EPS;
            return to_long() == e.to_long();
        }

        // same as equal but this function does not convert any value. thus, if the
        // values differ in type, it returns FALSE.
        bool strict_equal (const multitype& e) const
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
    };

    // a linked list powered by a handful of functions.
    template<typename T>
    class list
    {
    private:
        struct iter
        {
            struct iter *next;
            T value;
        } *head;
        Int _size;

        void destroy_util (iter *root)
        {
            if (root->next == nullptr)
                return;
            destroy_util(root->next);
            delete[] root->next;
            root->next = nullptr;
            --_size;
        }

    public:
        // constructors. if 'num_elms' is given, this function reserves a number of
        // elements after initialization.
        list (Int num_elms = 0)
        {
            head = new iter();
            _size = 0;
            for (Int i = 0; i < num_elms; ++i)
                push_back(T());
        }

        // push an element with value 'e' to the back of the list.
        void push_back (const T& e)
        {
            iter *root = head;
            while (root->next != nullptr)
                root = root->next;
            root->next = new iter();
            root->next->value = e;
            ++_size;
        }

        // push an element with value 'e' to the front of the list.
        void push_front (const T& e)
        {
            iter *add = new iter();
            add->next = head->next;
            add->next->value = e;
            head->next = add;
            ++_size;
        }

        // pop an element from the back of the list and return it.
        T pop_back()
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

        // pop an element from the front of the list and return it.
        T pop_front()
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

        // insert an element with value 'e' at the position 'pos'.
        void insert (Int pos, const T& e)
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

        // destroy the list, i.e. delete all elements.
        void destroy()
        {
            destroy_util(head);
        }

        // check if the list is empty.
        bool empty() const
        {
            return head->next == nullptr;
        }

        // get the size of the list.
        Int size() const
        {
            return _size;
        }

        // get the value at the position 'pos'.
        T& at (Int pos)
        {
            if (pos < 0 || pos >= _size)
                return *new T();
            iter *root = head;
            while (pos-- && root->next != nullptr)
                root = root->next;
            return root->next->value;
        }
        T at (Int pos) const
        {
            if (pos < 0 || pos >= _size)
                return T();
            iter *root = head;
            while (pos-- && root->next != nullptr)
                root = root->next;
            return root->next->value;
        }

        // remove the element at the position 'pos' from the list.
        void delete_at (Int pos)
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
    };

    // main database saver/handler of the whole project.
    class table
    {
    private:
        struct plist
        {
            struct plist *next;
            list<multitype> value;
        } *rows;
        list<multitype> keys;

        Int _num_rows;

    public:
        // constructor.
        table()
        {
            rows = new plist();
            _num_rows = 0;
        }

        // add new column with name 'e' to the table.
        void add_key (const multitype& e)
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

        // entirely remove a column with name 'e' from the table.
        void rm_key (const multitype& e)
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

        // get the ordinary number of the column named 'e' (starting from 0).
        Int get_key (const multitype& e) const
        {
            for (Int i = 0; i < keys.size(); ++i)
                if (e.strict_equal(keys.at(i)))
                    return i;
            return -1;
        }

        // check if the table has a column named 'e'.
        bool has_key (const multitype& e) const
        {
            return get_key(e) != -1;
        }

        // get the name list of all table columns.
        list<multitype> get_keys() const
        {
            return keys;
        }

        // add a row to the table
        void add_row()
        {
            plist *head = rows;
            while (head->next != nullptr)
                head = head->next;
            head->next = new plist();
            head->next->value = list<multitype>(keys.size());
            ++_num_rows;
        }

        // remove the 'row'-th row from the table (starting from 0).
        void rm_row (Int row)
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

        // get the number of rows in the table, not including the table head,
        // i.e. the row containing the column names.
        Int num_rows() const
        {
            return _num_rows;
        }

        // get the 'row'-th row.
        list<multitype>& get_row (Int row)
        {
            if (row < 0 || row >= _num_rows)
                return *new list<multitype>();
            plist *head = rows;
            while (row-- && head->next != nullptr)
                head = head->next;
            return head->next->value;
        }
        list<multitype> get_row (Int row) const
        {
            if (row < 0 || row >= _num_rows)
                return *new list<multitype>();
            plist *head = rows;
            while (row-- && head->next != nullptr)
                head = head->next;
            return head->next->value;
        }

        // get the row where the column named 'key_search' has the value of 'e'.
        // this function uses equal() to compare the values.
        // if there are multiple rows satisfying the condition, only the first valid
        // one is returned.
        list<multitype>& get_row_where (const multitype& key_search, const multitype& e, bool strict = false)
        {
            Int key_id = get_key(key_search);
            if (key_id == -1)
                return *new list<multitype>();
            plist *head = rows;
            while (head->next != nullptr)
            {
                if (strict ? head->next->value.at(key_id).strict_equal(e) : head->next->value.at(key_id).equal(e))
                    return head->next->value;
                head = head->next;
            }
            return *new list<multitype>();
        }
        list<multitype> get_row_where (const multitype& key_search, const multitype& e, bool strict = false) const
        {
            Int key_id = get_key(key_search);
            if (key_id == -1)
                return list<multitype>();
            plist *head = rows;
            while (head->next != nullptr)
            {
                if (strict ? head->next->value.at(key_id).strict_equal(e) : head->next->value.at(key_id).equal(e))
                    return head->next->value;
                head = head->next;
            }
            return list<multitype>();
        }

        // get the value of the column named 'key' on the 'row'-th row.
        multitype& get (Int row, const multitype& key)
        {
            if (row < 0 || row >= _num_rows)
                return *new multitype("bad_access");
            plist *head = rows;
            while (row-- && head->next != nullptr)
                head = head->next;
            Int pos = get_key(key);
            return pos == -1 ? (*new multitype("bad_access")) : head->next->value.at(pos);
        }
        multitype get (Int row, const multitype& key) const
        {
            if (row < 0 || row >= _num_rows)
                return multitype("bad_access");
            plist *head = rows;
            while (row-- && head->next != nullptr)
                head = head->next;
            Int pos = get_key(key);
            return pos == -1 ? (*new multitype("bad_access")) : head->next->value.at(pos);
        }

        // get the value of the column named 'key_get' on the row where there is
        // a column named 'key_search' that has the value of 'e'.
        // if there are multiple rows satisfying the condition, only the first valid
        // one is returned.
        multitype& get_where (const multitype& key_search, const multitype& e, const multitype& key_get, bool strict = false)
        {
            Int key_sid = get_key(key_search),
                key_gid = get_key(key_get);
            if (key_sid == -1 || key_gid == -1)
                return *new multitype("bad_access");
            plist *head = rows;
            while (head->next != nullptr)
            {
                if (strict ? head->next->value.at(key_sid).strict_equal(e) : head->next->value.at(key_sid).equal(e))
                    return head->next->value.at(key_gid);
                head = head->next;
            }
            return *new multitype("bad_access");
        }
        multitype get_where (const multitype& key_search, const multitype& e, const multitype& key_get, bool strict = false) const
        {
            Int key_sid = get_key(key_search),
                key_gid = get_key(key_get);
            if (key_sid == -1 || key_gid == -1)
                return multitype("bad_access");
            plist *head = rows;
            while (head->next != nullptr)
            {
                if (strict ? head->next->value.at(key_sid).strict_equal(e) : head->next->value.at(key_sid).equal(e))
                    return head->next->value.at(key_gid);
                head = head->next;
            }
            return multitype("bad_access");
        }

        // delete the first found row where the value of the column named 'key_search' is 'e'.
        // this function uses equal() to compare the values.
        // this function returns TRUE if a row is found and deleted.
        bool rm_row_where (const multitype& key_search, const multitype& e, bool strict = false)
        {
            Int key_sid = get_key(key_search);
            if (key_sid == -1)
                return false;
            plist *head = rows;
            while (head->next != nullptr)
            {
                if (strict ? head->next->value.at(key_sid).strict_equal(e) : head->next->value.at(key_sid).equal(e))
                {
                    plist *next = head->next->next;
                    delete[] head->next;
                    head->next = next;
                    --_num_rows;
                    return true;
                }
                head = head->next;
            }
            return false;
        }

        // create a new table out of the current one using a filter function.
        // the filter function must take 2 parameters:       [multitype] column_name,
        //                                             [list<multitype>] current_row,
        //                                                       [table] this_table.
        // the filter function is called on every cell. if true is returned,
        // the cell will exist in the new table.
        table filter (bool(*_filter_func)(multitype, list<multitype>, table)) const
        {
            int Nkeys = get_keys().size(),
                Nrows = num_rows();
            bool markRow[Nrows], markCol[Nkeys];
            memset(markRow, 0, sizeof markRow);
            memset(markCol, 0, sizeof markCol);
            for (int i = 0; i < Nrows; ++i)
                for (int j = 0; j < Nkeys; ++j)
                    if (_filter_func(get_keys().at(j), get_row(i), (*this)))
                        markRow[i] = markCol[j] = true;
            table new_table;
            for (int i = 0; i < Nkeys; ++i)
                if (markCol[i])
                    new_table.add_key(get_keys().at(i));
            for (int i = 0; i < Nrows; ++i)
                if (markRow[i])
                {
                    new_table.add_row();
                    for (int j = 0; j < Nkeys; ++j)
                        new_table.get(new_table.num_rows() - 1, get_keys().at(j)) = get_row(i).at(j);
                }
            return new_table;
        }
    };

    // a csv file reader/writer. ONLY INITIALIZE THIS ONCE in the project and
    // use the function get_table() to get the table instance to work on.
    class csv_handler
    {
    private:
        table _table;
        Pchar filename;
        FILE *fptr;

        list<Char> csv_str;
        bool formal_blank_line_flag = false;
        Char csv_read_char()
        {
            if (fptr == nullptr || feof(fptr))
                return '\0';
            Int ch = fgetc(fptr);
            if (ch == EOF)
            {
                if (!formal_blank_line_flag)
                    return '\n';
                formal_blank_line_flag = true;
                return '\0';
            }
            if (ch >= 32 && ch <= 126)
                csv_str.push_back((Char)ch);
            return ch;
        }
        Char csv_break_line()
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
        Pchar csv_export_pchar()
        {
            Pchar ret = new Char[csv_str.size() + 1];
            Int i = 0;
            for (; !csv_str.empty(); ++i)
                ret[i] = csv_str.pop_front();
            ret[i] = '\0';
            return ret;
        }

    public:
        // constructor. this class must be initialized with a string '_filename',
        // the name of the csv file.
        csv_handler (const Pchar _filename)
        {
            _table = table();
            string_copy(_filename, filename);
            fptr = nullptr;
        }

        // open the csv file for importing. the function returns TRUE on success,
        // and vice versa.
        bool init_read()
        {
            formal_blank_line_flag = false;
            return (fptr = fopen(filename, "r")) != nullptr;
        }

        // open the csv file for exporting. the function returns TRUE on success,
        // and vice versa.
        bool init_write()
        {
            return (fptr = fopen(filename, "w")) != nullptr;
        }

        // import the csv file into the table. default delimiter of csv is comma (,)
        // but you can provide another at your disposal.
        // this function terminates the FILE STREAM on completion.
        void read_and_terminate (const Char delim = ',')
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

        // export the table to the csv file. default delimiter of csv is comma (,)
        // but you can provide another at your disposal.
        // this function terminates the FILE STREAM on completion.
        void write_and_terminate (const Char delim = ',')
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

        // terminate the FILE STREAM.
        void terminate()
        {
            fclose(fptr);
        }

        // get the table.
        table& get_table()
        {
            return _table;
        }
        table get_table() const
        {
            return _table;
        }
    };
};

#endif // CSV_QUYENJD_H
