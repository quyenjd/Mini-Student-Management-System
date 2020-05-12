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
    void string_copy (const Pchar from, Pchar& to);

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
        multitype();
        multitype (const Int e);
        multitype (const Long e);
        multitype (const Char e);
        multitype (const Pchar e);
        multitype (const Double e);
        multitype (const multitype& e);
        void init();
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
        char* type() const;
        bool is_type (const Pchar e) const;
        bool is_unknown() const;
        Int to_int() const;
        Long to_long() const;
        Char to_char() const;
        Pchar to_str() const;
        Double to_double() const;
        bool equal (const multitype& e) const;
        bool strict_equal (const multitype& e) const;
    };

    class list
    {
    private:
        struct iter
        {
            struct iter *next;
            multitype value;
        } *head;
        Int _size;
        void destroy_util (iter *root);

    public:
        list (Int num_elms = 0);
        void push_back (const multitype& e);
        void push_front (const multitype& e);
        multitype pop_back();
        multitype pop_front();
        void insert (Int pos, const multitype& e);
        void destroy();
        bool empty() const;
        Int size() const;
        multitype& at (Int pos);
        multitype at (Int pos) const;
        void delete_at (Int pos);
    };

    class table
    {
    private:
        struct plist
        {
            struct plist *next;
            list value;
        } *rows;
        list keys;

        Int get_key (const multitype& e) const;
        Int _num_rows;

    public:
        table();
        void add_key (const multitype& e);
        void rm_key (const multitype& e);
        bool has_key (const multitype& e) const;
        list get_keys() const;
        void add_row();
        void rm_row (Int row);
        Int num_rows() const;
        list& get_row (Int row);
        list get_row (Int row) const;
        list& get_row_where (const multitype& key_search, const multitype& e);
        list get_row_where (const multitype& key_search, const multitype& e) const;
        multitype& get (Int row, const multitype& key);
        multitype get (Int row, const multitype& key) const;
        multitype& get_where (const multitype& key_search, const multitype& e, const multitype& key_get);
        multitype get_where (const multitype& key_search, const multitype& e, const multitype& key_get) const;
    };

    class csv_handler
    {
    private:
        table _table;
        Pchar filename;
        FILE *fptr;

        list csv_str;
        Char csv_read_char();
        Char csv_break_line();
        Pchar csv_export_pchar();

    public:
        csv_handler (const Pchar _filename);
        bool init_read();
        bool init_write();
        void read_and_terminate (const Char delim = ',');
        void write_and_terminate (const Char delim = ',');
        void terminate();
        table& get_table();
        table get_table() const;
    };
};

#endif // CSV_QUYENJD_H
