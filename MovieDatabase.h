#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    bool m_called_before; // false if the load function has not been called for this mdb object before
    TreeMultimap<std::string, Movie> m_t_movie_ID; // maps ID to movie
    TreeMultimap<std::string, Movie> m_t_director; // maps director to movies
    TreeMultimap<std::string, Movie> m_t_actor; // maps actor to movies
    TreeMultimap<std::string, Movie> m_t_genre; // maps genre to movies
};

#endif // MOVIEDATABASE_INCLUDED
