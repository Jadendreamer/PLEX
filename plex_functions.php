<?php
/*******************
* File Name: plex_functions.php
* Author: G. J. Krafsig
* Date: October 16, 2007
* Purpose: populate the plex database with random blocks
*		   for the online board
*******************/

/*******************
*          !!! IMPORTANT !!!
*
* DO NOT USE A ROOT LOGIN TO CONNECT
* TO AN ONLINE DATABASE. THIS IS FOR A 
* CONNECTION TO AN OFFLINE DATABASE FOR
* TESTING PURPOSES ONLY!
*******************/
mysql_connect("localhost", "root", "") or die ('Database connection error: ' . mysql_error());

//use the database for this game for the queries below
mysql_select_db("plex"); 

//call the function to fill the database table
//populate();

for ($i = 0; $i < 100; $i++)
	for ($j = 0; $j < 100; $j++)
		mysql_query("INSERT INTO board (x, y, depth, type) VALUES ('$i', '$j', '4', '-1')")
		or die ('cannot insert board blocks');

/*******************
* Purpose: Loop for all the depths, EXCEPT THE TOP ONE,
*		   to fill the board with blocks
* Precondition: database connection is open, database named plex exists, table named board exists
*
* SQL for board table:
* 		CREATE TABLE `board` (
*			`id` int(11) NOT NULL auto_increment,
*			`x` int(11) NOT NULL,
*			`y` int(11) NOT NULL,
*			`depth` int(11) NOT NULL,
*			`type` int(11) NOT NULL,
*			`locked` tinyint(1) NOT NULL,
*			UNIQUE KEY `id` (`id`)
*		) ENGINE=MyISAM AUTO_INCREMENT=0;
*
* Postcondition: online board table is now fully populated with values
*******************/
function populate()
{
	for ($depth = 0; $depth <= 3; $depth++)
		for ($i = 0; $i <= 100; $i++)
			for ($j = 0; $j <= 100; $j++)
			{
			
				//blocks at depth 0 should all be the same kind originally
				if ($depth == 0)
				{
					$block = 1;
					mysql_query("INSERT INTO board (x, y, type, depth) VALUES ('$i', '$j', '$block', '$depth')")
					or die ('cannot insert a block here');
				}
				//for all other depths
				else 
				{
				
					//generate a random block
					$block = rand(0, 9); 
					
					//no tall block below this one taking up two spaces on the board, add a block here
					if (!getTallBlock($i, $j, $depth-1)) 
						mysql_query("INSERT INTO board (x, y, type, depth) VALUES ('$i', '$j', '$block', '$depth')")
						or die ('cannot insert a block here');
					
					else //there is a tall block in this spot, put a NOBLOCK value there (-1)
						mysql_query("INSERT INTO board (x, y, type, depth) VALUES ('$i', '$j', '-1', '$depth')")
						or die ('cannot insert a block here');
				} //end else
			} //end for loop
} //end function populate
	
/*******************
* Purpose: check to see if the block at this location and depth
*		   is tall and takes up two spaces on the board
* Precondition: the x and y position, and the depth of the block
* Postcondition: return true if the block here is tall and takes up 2 depth spaces
*******************/
function getTallBlock($x, $y, $depth)
{
	//get the type of block from the database
	$result = mysql_query("SELECT type FROM board WHERE x='$x' AND y='$y' AND depth='$depth'")
			  or die ("cannot select block in this place");
	
	//store the results
	$row = mysql_fetch_array($result);
	
	//if this is a tall block, return true, otherwise return false
	switch ($row['type'])
	{
		case 5: case 7: return 1; break;
		default: return 0; break;
	}
}
?>