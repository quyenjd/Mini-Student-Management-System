#ifndef CSV_QUYENJD_H
#define CSV_QUYENJD_H

#include <cstdio>

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
    void string_copy (const Pchar from, Pchar& to);

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
        char* _type;

    public:
        // constructors
        multitype();
        multitype (const Int e);
        multitype (const Long e);
        multitype (const Char e);
        multitype (const Pchar e);
        multitype (const Double e);
        multitype (const multitype& e);

        // set multitype back to default value.
        void init();

        // assign functions
        void assign (const Int e);
        void assign (const Long e);
        void assign (const Char e);
        void assign (const Pchar e);
        void assign (const Double e);
        void assign (const multitype& e);
        multitype& operator= (const Int e);
        multitype& operator= (const Long e);
        multitype& operator= (const Char e);
        multitype& operator= (const Pchar e);
        multitype& operator= (const Double e);
        multitype& operator= (const multitype& e);

        // get type of current value. returns "int", "long", "char", "str", "double"
        // or "unknown" (default).
        char* type() const;

        // check if current value has the type of e. this equals to 'type() == e'.
        bool is_type (const Pchar e) const;

        // check if the value has not been set so far. this equals to 'type() == "unknown"'
        // and 'is_type("unknown")'
        bool is_unknown() const;

        // convert current value (of any type) to int.
        Int to_int() const;

        // convert current value (of any type) to long long.
        Long to_long() const;

        // convert current value (of any type) to char.
        Char to_char() const;

        // convert current value (of any type) to string.
        Pchar to_str() const;

        // convert current value (of any type) to double.
        Double to_double() const;

        // compare two multitypes. this function first converts the values into the
        // same logical type before making the comparison.
        bool equal (const multitype& e) const;

        // same as equal but this function does not convert any value. thus, if the
        // values differ in type, it returns FALSE.
        bool strict_equal (const multitype& e) const;
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
        void destroy_util (iter *root);

    public:
        // constructors. if 'num_elms' is given, this function reserves a number of
        // elements after initialization.
        list (Int num_elms = 0);

        // push an element with value 'e' to the back of the list.
        void push_back (const T& e);

        // push an element with value 'e' to the front of the list.
        void push_front (const T& e);

        // pop an element from the back of the list and return it.
        T pop_back();

        // pop an element from the front of the list and return it.
        T pop_front();

        // insert an element with value 'e' at the position 'pos'.
        void insert (Int pos, const T& e);

        // destroy the list, i.e. delete all elements.
        void destroy();

        // check if the list is empty.
        bool empty() const;

        // get the size of the list.
        Int size() const;

        // get the value at the position 'pos'.
        T& at (Int pos);
        T  at (Int pos) const;

        // remove the element at the position 'pos' from the list.
        void delete_at (Int pos);
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
        table();

        // add new column with name 'e' to the table.
        void add_key (const multitype& e);

        // entirely remove a column with name 'e' from the table.
        void rm_key (const multitype& e);

        // check if the table has a column named 'e'.
        bool has_key (const multitype& e) const;

        // get the ordinary number of the column named 'e' (starting from 0).
        Int get_key (const multitype& e) const;

        // get the name list of all table columns.
        list<multitype> get_keys() const;

        // add a row to the table
        void add_row();

        // remove the 'row'-th row from the table (starting from 0).
        void rm_row (Int row);

        // get the number of rows in the table, not including the table head,
        // i.e. the row containing the column names.
        Int num_rows() const;

        // get the 'row'-th row.
        list<multitype>& get_row (Int row);
        list<multitype>  get_row (Int row) const;

        // get the row where the column named 'key_search' has the value of 'e'.
        // this function uses equal() to compare the values.
        // if there are multiple rows satisfying the condition, only the first valid
        // one is returned.
        list<multitype>& get_row_where (const multitype& key_search, const multitype& e);
        list<multitype>  get_row_where (const multitype& key_search, const multitype& e) const;

        // get the value of the column named 'key' on the 'row'-th row.
        multitype& get (Int row, const multitype& key);
        multitype  get (Int row, const multitype& key) const;

        // get the value of the column named 'key_get' on the row where there is
        // a column named 'key_search' that has the value of 'e'.
        // this function uses equal() to compare the values.
        // if there are multiple rows satisfying the condition, only the first valid
        // one is returned.
        multitype& get_where (const multitype& key_search, const multitype& e, const multitype& key_get);
        multitype  get_where (const multitype& key_search, const multitype& e, const multitype& key_get) const;
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
        Char csv_read_char();
        Char csv_break_line();
        Pchar csv_export_pchar();

    public:
        // constructor. this class must be initialized with a string '_filename',
        // the name of the csv file.
        csv_handler (const Pchar _filename);

        // open the csv file for importing. the function returns TRUE on success,
        // and vice versa.
        bool init_read();

        // open the csv file for exporting. the function returns TRUE on success,
        // and vice versa.
        bool init_write();

        // import the csv file into the table. default delimiter of csv is comma (,)
        // but you can provide another at your disposal.
        // this function terminates the FILE STREAM on completion.
        void read_and_terminate (const Char delim = ',');

        // export the table to the csv file. default delimiter of csv is comma (,)
        // but you can provide another at your disposal.
        // this function terminates the FILE STREAM on completion.
        void write_and_terminate (const Char delim = ',');

        // terminate the FILE STREAM.
        void terminate();

        // get the table.
        table& get_table();
        table  get_table() const;
    };
};

#include "csv_impl.h"

#endif // CSV_QUYENJD_H
