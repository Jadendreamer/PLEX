/**************
* File Name: database.h
* Author: G. J. Krafsig
* Date: June 28, 2007
* Purpose: header file for database implementation
**************/
#ifndef DATABASE_H
#define DATABASE_H

#include <allegro.h>
#include <winalleg.h>
#include "mysql/mysql.h"

/**************
* Database Error Definitions
**************/
#define SUCCESS 200
#define ERR201 201
#define ERR202 202
#define ERR203 203
#define MAX_QUERY_LEN 500

class database
{
	public:
        //class constructor
		database(); 
		
		//connection & disconnect
		int       openConnection(char *host, char *db, char *user, char *pass); //connect to the database
		bool      disconnect(); //disconnect from the database
		
		//querying
		MYSQL_RES *query(char *query); //return result set
		char      *stringQuery(char *query); //return string
		int       intQuery(char *query); //return an integer
		bool      boolQuery(char *query); //return a boolean
		bool      updateQuery(char *query); //updates, returns true if update went through
		
		//free the query results
        bool free();
		
	private:
        MYSQL *sock;
        MYSQL_RES *result;
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        char *qbuf[MAX_QUERY_LEN];
};

char *dberror(int errorcode); //return a string for this error message

#endif
