/**************
* File Name: database.cpp
* Author: G. J. Krafsig
* Date: June 28, 2007
* Purpose: implementation of the game database
**************/
#include "database.h"

/**************
* Purpose: default constructor, initialize class values
* Precondition: none
* Postcondition: none
**************/
database::database()
{
    //initilize the mysql fields
    sock = NULL;
    row = NULL;
    result = NULL;
    field = NULL;          
}

/**************
* Purpose: connect to the appropriate database
* Precondition: host, database, user name and password
* Postcondition: connected to that database
**************/
int database::openconnection(char *host, char *db, char *user, char *pass)
{
    if (sock) //already connected to another database
        disconnect(); //disconnect from that one
        
    //initilize the socket
    sock = mysql_init(0);
    
    //something went wrong with the socket
    if (!sock)
        return ERR201;
     
    //try connecting to the database  
    if (!mysql_real_connect(sock, host, user, pass, db, 0, NULL, 0))
        return ERR202;
    
    //successfully connected to the database    
    return SUCCESS;  
}

/**************
* Purpose: disconnect from the database
* Precondition: none
* Postcondition: socket closed
**************/
bool database::disconnect()
{
    if (sock) //they have a socket open
    {
        mysql_close(sock);
        return true;
    }
    
    return true; //already disconnected
}

/**************
* Purpose: free the results from the database query
* Precondition: none
* Postcondition: results no longer there
**************/
bool database::free()
{
    if (result)
    {
        mysql_free_result(result); 
        return true;
    }
    
    return true;
}

/**************
* Purpose: return the approprite error message
* Precondition: error code
* Postcondition: string with the error returned
**************/
char *dberror(int errorcode)
{
    
    //display the appropriate error message for this error    
    switch(errorcode)
    {
        case SUCCESS: return "SUCCESS";
            break;
            
        case ERR201: return "201 SOCKET ERROR: SOCKET FAILURE";
            break;
            
        case ERR202: return "202 CONNECTION ERROR: CANNOT ACCESS THE SERVER";
            break;
            
        case ERR203: return "203 DATABASE ERROR: QUERY FAILED";
            break;
    }
    
    return ""; //no error, return null char
}
