#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "treemm.h"
#include <cassert>
#include <algorithm>

#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_udb = &user_database;
    m_mdb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)
{
    vector<MovieAndRank> rec_movies; // declare movie and rank vector that will be slowly added upon and eventually returned at the end of the function
    if(movie_count <= 0) // if the requested max movies to recommend is less than or equal to 0
        return rec_movies; // return an empty vector of movie recommendations
    User* u = m_udb->get_user_from_email(user_email); // u is the given user found through email
//    assert(u->get_full_name() == "Abdullah Fowler");
//    assert(u->get_email() == "AbFow2483@charter.net");
//    assert(u->get_watch_history()[0] == "ID22937");
//    assert(u->get_watch_history()[4] == "ID18156");
//    cerr << u->get_full_name() << endl;
    cerr << "running" << endl;
    for(int k = 0;k < u->get_watch_history().size();k++) // loop through the user's watch history movie ID's
    {
        cerr << "big loop" << endl;
//        cerr << u->get_watch_history()[k] << endl;
        Movie* mv = m_mdb->get_movie_from_id(u->get_watch_history()[k]); // mv points to each movie by getting it from each ID
//        cerr << mv->get_title() << endl;
        for(int i = 0;i < mv->get_directors().size();i++) // for each director in the movie
        {
            cerr << "director loop" << endl;
//            cerr << mv->get_directors()[i] << endl;
            vector<Movie*> movies_with_curr_director = m_mdb->get_movies_with_director(mv->get_directors()[i]);// create vector of all movies with this director of current movie
//            cerr << (movies_with_curr_director[i]->get_title()) << " here" << endl;
            for(int j = 0;j < movies_with_curr_director.size();j++) // loop through all the movies that have the curr director
            {
                cerr << "each movie 1" << endl;
                int marker = 0; // this is will turn to 1 if there is already an existing Movie and Rank object for this movie
                for(int f = 0;f < rec_movies.size();f++) // loop through movie and rank objects
                {
                    if(rec_movies[f].movie_id == movies_with_curr_director[j]->get_id()) // if there is already an object with the current movies ID
                    {
                        marker = 1;
                        rec_movies[f].compatibility_score += 20; // DON'T make another one, just add 20 to the current one's compatability score
                    }
                }
                if(marker == 0) // if there is no pre-existing MovieAndRank object for this movie
                {
                    MovieAndRank mar(movies_with_curr_director[j]->get_id(),20); // make a movie and rank object for it with a starting compatability of 20 because of the director
                    rec_movies.push_back(mar); // add it to the MovieAndRank vector
                }
            }
        }
        
        for(int i = 0;i < mv->get_actors().size();i++) // for each actor in the movie
        {
            cerr << "actor loop" << endl;
            vector<Movie*> movies_with_curr_actor = m_mdb->get_movies_with_actor(mv->get_actors()[i]);// create vector of all movies with this director of current movie
            for(int j = 0;j < movies_with_curr_actor.size();j++) // loop through all the movies that have the curr director
            {
                cerr << "each movie 2" << endl;
                int marker = 0; // this is will turn to 1 if there is already an existing Movie and Rank object for this movie
                for(int f = 0;f < rec_movies.size();f++) // loop through movie and rank objects
                {
                    if(rec_movies[f].movie_id == movies_with_curr_actor[j]->get_id()) // if there is already an object with the current movies ID
                    {
                        marker = 1;
                        rec_movies[f].compatibility_score += 30; // DON'T make another one, just add 20 to the current one's compatability score
                    }
                }
                if(marker == 0) // if there is no pre-existing MovieAndRank object for this movie
                {
                    MovieAndRank mar(movies_with_curr_actor[j]->get_id(),30); // make a movie and rank object for it with a starting compatability of 20 because of the director
                    rec_movies.push_back(mar); // add it to the MovieAndRank vector
                }
            }
        }
        
//        for(int i = 0;i < mv->get_genres().size();i++) // for each genre in the movie
//        {
//            cerr << "genre loop" << endl;
//            vector<Movie*> movies_with_curr_genre = m_mdb->get_movies_with_genre(mv->get_genres()[i]);// create vector of all movies with the genre of current movie
//            for(int j = 0;j < movies_with_curr_genre.size();j++) // loop through all the movies that have the curr genre
//            {
//                cerr << "each movie 3" << endl;
//                int marker = 0; // this is will turn to 1 if there is already an existing Movie and Rank object for this movie
//                for(int f = 0;f < rec_movies.size();f++) // loop through movie and rank objects
//                {
//                    if(rec_movies[f].movie_id == movies_with_curr_genre[j]->get_id()) // if there is already an object with the current movies ID
//                    {
//                        marker = 1;
//                        rec_movies[f].compatibility_score += 1; // DON'T make another one, just add 20 to the current one's compatability score
//                    }
//                }
//                if(marker == 0) // if there is no pre-existing MovieAndRank object for this movie
//                {
//                    MovieAndRank mar(movies_with_curr_genre[j]->get_id(),1); // make a movie and rank object for it with a starting compatability of 1 because of the genre
//                    rec_movies.push_back(mar); // add it to the MovieAndRank vector
//                }
//            }
//        }
    }
    // erasing repeat movies
    for(vector<MovieAndRank>::iterator p = rec_movies.begin();p != rec_movies.end();p++) // loop through all rec movies
    {
        cerr << "erasing repeat movies" << endl;
        if((*p).compatibility_score >= 1) // for each movie with a compatabilty score of at least one
        {
            for(int k = 0;k < u->get_watch_history().size();k++) // loop through the user's watch history movie ID's
            {
                if((u->get_watch_history())[k] == (*p).movie_id) // if this movie is in the user's watchlist as well as rec movies
                {
                    p = rec_movies.erase(p); // erase it from rec_movies because we don't want to recommend a movie they've already watched
                    p--; // decrement p to account for erase's incrementation
                }
            }
        }
    }
    cerr << "done first erasing" << endl;
    sort(rec_movies.begin(),rec_movies.end(),compare); // sort the movies in descending order based off compatibility score
    cerr << "sorted" << endl;
    if(movie_count < rec_movies.size()) // if there are more movies to be recommended than the number of movies requested
    {
        int num_to_subtract = rec_movies.size() - movie_count;
        cerr << "numtosubtract: " << num_to_subtract << endl;
        cerr << rec_movies.size() << endl;
        int counter = 0;
        vector<MovieAndRank>::iterator p = rec_movies.end();
        p--;
        while(num_to_subtract != 0)
        {
            p = rec_movies.erase(p);
            p--;
            num_to_subtract--;
        }
//        for(vector<MovieAndRank>::iterator p = rec_movies.end();p != rec_movies.begin();p--) // loop backwards through rec_movies and erase until the number needed to be erased is zero then break
//        {
//            cerr << "erasing extra movies" << endl;
//            counter++;
//            num_to_subtract--;
//            if(num_to_subtract == 0)
//            {
//                cerr << "THERE" << endl;
//                cerr << counter << endl;
//                break;
//            }
//            if(p == rec_movies.end())
//            {
//                p--;
//            }
//            p = rec_movies.erase(p);
//            p--;
//        }
        cerr << counter << endl;
        cerr << "done erasing" << endl;
        
    }
    return rec_movies;  // return the vector of Movie and Rank Objects
}
