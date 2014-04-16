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
#define MAX_QUERY_LEN 255

class database
{
	public:
		database(); // class constructor
		int openconnection(char *host, char *db, char *user, char *pass); //connect to the database
		bool disconnect(); //disconnect from the database
		MYSQL_RES *query(char *query); //query the database
		bool free(); //free the query result
		
	private:
        MYSQL *sock;
        MYSQL_RES *result;
        MYSQL_ROW *row;
        MYSQL_FIELD *field;
        char *qbuf[MAX_QUERY_LEN];
};

char *dberror(int errorcode); //return a string for this error message

#endif
