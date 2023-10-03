#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating)
{
    m_id = id;
    m_title = title;
    m_release_year = release_year;
    for(vector<string>::const_iterator p = directors.begin();p != directors.end();p++) // loop through directors and fill up m_directors with its movies
    {
        m_directors.push_back(*p);
    }
    for(vector<string>::const_iterator p = actors.begin();p != actors.end();p++) // loop through actors and fill up m_actors with its movies
    {
        m_actors.push_back(*p);
    }
    for(vector<string>::const_iterator p = genres.begin();p != genres.end();p++) // loop through genres and fill up m_genres with its movies
    {
        m_genres.push_back(*p);
    }
    m_rating = rating;
}

string Movie::get_id() const
{
    return m_id;
}

string Movie::get_title() const
{
    return m_title;
}

string Movie::get_release_year() const
{
    return m_release_year;
}

float Movie::get_rating() const
{
    return m_rating;
}

vector<string> Movie::get_directors() const
{
    return m_directors;
}

vector<string> Movie::get_actors() const
{
    return m_actors;
}

vector<string> Movie::get_genres() const
{
    return m_genres;  
}
