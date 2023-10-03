#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED
#include <string>
#include "treemm.h"



class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    bool m_called_before; // true if load has been called before
    TreeMultimap<std::string, User> tm; // tree multimap that holds all the emails and users
};

#endif // USERDATABASE_INCLUDED
