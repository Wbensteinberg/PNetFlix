#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"
#include <string>
#include <vector>

//class UserDatabase;
//class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count);
  private:
    const UserDatabase* m_udb; // pointer to user data base
    const MovieDatabase* m_mdb; // pointer to movie data base
    static bool compare(MovieAndRank a, MovieAndRank b) // for comparing compatability scores
    {
            // Sort from greatest to least
            return a.compatibility_score > b.compatibility_score;
    }
};

#endif // RECOMMENDER_INCLUDED
