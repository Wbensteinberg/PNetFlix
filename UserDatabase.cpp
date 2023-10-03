#include "UserDatabase.h"
#include "User.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "treemm.h"
#include <cassert>
using namespace std;

UserDatabase::UserDatabase()
{
    m_called_before = false; // has not been called yet
}

bool UserDatabase::load(const string& filename)
{
    if(m_called_before == true) // if the load function has been called on this user data base before
        return false; // return false
//    string s = "/Users/willsteinberg/Downloads/Pnetphlix/"; // set up path name for users.txt
//    s += filename; // s is now a path name for the file
    ifstream infile(filename); // make an ifstream object so we can read from the file
    if(!infile)
    {
        cerr << "here" << endl;
        return false;
    }
//    TreeMultimap<std::string, User> tm; // make a tree multi map of emails that map to users
    string x; // each line of the data file
    string name; // each person's name
    string email; // each person's email
    int n = -1; // number of movies in each person's watch history
    int line_count = 1; // current line
    vector<string> watch_history; // each user's watch history
    int counter = 0; // a marker for when we have processed every movie ID for a user
    while (getline(infile, x)) // process each line of the data file
    {
//        cerr << x << endl;
        if(n != -1 && counter != n) // if n has been set for this user
        {
            watch_history.push_back(x); // add each movie to the watch history
            line_count++;
            counter++;
            continue;
        }
        else if(line_count > 3) // if this is the end of a user and we have to create them
            // also reset all the user values
        {
            User u(name,email,watch_history); // make the user
            tm.insert(email, u); // insert the user into the tree multi map with the email as its key
            n = -1;
            line_count = 1;
            counter = 0;
            for(vector<string>::iterator p = watch_history.begin();p != watch_history.end();p++) // loop through watch history
            {
                p = watch_history.erase(p); // erase everything in watch history
                p--; // decrement p to account for the erase incrementation
            }
            continue;
        }
        if(line_count == 1)
        {
            name = x;
            line_count++;
            continue;
        }
        if(line_count == 2)
        {
            email = x;
            line_count++;
            continue;
        }
        if(line_count == 3)
        {
            n = atoi(x.c_str()); // n gets set to the number of movie ID's coming up
            line_count++;
            continue;
        }
        line_count++; // increment the line after each iteration
    }
    // make the last user
    User u(name,email,watch_history); // make the user
    tm.insert(email, u); // insert the user into the tree multi map with the email as its key
    n = -1;
    line_count = 1;
    counter = 0;
    for(vector<string>::iterator p = watch_history.begin();p != watch_history.end();p++) // loop through watch history
    {
        p = watch_history.erase(p); // erase everything in watch history
        p--; // decrement p to account for the erase incrementation
    }
    
    // ~TESTS~
    // first user
//    TreeMultimap<std::string,User>::Iterator i = tm.find("AbFow2483@charter.net");
//    assert(i.get_value().get_full_name() == "Abdullah Fowler");
//    assert(i.get_value().get_watch_history()[0] == "ID22937");
//    assert(i.get_value().get_watch_history()[1] == "ID04742");
//    assert(i.get_value().get_watch_history()[i.get_value().get_watch_history().size()-1] == "ID22199");
//    i.advance();
//    assert(!i.is_valid());
//
//    // random user
//    TreeMultimap<std::string,User>::Iterator y = tm.find("KellenArno@zoho.com");
//    assert(y.get_value().get_full_name() == "Kellen Arnold");
//    assert(y.get_value().get_watch_history()[0] == "ID35311");
//    assert(y.get_value().get_watch_history()[y.get_value().get_watch_history().size()-1] == "ID11686");
//    y.advance();
//    assert(!y.is_valid());
//
//    // second to last user
//    TreeMultimap<std::string,User>::Iterator g = tm.find("JaimS@icloud.com");
//    assert(g.get_value().get_full_name() == "Jaime Swanson");
//    assert(g.get_value().get_watch_history()[0] == "ID13295");
//    assert(g.get_value().get_watch_history()[g.get_value().get_watch_history().size()-1] == "ID17774");
//    g.advance();
//    assert(!g.is_valid());
//
//    // last user
//    TreeMultimap<std::string,User>::Iterator z = tm.find("KabiL@aol.com");
//    assert(z.get_value().get_full_name() == "Kabir Luna");
//    assert(z.get_value().get_watch_history()[0] == "ID36383");
//    assert(z.get_value().get_watch_history()[z.get_value().get_watch_history().size()-1] == "ID14614");
//    z.advance();
//    assert(!z.is_valid());
//
//    // user not in data file
//    TreeMultimap<std::string,User>::Iterator f = tm.find("wbensteinberg@gmail.com");
//    assert(!f.is_valid());
    
    m_called_before = true; // set the called before flag to true for this user data base
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string,User>::Iterator it = tm.find(email);
    if(!it.is_valid()) // if the user cannot be found
        return nullptr; // return nullptr
    User* up = &(it.get_value()); // make a user object that points to the value the iterator points to
    return up;
}









