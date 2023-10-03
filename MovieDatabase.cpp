#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

MovieDatabase::MovieDatabase()
{
    m_called_before = false; // starts out with load not having been called yet
}

bool MovieDatabase::load(const string& filename)
{
    if(m_called_before == true) // return false if load has been called before for this mdb
        return false;
//    string s = "/Users/willsteinberg/Downloads/Pnetphlix/"; // set up path name for users.txt
//    s += filename; // s is now a path name for the file
    ifstream infile(filename); // make an ifstream object so we can read from the file
    if(!infile)
    {
        cerr << "not loaded" << endl;
        return false;
    }
    if(infile)
    {
        cerr << "working" << endl;
    }
    string x; // each line of the data file
    string id; // each movie's id
    string name; // each movie's name
    string release_year; // each movie's release date
    vector<string> directors; // each movie's directors
    vector<string> actors; // each movie's actors
    vector<string> genres; // each movie's genre(s)
    float rating = 0;; // each movie's rating
    int line_count = 1; // current line
    while (getline(infile, x)) // process each line of the data file
    {
//        cerr << x << endl;
        if(line_count%8 == 1)
        {
            id = x;
            line_count++;
            continue;
        }
        if(line_count%8 == 2)
        {
            name  = x;
            line_count++;
            continue;
        }
        if(line_count%8 == 3)
        {
            release_year = x;
            line_count++;
            continue;
        }
        if(line_count%8 == 4)  // parse through director string and add directors to director vector
        {
//            cerr << "here" << endl;
            int counter = 0;
            int k = 0;
            while(k < x.size()) // each iteration through while loop adds a director to director list
            {
                string curr_director = "";
                for(;x[k] != ',';k++) // loop through segment of director string until comma
                {
                    if(k == x.size()) // if this is the last director in the string
                        break;
                    curr_director += x[k]; // create the curr director string
                }
//                cerr << curr_director << endl;
                directors.push_back(curr_director);
                k++;
                counter += k;
            }
            line_count++;
            continue;
        }
        if(line_count%8 == 5) // create actors vector for this movie
        {
            int counter = 0;
            int k = 0;
            while(k < x.size()) // each iteration through while loop adds a director to director list
            {
                string curr_actor = "";
                for(;x[k] != ',';k++) // loop through segment of director string until comma
                {
                    if(k == x.size()) // if this is the last director in the string
                        break;
                    curr_actor += x[k]; // create the curr director string
                }
                actors.push_back(curr_actor);
                k++;
                counter += k;
            }
            line_count++;
            continue;
        }
        if(line_count%8 == 6)
        {
            int counter = 0;
            int k = 0;
            while(k < x.size()) // each iteration through while loop adds a director to director list
            {
                string curr_genre = "";
                for(;x[k] != ',';k++) // loop through segment of director string until comma
                {
                    if(k == x.size()) // if this is the last director in the string
                        break;
                    curr_genre += x[k]; // create the curr director string
                }
                genres.push_back(curr_genre);
                k++;
                counter += k;
            }
            line_count++;
            continue;
        }
        if(line_count%8 == 7)
        {
            rating = atof(x.c_str());
            line_count++;
            continue;
        }
        if(line_count%8 == 0)  // create the movie, add it to its respected tree multi map and reset linecount
        {
            Movie m(id,name,release_year,directors,actors,genres, rating); // make the movie from the last 7 lines
            m_t_movie_ID.insert(id, m); // insert this movie into the ID as key multimap
            
            for(vector<string>::iterator p = directors.begin();p != directors.end();p++) // loop through directors
            {
                for(int k = 0;k != (*p).size();k++) // make every director lowercase
                {
                    (*p)[k] = tolower((*p)[k]);
                }
                m_t_director.insert(*p, m); // insert each director as a different key linked to this same movie
            }
            for(vector<string>::iterator p = actors.begin();p != actors.end();p++) // loop through actors
            {
                for(int k = 0;k != (*p).size();k++) // make every director lowercase
                {
                    (*p)[k] = tolower((*p)[k]);
                }
                m_t_actor.insert(*p, m); // insert each actor as a different key linked to this same movie
            }
            for(vector<string>::iterator p = genres.begin();p != genres.end();p++) // loop through genres
            {
                for(int k = 0;k != (*p).size();k++) // make every director lowercase
                {
                    (*p)[k] = tolower((*p)[k]);
                }
                m_t_genre.insert(*p, m); // insert each genre as a different key linked to this same movie
            }
            
            // clear the vectors
            for(vector<string>::iterator p = directors.begin();p != directors.end();p++) // loop through watch history
            {
                p = directors.erase(p); // erase everything in watch history
                p--; // decrement p to account for the erase incrementation
            }
            for(vector<string>::iterator p = actors.begin();p != actors.end();p++) // loop through watch history
            {
                p = actors.erase(p); // erase everything in watch history
                p--; // decrement p to account for the erase incrementation
            }
            for(vector<string>::iterator p = genres.begin();p != genres.end();p++) // loop through watch history
            {
                p = genres.erase(p); // erase everything in watch history
                p--; // decrement p to account for the erase incrementation
            }
            line_count = 1;
            continue;
        }
    }
    // make the last movie
    Movie m(id,name,release_year,directors,actors,genres, rating); // make the movie from the last 7 lines
    m_t_movie_ID.insert(id, m); // insert this movie into the ID as key multimap
    for(vector<string>::iterator p = directors.begin();p != directors.end();p++) // loop through directors
    {
        for(int k = 0;k != (*p).size();k++) // make every director lowercase
        {
            (*p)[k] = tolower((*p)[k]);
        }
        m_t_director.insert(*p, m); // insert each director as a different key linked to this same movie
    }
    for(vector<string>::iterator p = actors.begin();p != actors.end();p++) // loop through actors
    {
        for(int k = 0;k != (*p).size();k++) // make every director lowercase
        {
            (*p)[k] = tolower((*p)[k]);
        }
        m_t_actor.insert(*p, m); // insert each actor as a different key linked to this same movie
    }
    for(vector<string>::iterator p = genres.begin();p != genres.end();p++) // loop through genres
    {
        for(int k = 0;k != (*p).size();k++) // make every director lowercase
        {
            (*p)[k] = tolower((*p)[k]);
        }
        m_t_genre.insert(*p, m); // insert each genre as a different key linked to this same movie
    }
    
    // clear the vectors
    for(vector<string>::iterator p = directors.begin();p != directors.end();p++) // loop through watch history
    {
        p = directors.erase(p); // erase everything in watch history
        p--; // decrement p to account for the erase incrementation
    }
    for(vector<string>::iterator p = actors.begin();p != actors.end();p++) // loop through watch history
    {
        p = actors.erase(p); // erase everything in watch history
        p--; // decrement p to account for the erase incrementation
    }
    for(vector<string>::iterator p = genres.begin();p != genres.end();p++) // loop through watch history
    {
        p = genres.erase(p); // erase everything in watch history
        p--; // decrement p to account for the erase incrementation
    }

//    // ~TESTS~
//    // first ID
//    TreeMultimap<std::string,Movie>::Iterator i = m_t_movie_ID.find("ID10782");
//    assert(i.get_value().get_title() == "Santosh Subramaniam");
//    assert(i.get_value().get_release_year() == "2008");
//    assert(i.get_value().get_rating() == 5);
//    assert(i.get_value().get_directors()[0] == "M. Raja");
//    assert(i.get_value().get_actors()[0] == "Jayam Ravi");
//    assert(i.get_value().get_actors()[1] == "Genelia D'Souza");
//    assert(i.get_value().get_actors()[2] == "Prakash Raj");
//    assert(i.get_value().get_actors()[3] == "Sayaji Shinde");
//    assert(i.get_value().get_actors()[4] == "Geetha");
//    assert(i.get_value().get_genres()[0] == "Action");
//    assert(i.get_value().get_genres()[1] == "Comedy");
//    assert(i.get_value().get_genres()[2] == "Romance");
//    i.advance();
//    assert(!i.is_valid());
//
//    // random ID
//    TreeMultimap<std::string,Movie>::Iterator y = m_t_movie_ID.find("ID36770");
//    assert(y.get_value().get_title() == "The Man Without Gravity");
//    assert(y.get_value().get_release_year() == "2019");
//    assert(y.get_value().get_directors()[0] == "Marco Bonfanti");
//    assert(y.get_value().get_actors()[0] == "Elio Germano");
//    assert(y.get_value().get_actors()[1] == "Michela Cescon");
//    assert(y.get_value().get_actors()[4] == "Vincent Scarito");
//    assert(y.get_value().get_genres()[0] == "Fantasy");
//    y.advance();
//    assert(!y.is_valid());
//
//    // last ID
//    TreeMultimap<std::string,Movie>::Iterator z = m_t_movie_ID.find("ID03086");
//    assert(z.get_value().get_title() == "Jallikattu");
//    assert(z.get_value().get_release_year() == "2019");
//    assert(z.get_value().get_directors()[0] == "Lijo Jose Pellissery");
//    assert(z.get_value().get_actors()[0] == "Antony Varghese");
//    assert(z.get_value().get_actors()[2] == "Sabumon Abdusamad");
//    assert(z.get_value().get_actors()[4] == "Jaffer Idukki");
//    assert(z.get_value().get_genres()[0] == "Action");
//    assert(z.get_value().get_genres()[3] == "Thriller");
////    cerr << z.get_value().get_rating() << " test" << endl;
////    assert(z.get_value().get_rating() == 3.08333);
//    z.advance();
//    assert(!z.is_valid());
//
//    // first Director
//    TreeMultimap<std::string,Movie>::Iterator f = m_t_director.find("m. raja");
//    assert(f.get_value().get_title() == "Santosh Subramaniam");
//    assert(f.get_value().get_actors()[4] == "Geetha");
//    assert(f.get_value().get_id() == "ID10782");
//    assert(f.get_value().get_genres()[2] == "Romance");
//    assert(f.get_value().get_rating() == 5);
//    f.advance();
//    assert(f.get_value().get_title() == "Something Something... Unakkum Enakkum");
//    f.advance();
//    f.advance();
//    f.advance();
//    f.advance();
//    assert(f.get_value().get_title() == "Velaikkaran");
//    f.advance();
//    assert(!f.is_valid());
//
//    // random Director
//    f = m_t_director.find("marco bonfanti");
//    assert(f.get_value().get_title() == "The Man Without Gravity");
//    assert(f.get_value().get_actors()[4] == "Vincent Scarito");
//    assert(f.get_value().get_id() == "ID36770");
//    assert(f.get_value().get_genres()[0] == "Fantasy");
//    f.advance();
//    assert(!f.is_valid());
//
//    // last Director
//    f = m_t_director.find("lijo jose pellissery");
//    assert(f.get_value().get_title() == "Jallikattu");
//    assert(f.get_value().get_actors()[4] == "Jaffer Idukki");
//    assert(f.get_value().get_id() == "ID03086");
//    assert(f.get_value().get_genres()[3] == "Thriller");
//    f.advance();
////    assert(!f.is_valid());
//
//    // first Actor
//    TreeMultimap<std::string,Movie>::Iterator v = m_t_actor.find("jayam ravi");
//    assert(v.get_value().get_title() == "Santosh Subramaniam");
//    assert(v.get_value().get_directors()[0] == "M. Raja");
//    assert(v.get_value().get_actors()[4] == "Geetha");
//    assert(v.get_value().get_genres()[1] == "Comedy");
//    assert(v.get_value().get_rating() == 5);
//    v.advance();
//    v.advance();
//    assert(v.get_value().get_title() == "M. Kumaran S/O Mahalakshmi");
//
//    // Last Actor
//    TreeMultimap<std::string,Movie>::Iterator l = m_t_actor.find("scott bakula");
//    assert(l.get_value().get_title() == "Necessary Roughness");
//    assert(l.get_value().get_genres()[0] == "Comedy");
//    for(int k = 0;k < 13;k++)
//    {
//        l.advance();
//    }
//    assert(l.get_value().get_title() == "Lord of Illusions");
//    assert(l.get_value().get_id() == "ID05902");
//    l.advance();
//    assert(!l.is_valid());
//
//    l = m_t_actor.find("charles coburn");
//    assert(l.get_value().get_id() == "ID34690");
//    assert(l.get_value().get_title() == "Green Grass of Wyoming");
//
//    // Genre tests
//    TreeMultimap<std::string,Movie>::Iterator b = m_t_genre.find("fantasy");
//    assert(b.get_value().get_title() == "The Man Without Gravity");
//    assert(b.get_value().get_release_year() == "2019");
//    b.advance();
//    assert(b.get_value().get_title() == "Everything Is Terrible! Presents: The Great Satan");
//    assert(b.get_value().get_id() == "ID36649");
//
//    b = m_t_genre.find("romance");
//    assert(b.get_value().get_id() == "ID10782");
//    assert(b.get_value().get_title() == "Santosh Subramaniam");
    cerr << "GOT HERE" << endl;
    m_called_before = true;
    return true;
}




Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<std::string,Movie>::Iterator it = m_t_movie_ID.find(id);
    if(!it.is_valid()) // if the movie cannot be found
        return nullptr; // return nullptr
    Movie* mv = &(it.get_value()); // make a user object that points to the value the iterator points to
    return mv;  
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> mps;
    string d;
    for(int k = 0;k != director.size();k++) // copy the director string so it can be modified
    {
        d += director[k];
    }
    for(int k = 0;k != d.size();k++) // make the director lowercase
    {
        d[k] = tolower(d[k]);
    }
    TreeMultimap<std::string,Movie>::Iterator it = m_t_director.find(d); // set the iterator to the linked list of movies the director directed
    if(!it.is_valid()) // if the movie cannot be found
        return mps; // return empty vector
    while(it.is_valid()) // while the iterator is valid keep pushing back movies until there are no more movies
    {
        
        mps.push_back(&it.get_value()); // push back a pointer to each movie
        it.advance();
    }
    return mps;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> mps;
    string a;
    for(int k = 0;k != actor.size();k++) // copy the director string so it can be modified
    {
        a += actor[k];
    }
    for(int k = 0;k != a.size();k++) // make the director lowercase
    {
        a[k] = tolower(a[k]);
    }
    TreeMultimap<std::string,Movie>::Iterator it = m_t_actor.find(a); // set the iterator to the linked list of movies the director directed
    if(!it.is_valid()) // if the movie cannot be found
        return mps; // return empty vector
    while(it.is_valid()) // while the iterator is valid keep pushing back movies until there are no more movies
    {
        
        mps.push_back(&it.get_value()); // push back a pointer to each movie
        it.advance();
    }
    return mps;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> mps;
    string g;
    for(int k = 0;k != genre.size();k++) // copy the director string so it can be modified
    {
        g += genre[k];
    }
    for(int k = 0;k != g.size();k++) // make the director lowercase
    {
        g[k] = tolower(g[k]);
    }
    TreeMultimap<std::string,Movie>::Iterator it = m_t_genre.find(g); // set the iterator to the linked list of movies the director directed
    if(!it.is_valid()) // if the movie cannot be found
        return mps; // return empty vector
    while(it.is_valid()) // while the iterator is valid keep pushing back movies until there are no more movies
    {
        
        mps.push_back(&it.get_value()); // push back a pointer to each movie
        it.advance();
    }
    return mps;
}
