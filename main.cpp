#include<iostream>
#include<assert.h>
#include<algorithm>>
using namespace std;

const int max_book =10;
const int max_user =10;

struct book
{
    int id ;
    string name ;
    int total_quantity ;
    int total_borrow;

    book()
    {
        name="";
        id=-1;
        total_borrow=total_quantity=0 ;
    }
    void read()
    {
        cout <<"Enter info book & id & name & total_quantity \n";
        cin>>id >>name>>total_quantity ;
        total_borrow=0;
    }

    bool borrow(int user_id )
    {
        if (total_borrow-total_quantity==0)
            return false ;

        total_borrow++;
        return true;

    }

    void back_copy ()
    {
        assert(total_borrow>0);
        total_borrow--;
    }
    bool has_prefix(string prefix)
    {
        if (name.size()<prefix.size())
            return false ;

        for (int i =0 ; i<(int)prefix.size() ; i++)
        {
            if (prefix[i]!=name[i])
                return false;
        }
        return true ;
    }
    void prient()
    {
        cout <<"id = "<<id<<" name "<<name<<" total_quantity "<<total_quantity<<
             " total borrow "<<total_borrow<<"\n";

    }
};

bool compare_by_name(book &a,book &b)
{
    return a.name<b.name;
}
bool compare_by_id(book &a,book &b)
{
    return a.id<b.id;
}
struct user
{
    int id ;
    string name ;
    int borrow_book_id[max_book];
    int len;

    user()
    {

        id =-1;
        name="";
        len =0;

    }
    void read()
    {
        cout <<"enter user name & national id : \n";
        cin>>name>>id;
    }
    void borrow (int book_id)
    {
        borrow_book_id[len++]=book_id;
    }
    void return_copy(int book_id)
    {
        bool removed = false ;

        for (int i=0 ; i<len ; i++)
        {
            if (borrow_book_id[i]==book_id)
            {
                for (int j =i+1; j<len ; j++)
                {
                    //shift to remove
                    borrow_book_id[j-1]=borrow_book_id[j];
                    removed=true ;
                }
            }
        }
        if (!removed)
            cout << "User " << name << " never borrowed book id " << book_id
                 << "\n";
    }
    bool is_borrowed(int book_id)
    {
        for (int i = 0; i < len; ++i)
        {
            if (book_id == borrow_book_id[i])
                return true;
        }
        return false;
    }

    void print()
    {
        // sort what he borrowed
        sort(borrow_book_id, borrow_book_id + len);

        cout << "user " << name << " id " << id << " borrowed books ids: ";
        for (int i = 0; i < len; ++i)
            cout << borrow_book_id[i] << " ";
        cout << "\n";
    }

};
struct library_system
{
    int total_book;
    book books[max_book];
    int total_user;
    user users[max_user];


    library_system()
    {
        total_book=total_user=0;
    }
    void run()
    {
        while (true)
        {
            int choice =menu();
            if (choice == 1)
                add_book();
            else if (choice == 2)
                search_books_by_prefix();
            else if (choice == 3)
                print_who_borrowed_book_by_name();
            else if (choice == 4)
                print_library_by_id();
            else if (choice == 5)
                print_library_by_name();
            else if (choice == 6)
                add_user();
            else if (choice == 7)
                user_borrow_book();
            else if (choice == 8)
                user_return_book();
            else if (choice == 9)
                print_users();
            else
                break ;
        }

    }
    int menu()
    {
        int choice = -1;
        while (choice == -1)
        {
            cout << "\nLibrary Menu;\n";
            cout << "1) add_book\n";
            cout << "2) search_books_by_prefix\n";
            cout << "3) print_who_borrowed_book_by_name\n";
            cout << "4) print_library_by_id\n";
            cout << "5) print_library_by_name\n";
            cout << "6) add_user\n";
            cout << "7) user_borrow_book\n";
            cout << "8) user_return_book\n";
            cout << "9) print_users\n";
            cout << "10) Exit\n";


            cout << "\nEnter your menu choice [1 - 10]: ";
            cin >> choice;

            if (!(1 <= choice && choice <= 10))
            {
                cout << "Invalid choice. Try again\n";
                choice = -1;	// loop keep working
            }
        }
        return choice;
    }

    void add_book()
    {
        books[total_book++].read();
    }
    int find_book_idx_by_name(string name)
    {

        for (int i=0 ; i<total_book ; i++)
        {
            if (name == books[i].name)
                return i ;
        }
        return -1;
    }
    int find_user_idx_by_name(string name)
    {

        for (int i=0 ; i<total_user ; i++)
        {
            if (name == users[i].name)
                return i ;
        }
        return -1;
    }
    bool read_user_name_and_book_name(int &user_idx, int &book_idx, int trials =
                                          3)
    {

        string user_name;
        string book_name;
        while (trials--)
        {
            cout << "Enter user name and book name: ";
            cin>>user_name >>book_name;

            user_idx=find_user_idx_by_name(user_name);

            if (user_idx == -1)
            {
                cout << "Invalid user name. Try again\n";
                continue;
            }
            book_idx=find_book_idx_by_name(book_name);

            if (book_idx == -1)
            {
                cout << "Invalid book name. Try again\n";
                continue;
            }
            return true ;

        }
        cout << "You did several trials! Try later.";
        return false;
    }
    void search_books_by_prefix()
    {
        cout << "Enter book name prefix: ";
        string prefix;
        cin >> prefix;

        int cnt = 0;
        for (int i = 0; i < total_book; ++i)
        {
            if (books[i].has_prefix(prefix))
            {
                cout << books[i].name << "\n";
                ++cnt;
            }
        }

        if(!cnt)
            cout<<"No books with such prefix\n";
    }

    void print_who_borrowed_book_by_name ()
    {

        string name;
        cout <<"Enter book name \n";
        cin >>name ;

        int book_idx=find_book_idx_by_name(name);

        if (book_idx == -1)
        {
            cout << "Invalid book name.\n";
            return;
        }
        int book_id = books[book_idx].id;

        if (books[book_idx].total_borrow == 0)
        {
            cout << "No borrowed copies\n";
            return;
        }
        for (int i =0 ; i<total_book ; i++)
        {
            if (users[i].is_borrowed(book_id))
                cout << users[i].name << "\n";

        }

    }

    void print_library_by_id()
    {
        sort (books,books+total_book, compare_by_id );

        cout <<"***********************************\n";
        for (int i= 0 ; i<total_book ; i++)
            books[i].prient();

    }
    void print_library_by_name()
    {

        sort (books,books+total_book, compare_by_name );

        cout <<"***********************************\n";
        for (int i= 0 ; i<total_book ; i++)
            books[i].prient();
    }
    void add_user ()
    {
        users[total_user++].read();
    }
    void user_borrow_book()
    {
        int user_idx, book_idx;

        if (!read_user_name_and_book_name(user_idx, book_idx))
            return;

        int user_id = users[user_idx].id;
        int book_id = books[book_idx].id;

        if (!books[book_idx].borrow(user_id))
            cout << "No more copies available right now\n";
        else
            users[user_idx].borrow(book_id);
    }

    void user_return_book()
    {
        int user_idx, book_idx;

        if (!read_user_name_and_book_name(user_idx, book_idx))
            return;

        int book_id = books[book_idx].id;
        books[book_idx].back_copy();
        users[user_idx].return_copy(book_id);
    }
    void print_users()
    {
        cout << "\n";
        for (int i = 0; i < total_user; ++i)
            users[i].print();
    }

};
int main()
{
    library_system library ;
    library.run();

    return 0;
}
